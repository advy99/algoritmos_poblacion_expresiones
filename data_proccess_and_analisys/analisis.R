library(tidyverse)
library(ggplot2)
library(GGally)
library(RColorBrewer)

comprobar_distribuciones <- function(nombre_fichero, nombre_dataset = nombre_fichero) {
	
	datos <- read.csv(nombre_fichero, comment.char = "@", header = FALSE)
	
	names(datos) <- c("ArticularFace", "IrregularPorosity", "UpperSymphysialExtremity",
					  "BonyNodule", "LowerSymphysialExtremity", "DorsalMargin", 
					  "DorsalPlaeau", "VentralBevel", "VentralMargin", "ToddPhase")
	
	
	str(datos)
	
	datos$ArticularFace <- as.ordered(datos$ArticularFace)
	levels(datos$ArticularFace) <- c("RegularPorosity","RidgesFormation","RidgesAndGrooves",
									 "GroovesShallow","GroovesRest","NoGrooves")
	
	datos$IrregularPorosity <- as.ordered(datos$IrregularPorosity)
	levels(datos$IrregularPorosity) <- c("Absence","Medium","Much")
	
	datos$UpperSymphysialExtremity <- as.factor(datos$UpperSymphysialExtremity)
	datos$BonyNodule <- as.factor(datos$BonyNodule)
	datos$LowerSymphysialExtremity <- as.factor(datos$LowerSymphysialExtremity)
	datos$DorsalMargin <- as.factor(datos$DorsalMargin)
	datos$DorsalPlaeau <- as.factor(datos$DorsalPlaeau)
	
	datos$VentralBevel <- as.ordered(datos$VentralBevel)
	levels(datos$VentralBevel) <- c("Absent","InProcess","Present")
	
	datos$VentralMargin <- as.ordered(datos$VentralMargin)
	levels(datos$VentralMargin) <- c("Absent","PartiallyFormed","FormedWithoutRarefactions",
									 "FormedWitFewRarefactions","FormedWithLotRecessesAndProtrusions")
	
	datos$ToddPhase <- as.ordered(datos$ToddPhase)
	levels(datos$ToddPhase) <- c("Ph01-19","Ph02-20-21","Ph03-22-24","Ph04-25-26",
								 "Ph05-27-30","Ph06-31-34","Ph07-35-39","Ph08-40-44",
								 "Ph09-45-49","Ph10-50-")
	
	str(datos)
	
	
	summary(datos)
	
	# Todos en dorsal margin son Present, no aporta información!
	which(datos$DorsalMargin != "Present")
	
	ggplot(datos, aes(x = ToddPhase, fill = ToddPhase)) +
		geom_bar(stat = "count") +
		scale_fill_brewer(palette = "BrBG", direction = -1) +
		scale_y_continuous(breaks = seq(0, 300, by = 25)) +
		theme(legend.position = "none") + 
		labs(title = paste("Recuento de observaciones en cada clase en el dataset", nombre_dataset), y = "Número de observaciones")
	ggsave(paste("graficas/datos/distribucion_clases_", nombre_dataset, ".png", sep = ""), device = png, width = 1920, height = 1080, units = "px", dpi = 150)
	
	
	for (nombre in names(datos)[-10]) {
		ggplot(datos, aes_string(x = nombre, fill = "ToddPhase")) +
			geom_bar(stat = "count") + 
			scale_fill_brewer(palette = "BrBG", direction = -1) +
			labs(title = paste("Distribución de valores para", nombre, "en el dataset", nombre_dataset), y = "Número de observaciones")
		ggsave(paste("graficas/datos/densidad_", nombre, "_", nombre_dataset ,".png", sep = ""), device = png, width = 1920, height = 1080, units = "px", dpi = 150)
	}
	
	
	
}

comprobar_distribuciones("datos/completo.arff", "completo")
comprobar_distribuciones("datos/lateralidad0-original.arff", "lateralidad izquierda")
comprobar_distribuciones("datos/lateralidad1-original.arff", "lateralidad derecha")


