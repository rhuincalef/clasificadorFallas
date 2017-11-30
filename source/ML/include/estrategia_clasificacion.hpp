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
template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
class EstrategiaClasificacionMLAbstract: public EstrategiaClasificacionAbstract {

public:
	//Constructor 
	EstrategiaClasificacionMLAbstract();
	//EstrategiaClasificacionMLAbstract(FormateadorDatasetAbstract formateador);


	ProblemaT adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor);	
	ModeloT* cargarModelo(std::string pathModeloEntrenado);
	TipoMuestra clasificar(std::string pathModeloEntrenado, ProblemaT descriptor);


protected:
	FormateadorDatasetAbstract<SignatureT,ProblemaT,PointT>* formateador;
	//std::string pathModeloEntrenado;

};
#endif

#ifndef EstrategiaClasificacionSVM_DEF
#define EstrategiaClasificacionSVM_DEF
//template<class SignatureT,class ProblemaT, class ModeloT,class PointT>
template<class SignatureT,class PointT>
class EstrategiaClasificacionSVM : public EstrategiaClasificacionMLAbstract<SignatureT,svm_problem,svm_model,PointT>
{
  
public:
	//Constructor 
	EstrategiaClasificacionSVM();

	/*
	ProblemaT adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor);	
	ModeloT* cargarModelo(std::string pathModeloEntrenado);
	*/
	svm_problem adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor);	
	svm_model* cargarModelo(std::string pathModeloEntrenado);
	TipoMuestra clasificar(std::string pathModeloEntrenado, svm_problem descriptor);


};
#endif