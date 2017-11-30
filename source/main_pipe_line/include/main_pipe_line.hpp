// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include "../../utils/include/utils.hpp"

#include "../../descriptor/include/pointfeaturederivadas.hpp"
#include "../../descriptor/include/descriptor.hpp"
#include "../../ML/include/estrategia_clasificacion.hpp"


#ifndef MainPipeLine_DEF
#define MainPipeLine_DEF
template <class PointT,class SignatureT,class ProblemaT,class ModeloT>
class MainPipeLine{

public:
	//Constructor 
	MainPipeLine();
	
	//template <class SignatureT> PointFeature<SignatureT> computarNube(std::string pcdNoEscaneado);
	PointFeature<SignatureT,PointT>* computarNube(std::string pcdNoEscaneado);
	TipoMuestra clasificar(PointFeature<SignatureT,PointT>* descriptor);


private:
	std::string dirAlmacenamientoCapturas;
	EstrategiaDescriptorsAbstract<PointT,SignatureT>* estratDescriptor;
	EstrategiaClasificacionMLAbstract<SignatureT,ProblemaT,ModeloT,PointT>* estratClasificacion;
	//EstrategiaClasificacionAbstract* estratClasificacion;

	/*
	template <class SignatureT1,typename ProblemaT,typename ModeloT>
	EstrategiaClasificacionMLAbstract<SignatureT1,ProblemaT,ModeloT>* estratClasificacion;
	*/

//protected:
};
#endif



