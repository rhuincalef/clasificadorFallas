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



template<class PointT,class SignatureT>
EstrategiaDescriptorsAbstract<PointT,SignatureT>::EstrategiaDescriptorsAbstract(){

}

template<class PointT,class SignatureT>
std::string EstrategiaDescriptorsAbstract<PointT,SignatureT>::getPathModeloEntrenado(){
	return this->pathModeloEntrenado;
}

template<class PointT,class SignatureT>
PointFeature<SignatureT,PointT>* EstrategiaDescriptorsAbstract<PointT,SignatureT>::generarDescriptor(Nube<PointT>* n){

}

/*
template <class PointT,class SignatureT> PointFeature<SignatureT> generarDescriptor(Nube<PointT>* n){
	
}
*/

/************************************** Estrategia ESF **************************************/
template <class PointT>
ESF<PointT>::ESF(){
	this->pathModeloEntrenado = TRAIN_MODEL_ESF_DIR_DEFAULT + "/" + TRAIN_MODEL_NAME_DEFAULT;
}

template <class PointT>
PointFeature<pcl::ESFSignature640,PointT>* ESF<PointT>::generarDescriptor(Nube<PointT>* n){

	//typename pcl::PointCloud<PointT>::Ptr downsampling = n->getDownsamplingCloud();

	//Se procesa el descrptor especifico de la estrategia
	//PointFeatureESF<pcl::ESFSignature640,PointT>* featureESF (new PointFeatureESF<pcl::ESFSignature640,PointT>);
	PointFeatureESF<PointT>* featureESF (new PointFeatureESF<PointT>);
	featureESF->procesarDescriptorPCL(n);
	return featureESF;
}





/************************************** Estrategia GRSD **************************************/
template <class PointT>
GRSD<PointT>::GRSD(){
	this->pathModeloEntrenado = TRAIN_MODEL_GRSD_DIR_DEFAULT + "/" + TRAIN_MODEL_NAME_DEFAULT;
}


template <class PointT>
PointFeature<pcl::GRSDSignature21,PointT>* GRSD<PointT>::generarDescriptor(Nube<PointT>* n){

	//pcl::PointCloud<PointT>::Ptr downsampling = n->getDownsamplingCloud();

	//Se procesa el descrptor especifico de la estrategia
	//PointFeatureGRSD<pcl::GRSDSignature21,PointT>* featureGRSD (new PointFeatureGRSD<pcl::GRSDSignature21,PointT>);
	PointFeatureGRSD<PointT>* featureGRSD (new PointFeatureGRSD<PointT>);
	featureGRSD->procesarDescriptorPCL(n);
	return featureGRSD;

}


/*
namespace N {
  template<class T> class Y { void mf() { } }; // template definition
}
// template class Y<int>; // error: class template Y not visible in the global namespace
using N::Y;
// template class Y<int>; // error: explicit instantiation outside 
                          // of the namespace of the template
template class N::Y<char*>;      // OK: explicit instantiation
template void N::Y<double>::mf(); // OK: explicit instantiation

*/


/*
	Instanciacion explicita del metodo que tiene template. Se aplica para metodos y clases que tienen la 
	definicion de sus templates en archivos .hpp y .cpp separados. 

	Se definen las especializaciones de los tipos genericos de las clases templates,
	SOLAMENTE para aquellos metodos que tengan una implementacion(aunque sea de cuerpo vacio).
	Si existen metodos genericos que no tengan implementacion se retornara error de linkeo.
*/

template class EstrategiaDescriptorsAbstract<pcl::PointXYZRGB, pcl::ESFSignature640>;
template class EstrategiaDescriptorsAbstract<pcl::PointXYZRGB, pcl::GRSDSignature21>;
template class EstrategiaDescriptorsAbstract<pcl::PointXYZRGB, pcl::FPFHSignature33>;

template class ESF<pcl::PointXYZRGB>;
template class GRSD<pcl::PointXYZRGB>;
template class FPFH<pcl::PointXYZRGB>;





