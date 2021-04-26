set style line 1 pt 2 ps 2 lc rgb "red"
set style line 2 pt 5 ps 2 lc rgb "blue"


set key

set style fill solid

set xlabel "Indice del dato en el conjunto de test"
set grid ytics mytics xtics mxtics lw 1

# lateralidad 0
set title "Valores reales y predecidos por GA-P en Iris"
set term pngcairo dashed size 1400,1050
set output "salidas_png/iris_gap.png"

plot "datos/salida_iris_gap.dat" using 1:2  with p ls 1 title "Valor predecido", "datos/salida_iris_gap.dat" using 1:3  with p ls 2 title "Valor real"

set title "Valores reales y predecidos por Programación Genética en Iris"
set term pngcairo dashed size 1400,1050
set output "salidas_png/iris_gp.png"

plot "datos/salida_iris_gp.dat" using 1:2  with p ls 1  title "Valor predecido", "datos/salida_iris_gp.dat" using 1:3  with p ls 2 title "Valor real"




set title "Valores reales y predecidos por GA-P en el conjunto de datos completo"
set term pngcairo dashed size 1400,1050
set output "salidas_png/completo_gap.png"

plot "datos/salida_completo_final_gap.dat" using 1:2  with p ls 1  title "Valor predecido", "datos/salida_completo_final_gap.dat" using 1:3  with p ls 2 title "Valor real"


set title "Valores reales y predecidos por Programación Genética en el conjunto de datos completo"
set term pngcairo dashed size 1400,1050
set output "salidas_png/completo_gp.png"

plot "datos/salida_completo_final_gp.dat" using 1:2  with p ls 1  title "Valor predecido", "datos/salida_completo_final_gp.dat" using 1:3  with p ls 2 title "Valor real"
