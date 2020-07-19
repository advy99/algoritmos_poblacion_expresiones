# Trabajo de Fin de Grado

Este repositorio contiene mi trabajo de fin de grado en Ingeniería Informática en la UGR.


# Documentación

Puedes compilar la documentación ejecutando:

```sh
make documentacion
```

Puedes consultarla abriendo `doc/html/index.html` en tu navegador.

# Compilar

Existen dos opciones de compilación.

- Compilación con símbolos de depuración (pensado para depurar).
- Compilación con optimización (pensado para ejecutar).

Siempre que cambies de forma de compilar es recomendable limpiar objetos y binarios anteriores.

## Limpiar

Puedes limpiar binarios y objetos con:

```sh
make clean
```

## Compilación con símbolos de depuración

Para compilar con símbolos de depuración ejecuta:

```sh
make DEBUG=1
```

## Compilación con optimización

Para compilar con optimización ejecuta:

```sh
make
```



(EN CONSTRUCCION)
