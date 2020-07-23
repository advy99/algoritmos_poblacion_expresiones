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

OBJETIVO = $(BIN)/GA_P
OBJETOS = $(OBJ)/random.o $(OBJ)/nodo.o $(OBJ)/expresion.o $(OBJ)/poblacion.o $(OBJ)/GA_P.o $(OBJ)/main.o

N := $(shell echo $(OBJETIVO) $(OBJETOS) | wc -w )
X := 0
SUMA = $(eval X=$(shell echo $$(($(X)+1))))


all: clean INICIO $(OBJETIVO) FIN

DEBUG: FLAGS = --std=c++17 -g -Wall
DEBUG: MENSAJE = "Compilando\ usando\ C++17,\ sin\ optimización,\ con\ todos\ los\ warnings\ activados\ y\ con\ símbolos\ de\ depuración"
DEBUG: all






INICIO:
	@printf "\e[36mComenzando compilación de $(BIN)/GA_P\n\n"
	@printf "\e[94mCompilador: $(CXX)\n"
	@printf "\e[94mFlags del compilador: $(FLAGS)\n\n"
	@printf "\e[94m$(MENSAJE)\n\n"

$(OBJETIVO): $(OBJETOS)
	$(eval X=$(shell echo $$(($(X)+1))))
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el binario $@ a partir de $^\n"
	@$(CXX) $^ -o $@

$(OBJ)/random.o: $(SRC)/random.cpp
	$(eval X=$(shell echo $$(($(X)+1))))
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el objeto $@ a partir de $^\n"
	@$(CXX) -c $(FLAGS) $^ -I$(INC) -o $@

$(OBJ)/main.o: $(SRC)/main.cpp
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el objeto $@ a partir de $^\n"
	@$(CXX) -c $(FLAGS) $^ -I$(INC) -o $@

$(OBJ)/GA_P.o: $(SRC)/GA_P.cpp
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el objeto $@ a partir de $^\n"
	@$(CXX) -c $(FLAGS) $^ -I$(INC) -o $@

$(OBJ)/expresion.o: $(SRC)/expresion.cpp
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el objeto $@ a partir de $^\n"
	@$(CXX) -c $(FLAGS) $^ -I$(INC) -o $@

$(OBJ)/poblacion.o: $(SRC)/poblacion.cpp
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el objeto $@ a partir de $^\n"
	@$(CXX) -c $(FLAGS) $^ -I$(INC) -o $@

$(OBJ)/nodo.o: $(SRC)/nodo.cpp
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el objeto $@ a partir de $^\n"
	@$(CXX) -c $(FLAGS) $^ -I$(INC) -o $@


FIN:
	@printf "\n\e[36mCompilación finalizada con éxito\n"

clean:
	@printf "\e[36mLimpiando el directorio $(OBJ)\n"
	-@rm $(OBJ)/*.o 2> /dev/null || printf "\e[33mEl directorio $(OBJ) está vacio, nada que limpiar\n"
	@printf "\e[36mLimpiando el directorio $(BIN)\n"
	-@rm $(BIN)/* 2> /dev/null || printf "\e[33mEl directorio $(BIN) está vacio, nada que limpiar\n"
	@printf "\e[36mLimpieza completada\n"

documentacion:
	@printf "\e[36mComenzando compilación de la documentación del proyecto\n\e[33m\n"
	@doxygen doc/doxys/Doxyfile
	@printf "\e[36mFinalizada compilación de la documentación. Puedes consultarla en doc/html/index.html\n"
