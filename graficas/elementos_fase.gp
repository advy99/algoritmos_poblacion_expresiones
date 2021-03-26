set style line 1 lc rgb "red"
set style line 2 lc rgb "blue"
set style line 3 lc rgb "green"
set style line 4 lc rgb "royalblue"
set style line 5 lc rgb "plum"
set style line 6 lc rgb "olivedrab"
set style line 7 lc rgb "0x20B2AA"
set style line 8 lc rgb "0x90EE90"
set style line 9 lc rgb "0xADD8E6"
set style line 10 lc rgb "0xE9967A"

unset key

set style fill solid
set boxwidth 0.5

set xrange [0:11]
set xtics 1
set ytics 25
set xlabel "Clase"


set title "Distribución de los datos originales según su clase"
set term pngcairo dashed size 1400,1050
set output "salidas_png/num_elementos_fase.png"

plot for[i=0:9] "datos/num_elementos_fase.dat" every ::i::10 using 1:2  with boxes ls i
