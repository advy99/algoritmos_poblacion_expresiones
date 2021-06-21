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

set yrange [0:90]
set xtics 1
set ytics 5
set xlabel "Conjunto de datos"
set ylabel "ECM con 5x2cv"
set grid ytics mytics xtics mxtics lw 2

set style fill solid 0.50 border 0
set style histogram
set style data histogram
set xtics rotate by -45

set title "Comparación entre el conjunto de datos original y con sobremuestreo utilizando PG y una profundidad máxima de árbol de 20"
set term pngcairo enhanced size 1400,1050 font "Helvetica,16"
set output "comparacion_over_pg_20.png"

plot 'datos/resultados_20_over_pg.dat' using 2:xtic(1) ls 3 title "Conjunto de datos original", \
	 '' using 3 ls 4 title "Conjunto de datos con sobremuestreo"

set title "Comparación entre el conjunto de datos original y con sobremuestreo utilizando GA-P y una profundidad máxima de árbol de 20"
set term pngcairo enhanced size 1400,1050 font "Helvetica,16"
set output "comparacion_over_gap_20.png"

plot 'datos/resultados_20_over_gap.dat' using 2:xtic(1) ls 3 title "Conjunto de datos original", \
	 '' using 3 ls 4 title "Conjunto de datos con sobremuestreo"




set title "Comparación entre el conjunto de datos original y con sobremuestreo utilizando PG y una profundidad máxima de árbol de 40"
set term pngcairo enhanced size 1400,1050 font "Helvetica,16"
set output "comparacion_over_pg_40.png"

plot 'datos/resultados_40_over_pg.dat' using 2:xtic(1) ls 3 title "Conjunto de datos original", \
	 '' using 3 ls 4 title "Conjunto de datos con sobremuestreo"

set title "Comparación entre el conjunto de datos original y con sobremuestreo utilizando GA-P y una profundidad máxima de árbol de 40"
set term pngcairo enhanced size 1400,1050 font "Helvetica,16"
set output "comparacion_over_gap_40.png"

plot 'datos/resultados_40_over_gap.dat' using 2:xtic(1) ls 3 title "Conjunto de datos original", \
	 '' using 3 ls 4 title "Conjunto de datos con sobremuestreo"


set title "Comparación entre el conjunto de datos original y con sobremuestreo utilizando PG y una profundidad máxima de árbol de 60"
set term pngcairo enhanced size 1400,1050 font "Helvetica,16"
set output "comparacion_over_pg_60.png"

plot 'datos/resultados_60_over_pg.dat' using 2:xtic(1) ls 3 title "Conjunto de datos original", \
	 '' using 3 ls 4 title "Conjunto de datos con sobremuestreo"

set title "Comparación entre el conjunto de datos original y con sobremuestreo utilizando GA-P y una profundidad máxima de árbol de 60"
set term pngcairo enhanced size 1400,1050 font "Helvetica,16"
set output "comparacion_over_gap_60.png"

plot 'datos/resultados_60_over_gap.dat' using 2:xtic(1) ls 3 title "Conjunto de datos original", \
	 '' using 3 ls 4 title "Conjunto de datos con sobremuestreo"
