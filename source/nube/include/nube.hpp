// Clases: Nube

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/pcl_base.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d_omp.h>

#include "../../utils/include/utils.hpp"

// Link a explicacion de typename -->
//http://pages.cs.wisc.edu/~driscoll/typename.html

#ifndef Nube_DEF
#define Nube_DEF
template <typename PointT>
class Nube{
  //typedef typename pcl::PointCloud<PointT>::Ptr PointCloud;
public:
	//Constructor 
	Nube();
	
	//TODO: REMOVER ESTOS METODOS QUE SON TEMPORALES PARA TESTEAR LA CAPTURA
	Nube(std::string fullPathpcd);
	typename pcl::PointCloud<PointT>::Ptr getDownsamplingCloud();
	typename pcl::PointCloud<PointT>::Ptr getNormalsCloud();
	typename pcl::PointCloud<PointT>::Ptr getOriginalCloud();
	typename pcl::PointCloud<PointT>::Ptr getNoOutlierCloud();
	

private:
	typename pcl::PointCloud<PointT>::Ptr downsampling_cloud;
	typename pcl::PointCloud<PointT>::Ptr normals_cloud;
	typename pcl::PointCloud<PointT>::Ptr original_cloud;
	typename pcl::PointCloud<PointT>::Ptr no_outlier_cloud;

};
#endif