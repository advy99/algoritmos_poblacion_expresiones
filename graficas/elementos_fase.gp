set style line 1 lc rgb "red"
set style line 2 lc rgb "blue"
set style line 3 lc rgb "green"
set style line 4 lc rgb "royalblue"
set style line 5 lc rgb "plum"
set style line 6 lc rgb "olivedrab"
set style line 7 lc rgb "0x20B2AA"
set style line 8 lc rgb "0x90EE90"
set style line 9 lc rgb "0xADD8E6"

unset key

set style fill solid
set boxwidth 0.5

set xrange [0:11]
set xtics 1
set ytics 25
set xlabel "Clase"


# lateralidad 0
set title "Distribución de los datos originales de la lateralidad izquierda según su clase"
set term pngcairo dashed size 1400,1050
set output "salidas_png/num_elementos_fase_l0.png"

plot for[i=0:9] "../datos/conteo_clases/conteo_clases_l0_original.dat" every ::i::10 using 1:2  with boxes ls i

set title "Distribución de los datos de la lateralidad izquierda según su clase tras aplicar BorderlineSMOTE"
set term pngcairo dashed size 1400,1050
set output "salidas_png/num_elementos_fase_l0_BL-SMOTE.png"

set yrange [0:150]

plot for[i=0:9] "../datos/conteo_clases/conteo_clases_l0.dat" every ::i::10 using 1:2  with boxes ls i


# lateralidad 1
set title "Distribución de los datos originales de la lateralidad derecha según su clase"
set term pngcairo dashed size 1400,1050
set output "salidas_png/num_elementos_fase_l1.png"

plot for[i=0:9] "../datos/conteo_clases/conteo_clases_l1_original.dat" every ::i::10 using 1:2  with boxes ls i

set title "Distribución de los datos de la lateralidad derecha según su clase tras aplicar BorderlineSMOTE"
set term pngcairo dashed size 1400,1050
set output "salidas_png/num_elementos_fase_l1_BL-SMOTE.png"

set yrange [0:150]

plot for[i=0:9] "../datos/conteo_clases/conteo_clases_l1.dat" every ::i::10 using 1:2  with boxes ls i


# completo
set title "Distribución de los datos originales del conjunto completo según su clase"
set term pngcairo dashed size 1400,1050
set output "salidas_png/num_elementos_fase_completo.png"

set yrange [0:300]


plot for[i=0:9] "../datos/conteo_clases/conteo_clases_completo_original.dat" every ::i::10 using 1:2  with boxes ls i

set title "Distribución de los datos de la lateralidad derecha según su clase tras aplicar BorderlineSMOTE"
set term pngcairo dashed size 1400,1050
set output "salidas_png/num_elementos_fase_completo_BL-SMOTE.png"

set yrange [0:300]

plot for[i=0:9] "../datos/conteo_clases/conteo_clases_completo.dat" every ::i::10 using 1:2  with boxes ls i
