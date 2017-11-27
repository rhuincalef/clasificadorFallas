// Descriptor ESF con downsampling + diff. Alto y Ancho -->


#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
//#include <pcl/features/normal_3d.h>
#include <pcl/features/fpfh.h>
#include <pcl/features/vfh.h>
#include <pcl/features/grsd.h>
#include <pcl/features/esf.h>
#include <pcl/features/normal_3d_omp.h>

// Mediciones
#include <pcl/console/time.h>
// using for print_highlight, print_value, print_info
#include <pcl/console/print.h>


#include <boost/filesystem.hpp>
// command parse
#include <pcl/console/parse.h>
#include <math.h>

#include <pcl/features/principal_curvatures.h>

#include <pcl/ml/svm_wrapper.h>
//#include <pcl/filters/uniform_sampling.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/surface/convex_hull.h>

#include <pcl/common/distances.h>
#include <pcl/surface/gp3.h>
#include <pcl/features/moment_of_inertia_estimation.h>

#include "../../utils/include/utils.hpp"

#include "../include/descriptor.hpp"


EstrategiaDescriptorsAbstract::EstrategiaDescriptorsAbstract(){

}
std::string EstrategiaDescriptorsAbstract::getPathModeloEntrenado(){
	return this->pathModeloEntrenado;
}

/************************************** Estrategia ESF **************************************/
ESF::ESF(){
	this->pathModeloEntrenado = TRAIN_MODEL_ESF_DIR_DEFAULT + "/" + TRAIN_MODEL_NAME_DEFAULT;
}

template <class PointT> PointFeature<pcl::ESFSignature640> ESF::generarDescriptor(Nube<PointT> n){

	pcl::PointCloud<PointT> downsampling = n.getDownsamplingCloud();

	//Se procesa el descrptor especifico de la estrategia
	PointFeatureESF* featureESF (new PointFeatureESF);
	featureESF->procesarDescriptorPCL(n);
	return featureESF;
}





/************************************** Estrategia GRSD **************************************/
GRSD::GRSD(){
	this->pathModeloEntrenado = TRAIN_MODEL_GRSD_DIR_DEFAULT + "/" + TRAIN_MODEL_NAME_DEFAULT;
}


template <class PointT> PointFeature<pcl::GRSDSignature21> GRSD::generarDescriptor(Nube<PointT> n){

	pcl::PointCloud<PointT> downsampling = n.getDownsamplingCloud();

	//Se procesa el descrptor especifico de la estrategia
	PointFeatureGRSD* featureGRSD (new PointFeatureESF);
	featureGRSD->procesarDescriptorPCL(n);
	return featureGRSD;

}

