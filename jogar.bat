@echo off
cls
echo Compilando o projeto...

gcc -o campominado.exe src/back/campominado.c src/interface/interface.c src/main.c -I src/back -I src/interface

if %errorlevel% neq 0 (
    echo Erro na compilação!
    exit /b %errorlevel%
)

echo Compilação concluída com sucesso!

gcc src/back/campominado.c src/interface/interface.c src/main.c -o campominado

campominado.exe

pause
