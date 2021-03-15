# PG_ALGS

Este repositorio contiene mi implementación del varios algoritmo de Programación Genética (PG, GA_P, PG basados en reglas, etc) en C++, utilizados en mi Trabajo de Fin de Grado en Ingeniería Informática en la UGR.


# Documentación

Puedes compilar la documentación ejecutando:

```sh
make doc
```

Puedes consultarla abriendo `doc/html/index.html` en tu navegador.

# Compilar

Existen diversas formas de compilar.

- Ejecutando simplemente `make` : Compilar con optimización y utilizando OpenMP para añadir paralelismo.
- Utilizando la variable `debug` : Si definimos `debug` a 1 al compilar(ejecutando `make debug=1`) compilará con símbolos de depuración y sin OpenMP.

Además también podrémos utilizar la variable `GPROF` si queremos compilar para ejecutar `gprof`:

```sh
# podemos usar
make GPROF=1

# o bien
make debug=1 GPROF=1
```

Siempre que compiles se limpiarán los objetos y binarios anteriores.

También se compilará la documentación al compilar con ambas formas.

## Limpiar

Puedes limpiar binarios y objetos con:

```sh
make clean
```

## Compilación con símbolos de depuración

Para compilar con símbolos de depuración y sin optimización ejecuta:

```sh
make debug
```

## Compilación con optimización

Para compilar con optimización ejecuta:

```sh
make
```

## Manual make

Puedes consultar todas las opciones del Makefile con el target `help`

```sh
make help
```



(EN CONSTRUCCION)
