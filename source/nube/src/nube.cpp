#include "../../utils/include/utils.hpp"

#include "../include/nube.hpp"

template <typename PointT> Nube<PointT>::Nube(){

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

	//

	//if (pcl::io::loadPCDFile<pcl::PointXYZRGB> (fullPathCaptura, *original_cloud) == -1) //* load the file
	if (pcl::io::loadPCDFile<PointT> (fullPathCaptura, *original_cloud) == -1) //* load the file
	{
		std::cout << "No se pudo leer el archivo: "<< fullPathCaptura << std::endl;
		return;
	}
	std::cout << "Leida muestra " << fullPathCaptura << " con " << original_cloud->points.size () << std::endl;

	pcl::copyPointCloud(*original_cloud, *downsampling_cloud);
	/*if (pcl::io::loadPCDFile<pcl::PointXYZRGB> (fullPathArch, *original_cloud) == -1) //* load the file
	{
		std::cout << "No se pudo leer el archivo: "<< fullPathCaptura << std::endl;
		return 1;
	}
	*/
	std::cout << "Copiada muestra a downsampling_cloud " << fullPathCaptura << " con " << downsampling_cloud->points.size () << std::endl;
	//pcl::NormalEstimationOMP<pcl::PointXYZRGB, pcl::Normal> normalEstimation(0);
	pcl::NormalEstimationOMP<PointT, pcl::Normal> normalEstimation(0);
	normalEstimation.setInputCloud(original_cloud);
	// For every point, use all neighbors in a radius of 3cm.
	normalEstimation.setRadiusSearch(0.008);
	// A kd-tree is a data structure that makes searches efficient. More about it later.
	// The normal estimation object will use it to find nearest neighbors.
	//pcl::search::KdTree<pcl::PointXYZRGB>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZRGB>);
	typename pcl::search::KdTree<PointT>::Ptr kdtree(new pcl::search::KdTree<PointT>);
	normalEstimation.setSearchMethod(kdtree);

	// Calculate the normals.
	normalEstimation.compute(*normals_cloud);

	std::cout << "Computadas las normales para Nube con: " << normals_cloud->points.size() << " puntos." << std::endl;

}


template<class PointT>
typename pcl::PointCloud<PointT>::Ptr Nube<PointT>::getDownsamplingCloud(){
	return downsampling_cloud;
}


template<class PointT>
typename pcl::PointCloud<pcl::Normal>::Ptr Nube<PointT>::getNormalsCloud(){
	return normals_cloud;
}


template<class PointT>
typename pcl::PointCloud<PointT>::Ptr Nube<PointT>::getOriginalCloud(){

}

template<class PointT>
typename pcl::PointCloud<PointT>::Ptr Nube<PointT>::getNoOutlierCloud(){
	
}

/*
	Instanciacion explicita del metodo que tiene template. Se aplica para metodos y clases que tienen la 
	definicion de sus templates en archivos .hpp y .cpp separados. 

	Se definen las especializaciones de los tipos genericos de las clases templates,
	SOLAMENTE para aquellos metodos que tengan una implementacion(aunque sea de cuerpo vacio).
	Si existen metodos genericos que no tengan implementacion se retornara error de linkeo.
*/
template class Nube<pcl::PointXYZRGB>;



