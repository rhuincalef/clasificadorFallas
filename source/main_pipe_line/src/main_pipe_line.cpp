// Mediciones
#include <stdio.h>
#include <pcl/console/time.h>
// using for print_highlight, print_value, print_info
#include <pcl/console/print.h>

//#include "source/ML/include/estrategia_clasificacion.hpp"

//Constructor
MainPipeLine<pcl::ESFSignature640>::MainPipeLine(){
	std::cout << "Construyendo ESF..." << std::endl;  
	this->dirAlmacenamientoCapturas = "";
	this->estratDescriptor = new ESF;
	this->estratClasificacion = new EstrategiaClasificacionSVM;
}


MainPipeLine<pcl::GRSDSignature21>::MainPipeLine(){
	std::cout << "Construyendo GRSD..." << std::endl;  
	this->dirAlmacenamientoCapturas = "";
	this->estratDescriptor = new GRSD;
	this->estratClasificacion = new EstrategiaClasificacionSVM;
}


//Computar la nube
PointFeature<pcl::ESFSignature640> MainPipeLine::computarNube(std::string pcdNoEscaneado){
	//Se crea una nube y se emplea la estrategia de ESF para obtener el PointFeature	
	//Nube<pcl::PointXYZRGB> n (pcdNoEscaneado);
	Nube<pcl::PointXYZRGB>* n = new Nube<pcl::PointXYZRGB>(pcdNoEscaneado);
	PointFeature<pcl::ESFSignature640> pointFeature = this->estratDescriptor.generarDescriptor(*n);
	return pointFeature;
};

/*
//Computar la nube
template <typename SignatureT> PointFeature<SignatureT> MainPipeLine<SignatureT>::computarNube(std::string pcdNoEscaneado){
	
	//Se crea una nube y se emplea la estrategia de ESF para obtener el PointFeature	
	Nube<pcl::PointXYZRGB> n = new Nube<pcl::PointXYZRGB>(pcdNoEscaneado);
	PointFeature<pcl::ESFSignature640> pointFeature = this->estratDescriptor.generarDescriptor(n);
	return pointFeature;
}
*/


TipoMuestra MainPipeLine::clasificar(PointFeature<SignatureT> descriptor){

	svm_problem problema = this->estratClasificacion.adaptarDescriptor(descriptor);
	return this->estratClasificacion.clasificar(this->estratDescriptor.getPathModeloEntrenado(),
											problema);
}




