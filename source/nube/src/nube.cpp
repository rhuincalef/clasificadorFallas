#include "../../utils/include/utils.hpp"

#include "../include/nube.hpp"

template <typename PointT>
Nube<PointT>::Nube(){
	//this->abc = new pcl::PointCloud<PointT>;

}

//Constructor que simula incializar una muestra pcd cropeada,downsampleada y con normales (Prueba de training cropeada)

template <typename PointT> Nube<PointT>::Nube(std::string fullPathCaptura){

	//Se computa la nube completa
	//original_cloud (new pcl::PointCloud<PointT>);
	//downsampling_cloud (new pcl::PointCloud<PointT>);
	
	//this->original_cloud = new pcl::PointCloud<PointT>();
	/*
	this->downsampling_cloud =  new pcl::PointCloud<PointT>;
	*/
	
	/*
	original_cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
	downsampling_cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
	*/
	//pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	//normals_cloud (new pcl::PointCloud<pcl::Normal>); 
	
	/*
	this->normals_cloud = new pcl::PointCloud<PointT>;
	*/

	//Se computa la nube completa
	typename pcl::PointCloud<PointT>::Ptr abc (new pcl::PointCloud<PointT>);

	/*
	original_cloud (new pcl::PointCloud<PointT>);
	downsampling_cloud (new pcl::PointCloud<PointT>);
	normals_cloud (new pcl::PointCloud<pcl::Normal>);
	*/
	//std::cout << "Construyendo nube nueva..." << std::endl;
	//if (pcl::io::loadPCDFile<PointT> (fullPathCaptura, *original_cloud) == -1) //* load the file
	if (pcl::io::loadPCDFile<PointT> (fullPathCaptura, *abc) == -1) //* load the file
	{
		//std::cout << "No se pudo leer el archivo: "<< fullPathCaptura << std::endl;
		return;
	}
	//std::cout << "Leida muestra " << std::endl;
	this->original_cloud = abc;
	this->downsampling_cloud = abc;
	//std::cout << "Leida muestra 2" << std::endl;
	pcl::PointCloud<pcl::Normal>::Ptr normals_cloud1 (new pcl::PointCloud<pcl::Normal>);

	////std::cout << "Leida muestra " << fullPathCaptura << " con " << original_cloud->points.size () << std::endl;

	//pcl::copyPointCloud(*original_cloud, *downsampling_cloud);
	

	//std::cout << "Copiada muestra a downsampling_cloud " << fullPathCaptura << " con " << downsampling_cloud->points.size () << std::endl;
	//pcl::NormalEstimationOMP<pcl::PointXYZRGB, pcl::Normal> normalEstimation(0);

	pcl::NormalEstimationOMP<PointT, pcl::Normal> normalEstimation(0);
	//std::cout << "Instanciado NormalEstimationOMP " << std::endl;
	normalEstimation.setInputCloud(original_cloud);
	//std::cout << "Seteado original_cloud" << std::endl;

	// For every point, use all neighbors in a radius of 3cm.
	normalEstimation.setRadiusSearch(0.008);
	// A kd-tree is a data structure that makes searches efficient. More about it later.
	// The normal estimation object will use it to find nearest neighbors.
	//pcl::search::KdTree<pcl::PointXYZRGB>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZRGB>);
	typename pcl::search::KdTree<PointT>::Ptr kdtree(new pcl::search::KdTree<PointT>);
	normalEstimation.setSearchMethod(kdtree);

	
	//std::cout << "Por computar..." << std::endl;
	// Calculate the normals.
	normalEstimation.compute(*normals_cloud1);
	this->normals_cloud = normals_cloud1;
	//std::cout << "Computada normals_cloud!!" << std::endl;

	//std::cout << "Computadas las normales para Nube con: " << normals_cloud->points.size() << " puntos." << std::endl;


}


template<typename PointT> typename pcl::PointCloud<PointT>::Ptr
Nube<PointT>::getDownsamplingCloud(){
	return downsampling_cloud;
}

template<class PointT>
typename pcl::PointCloud<pcl::Normal>::Ptr Nube<PointT>::getNormalsCloud(){
	return normals_cloud;
}


template<typename PointT> typename pcl::PointCloud<PointT>::Ptr
Nube<PointT>::getOriginalCloud(){

}

template<typename PointT> typename pcl::PointCloud<PointT>::Ptr
Nube<PointT>::getNoOutlierCloud(){
	
}

/*
	Instanciacion explicita del metodo que tiene template. Se aplica para metodos y clases que tienen la 
	definicion de sus templates en archivos .hpp y .cpp separados. 

	Se definen las especializaciones de los tipos genericos de las clases templates,
	SOLAMENTE para aquellos metodos que tengan una implementacion(aunque sea de cuerpo vacio).
	Si existen metodos genericos que no tengan implementacion se retornara error de linkeo.
*/
template class Nube<pcl::PointXYZRGB>;



