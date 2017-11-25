#include "pointfeature.hpp"

#ifndef PointFeatureESF_DEF
#define PointFeatureESF_DEF

template<typename PointT> class PointFeatureESF : public PointFeature<PointT> {

public:
	//Constructor 
	PointFeatureESF();

private:
	pcl::PointCloud<pcl::ESFSignature640> descPCL;

};
#endif


#ifndef PointFeatureGRSD_DEF
#define PointFeatureGRSD_DEF
template<typename PointT> class PointFeatureGRSD : public PointFeature<PointT> {

public:
	//Constructor 
	PointFeatureGRSD();
  
private:
	pcl::PointCloud<pcl::GRSDSignature21> descPCL;

};
#endif
