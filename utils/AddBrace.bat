@echo off
for /R %%f in (*.cpp,*.c,*.h) do AddBrace.exe %%f

pause