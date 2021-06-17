set style line 1 lc rgb "red"
set style line 2 lc rgb "blue"
set style line 3 lc rgb "green"
set style line 4 lc rgb "royalblue"
set style line 5 lc rgb "plum"
set style line 6 lc rgb "olivedrab"
set style line 7 lc rgb "0x20B2AA"
set style line 8 lc rgb "0x90EE90"
set style line 9 lc rgb "0xADD8E6"

set key right top

set style fill solid
set boxwidth 1

set yrange [0:*]
set xtics 1
set ytics 5
set xlabel "Conjunto de datos"
set ylabel "RECM con 5x2cv"
set grid ytics mytics xtics mxtics lw 2

set style fill solid 0.50 border 0
set style histogram
set style data histogram
set xtics rotate by -45

set title "Comparación entre Programación Genética y GA-P con una profundidad máxima de árbol de 20"
set term pngcairo enhanced size 1400,1050
set output "comparacion_pg_gap_20.png"

plot 'datos/resultados_20.dat' using 2:xtic(1) ls 1 title "PG", \
	 '' using 3 ls 2 title "GA-P"

set title "Comparación entre Programación Genética y GA-P con una profundidad máxima de árbol de 40"
set term pngcairo enhanced size 1400,1050
set output "comparacion_pg_gap_40.png"

plot 'datos/resultados_40.dat' using 2:xtic(1) ls 1 title "PG", \
 	 '' using 3 ls 2 title "GA-P"

set title "Comparación entre Programación Genética y GA-P con una profundidad máxima de árbol de 60"
set term pngcairo enhanced size 1400,1050
set output "comparacion_pg_gap_60.png"

plot 'datos/resultados_60.dat' using 2:xtic(1) ls 1 title "PG", \
	 '' using 3 ls 2 title "GA-P"
