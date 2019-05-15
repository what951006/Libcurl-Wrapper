@echo off
cd %~dp0
SETLOCAL ENABLEDELAYEDEXPANSION

echo Begin build Debug
echo #################
call :BuildProject QAQNetwork\QAQNetwork.vcxproj Debug

echo Begin build Debug-Static
echo #################
call :BuildProject QAQNetwork\QAQNetwork.vcxproj Debug-Static

echo Begin build Release
echo #################
call :BuildProject QAQNetwork\QAQNetwork.vcxproj Release

echo Begin build Release-Static
echo #################
call :BuildProject QAQNetwork\QAQNetwork.vcxproj Release-Static

copy QAQNetwork\QAQNetwork.h ..\include\QAQNetwork.h
pause

:BuildProject
call "C:\Progra~2\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
MSBuild %1 /t:Rebuild /p:Configuration=%2 /p:Platform=x86
goto :eof