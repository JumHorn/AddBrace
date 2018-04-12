@echo off
for /R %%f in (*.cpp,*.c,*.h) do AddParenthesis.exe %%f
pause