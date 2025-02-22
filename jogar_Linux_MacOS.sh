#!/bin/bash

clear
echo "Compilando o projeto..."

gcc -o campominado src/back/campominado.c src/interface/interface.c src/main.c -I src/back -I src/interface

if [ $? -ne 0 ]; then
    echo "Erro na compilação!"
    exit 1
fi

echo "Compilação concluída com sucesso!"
echo "Executando o jogo..."

./campominado
