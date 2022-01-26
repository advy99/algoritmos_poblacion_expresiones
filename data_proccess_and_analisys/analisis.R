library(tidyverse)
library(ggplot2)
library(GGally)
library(RColorBrewer)

leer_datos <- function(nombre_fichero, has_header = FALSE) {
	datos <- read.csv(nombre_fichero, comment.char = "@", header = has_header)
	
	if (ncol(datos) == 10) {
		names(datos) <- c("ArticularFace", "IrregularPorosity", "UpperSymphysialExtremity",
						  "BonyNodule", "LowerSymphysialExtremity", "DorsalMargin", 
						  "DorsalPlaeau", "VentralBevel", "VentralMargin", "ToddPhase")
		
	} else {
		names(datos) <- c("ArticularFace", "IrregularPorosity", "UpperSymphysialExtremity",
						  "BonyNodule", "LowerSymphysialExtremity",
						  "DorsalPlaeau", "VentralBevel", "VentralMargin", "ToddPhase")
	}
	 
	

	datos$ArticularFace <- as.ordered(datos$ArticularFace)
	levels(datos$ArticularFace) <- c("RegularPorosity","RidgesFormation","RidgesAndGrooves",
									 "GroovesShallow","GroovesRest","NoGrooves")
	
	datos$IrregularPorosity <- as.ordered(datos$IrregularPorosity)
	levels(datos$IrregularPorosity) <- c("Absence","Medium","Much")
	
	datos$UpperSymphysialExtremity <- as.factor(datos$UpperSymphysialExtremity)
	datos$BonyNodule <- as.factor(datos$BonyNodule)
	datos$LowerSymphysialExtremity <- as.factor(datos$LowerSymphysialExtremity)
	
	if ("DorsalMargin" %in% names(datos) ) {
		datos$DorsalMargin <- as.factor(datos$DorsalMargin)
	}
	
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
	
	datos
}

comprobar_distribuciones <- function(datos, nombre_dataset) {
	
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
	
	
	
	for (nombre in names(datos)[-ncol(datos)]) {
		ggplot(datos, aes_string(x = nombre, fill = "ToddPhase")) +
			geom_bar(stat = "count") + 
			scale_fill_brewer(palette = "BrBG", direction = -1) +
			labs(title = paste("Distribución de valores para", nombre, "en el dataset", nombre_dataset), y = "Número de observaciones")
		ggsave(paste("graficas/datos/densidad_", nombre, "_", nombre_dataset ,".png", sep = ""), device = png, width = 1920, height = 1080, units = "px", dpi = 150)
	}
	
	
	
}

train_test_split <- function(datos, porcentaje_test = 0.2){
	indices_test <- sample(1:nrow(datos), nrow(datos) * porcentaje_test)
	
	resultado <- list(train = datos[-indices_test, ], test = datos[indices_test, ])
	resultado
}

completo <- leer_datos("datos/completo.arff")
lateralidad0 <- leer_datos("datos/lateralidad0-original.arff")
lateralidad1 <- leer_datos("datos/lateralidad1-original.arff")


comprobar_distribuciones(completo, "completo")
comprobar_distribuciones(lateralidad0, "lateralidad_izquierda")
comprobar_distribuciones(lateralidad1, "lateralidad_derecha")


completo <- completo %>% select(!DorsalMargin)
lateralidad0 <- lateralidad0 %>% select(!DorsalMargin)
lateralidad1 <- lateralidad1 %>% select(!DorsalMargin)

set.seed(1)


separacion_completo <- train_test_split(completo, 0.2)
separacion_l0 <- train_test_split(lateralidad0, 0.2)
separacion_l1 <- train_test_split(lateralidad1, 0.2)


write.csv(separacion_completo$train, "datos/completo_train.csv", quote = FALSE, row.names = FALSE)
write.csv(separacion_completo$test, "datos/completo_test.csv", quote = FALSE, row.names = FALSE)


write.csv(separacion_l0$train, "datos/lateralidad0_train.csv", quote = FALSE, row.names = FALSE)
write.csv(separacion_l0$test, "datos/lateralidad0_test.csv", quote = FALSE, row.names = FALSE)

write.csv(separacion_l1$train, "datos/lateralidad1_train.csv", quote = FALSE, row.names = FALSE)
write.csv(separacion_l1$test, "datos/lateralidad1_test.csv", quote = FALSE, row.names = FALSE)



completo_SMOTE <- leer_datos("datos/completo_train_SMOTE.csv", has_header = TRUE)


comprobar_distribuciones(completo_SMOTE, "completo_SMOTE")

completo_BLSMOTE <- leer_datos("datos/completo_train_BL.csv", has_header = TRUE)


comprobar_distribuciones(completo_BLSMOTE, "completo_BL_SMOTE")

