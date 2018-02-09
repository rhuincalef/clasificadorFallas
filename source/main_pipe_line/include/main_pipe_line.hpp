#include <iostream>
#include <json/json.h>
#include <json/writer.h>
#include "../../utils/include/utils.hpp"
#include "../../descriptor/include/pointfeaturederivadas.hpp"
#include "../../nube/include/nube.hpp"
#include "../../segmentation/include/segmentation.hpp"
#include "../../descriptor/include/descriptor.hpp"
#include "../../ML/include/estrategia_clasificacion.hpp"
#include "../../parser/include/parametrizador.hpp"

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
	typename std::vector<pcl::PointCloud<PointT>> computarNube(Nube<PointT>* n);

	template <class SignatureT,class ProblemaT,class ModeloT>
	TipoMuestra clasificar(PointFeature<SignatureT,PointT>* descriptor){
		/*
		return this->estratClasificacion->template clasificar<SignatureT,PointT,ProblemaT,
															ModeloT,pcl::SVMData>(
													this->estratDescriptor->getPathModeloEntrenado(),
													descriptor);
		*/
		return this->estratClasificacion->template clasificar<SignatureT,PointT,ProblemaT,
															ModeloT,pcl::SVMData>(
													this->getPathModeloEntrenado(),
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
	almacenarCluster(Nube<PointT>* n,Cluster<PointT> c, std::string dir_guardado_cluster);

	std::string
	getPathModeloEntrenado() const;

	void
	setPathModeloEntrenado(std::string path);

	static Parametrizador
	getParametrizador();

private:
	std::string dirAlmacenamientoCapturasClasificadas;//TODO: Cambiar esto en el diagrama de clases
	EstrategiaSegmentationAbstract<PointT>* estratSegmentacion;
	EstrategiaDescriptorsAbstract<PointT>* estratDescriptor;
	EstrategiaClasificacionMLAbstract* estratClasificacion;

	std::string pathModeloEntrenado;

	static Parametrizador parametrizador_;
	static bool configurado_;

	static void
	configurarParametrizador();

};
#endif
