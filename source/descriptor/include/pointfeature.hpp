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
template <class SignatureT> 
class PointFeature{

public:
	//Constructor 
	PointFeature();

	template<typename PointT> typename pcl::PointCloud<SignatureT>::Ptr procesarDescriptorPCL(Nube<PointT> n);


	
	template <class PointT> void calcularAltoAncho(pcl::PointCloud<PointT>* cloud,
														TipoDimensiones* dimensiones);
	
	

//private:
protected:
	typename pcl::PointCloud<SignatureT>::Ptr descPCL;
	double diffAltoAncho;

};
#endif
