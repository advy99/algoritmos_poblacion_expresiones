HOME     = .
BIN      = $(HOME)/bin
INC	   = $(HOME)/include
SRC      = $(HOME)/src
OBJ      = $(HOME)/obj
LIB      = $(HOME)/lib
DATOS	   = $(HOME)/datos
GRAFICAS = $(HOME)/graficas/datos

DEBUG=0

ifeq ($(DEBUG),0)
FLAGS = --std=c++17 -O3 -Wall
else
FLAGS = --std=c++17 -g -Wall
endif

all: $(BIN)/GA_P

$(BIN)/GA_P: $(OBJ)/random.o $(OBJ)/main.o
	g++ $^ -o $@

$(OBJ)/random.o: $(SRC)/random.cpp
	g++ -c $(FLAGS) $^ -I$(INC) -o $@

$(OBJ)/main.o: $(SRC)/main.cpp
	g++ -c $(FLAGS) $^ -I$(INC) -o $@


clean:
	-rm $(OBJ)/*.o
	-rm $(BIN)/*


documentacion:
	doxygen doc/doxys/Doxyfile

