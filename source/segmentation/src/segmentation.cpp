// Descriptor ESF con downsampling + diff. Alto y Ancho -->

#include <pcl/impl/instantiate.hpp>

#include "../../utils/include/utils.hpp"
#include "../include/segmentation.hpp"

/*
*/
template <typename PointT> void
PlanarAndEuclidean<PointT>::setNube (const pcl::PointCloud<PointT> &input)
{
  nube = input;
}

template <typename PointT> int
PlanarAndEuclidean<PointT>::getSizeNube()
{
  return nube.points.size();
}

template <typename PointT> pcl::PointCloud<PointT>
PlanarAndEuclidean<PointT>::getNube()
{
  return nube;
}
//The explicit instantiation part
/*
template class EstrategiaSegmentationAbstract<pcl::PointXYZRGB>; 
template class EstrategiaSegmentationAbstract<pcl::PointXYZ>; 
*/
template class PlanarAndEuclidean<pcl::PointXYZRGB>; 
template class PlanarAndEuclidean<pcl::PointXYZ>;