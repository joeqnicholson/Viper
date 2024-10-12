@echo off
echo Starting clean build for Unreal Engine project...

REM Set the path to your Unreal project directory
set PROJECT_DIR="C:\Users\Slim7\Documents\Unreal Projects\Viper"

REM Set the path to Unreal Build Tool (adjust this path to your Unreal Engine installation)
set UE_BUILD_TOOL="C:\Path\To\UnrealEngine\Engine\Binaries\DotNET\UnrealBuildTool.exe"

REM Set the name of your project
set PROJECT_NAME=Viper

REM Navigate to the project directory
cd %PROJECT_DIR%

REM Delete the Binaries, Intermediate, and Saved folders
echo Deleting Binaries folder...
rmdir /s /q Binaries

echo Deleting Intermediate folder...
rmdir /s /q Intermediate

echo Deleting Saved folder...
rmdir /s /q Saved

REM Run the Unreal Build Tool to rebuild the project (change 'Win64' and 'Development' as needed)
echo Building project with Unreal Build Tool...
%UE_BUILD_TOOL% %PROJECT_NAME%Editor Win64 Development -project="%PROJECT_DIR%\%PROJECT_NAME%.uproject" -progress -log

echo Clean build completed successfully!
pause
an