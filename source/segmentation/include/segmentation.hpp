// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include <vector>
#include <pcl/pcl_base.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/segmentation/extract_clusters.h>
#include "../../utils/include/utils.hpp"
#include "../../nube/include/nube.hpp"

//#include <pcl/point_types.h>
//#include <pcl/sample_consensus/ransac.h>
//#include <pcl/segmentation/sac_segmentation.h>

#ifndef EstrategiaSegmentationAbstract_DEF
#define EstrategiaSegmentationAbstract_DEF
template <typename PointT>
class EstrategiaSegmentationAbstract
{

public:
  //Constructor 
  EstrategiaSegmentationAbstract()
  {}

/*
  virtual std::vector<pcl::PointCloud<PointT>>
  computar(Nube n);
*/
//private:

};
#endif

#ifndef PlanarAndEuclidean_DEF
#define PlanarAndEuclidean_DEF
template <typename PointT>
//template <class PointT>
class PlanarAndEuclidean : public EstrategiaSegmentationAbstract<PointT>
{
  typedef typename pcl::PointCloud<PointT> PointCloud;
  //typedef typename pcl::EuclideanClusterExtraction<PointT> EuclideanClusterExtraction;
public:
  /** \brief Constructor that sets default values for member variables. */
  PlanarAndEuclidean ()
  {

  }

  void
  setNube (const pcl::PointCloud<PointT> &input);

  int
  getSizeNube ();

  pcl::PointCloud<PointT>
  getNube ();

protected:
  // Planar Segmentation variables.
  float distance_threshold_ = .009f;
  int max_iterations_ = 1000;
  //pcl::PointCloud<PointT> nube;
  PointCloud nube;
  pcl::EuclideanClusterExtraction<PointT> ec;

};
#endif
