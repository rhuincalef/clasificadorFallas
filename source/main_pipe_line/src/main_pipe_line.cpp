// Mediciones
#include <stdio.h>
#include <pcl/console/time.h>
// using for print_highlight, print_value, print_info
#include <pcl/console/print.h>

#include "../include/main_pipe_line.hpp"


//template MainPipeLine<pcl::ESFSignature640>::MainPipeLine();
//template MainPipeLine<pcl::GRSDSignature21>::MainPipeLine();


//Especializacion del constructor de la clase
//Constructor
/*
template <> MainPipeLine<pcl::PointXYZRGB,pcl::ESFSignature640,svm_problem,svm_model>::MainPipeLine(){
*/
template <> MainPipeLine<pcl::PointXYZRGB,pcl::ESFSignature640,svm_problem,svm_model,PointFeatureESF>::MainPipeLine(){
	std::cout << "Construyendo ESF..." << std::endl;  
	this->dirAlmacenamientoCapturas = "";
	//this->estratDescriptor = new ESF<pcl::PointXYZRGB>();
	this->estratDescriptor = new ESF<pcl::PointXYZRGB>();
	this->estratClasificacion = new EstrategiaClasificacionSVM<pcl::ESFSignature640,pcl::PointXYZRGB>();
}

/*
template <> MainPipeLine<pcl::PointXYZRGB,pcl::GRSDSignature21,svm_problem,svm_model>::MainPipeLine(){
*/
template <> MainPipeLine<pcl::PointXYZRGB,pcl::GRSDSignature21,svm_problem,svm_model,PointFeatureGRSD>::MainPipeLine(){
	std::cout << "Construyendo GRSD..." << std::endl;
	this->dirAlmacenamientoCapturas = "";
	//this->estratDescriptor = new GRSD<pcl::PointXYZRGB>();
	this->estratDescriptor = new GRSD<pcl::PointXYZRGB>();

	//this->estratClasificacion = new EstrategiaClasificacionSVM<pcl::GRSDSignature21,svm_problem,svm_model,pcl::PointXYZRGB>();
	this->estratClasificacion = new EstrategiaClasificacionSVM<pcl::GRSDSignature21,pcl::PointXYZRGB>();
}



//Computar la nube
/*
template<class PointT,class SignatureT,class ProblemaT,class ModeloT>
PointFeature<SignatureT,PointT>* MainPipeLine<PointT,SignatureT,ProblemaT,ModeloT>::computarNube(std::string pcdNoEscaneado){
	*/
template <class PointT,class SignatureT,class ProblemaT,class ModeloT,template<class>class PointFeatureT>
PointFeature<SignatureT,PointT>* MainPipeLine<PointT,SignatureT,ProblemaT,ModeloT,PointFeatureT>::computarNube(std::string pcdNoEscaneado){
	//Se crea una nube y se emplea la estrategia de ESF para obtener el PointFeature
	std::cout << "Entre a Main.ComputarNube()" << std::endl;
	Nube<PointT>* n = new Nube<PointT>(pcdNoEscaneado);
	std::cout << "Entre despues de instanciar la nube" << std::endl;
	//PointFeature<pcl::ESFSignature640> pointFeature = this->estratDescriptor->generarDescriptor(n);
	PointFeature<SignatureT,PointT>* pointFeature = this->estratDescriptor->generarDescriptor(n);
	std::cout << "Fin de Main.ComputarNube(). Genere el descriptor" << std::endl;
	return pointFeature;
};

/*
//BACKUP!!
template <>
PointFeature<pcl::ESFSignature640> MainPipeLine<pcl::PointXYZRGB,pcl::ESFSignature640>::computarNube(std::string pcdNoEscaneado){
	//Se crea una nube y se emplea la estrategia de ESF para obtener el PointFeature	
	//Nube<pcl::PointXYZRGB> n (pcdNoEscaneado);
	Nube<pcl::PointXYZRGB>* n = new Nube<pcl::PointXYZRGB>(pcdNoEscaneado);
	PointFeature<pcl::ESFSignature640> pointFeature = this->estratDescriptor->generarDescriptor(n);
	return pointFeature;
};
*/

//template <class PointT,class SignatureT,class ProblemaT,class ModeloT,class PointFeatureT>
template <class PointT,class SignatureT,class ProblemaT,class ModeloT,template<class>class PointFeatureT>
TipoMuestra MainPipeLine<PointT,SignatureT,ProblemaT,ModeloT,PointFeatureT>::clasificar(PointFeature<SignatureT,PointT>* descriptor){
	
	
	std::cout << "antes de adaptar el descriptor" << std::endl;

	ProblemaT problema = this->estratClasificacion->adaptarDescriptor(descriptor);

	std::cout << "despues de adaptar el descriptor" << std::endl;
	return this->estratClasificacion->clasificar(this->estratDescriptor->getPathModeloEntrenado(),
											problema);
}


//Instanciacion explicita de la clase
/*
template class MainPipeLine<pcl::PointXYZRGB,pcl::ESFSignature640,svm_problem,svm_model>;
template class MainPipeLine<pcl::PointXYZRGB,pcl::GRSDSignature21,svm_problem,svm_model>;
*/
/*
template class MainPipeLine<pcl::PointXYZRGB,pcl::ESFSignature640,svm_problem,svm_model,PointFeatureESF<pcl::PointXYZRGB>>;
template class MainPipeLine<pcl::PointXYZRGB,pcl::GRSDSignature21,svm_problem,svm_model,PointFeatureGRSD<pcl::PointXYZRGB>>;
*/
template class MainPipeLine<pcl::PointXYZRGB,pcl::ESFSignature640,svm_problem,svm_model,PointFeatureESF>;
template class MainPipeLine<pcl::PointXYZRGB,pcl::GRSDSignature21,svm_problem,svm_model,PointFeatureGRSD>;