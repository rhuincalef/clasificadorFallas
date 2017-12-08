// Clases: Nube

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/statistical_outlier_removal.h>

#include "../../utils/include/utils.hpp"

// Link a explicacion de typename -->
//http://pages.cs.wisc.edu/~driscoll/typename.html

#ifndef Nube_DEF
#define Nube_DEF
template <typename PointT>
class Nube
{

public:
  //Constructor
  Nube();

  Nube(typename pcl::PointCloud<PointT>::Ptr input);

  Nube(const pcl::PointCloud<PointT> &input);

	//TODO: REMOVER ESTOS METODOS QUE SON TEMPORALES PARA TESTEAR LA CAPTURA
	Nube(std::string fullPathpcd);
	pcl::PointCloud<pcl::Normal>::Ptr getNormalsCloud();
	typename pcl::PointCloud<PointT>::Ptr getNoOutlierCloud();

  typename pcl::PointCloud<PointT>::Ptr
  getDownsamplingCloud();

  typename pcl::PointCloud<PointT>::Ptr
  getOriginalCloud();


  typename std::vector<Cluster<PointT>>
  getClusters();
  
  void 
  agregarCluster(Cluster<PointT> c);

  void
  setNombre(std::string n);

  std::string
  getNombre();
  

private:
  typename pcl::PointCloud<PointT>::Ptr downsampling_cloud;
  pcl::PointCloud<pcl::Normal>::Ptr normals_cloud;
  typename pcl::PointCloud<PointT>::Ptr original_cloud;
  typename pcl::PointCloud<PointT>::Ptr no_outlier_cloud;

  typename std::vector<Cluster<PointT>> clusters;
  std::string nombre;

  void
  setAllClouds();

};
#endif


#ifndef CLUSTER_DEF
#define CLUSTER_DEF
template <class PointT>
class Cluster
{

public:
  //Constructor
  Cluster();

  Cluster(typename pcl::PointCloud<PointT>::Ptr input,
                                                    std::string nombre);

  void setOriginalCloud(pcl::PointCloud<PointT>::Ptr p);
  
  typename pcl::PointCloud<PointT>::Ptr
  getOriginalCloud();

  void setNombre(std::string nombre);

  std::string getNombre();

  void
  computarNormales();

  pcl::PointCloud<pcl::Normal>::Ptr
  getNormalsCloud();

private:
  typename pcl::PointCloud<PointT>::Ptr original_cloud;
  pcl::PointCloud<pcl::Normal>::Ptr normals_cloud;
  std::string nombre;


};
#endif



