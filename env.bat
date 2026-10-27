@echo off
set TOOLS=%USERPROFILE%\tools
set PATH=%TOOLS%\git\cmd;%TOOLS%\node;%TOOLS%\sqlite;%PATH%
chcp 65001 >nul
cd /d %USERPROFILE%\egorova
cmd /k
