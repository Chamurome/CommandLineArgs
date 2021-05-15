@echo off
cls
@REM Se parte de que la carpeta del proyecto eśta
@REM ubicada dos niveles por encima de la del script
set REL=..\..
@REM  averigua el directorio que aloja el script
set SCRIPT_DIR=%~d0%~p0
@REM deduce el directorio del proyecto según REL
set PROJECT_DIR=%SCRIPT_DIR%%REL%

cd "%PROJECT_DIR%"

rd build /s /Q
