@echo off
REM Change the Unreal Engine path as needed
set UE4_ROOT="C:\Program Files\Epic Games\UE_5.3.2"
set PROJECT_PATH="C:\Users\Slim7\Documents\Unreal Projects\Viper\Viper.uproject"

REM Navigate to Unreal's Build directory
cd %UE4_ROOT%\Engine\Build\BatchFiles

REM Run a clean build
Build.bat ViperEditor Win64 Development -project=%PROJECT_PATH% -clean