// Mediciones
#include <stdio.h>
#include <pcl/console/time.h>
// using for print_highlight, print_value, print_info
#include <pcl/console/print.h>
#include "../include/main_pipe_line.hpp"


template <class PointT>
MainPipeLine<PointT>::MainPipeLine(){
	std::cout << "Construyendo MainPipeLine..." << std::endl;
	//this->dirAlmacenamientoCapturas = "";
	//this->estratDescriptor = new ESF<pcl::PointXYZRGB,pcl::ESFSignature640,PointFeatureESF>();
	//this->estratClasificacion = new EstrategiaClasificacionSVM<pcl::ESFSignature640,svm_problem,svm_model,pcl::PointXYZRGB>();
	//this->estratDescriptor = new GRSD<pcl::PointXYZRGB,pcl::GRSDSignature21,PointFeatureGRSD>();
	//this->estratClasificacion = new EstrategiaClasificacionSVM<pcl::GRSDSignature21,svm_problem,svm_model,pcl::PointXYZRGB>();
}




//Computar la nube
template <class PointT>
std::vector<pcl::PointCloud<PointT>> MainPipeLine<PointT>::computarNube(
																Nube<PointT>* n){

	std::cout << "Entre a Main.ComputarNube()" << std::endl;
	std::cout << "Entre despues de instanciar la nube" << std::endl;

	this->estratSegmentacion->setNube(*n);
	typename std::vector <pcl::PointCloud<PointT>> clusters = this->estratSegmentacion->computar();
	std::cout << "Despues de segmentar: cant. clusters= "<< clusters.size() << std::endl;
	return clusters;
}

/*
template <class PointT>
std::vector<pcl::PointCloud<PointT>> MainPipeLine<PointT>::computarNube(std::string pcdNoEscaneado){

	std::cout << "Entre a Main.ComputarNube()" << std::endl;

	typename pcl::PointCloud<PointT>::Ptr p (new pcl::PointCloud<PointT>);
	
	if (pcl::io::loadPCDFile<PointT>(pcdNoEscaneado, *p) != 0)
	{
	  std::cerr << "Failed to read PCD test file." << std::endl;
	  return;
	}

	Nube<PointT>* n = new Nube<PointT>(p);
	std::cout << "Entre despues de instanciar la nube" << std::endl;

	this->estratSegmentacion->setNube(*n);
	typename std::vector <pcl::PointCloud<PointT>> clusters = this->estratSegmentacion->computar();
	std::cout << "Despues de segmentar: cant. clusters= "<< clusters.size() << std::endl;
	return clusters;
}
*/
/*
*/



/*
template <class PointT,class SignatureT,class ProblemaT,class ModeloT>
TipoMuestra MainPipeLine<PointT>::clasificar(PointFeature<SignatureT,PointT>* descriptor){

	return this->estratClasificacion->template clasificar<SignatureT,PointT,ProblemaT,
															ModeloT,pcl::SVMData>(
													this->estratDescriptor->getPathModeloEntrenado(),
													descriptor);
}
*/


template <class PointT>
void MainPipeLine<PointT>::setDirAlmacenamientoCapturasClasificadas(std::string dirCapturas){
	this->dirAlmacenamientoCapturasClasificadas = dirCapturas;
}

template <class PointT>
std::string MainPipeLine<PointT>::getDirAlmacenamientoCapturasClasificadas(){
	return this->dirAlmacenamientoCapturasClasificadas;
}

//template <template <class> class EstrategiaSegmentationT,class PointT> 
template <class PointT>
void MainPipeLine<PointT>::setEstrategiaSegmentacion(EstrategiaSegmentationAbstract<PointT>* estrategia){
	this->estratSegmentacion = estrategia;
}

//template <template <class> class EstrategiaSegmentationT,class PointT> 
template <class PointT>
EstrategiaSegmentationAbstract<PointT>* MainPipeLine<PointT>::getEstrategiaSegmentacion(){
	return this->estratSegmentacion;
}



template < class PointT>
void MainPipeLine<PointT>::setEstrategiaDescriptor(EstrategiaDescriptorsAbstract<PointT>* descriptor){
	this->estratDescriptor = descriptor;
}


template < class PointT >
EstrategiaDescriptorsAbstract<PointT>* MainPipeLine<PointT>::getEstrategiaDescriptor(){
	return this->estratDescriptor;

}

template <class PointT>
void MainPipeLine<PointT>::setEstrategiaClasificacion(EstrategiaClasificacionMLAbstract* clasificacion){
	this->estratClasificacion = clasificacion;
}

template <class PointT>
EstrategiaClasificacionMLAbstract* MainPipeLine<PointT>::getEstrategiaClasificacion(){
	return this->estratClasificacion;
}

//Lee de un directorio donde se cargan capturas. Invoca a leerCaptura(). 
template <class PointT>
std::vector<std::string> MainPipeLine<PointT>::leerDirCaptura(){

	std::string input_dir = this->dirAlmacenamientoCapturasClasificadas;
	std::vector<std::string> pcd_files;
	boost::filesystem::directory_iterator end_itr;
	for (boost::filesystem::directory_iterator itr (input_dir); itr != end_itr; ++itr)
	{
		// Only add PCD files
		if (!is_directory (itr->status ()) && boost::algorithm::to_upper_copy (boost::filesystem::extension (itr->path ())) == ".PCD" )
		{
		  pcd_files.push_back (itr->path ().string ());
		  std::cout << "Added " << itr->path().string().c_str() << " for processing." << std::endl;
		}
	}
	return pcd_files;
}


//Lee una captura recibiendo el nombre del pcl y retorna PointCloud<PointT>
template <class PointT>
int MainPipeLine<PointT>::leerCaptura(std::string pathCaptura,
											typename pcl::PointCloud<PointT>::Ptr cloud){
//typename pcl::PointCloud<PointT>::Ptr MainPipeLine<PointT>::leerCaptura(std::string dir){
	
	// Read a PCD file from disk.
	if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(pathCaptura.c_str(), *cloud) != 0)
	{
		std::cerr << "Failed to read test file. Please download `bachecitos_tw_4.pcd` and pass its path to the test." << std::endl;
		return -1;
	}

}



//Instanciacion explicita de la clase
template class MainPipeLine<pcl::PointXYZRGB>;


