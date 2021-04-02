#!/usr/bin/env python

from imblearn.over_sampling import BorderlineSMOTE
import pandas as pd
import csv

conjuntos = ["salida.dat"]
nombres_salida = ["salida_over_sampling.dat"]

for conjunto, salida in zip(conjuntos, nombres_salida):
	with open(conjunto) as archivo_csv:
        # leemos del csv
		reader = csv.reader(archivo_csv,  delimiter = ',')
        # por cada linea
		lineas = [i for i in reader]
		X = [dato[:-1] for dato in lineas]
		y = [dato[-1] for dato in lineas]

	oversample = BorderlineSMOTE()
	X, y = oversample.fit_resample(X, y)

	X = [ list(map(lambda x: round(x), dato)) for dato in X]

	print(len(X))
	print(len(y))

	f = open(salida, "w")

	i = 0
	for dato in X:
		for valor in dato:
			f.write(str(valor))
			f.write(',')
		f.write(y[i])
		f.write("\n")
		i += 1
