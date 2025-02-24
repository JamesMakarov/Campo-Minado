# Nome do executável
EXEC = campominado

# Diretórios
SRC_DIR = src
BACK_DIR = $(SRC_DIR)/back
INTERFACE_DIR = $(SRC_DIR)/interface

# Arquivos fonte
SRC_FILES = $(BACK_DIR)/campominado.c $(INTERFACE_DIR)/interface.c $(SRC_DIR)/main.c

# Flags do compilador
CFLAGS = -I$(BACK_DIR) -I$(INTERFACE_DIR) -Wall -Wextra -Wpedantic

# Comando para compilar
CC = gcc

# Regra padrão: compila o programa
all: $(EXEC)

$(EXEC): $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $(SRC_DIR)/$(EXEC)

# Regra para rodar o jogo após compilar
run: all
	./$(SRC_DIR)/$(EXEC)

# Regra para limpar os arquivos gerados
clean:
	rm -f $(SRC_DIR)/$(EXEC)