@ECHO off
ECHO #***************************************************************
ECHO #	File : clean.bat
ECHO #
ECHO #	Command lines script:	Clearing output, temporary and log files
ECHO #***************************************************************


@ECHO on

::del *.o /s
del SerialTerminal.chm
del /f /q /s workdir\
rmdir workdir