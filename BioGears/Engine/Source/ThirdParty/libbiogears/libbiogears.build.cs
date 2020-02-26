// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class libbiogears : ModuleRules
{
  private string PluginBinaryPath
  {
    get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../Binaries/")); }
  }

  private string ProjectBinaryPath
  {
    get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../../../../Binaries/")); }
  }

  private string ProjectContentPath
  {
    get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../../Content/")); }
  }
  public libbiogears(ReadOnlyTargetRules Target) : base(Target)
  {
    Type = ModuleType.External;
    bUseRTTI = true;
    switch (Target.Platform)
    {
      /*
      !   BioGears > 7.3.1  allows parallel installs of platforms and configurations
      !   Assuming Source/ThirdParty/libbiogears/usr/{lib,bin}/{PLATFORM}/{CONFIG}
      ! 
      */
      case UnrealTargetPlatform.Win32:
        setup_windows_ia32(Target);
        break;
      case UnrealTargetPlatform.Win64:
        setup_windows_amd64(Target);
        break;
      case UnrealTargetPlatform.Android:
        setup_android(Target);
        break;
      case UnrealTargetPlatform.Mac:
        setup_macos(Target);
        break;
      case UnrealTargetPlatform.Linux:
        break;
      default:
        break;
    }
    PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

    PublicIncludePaths.AddRange(
    new string[] {
      // ... add other public include paths required here ...
      Path.Combine(ModuleDirectory, "usr","include")
      ,Path.Combine(ModuleDirectory, "usr","include", "eigen3")
    }
    );


    PrivateIncludePaths.AddRange(
    new string[] {
      // ... add other private include paths required here ...
      Path.Combine(ModuleDirectory, "usr","include")
      ,Path.Combine(ModuleDirectory, "usr","include", "eigen3")
    }
    );

    PublicDependencyModuleNames.AddRange(
    new string[]
    {
		// ... add other public dependencies that you statically link with here ...
        "Core",
        "CoreUObject",
    });



    DynamicallyLoadedModuleNames.AddRange(
    new string[]
    {
      // ... add any modules that your module loads dynamically here ...
    }
    );
    //TODO: Auto Determine BioGears Library Function
    prepare_content("7.3.0");


  }

  protected void prepare_content(string version)
  {
    string biogears_content_destination = Path.Combine(ProjectContentPath, version);
    string biogears_data_path = Path.Combine(ModuleDirectory, "usr", "share", "biogears", version, "data");
    string biogears_xsd_path = Path.Combine(ModuleDirectory, "usr", "share", "biogears", version, "xsd");

    System.Console.WriteLine("Preparing libBioGears resource requirments");
    System.Console.WriteLine("\t--> Data {0}", biogears_data_path);
    System.Console.WriteLine("\t--> XSD {0}", biogears_xsd_path);
    System.Console.WriteLine("\t--> Prepared in {0}", biogears_content_destination);

    if (!Directory.Exists(biogears_content_destination))
    { Directory.CreateDirectory(biogears_content_destination); }

    var destination = new DirectoryInfo(biogears_content_destination);
    var source = new DirectoryInfo(biogears_data_path);
    CopyAll(source, destination);

    string biogears_xsd_destination = Path.Combine(biogears_content_destination, "xsd");
    if (!Directory.Exists(biogears_xsd_destination))
    { Directory.CreateDirectory(biogears_xsd_destination); }

    destination = new DirectoryInfo(biogears_xsd_destination);
    source = new DirectoryInfo(biogears_xsd_path);
    CopyAll(source, destination);
  }

  protected void CopyAll(DirectoryInfo source, DirectoryInfo target)
  {
    Directory.CreateDirectory(target.FullName);

    // Copy each file into the new directory.
    foreach (FileInfo original in source.GetFiles())
    {
      string dest = Path.Combine(target.FullName, original.Name);
      if (!File.Exists(dest) || (File.GetLastWriteTimeUtc(dest) > File.GetLastWriteTimeUtc(dest)))
      {
        // NOTE: For some reason, overwrite still fails on read-only dest file!
        if (File.Exists(dest))
        {
          File.SetAttributes(dest, FileAttributes.Normal);
          File.Delete(dest);
        }

        original.CopyTo(dest, true);
        File.SetAttributes(dest, FileAttributes.Normal);

      }
    }

    // Copy each subdirectory using recursion.
    foreach (DirectoryInfo diSourceSubDir in source.GetDirectories())
    {
      DirectoryInfo nextTargetSubDir =
          target.CreateSubdirectory(diSourceSubDir.Name);
      CopyAll(diSourceSubDir, nextTargetSubDir);
    }
  }

  protected void setup_windows_ia32(ReadOnlyTargetRules Target)
  {
    string[] destinationDirs = {
       Path.Combine(ProjectBinaryPath, "Win32")
      ,Path.Combine(PluginBinaryPath, "Win32")
    };

    setup_windows(Target, destinationDirs);
  }
  protected void setup_windows_amd64(ReadOnlyTargetRules Target)
  {
    string[] destinationDirs = {
      Path.Combine(ProjectBinaryPath, "Win64")
      ,Path.Combine(PluginBinaryPath, "Win64")
    };

    setup_windows(Target, destinationDirs);
  }

  protected void setup_windows(ReadOnlyTargetRules Target, string[] destinationDirs)
  {
    //Visual Studio 2017 = msvc15
    //Visual Studio 2019 = msvc16
    string msvc_ver = (Target.WindowsPlatform.Compiler == WindowsCompiler.VisualStudio2019) ? "msvc16" : "msvc15";
    string configuration = (Target.Configuration == UnrealTargetConfiguration.Debug
                             || Target.Configuration == UnrealTargetConfiguration.DebugGame
                             || Target.Configuration == UnrealTargetConfiguration.Development) ? "RelWithDebInfo" : "Release";
    string[] libraries = { "Log4cpp.lib", "xerces-c_3_2.lib", "biogears_cdm.lib", "biogears.lib" };
    string[] dlls = { "Log4cpp.dll", "xerces-c_3_2.dll", "libbiogears_cdm.dll", "libbiogears.dll" };

    string libPath = Path.Combine(ModuleDirectory, "usr", "lib", msvc_ver, configuration);
    foreach (string library in libraries)
    {
      PublicAdditionalLibraries.Add(Path.Combine(libPath, library));
    }
    string dllPath = Path.Combine(ModuleDirectory, "usr", "bin", msvc_ver, "RelWithDebInfo");
    foreach (string dll in dlls)
    {
      PublicDelayLoadDLLs.Add(Path.Combine(dllPath, dll));
      foreach (string destination in destinationDirs)
      {
        if (!Directory.Exists(destination))
        { Directory.CreateDirectory(destination); }
        string source = Path.Combine(dllPath, dll);
        string destFile = Path.Combine(destination, dll);
        if (!File.Exists(destFile) || (File.GetLastWriteTimeUtc(source) > File.GetLastWriteTimeUtc(destFile)))
        {
          // NOTE: For some reason, overwrite still fails on read-only dest file!
          if (File.Exists(destFile))
          {
            File.SetAttributes(destFile, FileAttributes.Normal);
            File.Delete(destFile);
          }
          System.Console.WriteLine("-->   Copying" + source + " to " + destFile);
          File.Copy(source, destFile);
          File.SetAttributes(destFile, FileAttributes.Normal);
        }

        string sourcePDB = source.Replace("bin", "lib").Replace(".dll", ".pdb");
        string destPDB = destFile.Replace(".dll", ".pdb");
        if ( File.Exists(destPDB) && (!File.Exists(destPDB)  || (File.GetLastWriteTimeUtc(sourcePDB) > File.GetLastWriteTimeUtc(destPDB))))
        {
          // NOTE: For some reason, overwrite still fails on read-only dest file!
          if (File.Exists(destPDB))
          {
            File.SetAttributes(destPDB, FileAttributes.Normal);
            File.Delete(destPDB);
          }
          System.Console.WriteLine("-->   Copying" + sourcePDB + " to " + destPDB);
          File.Copy(sourcePDB, destPDB);
          File.SetAttributes(destPDB, FileAttributes.Normal);
        }
      }
    }
  }
  protected void setup_android(ReadOnlyTargetRules Target)
  {
    string build_conf = "Release";
    if (Target.Configuration == UnrealTargetConfiguration.Debug
         || Target.Configuration == UnrealTargetConfiguration.DebugGame
         || Target.Configuration == UnrealTargetConfiguration.Development)
    {
      build_conf = "Debug";
    }
    PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "usr", "lib", "linux-gcc5", build_conf, "liblog4cpp.so"));
    PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "usr", "lib", "linux-gcc5", build_conf, "libxerces-c.so"));
    PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "usr", "lib", "linux-gcc5", build_conf, "libbiogears_cdm.so"));
    PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "usr", "lib", "linux-gcc5", build_conf, "libbiogears.so"));

  }
  protected void setup_macos(ReadOnlyTargetRules Target)
  {
    string build_conf = "Release";
    if (Target.Configuration == UnrealTargetConfiguration.Debug
         || Target.Configuration == UnrealTargetConfiguration.DebugGame
         || Target.Configuration == UnrealTargetConfiguration.Development)
    {
      build_conf = "Debug";
    }
    PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "usr", "lib", "macos-clang", build_conf, "liblog4cpp.dylib"));
    PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "usr", "lib", "macos-clang", build_conf, "libxerces-c.dylib"));
    PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "usr", "lib", "macos-clang", build_conf, "libbiogears_cdm.dylib"));
    PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "usr", "lib", "macos-clang", build_conf, "libbiogears.dylib"));
  }

}
