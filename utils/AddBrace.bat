@echo off
for /R %%f in (*.cpp,*.c,*.h) do AddBrace.exe %%f

::--indent=tab
AStyle.exe --style=allman --recursive --suffix=none ./*.cpp,*.c,*.h

pause