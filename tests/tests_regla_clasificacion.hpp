#ifndef TESTS_REGLA_CLASIFICACION
#define TESTS_REGLA_CLASIFICACION

#include <gtest/gtest.h>
#include "algoritmos_poblaciones/ReglaClasificacion.hpp"

TEST (ReglaClasificacion, IgualElMismo) {
	algoritmos_poblacion_expresiones::ReglaClasificacion regla;

	EXPECT_EQ(regla, regla);
}

TEST (ReglaClasificacion, CambiarClase) {
	algoritmos_poblacion_expresiones::ReglaClasificacion regla;
	EXPECT_TRUE(regla.consultar_clase() == "");

	regla.cambiar_clase("Clase1");

	EXPECT_TRUE(regla.consultar_clase() == "Clase1");

}

TEST (ReglaClasificacion, InsertarAntecedentes) {
	algoritmos_poblacion_expresiones::ReglaClasificacion regla;

	regla.modificar_antecedente("ANT1", "VALOR1");

	EXPECT_EQ(regla.consultar_antecedente("ANT1"), "VALOR1");


}

TEST (ReglaClasificacion, ConsultarNumAntecedentesVacio) {
	algoritmos_poblacion_expresiones::ReglaClasificacion regla;


	EXPECT_EQ(regla.num_antecedentes(), 0);

}


TEST (ReglaClasificacion, ConsultarNumAntecedentes) {
	algoritmos_poblacion_expresiones::ReglaClasificacion regla;

	regla.modificar_antecedente("ANT1", "VALOR1");
	regla.modificar_antecedente("ANT2", "VALOR2");
	regla.modificar_antecedente("ANT3", "VALOR3");
	regla.modificar_antecedente("ANT4", "VALOR4");

	EXPECT_EQ(regla.num_antecedentes(), 4);

}

TEST (ReglaClasificacion, ConvertirString) {
	algoritmos_poblacion_expresiones::ReglaClasificacion regla;

	regla.modificar_antecedente("ANT1", "VALOR1");
	regla.modificar_antecedente("ANT2", "VALOR2");

	regla.cambiar_clase("Clase1");

	EXPECT_EQ(regla.como_string(), "IF ANT1 IS VALOR1 AND ANT2 IS VALOR2 THEN CLASS IS Clase1");
}


TEST (ReglaClasificacion, DatoCoincideConRegla) {
	algoritmos_poblacion_expresiones::ReglaClasificacion regla;

	regla.modificar_antecedente("ANT1", "VALOR1");
	regla.modificar_antecedente("ANT2", "VALOR2");

	regla.cambiar_clase("Clase1");

	std::map<std::string, std::string> dato1;

	dato1["ANT1"] = "VALOR1";
	dato1["ANT2"] = "VALOR2";

	EXPECT_TRUE(regla.coincide_regla(dato1));

}


TEST (ReglaClasificacion, DatoNoCoincideConRegla) {
	algoritmos_poblacion_expresiones::ReglaClasificacion regla;

	regla.modificar_antecedente("ANT1", "VALOR1");
	regla.modificar_antecedente("ANT2", "VALOR2");

	regla.cambiar_clase("Clase1");

	std::map<std::string, std::string> dato1;

	dato1["ANT1"] = "VALOR1";
	dato1["ANT2"] = "VALOR2";

	std::map<std::string, std::string> dato2 = dato1;

	dato2["ANT3"] = "VALOR1";

	std::map<std::string, std::string> dato3 = dato1;

	dato3["ANT1"] = "VALOR0";

	EXPECT_FALSE(regla.coincide_regla(dato2));
	EXPECT_FALSE(regla.coincide_regla(dato3));

}


TEST (ReglaClasificacion, ConstructorCopia) {
	algoritmos_poblacion_expresiones::ReglaClasificacion regla;

	regla.modificar_antecedente("ANT1", "VALOR1");
	regla.modificar_antecedente("ANT2", "VALOR2");
	regla.modificar_antecedente("ANT3", "VALOR3");

	regla.cambiar_clase("Clase1");


	algoritmos_poblacion_expresiones::ReglaClasificacion otra_regla(regla);

	EXPECT_EQ(regla, otra_regla);
}


#endif
