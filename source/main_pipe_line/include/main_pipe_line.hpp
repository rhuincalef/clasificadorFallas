#include <iostream>
#include "../../utils/include/utils.hpp"

#include "../../descriptor/include/pointfeaturederivadas.hpp"
#include "../../nube/include/nube.hpp"

#include "../../segmentation/include/segmentation.hpp"
#include "../../descriptor/include/descriptor.hpp"
#include "../../ML/include/estrategia_clasificacion.hpp"


#ifndef MainPipeLine_DEF
#define MainPipeLine_DEF

template <class PointT>
class MainPipeLine{

public:
	//Constructor 
	MainPipeLine();
	
	//Lee de un directorio donde se cargan capturas. Invoca a leerCaptura(). 
	std::vector<std::string> leerDirCaptura();

	//Lee una captura recibiendo el nombre del pcl y retorna PointCloud<PointT>
	//typename pcl::PointCloud<PointT>::Ptr leerCaptura(std::string dir);
	int leerCaptura(std::string pathCaptura, typename pcl::PointCloud<PointT>::Ptr cloud);

	
	//template <class SignatureT>
	//std::vector<pcl::PointCloud<PointT>> computarNube(std::string pcdNoEscaneado);
	std::vector<pcl::PointCloud<PointT>> computarNube(Nube<PointT>* n);

	template <class SignatureT,class ProblemaT,class ModeloT>
	TipoMuestra clasificar(PointFeature<SignatureT,PointT>* descriptor){

		//template <class SignatureT,class PointT,class ProblemaT,class ModeloT,class MuestraT>
		return this->estratClasificacion->template clasificar<SignatureT,PointT,ProblemaT,
															ModeloT,pcl::SVMData>(
													this->estratDescriptor->getPathModeloEntrenado(),
													descriptor);
	}


	//Getters y setters
	void setDirAlmacenamientoCapturasClasificadas(std::string dirCapturas);
	std::string getDirAlmacenamientoCapturasClasificadas();


	
	void setEstrategiaSegmentacion(EstrategiaSegmentationAbstract<PointT>* estrategia);
	
	EstrategiaSegmentationAbstract<PointT>* getEstrategiaSegmentacion();
	

	void setEstrategiaDescriptor(EstrategiaDescriptorsAbstract<PointT>* descriptor);	
	EstrategiaDescriptorsAbstract<PointT>* getEstrategiaDescriptor();



	void setEstrategiaClasificacion(EstrategiaClasificacionMLAbstract* clasificacion);
	EstrategiaClasificacionMLAbstract* getEstrategiaClasificacion();



	void 
	almacenarCluster(Nube<pcl::PointXYZRGB>n,clustersReales[i],pointFeature->getAlto(),pointFeature->getAncho());







private:
	std::string dirAlmacenamientoCapturasClasificadas;//TODO: Cambiar esto en el diagrama de clases
	EstrategiaSegmentationAbstract<PointT>* estratSegmentacion;
	EstrategiaDescriptorsAbstract<PointT>* estratDescriptor;
	EstrategiaClasificacionMLAbstract* estratClasificacion;


};
#endif



