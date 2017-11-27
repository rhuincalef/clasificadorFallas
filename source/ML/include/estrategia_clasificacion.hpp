// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include "../../utils/include/utils.hpp"

#include "formateador_dataset.hpp"
#include "../../descriptor/include/pointfeaturederivadas.hpp"

#ifndef EstrategiaClasificacionMLAbstract_DEF
#define EstrategiaClasificacionMLAbstract_DEF
class EstrategiaClasificacionMLAbstract{

public:
	//Constructor 
	EstrategiaClasificacionMLAbstract();
	EstrategiaClasificacionMLAbstract(FormateadorDatasetAbstract formateador);
	
	/*
	TipoMuestra clasificar(std::string pathDatasetTmp); 
	int leerDatasetTmp(std::string pathDatasetTmp);
	*/
	template <class SignatureT,class ProblemaT> ProblemaT adaptarDescriptor(PointFeature<SignatureT> descriptor);
	template <class ProblemaT> void clasificar(std::string pathModeloEntrenado, 
													ProblemaT descriptor);


protected:
	FormateadorDatasetAbstract formateador;
	std::string pathModeloEntrenado;

};
#endif

#ifndef EstrategiaClasificacionSVM_DEF
#define EstrategiaClasificacionSVM_DEF
class EstrategiaClasificacionSVM : public EstrategiaClasificacionMLAbstract
{
  
public:
	//Constructor 
	EstrategiaClasificacionSVM();

	template <class SignatureT> svm_problem adaptarDescriptor(PointFeature<SignatureT> descriptor);
	
	TipoMuestra clasificar(std::string pathModeloEntrenado, svm_problem descriptor);



//private:

};
#endif