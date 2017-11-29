// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include "../../utils/include/utils.hpp"

#include "formateador_dataset.hpp"
#include "../../descriptor/include/pointfeaturederivadas.hpp"


#ifndef EstrategiaClasificacionAbstract_DEF
#define EstrategiaClasificacionAbstract_DEF

class EstrategiaClasificacionAbstract {


};


//template svm_problem EstrategiaClasificacionAbstract::adaptarDescriptor(PointFeature<pcl::ESFSignature640>);


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


	svm_problem adaptarDescriptor(PointFeature<SignatureT> descriptor);	
	svm_model* cargarModelo(std::string pathModeloEntrenado);
	TipoMuestra clasificar(std::string pathModeloEntrenado, svm_problem descriptor);

};
#endif