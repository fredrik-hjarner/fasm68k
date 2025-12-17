@echo off
setlocal
set "DIR=%~dp0"
set "INCLUDE=%DIR%fasm2\include;%DIR%src;%INCLUDE%"
"%DIR%fasm2\fasmg.exe" -iInclude 'm68k.inc' %*

