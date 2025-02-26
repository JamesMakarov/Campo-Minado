# Compilador
CC = gcc

# Diretórios dos arquivos-fonte
SRC_DIR = src
BACK_DIR = $(SRC_DIR)/back
INTERFACE_DIR = $(SRC_DIR)/interface

# Arquivos-fonte
SRC_FILES = $(BACK_DIR)/campominado.c $(INTERFACE_DIR)/interface.c $(SRC_DIR)/main.c

# Arquivo de saída
OUTPUT = campominado

# Flags de compilação
CFLAGS = -I $(BACK_DIR) -I $(INTERFACE_DIR)

# Regra principal (compila e executa)
all: clean $(OUTPUT)

# Regra para compilar
$(OUTPUT): $(SRC_FILES)
	@clear
	@echo "Compilando o projeto..."
	@$(CC) -o $(OUTPUT) $(SRC_FILES) $(CFLAGS) >/dev/null 2>&1
	@if [ $$? -ne 0 ]; then echo "Erro na compilação!"; exit 1; fi
	@echo "Compilação concluída com sucesso!"

# Regra para limpar arquivos gerados
clean:
	@rm -f $(OUTPUT)
	@echo "Arquivos de compilação removidos."

# Regra para executar o jogo
run: all
	@echo "Executando o jogo..."
	@./$(OUTPUT)
