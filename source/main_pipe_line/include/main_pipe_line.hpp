// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include "../../utils/include/utils.hpp"

#include "../../descriptor/include/pointfeaturederivadas.hpp"
#include "../../descriptor/include/descriptor.hpp"
#include "../../ML/include/estrategia_clasificacion.hpp"


#ifndef MainPipeLine_DEF
#define MainPipeLine_DEF
template <class SignatureT>
class MainPipeLine{

public:
	//Constructor 
	MainPipeLine();
	
	//template <class SignatureT> PointFeature<SignatureT> computarNube(std::string pcdNoEscaneado);
	PointFeature<SignatureT> computarNube(std::string pcdNoEscaneado);
	
	//NOTA IMPORTANTE: Al implementar los tipos genericos(templates) estos deben estar en el .hpp,
	//si no tienen un tipo explicito.
	/*
	//Computar la nube
	PointFeature<SignatureT> computarNube(std::string pcdNoEscaneado){
		//Se crea una nube y se emplea la estrategia de ESF para obtener el PointFeature	
		//Nube<pcl::PointXYZRGB> n (pcdNoEscaneado);
		Nube<pcl::PointXYZRGB>* n = new Nube<pcl::PointXYZRGB>(pcdNoEscaneado);
		PointFeature<pcl::ESFSignature640> pointFeature = this->estratDescriptor.generarDescriptor(*n);
		return pointFeature;
	};
	*/

	TipoMuestra clasificar(PointFeature<SignatureT> descriptor);

private:
	std::string dirAlmacenamientoCapturas;
	EstrategiaDescriptorsAbstract estratDescriptor;
	EstrategiaClasificacionMLAbstract estratClasificacion;

	/*
	EstrategiaDescriptorsAbstract estratDescriptor;
	EstrategiaClasificacionMLAbstract estrClasificacion; 
	*/

//protected:

};
#endif



