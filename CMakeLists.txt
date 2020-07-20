# version mínima de CMake

cmake_minimum_required(VERSION 3.10)

# nombre del projecto
project(TFG)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# incluir la carpeta de codigo
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(GA_P ${SOURCES})


add_custom_target(documentacion
	COMMAND doxygen doc/doxys/Doxyfile
		  
)
