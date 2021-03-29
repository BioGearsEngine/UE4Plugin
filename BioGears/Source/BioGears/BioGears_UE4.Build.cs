using UnrealBuildTool;
using System;
using System.Linq;
using System.IO;
using System.Diagnostics;
using System.Text;
using System.Runtime.InteropServices;

public class BioGears_UE4 : ModuleRules
{
	private string ModulePath { get { return ModuleDirectory; } }
	private string ThirdPartyPath { get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); } }

	//!
	//!  This PATH is used to build binaries at the top most level of the source tree. The goal of this is
	//!  to avoid LONG_PATHS which excced the 250 character limited allowed by msbuild
	//!
	private string ThirdPartyBuildPath { get { return Path.GetFullPath(Path.Combine(ModulePath, "../../../../../ThirdParty/")); } }
	private bool bVerboseLogs { get { return true; } }
	private string ProjectBinaryPath { get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../../Binaries/")); } }
	private string PluginBinaryPath { get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../Binaries/")); } }
	private string[] getBioGearsLibraries()	{ return new string[] { "biogears", "biogears_cdm" };	}
	private string[] getThirdpartyLibraries()	{ return new string[] {  "Log4cpp", "xerces-c_3" };	}

	public BioGears_UE4(ReadOnlyTargetRules Target) : base(Target)
	{
		bUseRTTI = true;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableExceptions = true;

		PublicDefinitions.Add("XERCES_INCLUDE_WCHAR_H=0");


		PublicIncludePaths.AddRange(
					new string[] {
							 Path.Combine(ThirdPartyBuildPath, "Binaries", "include")
							,Path.Combine(ThirdPartyBuildPath, "Binaries", "include", "biogears")
							,Path.Combine(ThirdPartyBuildPath, "Binaries", "include", "eigen3")
					}
				);


		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
		);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add other public dependencies that you statically link with here ...
                "Core",
				"CoreUObject",
				"Engine",
				"Projects",
				"XmlParser",
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
		);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);

		if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Win32)
		{
			// todo ohg
			//PublicAdditionalLibraries.Add("psapi.lib");
		}

		LoadBioGears(Target);
	}
	public bool IsDebug()
	{
		//return true;
		return Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.Development  /*&& BuildConfiguration.bDebugBuildsActuallyUseDebugCRT*/;
	}
	private bool LoadBioGears(ReadOnlyTargetRules target)
	{

		string platformDir = "";
		string buildDir = "";
		string libExtension = "";
		string dllExtension = "";
		string pdbExtension = "";
		if (target.Platform == UnrealTargetPlatform.Win64)
		{
			platformDir = "Win64";
			buildDir = IsDebug() ? "RelWithDebInfo" : "Release";
			libExtension = ".lib";
			dllExtension = ".dll";
			pdbExtension = ".pdb";
		}
		else if (target.Platform == UnrealTargetPlatform.Android)
		{
			platformDir = "aarch64";
			buildDir = "Release";
			libExtension = ".so";
			dllExtension = "";
			pdbExtension = "";
		}

		var isModelBuilded = BuildModel(target);

		if (!isModelBuilded)
		{
			return false;
		}

		var LibrariesPath = Path.Combine(ThirdPartyBuildPath, "Binaries", "lib", platformDir, buildDir);

		foreach (var libName in getBioGearsLibraries())
		{
			var libraryPath = Path.Combine(LibrariesPath, libName + libExtension);
			PublicAdditionalLibraries.Add(libraryPath);
		}

		LibrariesPath = Path.Combine(ThirdPartyBuildPath, "Binaries", "lib");

		foreach (var libName in getThirdpartyLibraries())
		{
			var libraryPath = Path.Combine(LibrariesPath, libName + libExtension);
			PublicAdditionalLibraries.Add(libraryPath);
		}

		string binPath = Path.Combine(ThirdPartyBuildPath, "Binaries", "bin", platformDir, buildDir);
		DirectoryInfo binDirectory = new DirectoryInfo(binPath);
		foreach (var binFile in binDirectory.GetFiles("*" + dllExtension))
		{
			if (bVerboseLogs)
			{
				System.Console.WriteLine("--> Adding " + binFile.Name);
			}

			string fullFilename = Path.Combine(binPath, binFile.Name);
			CopyDll(fullFilename, platformDir, dllExtension, pdbExtension, target.Platform == UnrealTargetPlatform.Win64);

		}

		binPath = Path.Combine(ThirdPartyBuildPath, "Binaries", "bin");
		binDirectory = new DirectoryInfo(binPath);
		foreach (var binFile in binDirectory.GetFiles("*" + dllExtension))
		{
			if (bVerboseLogs)
			{
				System.Console.WriteLine("--> Adding " + binFile.Name);
			}

			string fullFilename = Path.Combine(binPath, binFile.Name);
			CopyDll(fullFilename, platformDir, dllExtension, pdbExtension, target.Platform == UnrealTargetPlatform.Win64);

		}

		PublicIncludePaths.Add(Path.Combine(ThirdPartyBuildPath, "Binaries", "include"));
		PublicIncludePaths.Add(Path.Combine(ThirdPartyBuildPath, "Binaries", "include", "biogears"));
		PublicIncludePaths.Add(Path.Combine(ThirdPartyBuildPath, "Binaries", "include", "eigen3"));


		return true;
	}
	public void CopyDll(string source, string platform, string binExtension, string pdbExtension, bool copyPDBs)
	{
		string[] sourceSplit = source.Split('/', '\\');
		string dllFilename = sourceSplit[sourceSplit.Length - 1];

		// Copying to both the plugin's binaries folder (for plugin distribution) and the project's binaries folder (for shipping builds)
		string[] destDirList = {
			Path.Combine(ProjectBinaryPath, platform),
			Path.Combine(PluginBinaryPath, platform),
		};

		foreach (string destDir in destDirList)
		{
			if (!Directory.Exists(destDir))
			{
				Directory.CreateDirectory(destDir);
			}

			string destFile = Path.Combine(destDir, dllFilename);
			if (!File.Exists(destFile) || (File.GetLastWriteTimeUtc(source) > File.GetLastWriteTimeUtc(destFile)))
			{
				string fileStatus = !File.Exists(destFile) ? "missing" : "newer";
				System.Console.WriteLine("-->   Copying (" + fileStatus + ") " + source + " to " + destFile);

				// NOTE: For some reason, overwrite still fails on read-only dest file!
				if (File.Exists(destFile))
				{
					File.SetAttributes(destFile, FileAttributes.Normal);
					File.Delete(destFile);
				}

				File.Copy(source, destFile);
				File.SetAttributes(destFile, FileAttributes.Normal);

				if (IsDebug())
				{
					string sourcePDB = source.Replace(binExtension, pdbExtension);
					string destPDB = destFile.Replace(binExtension, pdbExtension);
					if (File.Exists(sourcePDB))
					{
						System.Console.WriteLine("-->   Copying (pdb) " + sourcePDB + " to " + destPDB);
						File.Copy(sourcePDB, destPDB, true);
					}

				}
			}
		} // foreach

		RuntimeDependencies.Add(Path.Combine(ProjectBinaryPath, platform, dllFilename));
		PublicDelayLoadDLLs.Add(Path.Combine(ProjectBinaryPath, platform, dllFilename));

	}

	private bool BuildModel(ReadOnlyTargetRules Target)
	{

		string buildType;
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			buildType = IsDebug() ? "RelWithDebInfo" : "Release";
		}
		else
		{
			buildType = "Release";
		}

		var buildDirectory = buildType;
		var buildPath = Path.Combine(ThirdPartyBuildPath, "Intermediate", buildDirectory);

		var configureCommand = CreateCMakeBuildCommand(buildPath, buildType, Target);
		var configureCode = ExecuteCommandSync(configureCommand, Target);
		if (configureCode != 0)
		{
			Console.WriteLine("Cannot configure CMake project. Exited with code: "
							  + configureCode + ". Is cmake in your PATH?");
			return false;
		}

		var installCommand = CreateCMakeInstallCommand(buildPath, buildType, Target);
		var buildCode = ExecuteCommandSync(installCommand, Target);
		if (buildCode != 0)
		{
			Console.WriteLine("Cannot build project. Exited with code: " + buildCode);
			return false;
		}
		return true;
	}


	private string CreateCMakeBuildCommand(string buildDirectory,
											string buildType,
											ReadOnlyTargetRules Target)
	{

		string cmake_executable;
		Console.WriteLine(RuntimeInformation.OSDescription);


		if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
		{ cmake_executable = "cmake"; }
		else if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
		{ cmake_executable = "cmake.exe"; }
		else { cmake_executable = "cmake.exe"; }


		string platformDir;
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			platformDir = "Win64";
		}
		else
		{
			platformDir = "aarch64";
		}


		var currentDir = ModulePath;
		var installPath = Path.Combine(ThirdPartyBuildPath, "Binaries");
		var sourceDir = ThirdPartyPath;
		//NOTE: Hard Coded Generator
		var arguments = " -G \"Visual Studio 15 2017\"" +
						" -A x64 " +
						" -T host=x64" +
						" -S " + sourceDir +
						" -B " + buildDirectory +
						" -DBioGears_PLATFORM_PREFIX=" + platformDir +
						" -DCMAKE_BUILD_TYPE=" + buildType +
						" -DCMAKE_INSTALL_PREFIX=" + installPath;

		Console.WriteLine(cmake_executable + arguments);
		return cmake_executable + arguments;
	}

	private string CreateCMakeInstallCommand(string buildDirectory,
												string buildType,
												ReadOnlyTargetRules Target)
	{
		string cmake_executable;
		if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
		{
			cmake_executable = "cmake";
		}
		else
		{
			cmake_executable = "cmake.exe";
		}
		return cmake_executable + " --build " + buildDirectory +
			   " --config " + buildType;
	}

	private int ExecuteCommandSync(string command, ReadOnlyTargetRules Target)
	{
		Console.WriteLine("Running: " + command);
		string shell_executable;
		string arguments;
		if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
		{
			shell_executable = "/bin/sh";
			arguments = "-c " + command;
		}
		else
		{
			shell_executable = "cmd.exe";
			arguments = "/c " + command;
		}
		var processInfo = new ProcessStartInfo(shell_executable, arguments)
		{
			CreateNoWindow = true,
			UseShellExecute = false,
			RedirectStandardError = true,
			RedirectStandardOutput = true,
			WorkingDirectory = ModulePath
		};

		StringBuilder sb = new StringBuilder();
		Process p = Process.Start(processInfo);
		p.OutputDataReceived += (sender, args) => Console.WriteLine(args.Data);
		p.BeginOutputReadLine();
		p.WaitForExit();

		return p.ExitCode;
	}

}
