# Resumen Programación genética (Diapositivas de Oscar Cordón)

## Introducción

Programación Genética: Puede ser definida como una instancia específica de algoritmo genético para inducir programas en ordenadores de forma automática, no es necesario especificar como ha de hacerlo.

Comenzo sobre 1985, aunque el principal impulso fue por parte de John Koza a principios de los 90.

La diferencia entre Algoritmos Genéticos y Programación Genética esta en la representación: Los cromosómas son programas de ordenador. Los operadores genéticos se han de adaptar a esta representación.


Normalmente en Programación Genética:

- Representación: Estructuras de árboles.
- Cruce: Intercambio de subárboles.
- Mutaciones: Cambios aleatorios en los árboles.
- Selección de padres: Ajuste proporcional (? Preguntar qué es)
- Selección de supervivientes: Generacional o reemplazo fijo

Usaré PG para referirme a Programación Genética y AG para referirme a Algoritmos Genéticos.


## Descripción general. Representación y operadores

### Representación de los programas

PG aplica AG en el campo de programas para ordenadores.

Un programa es un lenguaje general para expresar soluciones a gran variedad de problemas.

Gran variedad de problemas de muchos ámbitos se pueden reformular para que se conviertan en problemas de búsqueda que un programa de ordenador pueda resolver.

Teoricamente todos los problemas de IA, Machine Learning y sistemas adaptativos pueden adaptarse a problemas de búsqueda para un ordenador.

Existen diferentes formas de representar programas de ordenador en PG:

- Árboles de expresiones.
- Secuencias de instrucciones para Autómatas Finitos (imagino que además deterministas).
- Secuencias de instrucciones en código máquina.

La más extendida es la representación basada en árboles.

PG normalmente trabaja con programas simples, que no consideran bucles, aunque existen implementaciones más avanzadas.




### Representación basáda en árboles

Los árboles son una representación universal, algunos ejemplos interesantes para los que podemos utilizar esta representación son:

- Fórmulas aritméticas.
- Fórmulas lógicas.
- Programas escritos en C (o cualquier otro lenguaje).


### Función de ajuste

### Generación de la población inicial

### Operadores genéticos en progracación genética

### The bloat problem (no se me ocurre como traducirlo, ¿el problema de la sobrecarga, tal vez?)


## Bibliografía

- Diapositivas de Oscar Cordón
