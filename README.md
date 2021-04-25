# algoritmos_poblacion_expresiones

Este repositorio contiene mi implementación del varios algoritmos de Programación Genética (PG, GA_P) en C++, utilizados en mi Trabajo de Fin de Grado en Ingeniería Informática en la UGR.

# Estructuración del código

El código se estructura en diversos ficheros para realizar el preprocesado, así como un espacio de nombres propio donde se han implementado los algoritmos basados en una población de expresiones.

También existe una clase `Random` que utilizo como generador de números aleatorios utilizando aritmética modular.

## Espacio de nombres para los algoritmos

Este espacio de nombres está compuesto por:

- `algoritmos_poblacion_expresiones::AlgoritmoPoblacion`: Clase abstracta con los elementos comunes de un algoritmo con una población.
- `algoritmos_poblacion_expresiones::Poblacion`: Clase que representa un conjunto de individuos que conforman una población.
- `algoritmos_poblacion_expresiones::Expresion`: Clase que representa una expresión de Programación Genética.
- `algoritmos_poblacion_expresiones::Nodo`: Clase que representa un nodo de una expresión de Programación Genética.
- `algoritmos_poblacion_expresiones::AlgoritmoPG`: Clase que implementa el algoritmo Programación Genética.
- `algoritmos_poblacion_expresiones::Expresion_GAP`: Clase que implementa una expresión de GA-P.
- `algoritmos_poblacion_expresiones::AlgoritmoGA_P`: Clase que implementa el algoritmo GA-P.

En cada una de estas clases encontrarás más información sobre sus componentes y operadores.

# Documentación

Puedes compilar la documentación ejecutando:

```sh
make doc
```

Puedes consultarla abriendo `doc/html/index.html` en tu navegador.

# Compilar

Existen diversas formas de compilar, todas ellas utilizando el comando `make`.

- Sin parámetros (`make`): Compilar con optimización y utilizando OpenMP para añadir paralelismo.
- Target `test` (`make test`): Compilar los test de GTest.
- Target `doc` (`make doc`): Compilar la documentación.
- Target `clean` (`make clean`): Limpiar los objetos tras una compilación.
- Variable `OPTIMIZACION` (`make OPTIMIZACION=3`): Por defecto 3, asignar un nivel de compilación. Los posibles valores son 0, 1, 2, 3 y g.
- Variable `OPENMP` (`make OPENMP=1`): Por defecto 1. Activar o desactivar la compilación con OpenMP, 0 desactivado, 1 activado.
- Variable `DEBUG` (`make DEBUG=0`): Por defecto 0. Activar o desactivar la compilación con símbolos de depuración.
- Variable `GPROF` (`make GPROF=0`): Por defecto 0. Activar o desactivar la compilación con GPROF de cara a hacer profiling al software.

Siempre que se compile se recompilará la documentación, de cara a posibles cambios.

Todas las variables se pueden combinar, por ejemplo, es posible cambiar el nivel de optimización y a la vez desactivar OpenMP.

## Manual make

Puedes consultar todas las opciones del Makefile con el target `help`

```sh
make help
```
