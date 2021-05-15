@echo off
@REM Se parte de que la carpeta del proyecto eśta
@REM ubicada dos niveles por encima de la del script
set REL=..\..
@REM  averigua el directorio que aloja el script
set SCRIPT_DIR=%~d0%~p0
@REM deduce el directorio del proyecto según REL
set PROJECT_DIR=%SCRIPT_DIR%%REL%
@REM  establece el directorio de construcción y lo crea si no existe.
set BUILD_DIR=%PROJECT_DIR%\build
IF NOT EXIST %BUILD_DIR% mkdir "%BUILD_DIR%"

call "%SCRIPT_DIR%\build.bat"
if errorlevel 1 exit /B %errorlevvel%

cd "%BUILD_DIR%"
.\app.exe
echo --------------------------------------------------------------------------------
cd "%PROJECT_DIR%"


