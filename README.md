# GA_P

Este repositorio contiene mi implementación del algoritmo GA_P en C++, utilizado en mi Trabajo de Fin de Grado en Ingeniería Informática en la UGR.


# Documentación

Puedes compilar la documentación ejecutando:

```sh
make doc
```

Puedes consultarla abriendo `doc/html/index.html` en tu navegador.

# Compilar

Existen dos opciones de compilación.

- Compilación con símbolos de depuración (pensado para depurar).
- Compilación con optimización (pensado para ejecutar).

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
