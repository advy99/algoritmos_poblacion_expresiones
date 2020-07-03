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

La función de ajuste en PG debe ser una medida de la habilidad para resolver el problema del programa codificado.

En principio será necesaria una evaluación recursiva de las expresiones de los árboles. Se hará dando valores a las hojas del árbol y aplicando las operaciones del árbol, recorriendolo de abajo hasta arriba y finalmente devolver el valor asociado a la raíz del árbol.

Aun así la evaluación se puede implementar de forma iterativa, utilizando una estructura de datos de tipo pila para recorrer el árbol en preorder y realizar todas las operaciones.

Existe una gran diferencia entre la evaluación de los árboles para ajustar los datos y los árboles (programas) que realmente se pueden ejecutar.

La ejecución puede cambiar el entorno, al calcular el ajuste.

Los cálculos del ajuste realizados en forma de simulaciones requerirán mucha cantidad de tiempo, aunque normalmente las formas evolucionadas (?) son muy buenas.

### Generación de la población inicial

Esta basada en la generación aleatoria de programas (árboles de expresiones), que pueden ser tanto directos como no directos:

Para generar un árbol aleatorio las reglas de la gramática que generará los árboles serán aplicadas de forma progresiva y aleatoria, de forma directa o implicita.

Los programas generados aleatoriamente son:

- Distintos tamaños y formas.
- Sintacticamente válidos.
- Ejecutables.

También es necesario establecer un límite máximo de profundidad para los árboles $D_{max}$.

Existen dos métodos.

- Árboles completos: Todas las ramas tienen profundidad $ = D_{max}$
	- Nodos con profundidad $d < D_{max}$ escogen un elemento aleatorio de símbolos no terminales (conjunto F).
	- Nodos con profundidad $d = D_{max}$ escogen un elemento aleatorio de elementos terminales (conjunto T).
- Árboles incompletos: Todas las ramas tienen una profundidad $\leq D_{max}$.
	- Nodos con profundidad d < D_{max} escogen un elemento aleatorio de simboles terminales o no terminales. $F \cup T$

Normalmente en PG se suelen utilizar ámbos métodos para mayor diversidad, la mitad de la población será generada con árboles completos y la otra mitad con incompletos.

Para añadir más diversidad es posible:
- Generar un porcentaje de árboles aleatorios de cada tamaño valido.
- Generar árboles totalmente aleatorios haciendo uso de símbolos terminales.


### Operadores genéticos en programación genética

#### Selección y reemplazamiento

La selección de padres es normalmente proporcional al ajuste (por torneo).

En grandes poblaciones necesitaremos medidas más fuertes para incrementar la eficiencia:

- Ordenar la población por ajuste y dividirla en dos grupos.
- Grupo 1: x% mejor de la población.
- Grupo 2: 100-x% de la población.
- El 80% de los elementos seleccionados será del grupo 1, el 20% restante del grupo 2.
- Para poblaciones de tamaño 1.000, 2.000, 4.000 y 8.000 normalmente utilizaremos $x = 32%, 16%, 8%, 4%$ respectivamente.

Para el reemplazamiento utilizaremos el esquema generacional (una generación sustituye por completo a la siguiente) con elitismo (mantenemos la mejor solución de la generación anterior en la siguiente).

Recientemente el reemplazamiento estacionario se esta volviendo popular por su elitismo.

Es esquema de generación de hijos es distinto al esquema utilizado por AG. Los AG utilizan un esquema de cruce y mutación, ambos probabilisticos, en PG utilizaremos cruce o mutación, no ambos a la vez, y escogeremos cual de los dos utilizar de forma probabilistica.

Esto tendrá un impacto en como serán los operadores genéticos en PG.

#### Cruce



### The bloat problem (no se me ocurre como traducirlo, ¿el problema de la sobrecarga, tal vez?)


## Bibliografía

- Diapositivas de Oscar Cordón
