MAIN := main

# Pastas
INCLUDES := includes
SRC := src

# Objetos a compilar
OBJECTS := $(MAIN).o $(SRC)/Aluno.o $(SRC)/Indice.o $(SRC)/SistemaGerenciador.o

# Flags do compilador
FLAGS := -Wall -Wextra -std=c++17 -pedantic-errors -I$(INCLUDES)

# Debug
DEBUG := -g

# Bibliotecas extras
MATH := -lm

# Compilador
CC := g++

# Ajuste para SO
ifeq ($(OS), Windows_NT)
OUTPUTMAIN := $(MAIN).exe
else
OUTPUTMAIN := $(MAIN).out
endif

# Alvo principal
all: $(OUTPUTMAIN)
	@echo Compiling 'all' complete!

# Linkagem final
$(OUTPUTMAIN): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(OUTPUTMAIN) $(MATH)

# Regras de compilação dos objetos
$(MAIN).o: $(MAIN).cpp $(INCLUDES)/Aluno.hpp $(INCLUDES)/Indice.hpp $(INCLUDES)/SistemaGerenciador.hpp
	$(CC) $(FLAGS) -c $(MAIN).cpp -o $(MAIN).o

$(SRC)/Aluno.o: $(SRC)/Aluno.cpp $(INCLUDES)/Aluno.hpp
	$(CC) $(FLAGS) -c $(SRC)/Aluno.cpp -o $(SRC)/Aluno.o

$(SRC)/Indice.o: $(SRC)/Indice.cpp $(INCLUDES)/Indice.hpp
	$(CC) $(FLAGS) -c $(SRC)/Indice.cpp -o $(SRC)/Indice.o

$(SRC)/SistemaGerenciador.o: $(SRC)/SistemaGerenciador.cpp $(INCLUDES)/SistemaGerenciador.hpp $(INCLUDES)/Aluno.hpp $(INCLUDES)/Indice.hpp
	$(CC) $(FLAGS) -c $(SRC)/SistemaGerenciador.cpp -o $(SRC)/SistemaGerenciador.o

# Limpeza
clean:
	rm -rf $(OBJECTS)
	rm -rf $(OUTPUTMAIN)
	@echo Cleanup complete!!!

# Executar
run: all
	./$(OUTPUTMAIN)
	@echo Executing 'all' complete!!!
