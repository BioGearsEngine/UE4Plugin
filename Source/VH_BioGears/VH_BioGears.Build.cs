using UnrealBuildTool;
using System;
using System.Linq;
using System.IO;
using System.Diagnostics;
using System.Text;
using System.Runtime.InteropServices;
using Tools.DotNETCommon;

// 
// This plugin depends on BioGears 7.3.2 http://github.com/BiogearsEngine/core
// 
// Due to legacy path limitations in old Windows Utilities. This plugin will place 
// The build intermediaries in <ROOT>/ThirdParty/build/<PLATFORM>/<CONFIGURATION>/bg
// The build artifacts are installed in <ROOT>/ThirdParty/Artifacts/<PLATFORM><CONFIGURATION>
//  
// Supported Platforms:
//		Win64
//		Android arm7va-neon
//		Android arm64-v8

public class VH_BioGears : ModuleRules
{
	// Build Configuration Information
	protected class ThirdPartyConfig
	{
		public string[] libraries;

		public string platform;
		public string project;
		public string architecture;
		public string configuration;
		public string lib_suffix;
		public string dll_suffix;
		public string pdb_suffix;
		public string exe_suffix;

		public string build_path;
		public string install_path;
		public string include_path;
		public string binary_path;
		public string library_path;
		public string native_path;

		public ThirdPartyConfig() {
			project = "external_deps";
		}
	};

	// This PATH is used to build binaries at the top most level of the source tree. The goal of this is
	// to avoid LONG_PATHS which excced the 250 character limited allowed by msbuild
	//REPO ROOT

	private string RepoRoot { get { return Path.GetFullPath(Path.Combine(EngineDirectory, "../")); } }
	private string ThirdpartyBuildDir { get { return Path.GetFullPath(Path.Combine(RepoRoot, "ThirdParty/")); } }
	private string EngineBinaryPath { get { return Path.GetFullPath(Path.Combine(EngineDirectory, "Binaries/")); } }

	//Plugin Directories
	private string ThirdpartySourceDir { get { return Path.GetFullPath(Path.Combine(PluginDirectory, "ThirdParty/")); } }
	private string PluginBinaryPath { get { return Path.GetFullPath(Path.Combine(PluginDirectory, "Binaries/")); } }

	//Game Directories - So odd to me this isn't in ModuleRules
	private string GameBinaryPath { get { return Path.GetFullPath(Path.Combine(PluginDirectory, "../../Binaries/")); } }

	private bool bVerboseLogs { get { return true; } }

	private bool bDebug { get { return Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.Development; } }

	//  Location where the CMake List is located
	private string CMakeSourcePath { get { return Path.GetFullPath(Path.Combine(PluginDirectory, "ThirdParty")); } }

	//  Location where CMAKE builds biogears (Note: Must be short path to avoid msbuild errors)
	private string CMakeBuildPath { get { return Path.GetFullPath(Path.Combine(PluginDirectory, "../../../ThirdParty/BioGears")); } }


	public VH_BioGears( ReadOnlyTargetRules target ) : base(target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		//Type = ModuleType.External;
		bEnableExceptions = true;
		bUseRTTI = (target.Platform != UnrealTargetPlatform.Android);

		PublicIncludePaths.AddRange(new string[]
		{
            // Project paths
            Path.Combine(ModuleDirectory, "Core/Public"),
			Path.Combine(ModuleDirectory, "Physiology/Public"),
			Path.Combine(ModuleDirectory, "Scenario/Public"),
			Path.Combine(ModuleDirectory, "Subsystems/Public"),
			Path.Combine(ModuleDirectory, "Utilities/Public"),
		});

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"Projects",
			"XmlParser",
		});

		PublicDefinitions.AddRange(new string[]
		{ });

		PrivateIncludePaths.AddRange(new string[] { });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		DynamicallyLoadedModuleNames.AddRange(new string[] { });

		if (!LoadBioGears()) {
			System.Console.WriteLine("Failed to build BioGgears. Stopping Build.");
			System.Environment.Exit(5);
		}
	}


	private void StagePlatformLibraries( ThirdPartyConfig config ) {
		AddLibraries(config);

		PublicIncludePaths.Add(Path.Combine(config.include_path));
		PublicIncludePaths.Add(Path.Combine(config.include_path, "biogears"));
		PublicIncludePaths.Add(Path.Combine(config.include_path, "eigen3"));
	}

	private bool LoadBioGears() {
		ConfigHierarchy engineConfig = ConfigCache.ReadHierarchy(ConfigHierarchyType.Engine, new DirectoryReference(PluginDirectory), Target.Platform);
		System.Console.WriteLine("Loading BioGears. This will build external libraries to " + ThirdpartyBuildDir);

		PublicDefinitions.Add("XERCES_INCLUDE_WCHAR_H=0");

		ThirdPartyConfig config = new ThirdPartyConfig();
		config.project = "bg-meta";

		if (Target.Platform == UnrealTargetPlatform.Win64) {
			System.Console.WriteLine("Windows platform detected assuming Visual Studio 2015");

			bool bBindingsWindows = false;
			if (engineConfig.GetBool("/Scripts/VH_BioGears/Thirdparty", "bEnableBiogearsOnWindows", out bBindingsWindows)) {
				if (!bBindingsWindows) {
					return true;
				}
			}
			PublicDefinitions.Add("WITH_BIOGEARS_BINDING=1");
			PublicDefinitions.Add("BIOGEARS_IO_PRESENT");
			PublicDefinitions.Add("BIOGEARS_IO_EMBED_STATES");

			config.platform = "Win64";
			config.architecture = "x86_64";
			config.configuration = bDebug ? "dbg" : "rel";
			config.dll_suffix = ".dll";
			config.exe_suffix = ".exe";
			config.lib_suffix = ".lib";
			config.pdb_suffix = ".pdb";
			config.libraries = new string[] { "xerces-c_3", "biogears_common", "biogears_io", "biogears_cdm", "biogears" };

			if (!BuildModel(config)) {
				System.Console.WriteLine("		Failed To Build Model");
				return false;
			}
			StagePlatformLibraries(config);
			return true;
		} else if (Target.Platform == UnrealTargetPlatform.Android) {
			var bBuildForArmV7 = true;
			var bBuildForArm64 = true;
			var bBuildForX8664 = false;
			var bBuildForX86 = false;

			bool bBindingsAndroid = false;
			if (engineConfig.GetBool("/Scripts/VH_BioGears/Thirdparty", "bEnableBiogearsOnAndroid", out bBindingsAndroid)) {
				if (!bBindingsAndroid) {
					return true;
				}
				PublicDefinitions.Add("WITH_BIOGEARS_BINDING=1");
				PublicDefinitions.Add("BIOGEARS_IO_PRESENT");
				PublicDefinitions.Add("BIOGEARS_IO_EMBED_STATES");

			} else {
				//Android UE4 Integration is currently broken so if the INI file does not contain a
				//Explicit request to buildt these bindings we will abort and build the plugin with out
				//BioGear
				return true;
			}

			//Reading from  BaseGame.ini, DefaultGame.ini, etc... in the game folder. Look for the section
			// Target.ProjectFile.Directory contains the correct values for the AndroidRuntimeSettings. The config files in the plugin directlty
			// Were used to get the custom VH_BioGears INI. 
			ConfigHierarchy targetConfig = ConfigCache.ReadHierarchy(ConfigHierarchyType.Engine, Target.ProjectFile.Directory, Target.Platform);

			targetConfig.GetBool("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings", "bBuildForArmV7", out bBuildForArmV7);
			targetConfig.GetBool("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings", "bBuildForArm64", out bBuildForArm64);
			targetConfig.GetBool("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings", "bBuildForX8664", out bBuildForX8664);
			targetConfig.GetBool("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings", "bBuildForX86", out bBuildForX86);

			System.Console.WriteLine("Engine contains bBuildForArmV7 {0}", targetConfig.GetBool("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings", "bBuildForArmV7", out bBuildForArmV7));
			System.Console.WriteLine("Engine contains bBuildForArm64 {0}", targetConfig.GetBool("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings", "bBuildForArm64", out bBuildForArm64));
			System.Console.WriteLine("Engine contains bBuildForX8664 {0}", targetConfig.GetBool("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings", "bBuildForX8664", out bBuildForX8664));
			System.Console.WriteLine("Engine contains bBuildForX86 {0}", targetConfig.GetBool("/Script/AndroidRuntimeSettings.AndroidRuntimeSettings", "bBuildForX86", out bBuildForX86));

			System.Console.WriteLine("bBuildForArmV7={0} bBuildForArm64={1} bBuildForX8664={2} bBuildForX86={3}", bBuildForArmV7, bBuildForArm64, bBuildForX8664, bBuildForX86);

			System.Console.WriteLine("\n\nConfig Cache");

			config.platform = "Android";
			config.configuration = bDebug ? "dbg" : "rel";
			config.lib_suffix = ".so";
			config.libraries = new string[] { "libicuuc", "libicudata", "libxerces-c-3.2", "libbiogears_common", "libbiogears_io", "libbiogears_cdm", "libbiogears" };

			PublicDefinitions.Add("EIGEN_HAS_CXX11_MATH=0");
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "VH_Biogears_APL.xml"));
			if (bBuildForArmV7) {
				// Build for Armeabi-v7a
				Console.WriteLine("Building third party dependencies for VH_Biogears for armeabi-v7a");
				config.architecture = "armeabi-v7a";
				if (!BuildModel(config)) {
					return false;
				}
				StagePlatformLibraries(config);
			}

			if (bBuildForArm64) {
				// Build for Arm64-v8a
				Console.WriteLine("Building third party dependencies for VH_Biogears for arm64-v8a");
				config.architecture = "arm64-v8a";
				if (!BuildModel(config)) {
					return false;
				}
				StagePlatformLibraries(config);
			}

			if (bBuildForX8664) {
				// Build for x86_64
				Console.WriteLine("Building third party dependencies for VH_Biogears for x86_64");
				config.architecture = "x86_64";
				if (!BuildModel(config)) {
					return false;
				}
				StagePlatformLibraries(config);
			}

			if (bBuildForX86) {
				// Build for x86
				Console.WriteLine("Building third party dependencies for VH_Biogears for x86");
				config.architecture = "x86";
				if (!BuildModel(config)) {
					return false;
				}
				StagePlatformLibraries(config);
			}
			return bBuildForArmV7 || bBuildForArm64 || bBuildForX8664 || bBuildForX86;

		} else if (Target.Platform == UnrealTargetPlatform.Linux) {
			System.Console.WriteLine("Linux Detected. Assuming x86_64 gnueabi");

			bool bBindingsLinux = false;
			if (engineConfig.GetBool("/Scripts/VH_BioGears/Thirdparty", "bEnableBiogearsOnLinux", out bBindingsLinux)) {
				if (!bBindingsLinux) {
					return true;
				}
			}
			PublicDefinitions.Add("WITH_BIOGEARS_BINDING=1");
			PublicDefinitions.Add("BIOGEARS_IO_PRESENT");
			PublicDefinitions.Add("BIOGEARS_IO_EMBED_STATES");


			config.platform = "Linux";
			config.architecture = "x86_64";
			config.configuration = bDebug ? "dbg" : "rel";
			config.lib_suffix = ".so";
			config.libraries = new string[] { "libbiogears_common", "libbiogears_io", "libbiogears_cdm", "libbiogears", "libxerces-c-3.2" };

			if (!BuildModel(config)) {
				System.Console.WriteLine("		Failed To Build Model");
				return false;
			}
			StagePlatformLibraries(config);
			return true;
		} else if (Target.Platform == UnrealTargetPlatform.Mac) {
			System.Console.WriteLine("MacOs detected assuming Intel based MacOS");

			bool bBindingsMacOS = false;
			if (engineConfig.GetBool("/Scripts/VH_BioGears/Thirdparty", "bEnableBiogearsOnMacOs", out bBindingsMacOS)) {
				if (!bBindingsMacOS) {
					return true;
				}
			}
			PublicDefinitions.Add("WITH_BIOGEARS_BINDING=1");
			PublicDefinitions.Add("BIOGEARS_IO_PRESENT");
			PublicDefinitions.Add("BIOGEARS_IO_EMBED_STATES");

			config.platform = "MacOS";
			config.configuration = bDebug ? "debug" : "release";
			config.lib_suffix = ".a";
			config.dll_suffix = ".dylib";
			config.pdb_suffix = ".dsym";
			config.libraries = new string[] { "libxerces-c-3.2", "libbiogears_common", "libbiogears_io", "libbiogears_cdm", "libbiogears" };

			if (!BuildModel(config)) {
				return false;
			}
			StagePlatformLibraries(config);
			return true;
		} else if (Target.Platform == UnrealTargetPlatform.IOS) {
			bool bBindingsIOS = false;
			if (engineConfig.GetBool("/Scripts/VH_BioGears/Thirdparty", "bEnableBiogearsOnIOS", out bBindingsIOS)) {
				if (!bBindingsIOS) {
					return true;
				}
			}
			System.Console.WriteLine("VH_BioGears does not support IOS at this time. Patches accepted at http://github.com/biogearsengine");
			return false;
		} else {
			System.Console.WriteLine("The current platform is not supported by libBioGears.");
			return false;
		}
	}

	private void AddLibraries( ThirdPartyConfig config ) {
		if (Target.Platform == UnrealTargetPlatform.Win64) {
			// Add static library files
			System.Console.WriteLine("Adding static library files From " + config.library_path);

			DirectoryInfo libDirectory = new DirectoryInfo(config.library_path);
			FileInfo[] libFiles = libDirectory.GetFiles("*" + config.lib_suffix);
			foreach (FileInfo lib in libFiles) {
				// Add static library files (.lib)
				string libraryPath = Path.Combine(config.library_path, lib + config.lib_suffix);
				if (bVerboseLogs) {
					System.Console.WriteLine("	--> " + lib);
				}

				PublicAdditionalLibraries.Add(Path.Combine(config.library_path, lib.FullName));
			}
			System.Console.WriteLine();

			// Add dynamic library files
			System.Console.WriteLine("Adding dynamic library files from " + config.binary_path);

			DirectoryInfo dllDirectory = new DirectoryInfo(config.binary_path);
			FileInfo[] dllFiles = dllDirectory.GetFiles("*" + config.dll_suffix);
			foreach (FileInfo dll in dllFiles) {
				if (bVerboseLogs) {
					System.Console.WriteLine("	--> " + dll);
				}

				// NOTE: This will auto-copy the dll's to the staged bin path!
				RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)", dll.Name), Path.Combine(dllDirectory.FullName, dll.Name), StagedFileType.NonUFS);
			}
			System.Console.WriteLine();

			// Add pdb files
			System.Console.WriteLine("Adding Debug symbol files from " + config.library_path);

			FileInfo[] pdbFiles = libDirectory.GetFiles("*" + config.pdb_suffix);
			foreach (FileInfo pdb in pdbFiles) {
				if (bVerboseLogs) {
					System.Console.WriteLine("	--> " + pdb.Name);
				}

				// This will auto-copy the pdb's to the staged bin path
				RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)", pdb.Name), Path.Combine(libDirectory.FullName, pdb.Name), StagedFileType.NonUFS);
			}
			System.Console.WriteLine();
		} else if (Target.Platform == UnrealTargetPlatform.Android) {
			bEnableUndefinedIdentifierWarnings = false;
			bEnableExceptions = true;

#if UE_4_24_OR_LATER
				ShadowVariableWarningLevel = WarningLevel.Off;
#else
			bEnableShadowVariableWarnings = false;
#endif

			System.Console.WriteLine("Adding library files from " + config.library_path);
			foreach (string lib in config.libraries) {
				string path = Path.Combine(config.library_path, lib + config.lib_suffix);

				// Adding static library files
				if (bVerboseLogs) {
					System.Console.WriteLine("-->" + path);
				}
				PublicAdditionalLibraries.Add(path);
			}
		}
	}


	private bool BuildModel( ThirdPartyConfig config ) {
		// Build Paths
		config.build_path = Path.Combine(ThirdpartyBuildDir, config.platform, config.architecture, config.configuration, config.project);
		config.install_path = Path.Combine(ThirdpartyBuildDir, "Artifacts", config.platform, config.architecture, config.configuration);
		config.include_path = Path.Combine(ThirdpartyBuildDir, "Artifacts", config.platform, config.architecture, config.configuration, "include");
		config.binary_path = Path.Combine(ThirdpartyBuildDir, "Artifacts", config.platform, config.architecture, config.configuration, "bin");
		config.library_path = Path.Combine(ThirdpartyBuildDir, "Artifacts", config.platform, config.architecture, config.configuration, "lib");

		// Build Commands
		string buildCommand = CreateCMakeBuildCommand(config);
		if (String.IsNullOrEmpty(buildCommand)) {
			return false;
		}

		int buildCode = ExecuteCommandSync(buildCommand);
		if (buildCode != 0) {
			Console.WriteLine("Cannot configure CMake project. Exited with code: " + buildCode + ". Are CMAKE/git in your PATH?");
			return false;
		}

		// Install Commands
		string installCommand = CreateCMakeInstallCommand(config);
		if (String.IsNullOrEmpty(installCommand)) {
			return false;
		}

		int installCode = ExecuteCommandSync(installCommand);
		if (installCode != 0) {
			Console.WriteLine("Cannot build project. Exited with code: " + installCode);
			return false;
		}
		return true;
	}

	private string CreateCMakeBuildCommand( ThirdPartyConfig config ) {
		Console.WriteLine(RuntimeInformation.OSDescription);

		string executable = "cmake" + config.exe_suffix;
		string arguments = ""; ;

		if (Target.Platform == UnrealTargetPlatform.Win64) {
			string csharp_version = AppDomain.CurrentDomain.SetupInformation.TargetFrameworkName;
			string generator = "Visual Studio" + (csharp_version.StartsWith("4.0.30319") ? " 15 2017" : " 16 2019");

			System.Console.Write("csharp_version={0}\n", csharp_version);
			System.Console.Write("generator={0}\n", generator);

			arguments = " -G " + ((true) ? "\"Visual Studio 15 2017\"" : "\"Visual Studio 16 2019\"") + // TODO: Find Away to determine the Visual studio Version
						" -A x64 " +
						" -B " + config.build_path + // Where Intermediate Directory will be created
						" -S " + ThirdpartySourceDir + // Location of CMakeLists.txt
						" -D CMAKE_INSTALL_PREFIX=" + config.install_path + // Where include/bin/lib/share are created
						" -D CMAKE_BUILD_TYPE=" + ((config.configuration == "rel") ? "Release" : "RelWithDebInfo") + // Release, Debug, RelWithDebInfo
						" -D BG_META_PLATFORM=" + config.platform +
						" -D BG_META_ARCHITECTURE=" + config.architecture +
						" -D BG_META_CONFIGURATION=" + config.configuration;
		} else if (Target.Platform == UnrealTargetPlatform.Android) {
			string android_ndk_root = Environment.GetEnvironmentVariable("ANDROID_NDK_ROOT");
			string android_home = Environment.GetEnvironmentVariable("ANDROID_HOME");
			string ant_home = Environment.GetEnvironmentVariable("ANT_HOME");
			Environment.SetEnvironmentVariable("UE4_LINUX_USE_LIBCXX","0");
			string android_toolchain_file;

			if (String.IsNullOrEmpty(android_ndk_root)) {
				android_toolchain_file = Path.Combine(ThirdpartySourceDir, "toolchians", "android.toolchain.cmake");
			} else {
				if (File.Exists(Path.Combine(android_ndk_root, "source.properties"))) {
					string[] properties = System.IO.File.ReadAllLines(Path.Combine(android_ndk_root, "source.properties"));
					foreach (string line in properties) {
						string[] keyvalue = line.Split('=');
						if (keyvalue.Length == 2 && keyvalue[0] == "Pkg.Revision") {
							System.Console.Write("Android NDK ver = {0}", keyvalue[1]);
						}
					}
					android_toolchain_file = Path.Combine(android_ndk_root, "build", "cmake", "android.toolchain.cmake");
				} else {
					System.Console.WriteLine("ANDROID_NDK_ROOT does not appear to be a valid. Please ensure your NDK installation is complete");
					return "";
				}
			}

			string cmake_make_program = Environment.GetEnvironmentVariable("CMAKE_MAKE_PROGRAM");
			if (String.IsNullOrEmpty(cmake_make_program)) {
				// Assuming windows-x86-64 is the host architecture at this time
				// TODO: Find away to ask csharp or unreal what OS I'm on to pick the right ndk
				cmake_make_program = Path.Combine(android_ndk_root, "prebuilt", "windows-x86_64", "bin", "make" + config.exe_suffix);
			}

			arguments = " -G \"Unix Makefiles\"" +
						" -B " + config.build_path +
						" -S " + ThirdpartySourceDir +
						" -D CMAKE_BUILD_TYPE=Release" +
						" -D CMAKE_MAKE_PROGRAM=" + cmake_make_program +
						" -D CMAKE_TOOLCHAIN_FILE=" + android_toolchain_file +
						" -D ANDROID_STL=gnustl_shared" +
						" -D ANDROID_CPP_FEATURES='rtti;exceptions'" +
						" -D ANDROID_ABI=" + ((config.architecture == "armeabi-v7a") ? "armeabi-v7a" : "arm64-v8a") + ((config.architecture == "arm64-v8a") ? "" : " -DANDROID_ARM_NEON=ON") +
						" -D ANDROID_PLATFORM=\"android-24\"" +
						" -D CMAKE_INSTALL_PREFIX=" + config.install_path +
						" -D CMAKE_PREFIX_PATH=" + config.native_path +
						" -D CMAKE_FIND_ROOT_PATH=" + config.install_path +
						" -D CMAKE_BUILD_TYPE=" + ((config.configuration == "rel") ? "Release" : "RelWithDebInfo") +
						" -D XERCES_C_transcoder=icu" +
						" -D BG_META_PLATFORM=" + config.platform +
						" -D BG_META_ARCHITECTURE=" + config.architecture +
						" -D BG_META_CONFIGURATION=" + config.configuration +
						" -D NATIVE_CODE_GENERATOR=\"Visual Studio 15 2017 Win64\""; //TODO: Figure out which Visual Studios are installed
		} else {
			// This is a branch for native compiles like MacOS 
			// Due to the need for toolchain piles all future supported cross compiles (IOS) will need an explicit branch condition to set the TOOLCHAIN_FILE
			arguments = "-G \"Unix Makefiles\"" +
						" -B " + config.build_path +
						" -S " + ThirdpartySourceDir +
						" -D CMAKE_INSTALL_PREFIX=" + config.install_path +
						" -D CMAKE_BUILD_TYPE=" + ((config.configuration == "rel") ? "Release" : "RelWithDebInfo") +
						" -D BG_META_PLATFORM=" + config.platform +
						" -D BG_META_ARCHITECTURE=" + config.architecture +
						" -D BG_META_CONFIGURATION=" + config.configuration;
		}

		if (bVerboseLogs) {
			Console.WriteLine(executable + arguments);
		}

		return executable + arguments;
	}

	private string CreateCMakeInstallCommand( ThirdPartyConfig config ) {
		string executable = "cmake" + config.exe_suffix;

		string arguments = " --build " + config.build_path +
							" --config " + ((config.configuration == "rel") ? "Release" : "RelWithDebInfo");

		if (bVerboseLogs) {
			Console.WriteLine(executable + arguments);
		}

		return executable + arguments;
	}

	private int ExecuteCommandSync( string command ) {
		Console.WriteLine("Running: " + command);

		string executable;
		string arguments;

		if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux)) {
			executable = "/bin/sh";
			arguments = "-c " + command;
		} else {
			executable = "cmd.exe";
			arguments = "/c " + command;
		}

		ProcessStartInfo processInfo = new ProcessStartInfo(executable, arguments) {
			CreateNoWindow = true,
			UseShellExecute = false,
			RedirectStandardError = true,
			RedirectStandardOutput = true,
			WorkingDirectory = ModuleDirectory
		};

		Process process = Process.Start(processInfo);
		process.OutputDataReceived += ( sender, args ) => Console.WriteLine(args.Data);
		process.ErrorDataReceived += ( sender, args ) => Console.WriteLine(args.Data);

		process.BeginOutputReadLine();
		process.BeginErrorReadLine();

		process.WaitForExit();

		return process.ExitCode;
	}
}
