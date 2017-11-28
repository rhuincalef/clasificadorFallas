// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include "../../utils/include/utils.hpp"

#include "formateador_dataset.hpp"
#include "../../descriptor/include/pointfeaturederivadas.hpp"


#ifndef EstrategiaClasificacionAbstract_DEF
#define EstrategiaClasificacionAbstract_DEF

class EstrategiaClasificacionAbstract {

};
#endif

#ifndef EstrategiaClasificacionMLAbstract_DEF
#define EstrategiaClasificacionMLAbstract_DEF
template <class SignatureT,class ProblemaT,class ModeloT>
//class EstrategiaClasificacionMLAbstract{
class EstrategiaClasificacionMLAbstract: public EstrategiaClasificacionAbstract {

public:
	//Constructor 
	EstrategiaClasificacionMLAbstract();
	//EstrategiaClasificacionMLAbstract(FormateadorDatasetAbstract formateador);


	ProblemaT adaptarDescriptor(PointFeature<SignatureT> descriptor);	
	ModeloT* cargarModelo(std::string pathModeloEntrenado);
	//void clasificar(std::string pathModeloEntrenado,ProblemaT descriptor);
	TipoMuestra clasificar(std::string pathModeloEntrenado, ProblemaT descriptor);


protected:
	FormateadorDatasetAbstract<SignatureT,ProblemaT>* formateador;
	//std::string pathModeloEntrenado;

};
#endif

#ifndef EstrategiaClasificacionSVM_DEF
#define EstrategiaClasificacionSVM_DEF
template<class SignatureT>
class EstrategiaClasificacionSVM : public EstrategiaClasificacionMLAbstract<SignatureT,svm_problem,svm_model>
{
  
public:
	//Constructor 
	EstrategiaClasificacionSVM();
	
	/*
	template <class SignatureT1,typename ProblemaT> ProblemaT adaptarDescriptor(PointFeature<SignatureT1> descriptor);	
	template <typename ModeloT> ModeloT* cargarModelo(std::string pathModeloEntrenado);
	//void clasificar(std::string pathModeloEntrenado,ProblemaT descriptor);
	template <typename ProblemaT> TipoMuestra clasificar(std::string pathModeloEntrenado, ProblemaT descriptor);
	*/


};
#endif