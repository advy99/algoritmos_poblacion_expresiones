CXX      = g++
HOME     = .
BIN      = $(HOME)/bin
INC	   = $(HOME)/include
SRC      = $(HOME)/src
OBJ      = $(HOME)/obj
LIB      = $(HOME)/lib
DATOS	   = $(HOME)/datos
GRAFICAS = $(HOME)/graficas/datos

FLAGS = --std=c++17 -O3 -Wall
MENSAJE = "Compilando\ usando\ C++17,\ con\ optimización\ de\ máximo\ nivel\ y\ con\ todos\ los\ warnings\ activados"

all: INICIO $(BIN)/GA_P FIN

DEBUG: FLAGS = --std=c++17 -g -Wall
DEBUG: MENSAJE = "Compilando\ usando\ C++17,\ sin\ optimización,\ con\ todos\ los\ warnings\ activados\ y\ con\ símbolos\ de\ depuración"
DEBUG: all


INICIO:
	@printf "\e[36mComenzando compilación de $(BIN)/GA_P\n\n"
	@printf "\e[94mCompilador: $(CXX)\n"
	@printf "\e[94mFlags del compilador: $(FLAGS)\n\n"
	@printf "\e[94m$(MENSAJE)\n\n"

$(BIN)/GA_P: $(OBJ)/random.o $(OBJ)/nodo.o $(OBJ)/expresion.o $(OBJ)/poblacion.o $(OBJ)/GA_P.o $(OBJ)/main.o
	@printf "\e[31m[7/7] \e[32mCreando el binario $@ a partir de $^\n"
	@$(CXX) $^ -o $@

$(OBJ)/random.o: $(SRC)/random.cpp
	@printf "\e[31m[1/7] \e[32mCreando el objeto $@ a partir de $^\n"
	@$(CXX) -c $(FLAGS) $^ -I$(INC) -o $@

$(OBJ)/main.o: $(SRC)/main.cpp
	@printf "\e[31m[6/7] \e[32mCreando el objeto $@ a partir de $^\n"
	@$(CXX) -c $(FLAGS) $^ -I$(INC) -o $@

$(OBJ)/GA_P.o: $(SRC)/GA_P.cpp
	@printf "\e[31m[5/7] \e[32mCreando el objeto $@ a partir de $^\n"
	@$(CXX) -c $(FLAGS) $^ -I$(INC) -o $@

$(OBJ)/expresion.o: $(SRC)/expresion.cpp
	@printf "\e[31m[3/7] \e[32mCreando el objeto $@ a partir de $^\n"
	@$(CXX) -c $(FLAGS) $^ -I$(INC) -o $@

$(OBJ)/poblacion.o: $(SRC)/poblacion.cpp
	@printf "\e[31m[4/7] \e[32mCreando el objeto $@ a partir de $^\n"
	@$(CXX) -c $(FLAGS) $^ -I$(INC) -o $@

$(OBJ)/nodo.o: $(SRC)/nodo.cpp
	@printf "\e[31m[2/7] \e[32mCreando el objeto $@ a partir de $^\n"
	@$(CXX) -c $(FLAGS) $^ -I$(INC) -o $@


FIN:
	@printf "\e[36mCompilación finalizada con éxito\n"

clean:
	@printf "\e[36mLimpiando el directorio $(OBJ)\n"
	-@rm $(OBJ)/*.o 2> /dev/null || printf "\e[33mEl directorio $(OBJ) está vacio, nada que limpiar\n"
	@printf "\e[36mLimpiando el directorio $(BIN)\n"
	-@rm $(BIN)/* 2> /dev/null || printf "\e[33mEl directorio $(BIN) está vacio, nada que limpiar\n"
	@printf "\e[36mLimpieza completada\n"

documentacion:
	@printf "\e[36mComenzando compilación de la documentación del proyecto\n\e[33m"
	@doxygen doc/doxys/Doxyfile
	@printf "\e[36mFinalizada compilación de la documentación. Puedes consultarla en doc/html/index.html"
