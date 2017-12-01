// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include <pcl/features/esf.h>
#include <pcl/features/fpfh.h>
#include <pcl/features/grsd.h>
#include <pcl/ml/svm_wrapper.h>
#include <pcl/features/normal_3d.h>

#include <pcl/point_types.h>

#include "../../utils/include/utils.hpp"
#include "../../nube/include/nube.hpp"


#ifndef PointFeature_DEF
#define PointFeature_DEF
template <class SignatureT,class PointT> 
class PointFeature{

public:
	//Constructor 
	PointFeature();

	void procesarDescriptorPCL(Nube<PointT>* n);

	void calcularAltoAncho(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud,TipoDimensiones* dimensiones);

	double getDiffAltoAncho();
	typename pcl::PointCloud<SignatureT>::Ptr getDescriptorPCL();

	//virtual void c();
	virtual void computarDescriptor(Nube<pcl::PointXYZRGB>* n);

//private:
protected:
	typename pcl::PointCloud<SignatureT>::Ptr descPCL;
	double diffAltoAncho;

};
#endif
