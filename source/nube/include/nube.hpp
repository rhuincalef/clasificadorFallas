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
  Nube()
  {}

  Nube(typename pcl::PointCloud<PointT>::Ptr input)
  {
    typename pcl::PointCloud<PointT>::Ptr downsampling_cloud (new pcl::PointCloud<PointT>);
    this->downsampling_cloud = downsampling_cloud;
    typename pcl::PointCloud<PointT>::Ptr no_outlier_cloud (new pcl::PointCloud<PointT>);
    this->no_outlier_cloud = no_outlier_cloud;
    this->original_cloud = input;
    this->setAllClouds ();
  }

  //Nube(typename pcl::PointCloud<PointT>::Ptr input);

  Nube(const pcl::PointCloud<PointT> &input);

	//TODO: REMOVER ESTOS METODOS QUE SON TEMPORALES PARA TESTEAR LA CAPTURA
	Nube(std::string fullPathpcd);
	pcl::PointCloud<pcl::Normal>::Ptr getNormalsCloud();
	typename pcl::PointCloud<PointT>::Ptr getNoOutlierCloud();

  typename pcl::PointCloud<PointT>::Ptr
  getDownsamplingCloud()
  {
    return this->downsampling_cloud;
  }

  typename pcl::PointCloud<PointT>::Ptr
  getOriginalCloud()
  {
  	return this->original_cloud;
  }

private:
  typename pcl::PointCloud<PointT>::Ptr downsampling_cloud;
  pcl::PointCloud<pcl::Normal>::Ptr normals_cloud;
  typename pcl::PointCloud<PointT>::Ptr original_cloud;
  typename pcl::PointCloud<PointT>::Ptr no_outlier_cloud;

  //void
  //setAllClouds();
  void
  setAllClouds()
  {
    pcl::VoxelGrid<PointT> voxel_grid_filter;
    voxel_grid_filter.setInputCloud(this->original_cloud);
    voxel_grid_filter.setLeafSize(0.01f, 0.01f, 0.01f);
    voxel_grid_filter.filter(*this->downsampling_cloud);
    // Create the filtering object
    typename pcl::StatisticalOutlierRemoval<PointT> sor;
    sor.setInputCloud (this->original_cloud);
    // setMeanK - Set the number of nearest neighbors to use for mean distance estimation.
    sor.setMeanK (50);
    sor.setStddevMulThresh (1);
    sor.filter (*this->no_outlier_cloud);
    // The mapping tells you to what points of the old cloud the new ones correspond,
    // but we will not use it. Avoiding Nan
    std::vector<int> mapping;
    pcl::removeNaNFromPointCloud(*this->no_outlier_cloud, *this->no_outlier_cloud, mapping);
  }

};
#endif