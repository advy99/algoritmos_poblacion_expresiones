#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Se necesita un parámetro, el fichero de datos"
	exit -1
fi

TAM_POBLACION=1000
PROB_VAR=0.3
PROFUNDIDAD_MAX=10
NUM_EVALS=1000000
PROB_CRUCE_GP=0.75
PROB_CRUCE_GA=0.75
PROB_MUTACION_GP=0.05
PROB_MUTACION_GA=0.05
PROB_CRUCE_INTRANICHO=0.3
TAM_TORNEO=100
NUM_HILOS=2

mkdir -p salidas_ejecuciones/

semillas=(12345 92034 8324 34679 34634)

for semilla in ${semillas[*]}
do
	./bin/main $1 $TAM_POBLACION $PROB_VAR $PROFUNDIDAD_MAX $NUM_EVALS $PROB_CRUCE_GP $PROB_CRUCE_GA $PROB_MUTACION_GP $PROB_MUTACION_GA $PROB_CRUCE_INTRANICHO $TAM_TORNEO $NUM_HILOS $semilla > salidas_ejecuciones/$(basename ${1})_${semilla}.dat &
done

wait

echo "Ejecutado"
