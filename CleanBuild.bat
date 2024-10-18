@echo off
echo Starting clean build for Unreal Engine project...

REM Set the path to your Unreal project directory
set PROJECT_DIR="C:\Users\Slim7\Documents\Unreal Projects\Viper"

REM Set the path to Unreal Engine installation directory
set UE_DIR="C:\Path\To\UnrealEngine"

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

REM Generate project files
echo Generating project files...
"%UE_DIR%\Engine\Binaries\DotNET\UnrealBuildTool.exe" -projectfiles -project="%PROJECT_DIR%\%PROJECT_NAME%.uproject" -game -rocket -progress

REM Run the Unreal Build Tool to rebuild the project
echo Building project with Unreal Build Tool...
"%UE_DIR%\Engine\Binaries\DotNET\UnrealBuildTool.exe" %PROJECT_NAME%Editor Win64 Development -project="%PROJECT_DIR%\%PROJECT_NAME%.uproject" -progress -log

echo Clean build completed successfully!
pause
