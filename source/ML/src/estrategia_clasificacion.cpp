#include "../../utils/include/utils.hpp"

#include "../include/estrategia_clasificacion.hpp"


//Constructores 
EstrategiaClasificacionMLAbstract::EstrategiaClasificacionMLAbstract(){

}

EstrategiaClasificacionMLAbstract::EstrategiaClasificacionMLAbstract(FormateadorDatasetAbstract formateador){
	this->formateador = formateador;
}



/************************** Estrategia clasificacion SVM **************************/
template <class SignatureT> svm_problem EstrategiaClasificacionSVM::adaptarDescriptor(PointFeature<SignatureT> descriptor){
	return this->formateador.adaptarDescriptor(descriptor);
}

//TODO: CONTINUAR POR ACA!!!
TipoMuestra EstrategiaClasificacionSVM::clasificar(std::string pathModeloEntrenado, svm_problem descriptor){




}




