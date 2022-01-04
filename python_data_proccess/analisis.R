library(tidyverse)
library(ggplot2)

datos <- read.csv("datos/completo.arff", comment.char = "@", header = FALSE)

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

