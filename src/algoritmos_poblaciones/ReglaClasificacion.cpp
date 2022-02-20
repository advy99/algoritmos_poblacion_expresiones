#include "algoritmos_poblaciones/ReglaClasificacion.hpp"


namespace algoritmos_poblacion_expresiones {


std::size_t ReglaClasificacion :: num_antecedentes() const {
	return antecedentes_.size();
}


void ReglaClasificacion :: cambiar_clase(const std::string & nueva_clase) {
	clase_ = nueva_clase;
}

std::string ReglaClasificacion :: consultar_clase() const {
	return clase_;
}

void ReglaClasificacion :: modificar_antecedente(const std::string & clave,
																 const std::string & valor) {

	antecedentes_[clave] = valor;

}

void ReglaClasificacion :: modificar_antecedente(const std::pair<std::string, std::string> & antecedente) {
	modificar_antecedente(antecedente.first, antecedente.second);
}

void ReglaClasificacion :: eliminar_antecedente(const std::string & clave) {
	antecedentes_.erase(clave);
}


std::string ReglaClasificacion :: consultar_antecedente(const std::string & clave) const {
	return antecedentes_.at(clave);
}


std::string ReglaClasificacion :: como_string() const {

	std::string regla = "IF ";

	for (const auto & antecedente: antecedentes_){
		regla += antecedente.first + " IS " + antecedente.second + " ";

		if (antecedente != *(antecedentes_.crbegin()) ) {
			regla += "AND ";
		}
	}

	regla += "THEN CLASS IS " + clase_;

	return regla;

}

bool ReglaClasificacion :: operator== (const ReglaClasificacion & otra) const {
	return antecedentes_ == otra.antecedentes_ && clase_ == otra.clase_;
}


std::ostream & operator<< (std::ostream & os, const ReglaClasificacion & regla){
	// obtenemos el string y lo sacamos por el flujo
	std::string regla_str = regla.como_string();

	os << regla_str;

	return os;
}





}
