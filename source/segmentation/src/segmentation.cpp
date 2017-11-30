// Descriptor ESF con downsampling + diff. Alto y Ancho -->

#include <pcl/impl/instantiate.hpp>

#include "../../utils/include/utils.hpp"
#include "../include/segmentation.hpp"

template <typename PointT> std::vector<pcl::PointCloud<PointT>>
EstrategiaSegmentationAbstract<PointT>::computar(pcl::PointCloud<PointT> &input)
{
}

/******************************************** Metodos PlanarAndEuclidean **********************************************/

template <typename PointT> float
PlanarAndEuclidean<PointT>::getDistanceThreshold () const
{
  return distance_threshold_;
}

template <typename PointT> void
PlanarAndEuclidean<PointT>::setDistanceThreshold (float thresh)
{
  distance_threshold_ = thresh;
}

template <typename PointT> int
PlanarAndEuclidean<PointT>::getMinClusterSize () const
{
  return min_cluster_size_;
}

template <typename PointT> void
PlanarAndEuclidean<PointT>::setMinClusterSize (int min_cluster_size)
{
  min_cluster_size_ = min_cluster_size;
}

template <typename PointT> int
PlanarAndEuclidean<PointT>::getMaxClusterSize () const
{
  return max_cluster_size_;
}

template <typename PointT> void
PlanarAndEuclidean<PointT>::setMaxClusterSize (int max_cluster_size)
{
  max_cluster_size_ = max_cluster_size;
}

template <typename PointT> int 
PlanarAndEuclidean<PointT>::getMaxIterations () const
{
  return max_iterations_;
}

template <typename PointT> void 
PlanarAndEuclidean<PointT>::setMaxIterations (int max_iterations)
{
  max_iterations_ = max_iterations;
}

template <typename PointT> double 
PlanarAndEuclidean<PointT>::getClusterTolerance () const
{
  return tolerance_;
}

template <typename PointT> void
PlanarAndEuclidean<PointT>::setClusterTolerance (double tolerance)
{
  tolerance_ = tolerance;
}

template <typename PointT> void
PlanarAndEuclidean<PointT>::setNube (const pcl::PointCloud<PointT> &input)
{
  nube = input;
}

template <typename PointT> int
PlanarAndEuclidean<PointT>::getSizeNube ()
{
  return nube.points.size();
}

template <typename PointT> pcl::PointCloud<PointT>
PlanarAndEuclidean<PointT>::getNube ()
{
  return nube;
}

template <typename PointT> void
PlanarAndEuclidean<PointT>::planarSegmentation (const pcl::PointCloud<PointT> &input, pcl::PointCloud<PointT> cloud_no_plane, pcl::PointCloud<PointT> cloud_plane)
{
  pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
  pcl::SACSegmentation<PointT> segmentation;
  segmentation.setOptimizeCoefficients (true);
  segmentation.setModelType (pcl::SACMODEL_PLANE);
  segmentation.setMaxIterations (max_iterations_);
  segmentation.setMethodType (pcl::SAC_RANSAC);
  segmentation.setDistanceThreshold (distance_threshold_);
  pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
  typename pcl::PointCloud<PointT>::Ptr cloud (new pcl::PointCloud<PointT>);
  *cloud = input;
  int nr_points = (int) cloud->points.size ();
  while (cloud->points.size () > 0.3 * nr_points)
  {
  	segmentation.setInputCloud (cloud);
  	segmentation.segment (*inliers, *coefficients);
  	if (inliers->indices.size () == 0)
  	{
  	  std::cout << "Could not estimate a planar model for the given dataset." << std::endl;
  	  break;
  	}
  	// Extract the planar inliers from the input cloud
  	pcl::ExtractIndices<PointT> extract;
  	extract.setInputCloud (cloud);
  	extract.setIndices (inliers);
  	extract.setNegative (false);
  	// Get the points associated with the planar surface
  	extract.filter (cloud_plane);
  	extract.setNegative (true);
  	extract.filter (cloud_no_plane);
  	*cloud = cloud_no_plane;
  }
}

template <typename PointT> void
PlanarAndEuclidean<PointT>::euclideanClusterExtraction (const pcl::PointCloud<PointT> &input, std::vector<pcl::PointCloud<PointT>>)
{
  typename pcl::PointCloud<PointT>::Ptr cloud (new pcl::PointCloud<PointT>);
  *cloud = input;
  std::vector<pcl::PointIndices> cluster_indices;
  typename pcl::search::KdTree<PointT>::Ptr tree(new pcl::search::KdTree<PointT>);
  pcl::EuclideanClusterExtraction<PointT> ec;
  ec.setClusterTolerance (tolerance_);
  ec.setMinClusterSize (min_cluster_size_);
  ec.setMaxClusterSize (25000);
  ec.setSearchMethod (tree);
  ec.setInputCloud (cloud);
  ec.extract (cluster_indices);
}

template <typename PointT> std::vector<pcl::PointCloud<PointT>>
PlanarAndEuclidean<PointT>::computar (pcl::PointCloud<PointT> &input)
{
}

//The explicit instantiation part
/*
template class EstrategiaSegmentationAbstract<pcl::PointXYZRGB>; 
template class EstrategiaSegmentationAbstract<pcl::PointXYZ>; 
*/
template class PlanarAndEuclidean<pcl::PointXYZRGB>; 
template class PlanarAndEuclidean<pcl::PointXYZ>;
