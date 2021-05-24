import pandas as pd
import csv
import smogn
from smogn.over_sampling import over_sampling
import sys
import seaborn
import matplotlib.pyplot as plt


if len(sys.argv) != 3:
	print("ERROR: Introduzca el nombre del fichero de datos y la ruta de salida")
	exit()


caracteristicas = []

for i in range(0, 10):
	caracteristicas.append("C{}".format(i))

print(caracteristicas)

datos = pd.read_csv(sys.argv[1], header=None, names=caracteristicas)


smogn.box_plot_stats(datos['C9'])['stats']
seaborn.kdeplot(datos['C9'], label = "Original")

plt.ylabel("Densidad en el conjunto de datos")
plt.xlabel("Edad")

plt.legend()
plt.show()
plt.clf()
datos.to_csv(sys.argv[2], index = False, header = False)


# buenos resultados entre 0.6 y 0.8 de rel_coef

datos_over_sampling = smogn.smoter(data = datos, y = 'C9', k = 5, pert = 0.02, samp_method = "extreme",
									under_samp = True, drop_na_col = True, drop_na_row = True, replace = False,
									rel_thres = 0.5,
								    rel_method = "auto",
								    rel_xtrm_type = "low",
								    rel_coef = 0.7)

print(datos.shape)
print(datos_over_sampling.shape)

plt.ylabel("Densidad en el conjunto de datos")
plt.xlabel("Edad")

smogn.box_plot_stats(datos['C9'])['stats']
smogn.box_plot_stats(datos_over_sampling['C9'])['stats']

seaborn.kdeplot(datos['C9'], label = "Original")
seaborn.kdeplot(datos_over_sampling['C9'], label = "Modified")

plt.legend()
plt.show()
