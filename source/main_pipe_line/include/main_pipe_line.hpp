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

	template <class PointT1,class SignatureT>
	std::vector<pcl::PointCloud<PointT1>> computarNube(std::string pcdNoEscaneado);

	
	template <class SignatureT>
	TipoMuestra clasificar(PointFeature<SignatureT,PointT>* descriptor);


	//Getters y setters
	void setDirAlmacenamientoCapturasClasificadas(std::string dirCapturas);
	std::string getDirAlmacenamientoCapturasClasificadas();

	template <template <class> class EstrategiaSegmentationT>
	void setEstrategiaSegmentacion(EstrategiaSegmentationT<PointT>* estrategia);


	template <template <class> class EstrategiaSegmentationT>
	EstrategiaSegmentationT<PointT>* getEstrategiaSegmentacion();

	template < template<class> class EstrategiaDescriptorsT>
		void setEstrategiaDescriptor(EstrategiaDescriptorsT<PointT>* descriptor);

	template < template<class> class EstrategiaDescriptorsT >
		EstrategiaDescriptorsT<PointT>* getEstrategiaDescriptor();

	void setEstrategiaClasificacion(EstrategiaClasificacionMLAbstract* clasificacion);
	EstrategiaClasificacionMLAbstract* getEstrategiaClasificacion();


private:
	std::string dirAlmacenamientoCapturasClasificadas;//TODO: Cambiar esto en el diagrama de clases
	EstrategiaSegmentationAbstract<PointT>* estratSegmentacion;
	EstrategiaDescriptorsAbstract<PointT>* estratDescriptor;
	EstrategiaClasificacionMLAbstract* estratClasificacion;


};
#endif



