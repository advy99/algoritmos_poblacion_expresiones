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

En lugar de utilizar estructuras lineales para representar cromosómas (vectores de enteros, de bits, de valores reales, etc) como en algoritmos evolutivos, algoritmos genéticos y otras estrategias evolutivas utilizaremos una representación con estructuras no lineales, árboles.

En los modelos que usan representaciones lineales el tamaño de los cromosómas es siempre fijo a un tamaño, en el caso de los árboles en PG puede varirar al modificar la profundidad y anchura del árbol.


La representación de programas en forma de árboles se puede realizar utilizando una gramática libre del contexto (definida en la Jerarquía de Chomsky) que defina las sentencias válidas del lenguaje.

PG puede directamente gestionar las expresiones del árbol y las reglas necesarias para evalauarlas, por lo que no será necesario hacer ninguna referencia al lenguaje libre de contexto que la genera.

Un cromosóma codificará la expresión en forma de árbol usando métodos de representación de árboles, normalmente en preorder.


Para poder realizar la representación necesitamos definir dos conjuntos:

- Conjunto T: Variables y constantes del problema. Ej: x_1, x_2, constantes, etc.
- Conjunto S: Funciones e instrucciones del programa. Ej: +, -, \*, /, if-then-else, etc.

S y T deben contener todo lo necesario para resolver el problema en cuestión a resolver. (En mi caso particular tendré que realizar un estudio del problema, un enfoque de como resolverlo, y de ahí obtener todo lo necesario para estos conjuntos).

Se suelen seguir estas reglas generales:

- Toda variable o constante $t \in T$ es una expresión correcta.
- f(e_1, ..., e_n) es una expresión correcta si $f \in F$, $aridad(f) = n$ y e_1, ... e_n son expresiones correctas.
- No existen otras formas de expresiones correctas.

En general, las expresiones de PG no están tipadas, como propiedad, toda función debe aceptar cualquier símbolo terminal y cualquier tipo de dato devuelto por otra función como parámetro.

(Mirar ejemplos de todo esto en las diapositivas)


### Función de ajuste

### Generación de la población inicial

### Operadores genéticos en progracación genética

### The bloat problem (no se me ocurre como traducirlo, ¿el problema de la sobrecarga, tal vez?)


## Bibliografía

- Diapositivas de Oscar Cordón
