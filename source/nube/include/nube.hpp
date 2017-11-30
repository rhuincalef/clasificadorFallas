// Clases: Nube

#include <pcl/io/pcd_io.h>
#include <iostream>
#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/visualization/cloud_viewer.h>

#include <pcl/segmentation/extract_clusters.h>

#include <pcl/features/normal_3d_omp.h>
#include <pcl/console/parse.h>
#include <pcl/features/principal_curvatures.h>

#include <pcl/filters/voxel_grid.h>
#include <vector>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

#include <iostream>
#include "../../utils/include/utils.hpp"
#include <stdlib.h>

// Link a explicacion de typename -->
//http://pages.cs.wisc.edu/~driscoll/typename.html

#ifndef Nube_DEF
#define Nube_DEF
template <class PointT>
class Nube{

public:
	//Constructor 
	Nube();
	
	//TODO: REMOVER ESTOS METODOS QUE SON TEMPORALES PARA TESTEAR LA CAPTURA
	Nube(std::string fullPathpcd);
	typename pcl::PointCloud<PointT>::Ptr getDownsamplingCloud();
	pcl::PointCloud<pcl::Normal>::Ptr getNormalsCloud();
	typename pcl::PointCloud<PointT>::Ptr getOriginalCloud();
	typename pcl::PointCloud<PointT>::Ptr getNoOutlierCloud();
	

private:
	typename pcl::PointCloud<PointT>::Ptr downsampling_cloud;
	//pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::PointCloud<pcl::Normal>::Ptr normals_cloud;


	typename pcl::PointCloud<PointT>::Ptr original_cloud;
	typename pcl::PointCloud<PointT>::Ptr no_outlier_cloud;

};
#endif