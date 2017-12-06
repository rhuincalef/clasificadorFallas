// segmentation.hpp
// c++ standar import
#include <iostream>
#include <vector>
// PCLs import
#include <pcl/point_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/features/principal_curvatures.h>
#include <pcl/features/normal_3d_omp.h>
// 
#include "../../utils/include/utils.hpp"
#include "../../nube/include/nube.hpp"

#ifndef EstrategiaSegmentationAbstract_DEF
#define EstrategiaSegmentationAbstract_DEF
template <typename PointT>
class EstrategiaSegmentationAbstract
{

public:
  //Constructor 
  EstrategiaSegmentationAbstract()
  {}

  virtual std::vector<pcl::PointCloud<PointT>>
  computar(pcl::PointCloud<PointT> &input);

};
#endif

#ifndef PlanarAndEuclidean_DEF
#define PlanarAndEuclidean_DEF
template <typename PointT>
class PlanarAndEuclidean : public EstrategiaSegmentationAbstract<PointT>
{

public:
  /** \brief Constructor that sets default values for member variables. */
  PlanarAndEuclidean ()
  {

  }

  /** \brief Returns the distance threshold. If the distance between two points is less or equal to
    * distance threshold value, then those points assumed to be neighbouring points.
    */
  float
  getDistanceThreshold () const;

  /** \brief Allows to set distance threshold.
    * \param[in] thresh new threshold value for neighbour test
    */
  void
  setDistanceThreshold (float thresh);

  /** \brief Get the minimum number of points that a cluster needs to contain in order to be considered valid. */
  int
  getMinClusterSize () const;

  /** \brief Set the minimum number of points that a cluster needs to contain in order to be considered valid.
    * \param[in] min_cluster_size the minimum cluster size
    */
  void 
  setMinClusterSize (int min_cluster_size);

  int
  getMaxClusterSize () const;

  void
  setMaxClusterSize (int max_cluster_size);

  int 
  getMaxIterations () const;

  void 
  setMaxIterations (int max_iterations);

  double 
  getClusterTolerance () const;

  void
  setClusterTolerance (double tolerance);

  /* Uilizados en 1er test - Deprecated */
  void
  setNube (const pcl::PointCloud<PointT> &input);

  int
  getSizeNube ();

  pcl::PointCloud<PointT>
  getNube ();

  std::vector<pcl::PointCloud<PointT>>
  computar(pcl::PointCloud<PointT> &input);
  /* Fin Uilizados en 1er test - Deprecated */

  void
  setNube (Nube<PointT> &n);

  Nube<PointT>
  getNube() const;

  //computar(pcl::PointCloud<PointT>::Ptr &input);
  std::vector<pcl::PointCloud<PointT>>
  computar ();

  void
  planarSegmentation(const pcl::PointCloud<PointT> &input, pcl::PointCloud<PointT> &cloud_no_plane, pcl::PointCloud<PointT> &cloud_plane);

protected:
  // Planar Segmentation variables.
  float distance_threshold_ = .009f;
  int max_iterations_ = 1000;
  // Euclidean Cluster Extraction
  float tolerance_ = .023f;
  int min_cluster_size_ = 220;
  int max_cluster_size_ = 25000;
  pcl::PointCloud<PointT> nube;
  Nube<PointT> nube_;
  pcl::SACSegmentation<PointT> sac_seg_;
  pcl::ExtractIndices<PointT> extract_;
  pcl::EuclideanClusterExtraction<PointT> ec;

  /*
  void
  planarSegmentation(const pcl::PointCloud<PointT> &input, pcl::PointCloud<PointT> cloud_no_plane, pcl::PointCloud<PointT> cloud_plane);
  */
  
  void
  euclideanClusterExtraction(const pcl::PointCloud<PointT> &input, std::vector<pcl::PointCloud<PointT>> &clusters_cloud);

  /*
  TODO: cambiar nombre metodo.
    Metodo usado por euclideanClusterExtraction para separar los cluster que cumplan con lo siguiente:
    if (!(pc1>0.003 && pc1<0.06))
      continue;
    if (!(pc2>0.0012 && pc2<0.0155))
      continue;
    Donde, pc1 es maxPrincipalCurvature y pc2 es minPrincipalCurvature
  */
  bool
  principalCurvaturesEstimationProm(typename pcl::PointCloud<PointT>::Ptr input);

};
#endif
