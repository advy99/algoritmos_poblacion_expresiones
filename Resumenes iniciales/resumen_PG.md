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

Normalmente como operador de cruce se suele utilizar una recombinación de subárboles escogidos de forma aleatoria entre los dos padres.

Este método tendrá dos parámetros:

- Probabilidad p_{c} de escoger recombinación contra mutación.
- Probabilidad de escoger un unto interno de cada padre como punto de cruce( Uno para cada árbol? imagino que si, preguntar aun así. las hojas tambien pueden contar como subárbol? si el punto que escogemos es un símbolo terminal, el del otro árbol también ha de ser terminal, o se puede reparar de alguna forma?).

El tamaño de los hijos generados puede superar el tamaño de los padres.


##### Selección de puntos de cruce

El algoritmo para seleccinar el punto de corte es más eficiente si la probabilidad de cada punto no es uniforme, es decir, si la sesgamos siguiendo unos criterios:

- Los arcos conectados a símbolos terminales tendrán una probabilidad menor que los arcos conectados a funciones.
- La regla general es que la probabilidad de seleccionar arcos con símbolos terminales ha de ser menor a 1/#arcos\_en\_el\_arbol.

Por este motivo los hijos son más distintos de los padres.

Cuando el punto de cruce ha sido seleccionado en el primer árbol una decisión aleatoria queda sesgada de cara a decidir el punto de cruce del segundo árbol para verificar las siguientes restricciones:

- La recombinación ha de ser con un subárbol con tipos compatibles (si es PG tipada).
- Asegurarse obtener un subárbol de un tamaño apropiado.

##### Aspectos importantes de cara a la implementación del cruce

Existe una dificultad para determinar el subárbol a intercambiar en la codificación de preorder del árbol.

La operación se puede implementar de dos formas distintas.

- Aplicando las producciones de la gramática para obtener la codificación del árbol, deteniendose en un punto aleatorio y considerar que el resto del árbol que queda por generar es el que se va a intercambiar.
- Escoger un punto aleatorio en la representación, determinar el inicio y fin del subárbol asociado en la representación en preorder y ese será el subárbol a intercambiar.


##### Diferencias entre el cruce de AG y PG

El cruce en PG es más brusco que en AG.

Cuando aplicamos el cruce en dos individuos iguales, en PG rara ver se generan dos hijos iguales, mientras que en AG esto suele ocurrir muy a menudo.

Esto implica que la recombinación de dos árboles bien ajustados y que son similares (el algoritmo esta cercano a la convergencia) no implica necesariamente que nos lleve a dos buenos descendientes.

Por estos motivos, el algoritmo explora el espacio de búsqueda de una forma apropiada pero no lo explota tanto como nos gustaría.

Esto nos llevará a que normalmente el tamaño de las poblaciones utilizadas en PG es mucho más grande que en AG.

#### Mutación

La más común suele ser el reemplazamiento de un subárbol por otro árbol generado de forma aleatoria.

El tamaño del hijo puede ser mayor que el tamaño del padre.

La mutación cuenta con dos parámetros:

- Probabilidad $p_m$ de escoger mutación contra recombinación. (debería ser 1-p_c, no? porque si mal no he entendido escogemos uno u otro, nunca ambos).
- Probabilidad de escoger cierto nodo como raíz del subárbol donde realizar el reemplazamiento.

Usualmente se utiliza un valor de $p_m$ cercano a 0, como 0.05.

El hecho de que la mutación sea menos importante en PG que en AG es que el cruce en PG de por si ya nos asegura una gran diversidad por los motivos ya explicados, de hecho, esta mutación es equivalente a recombinar el árbol acual con otro generado de forma aleatoria.




### The bloat problem (no se me ocurre como traducirlo, ¿el problema de la sobrecarga, tal vez?)

Este problema se da cuando sobrevive la solución más sobrecargada, en nuestro caso, cuando sobrevive el árbol con mayor tamaño, y esto hace que con las generaciones el tamaño de las soluciones se vea incrementado de forma significativa.

Necesitamos medidas para paliar este problema:

- Prohibir variaciones de operadores que generen hijos demasiado grandes.

- Ejercer presión sobre estas soluciones: Penalizar el tamaño de una solución por ser demasiado grande, tratando el tamaño como una restricción débil.



## Ejemplos de aplicación: Regresión simbólica

### Introducción a la regresión simbólica

Las distintas técnicas de regresión nos permiten derivar expresiones matemáticas $g$ que modelan el comportamiento de un sistema del que tenemos su entrada y salida.

Las técnicas clásicas de regresión requieren una expresión especificada a priori, por ejemplo, lineal, cuadrática, exponencial, logarítmica, etc, y simplemente se determinan los coeficientes de la expresión utilizando técnicas de optimización para estimar estos coeficientes.

La regresión simbólica es capaz de automáticamente obtener tanto la estructura de la expresión como el valor de sus coeficientes. Es muy util para sistemas no lineales de identificación (identificación de estructuras y estimación de parámetros).

Las técnicas de inducción de los programas pueden ser aplicadas para determinar la expresión algebráica de $g$, aunque esto requiere que se codifique la expresión de forma adecuada (usando por ejemplo una representación basada en árboles) y aplicar un algoritmo de Programación Genética.

Por este motivo la Regresión Simbólica es la principal aplicación de la Programación Genética.

### Regresión Simbólica utilizando Programación Genética


La expresión a encontrar $g$ es más simple si se tienen en cuenta las constantes numéricas, al reducir el número de variables. El valor de estas constantes son escogidos al azar al generar la población inicial de programas.

Esto nos genera el problema de que los valores de estas constantes solo puede ser modificado por las mutaciones. Como consecuencia, el obtener los valores óptimos será mucho más dificil.


## Programación Genética y Algoritmos Genéticos: El modelo GA-P

### Introducción a GA-P

La forma en la que PG trabaja con constantes aleatorias puede ser mejorada utilizando las siguientes medidas:

- Modificar la mutación de PG de forma que los coeficientes reales sean mutados como el operador de mutación de un AG.
- Incorporar métodos de optimización de coeficientes antes de evaluar las expresiones (PG hibrida).
- Evaluar de forma conjunta las expresiones (PG) y las constantes (AG) mediante un algoritmo GA-P.


### Representación de programas en GA-P

Los algoritmos GA-P son una hibridación entre GA y PG.

Cada individuo contendrá una expresión (PG) y un array de coeficientes (GA), de forma que ambas partes evolucionen a la vez.

### Operadores genéticos en GA-P

Los operadores de cruce y mutación son aplicados de forma independiente en las componenes de AG y PG del algoritmo GA-P. Las probabilidades de cruce y mutación de cada componente son independientes.

Es posible utilizar cualquier tipo de esquema de selección y reemplazamiento. La propuesta original consideraba selección por torneo y reemplazamiento estacionario.

### Ventajas de los algoritmos GA-P

- Pueden gestionar tanto información numérica como simbólica.
- Mayor precisión en los resultados finales.
- El tamaño de la población de GA-P puede ser menor que en PG, y por lo tanto mostrará una convergencia más rápida.
- Representación más compacta, se adapta mejor al problema que PG.

### Algunas consideraciones del comportamiento de los algoritmos GA-P

La población de GA-P evoluciona hasta organizarse en varias subpoblaciones compuestas por individuos con la misma expresión (PG) y distintos coeficientes (AG).

Estos individuos compiten entre si y con individuos de las otras subpoblaciones. Esto hace que el tamaño de la población sea dinámico como en AG, ya que al principio pueden coexistir distintas expresiones, pero finalmente solo la subpoblación con la mejor expresión sobrevive.

Esto hace que al principio el algoritmo se comporte como PG y al final como un AG.

Se puede conseguir un comportamiento más compacto utilizando una aproximación evolutiva multimodal (niching).


## Aplicaciones


## Bibliografía

- Diapositivas de Oscar Cordón
