// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include <pcl/features/esf.h>
#include <pcl/features/fpfh.h>
#include <pcl/features/grsd.h>
#include <pcl/ml/svm_wrapper.h>
#include <pcl/features/normal_3d.h>

#include <pcl/point_types.h>

#include "../../utils/include/utils.hpp"

/*
#ifndef _TIPO_PUNTO_T
#define _TIPO_PUNTO_T

template <typename PointT> class PointCloud;

#endif
*/

#ifndef PointFeature_DEF
#define PointFeature_DEF
template <typename PointT> class PointFeature{

public:
	//Constructor 
	PointFeature();

private:
	pcl::PointCloud<PointT> descPCL;
	double diffAltoAncho;

};
#endif

/*
#ifndef PointFeatureESF_DEF
#define PointFeatureESF_DEF

class PointFeatureESF : public PointFeature {

public:
	//Constructor 
	PointFeatureESF();

private:
	pcl::PointCloud<pcl::ESFSignature640> descPCL;

};
#endif


#ifndef PointFeatureGRSD_DEF
#define PointFeatureGRSD_DEF
class PointFeatureGRSD : public PointFeature
{
public:
	//Constructor 
	PointFeatureGRSD();
  
private:
	pcl::PointCloud<pcl::GRSDSignature21> descPCL;

	
};
#endif

#ifndef PointFeatureFPFH_DEF
#define PointFeatureFPFH_DEF
class PointFeatureFPFH : public PointFeature
{
public:
	//Constructor 
	PointFeatureFPFH();  
//private:
	
};
#endif


*/