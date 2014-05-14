@echo off
setlocal enabledelayedexpansion

:: Initial config
set /p date_input="Enter the date of the last pack [MM-DD-YYYY] : " %=%
set date=:%date_input%

echo Preparation...
SLEEP 2

mkdir ..\..\temp
pushd ..
set SOURCE_DIR=%cd%
pushd ..\temp
set DEST_DIR=%cd%
popd
set FILENAMES_TO_COPY=*.jar *.tga *.dds *.bik *.fpk *.mp3 *.wav *.exe

:: Create an exclusion list

echo :: Excluded files > PackBaseExclude.txt
echo Assets\MCP0.FPK >> PackBaseExclude.txt
echo Assets\Modules\Custom_Civilizations_MCP\ >> PackBaseExclude.txt
echo Assets\Sounds\Addon_audio\ >> PackBaseExclude.txt
echo Assets\Sounds\NEW\ >> PackBaseExclude.txt
echo Assets\Sounds\Soundtrack\OpeningMenuCiv4.mp3 >> PackBaseExclude.txt
echo checker\ >> PackBaseExclude.txt
echo and2_checker.exe >> PackBaseExclude.txt
echo Uninstall.exe >> PackBaseExclude.txt

:: Begin process

echo Gathering binaries into a temp folder...
SLEEP 2

for /R "%SOURCE_DIR%" %%F IN (%FILENAMES_TO_COPY%) do (
    if exist "%%F" (
    	set FILE_DIR=%%~dpF
    	set FILE_INTERMEDIATE_DIR=!FILE_DIR:%SOURCE_DIR%=!
    	xcopy /S /I /Y /d%date% /exclude:PackBaseExclude.txt "%%F" "%DEST_DIR%!FILE_INTERMEDIATE_DIR!" 
    )
)

:: Compression

echo Compressing files...
SLEEP 2

checker\7za.exe a -mx=9 -mmt=on AND2_PACK_UPDATE_XX.7z ..\temp\Assets\

echo Cleaning folder...
SLEEP 2

rd /s/q "..\temp\"
DEL -y PackBaseExclude.txt

PAUSE