# Introduction
This reposiotory is a simple example of a Plugin architecture for the UE4 Engine to interface with BioGears.  It supports several action types and polling mechanisims. 

We hope to maintain and contribute to this plugin overtime to create a more robust UE4 capabilities when interfacing with BioGears

## Summary of required items

|Requirment | NOTE |
| android-ndk-17c | This is the only version of the NDK that the current native components can build under UE4.23 the required UE4 version of this plugin.
|android-21 | This is the API and build tools you must install to build the Non native parts of the Android Package
| Gradle | A tool for bundling up Java Builds| 
| Ant    | A tool for bundling up Java Builds|
| CMake > 20.0 | A Meta Project Compiler for building BioGears | 
|GRADLE_HOME| The Build will use this to find gradle even if its in your path|
|JAVA_HOME| The Build will use this to find JAVA |
|ANDROID_NDK_ROOT| Parts of the Build use this to find your NDK |
|ANDROID_SDK_HOME| Parts of the Build use this to find the SDK|
|ANDROID_NDK_VERSION| This helps the Build choose the right NDK componets to build against |
|ANDROID_HOME| This helps the build find the SDK in various parts of the build |
|NDK_ROOT| Again some parts of the build use this variable|
|NDKROOT|| Others use this|

*We will work to reduce these requirments over time* 

## Getting Started (Burncare)
Make a fresh checkout of the BURNCARE Repsitory. For this article we assume the REPO is checked in to E:\burncare on a windows 10 machine with Visual Studio MSVC15 2017 installed.  Adjust all paths based off your checkout location/

Repo Location in P4V
```P4
UE4/Buncare
```

After Burncare is checked out **DELETE** E:\Burncare\Game\Plugins\VH_Biogears

## Pulling VH_Biogears
VH_Biogears is versioned in GIT.  We keep a copy of it in the Burncare repo but for development purposes you need to clone it from GIT.  If you have your P4IGNORE setup (See Seeting up P4Ignore)  then P4 will ignore the extra files from the clone

In a command prompt go to 
```bash
cd E:\Burncare\Game\Plugins
git clone ssh://git@sed-stash.us.ara.com:7999/bg/ue4plugin.git VH_Biogears
```

Once this is done run GenerateProjectFiles.bat in E:\burncare and build the engine as normal. Once the build is done (4 hours) setup Visual studio to run the game as an editor

## Running the engine from Visual Studio
Open UE4 and right click the *Game* target in the *Solution Explorer*. Select properties. In the proeprties window select debug and fill in the command line arguments as 

```bash
  Game -log
```

Use the Green Arrow or F5 to launch the editor from inside MSVC

## Installing Android Toolchain
You will need to download the android-sdk and android-ndks for this project. The Engine comes bundeled with an installer for NVPACK_1R7 which is a good starting place, but not required. 

You can download the SDK, NDK and Java 1_8 from the following locations

| Package | URL | Date | 
|---------|-----|------|
| Java    |https://www.oracle.com/java/technologies/javase/javase-jdk8-downloads.html#license-lightbox ||
| Android SDK | https://dl.google.com/android/repository/commandlinetools-win-7583922_latest.zip | |
| Android NDK | https://dl.google.com/android/repository/android-ndk-r17c-windows-x86_64.zip|| 
| Gradle | https://gradle.org/next-steps/?version=4.1&format=all |
| Cmake | https://github.com/Kitware/CMake/releases/download/v3.20.5/cmake-3.20.5-windows-x86_64.msi|


Java JDK 1.8 Is getting older and harder to download JAVA 11 may work but since we are using an older SDK set of tools it doesn't hurt to have the version of java they were built against avaliable.

### Warning
For this build to work Gradle/CMake and Java need to be in the PATH of the Visual Studio instance.  Adding them to your PATH is the easiest solution, but if this conflicts with your standard environment you can choose to write a BAT file which primes the PATH or set them in a command prompt before launching Visual Studio.


For this tutorial lets assume that everything was installed in 

```
E:\AndroidTools
```
You should now have a folder structure that looks like this

```
 E:\AndroidTools\
 |---jdk1.8.0_77
 |---android-ndk-r17c
 |---gradle
 `---cmdline-tools
```

### Environment Variables
When build your environment will need to contain the following variables. Adjust accordingly to your actual install locations

|Variable | Value|
|---------|------|
|GRADLE_HOME|E:\AndroidTools\gradle|
|JAVA_HOME|E:\AndroidTools\jdk1.8.0_77\|
|ANDROID_NDK_ROOT|E:\AndroidTools\android-ndk-r17c|
|ANDROID_SDK_HOME|E:\AndroidTools\|
|ANDROID_NDK_VERSION| android-ndk-r17c |
|ANDROID_HOME|E:\AndroidTools\android-sdk|
|NDK_ROOT|E:\AndroidTools\android-ndk-r17c|
|NDKROOT||E:\AndroidTools\android-ndk-r17c|

|P4IGNORE|.p4ignore.txt|

Open the SDKManager in *E:\AndroidTools\cmdline-tools\bin\sdkmanager.bat

### Installing SDK Components
The command line tools simply allows you to install packages that will be used durring the build.  The following commands should install all required packages

```
   E:\AndroidTools\cmdline-tools\binsdkmanager --sdk_root=E:\AndroidTools\android-sdk\ Platforms;android-21 ndk;17.2.4988734 build-tools;27.0.3 cmake;3.18.1
```
## Setting UE4Editor for  Android
Before Packaging for Android a few things should be known. First the inculusion of BioGears in the Android Build is dependent on values in

```bash
E:\burncare\Game\Plugins\VH_Biogears\Config\DefaultEngine.ini
```

```ini
[/Scripts/VH_BioGears/Thirdparty]
bEnableBiogearsOnWindows=True
bEnableBiogearsOnAndroid=True
```

To build with out biogears libraries for testing change bEnableBiogearsOnAndroid to false else leave it as true. 

Next in the running editor go to Edit->Project Settings -> Android and uncheck **Support armv7** At this time armv7-eabi is untested and can not be gaurenteed to function.

Now in Platforms:Android SDK: Set the following values

| Field | Value |
|-------|-------|
| Location of Android SDK | E:\AndroidTools\android-sdk|
| Location of Android NDK | E:\AndroidTools\android-ndk-r17c
| Location of ANT | EMPTY | 
| Locatin of JAVA | E:\AndroidTools\jdk1.8.0_77 | 
| SDK API Level | latest | 
| NDK API Level | android-21 |

## Setting up P4Ignore
P4 Will check the current environment it is running under  for a P4IGNORE variable and read the file it points to. This file can be absolute and shared among all P4Ignore repos or it can be relative and it will read it with respect to the current Depot.  A P4Ignore is provided in the Burncare Repo so please set your P4Ignore to `.p4ignore` or maintain one yourself to avoid checking **E:\Burncare\Thirdparty\\** and **E:\Burncare\Game\PLugins\VH_Biogears\.git**

## Packaging the Build
In the UE4 Editor File->Package Project->Android->Android Multi. Select the default folder of E:\Burncare\Android (2 hour wait)

## License
This plugin is provied under the APACHE 2.0 license.


+
https://dl.google.com/android/repository/commandlinetools-win-7583922_latest.zip