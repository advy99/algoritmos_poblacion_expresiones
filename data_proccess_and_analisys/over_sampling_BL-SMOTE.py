#!/usr/bin/env python

import imblearn.over_sampling
import sklearn as skl
import pandas as pd
import csv
import sys

if len(sys.argv) != 3:
	print("ERROR: Introduzca el nombre del fichero de datos y la ruta de salida")
	exit()

conjunto = sys.argv[1]
salida = sys.argv[2]

csv_header = ""

with open(conjunto) as archivo_csv:
    # leemos del csv
	reader = csv.reader(archivo_csv,  delimiter = ',')
	csv_header = next(reader) 
    # por cada linea
	lineas = [i for i in reader]
	X = [dato[:-1] for dato in lineas]
	y = [dato[-1] for dato in lineas]

# transformamos los datos para poder usarlos con BL-SMOTE
encoder = skl.preprocessing.OrdinalEncoder()
encoder.fit(X)
X = encoder.transform(X)

# aplicamos el BL-SMOTE con los datos como númericos con OrdinalEncoder
oversample = imblearn.over_sampling.BorderlineSMOTE(random_state = 2)
X, y = oversample.fit_resample(X, y)

# hacemos la conversión a la inversa, para tener las categorías que utilizamos nosotros
X = encoder.inverse_transform(X)

f = open(salida, "w")
f.write(",".join(csv_header))
f.write("\n")

i = 0
for dato in X:
	for valor in dato:
		f.write(str(valor))
		f.write(',')
	f.write(y[i])
	f.write("\n")
	i += 1
