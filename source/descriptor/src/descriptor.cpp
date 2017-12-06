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



/************************************** EstrategiaDescriptorsAbstract **************************************/

/*
//BACKUP!
template<class PointT,class SignatureT>
EstrategiaDescriptorsAbstract<PointT,SignatureT>::EstrategiaDescriptorsAbstract(){

}

template<class PointT,class SignatureT>
std::string EstrategiaDescriptorsAbstract<PointT,SignatureT>::getPathModeloEntrenado(){
	return this->pathModeloEntrenado;
}

template<class PointT,class SignatureT>
PointFeature<SignatureT,PointT>* EstrategiaDescriptorsAbstract<PointT,SignatureT>::generarDescriptor(Nube<PointT>* n){
	std::cout << "EstrategiaDescriptorsAbstract.generarDescriptor() SUPERCLASE!!!" << std::endl;
}
*/


template<class PointT>
EstrategiaDescriptorsAbstract<PointT>::EstrategiaDescriptorsAbstract(){
	std::cout << "Construido EstrategiaDescriptorsAbstract!: "<< std::endl;

}

template<class PointT>
std::string EstrategiaDescriptorsAbstract<PointT>::getPathModeloEntrenado(){
	return this->pathModeloEntrenado;
}

/*
template<class PointT,class SignatureT,template<class> class PointFeatureConcretoT>
PointFeature<SignatureT,PointT>* EstrategiaDescriptorsAbstract<PointT>::generarDescriptor(Nube<PointT>* n){	
	std::cout << "EstrategiaDescriptorsAbstract.generarDescriptor() SUPERCLASE!!!" << std::endl;
	//PointFeatureGRSD<PointT>* featureGRSD (new PointFeatureGRSD<PointT>);
	PointFeatureConcretoT<PointT>* feature (new PointFeatureConcretoT<PointT>);
	feature->procesarDescriptorPCL(n);
	return feature;
}
*/





/************************************** Estrategia ESF **************************************/
template<class PointT,class SignatureT,template<class> class PointFeatureConcretoT>
ESF<PointT,SignatureT,PointFeatureConcretoT>::ESF(){
	this->pathModeloEntrenado = ROOT_MODELO + TRAIN_MODEL_ESF_DIR_DEFAULT + TRAIN_MODEL_NAME_DEFAULT;
	std::cout << "ESF->pathModeloEntrenado: "<< this->pathModeloEntrenado << std::endl;
}


/*
template<class PointT,class SignatureT,template<class> class PointFeatureConcretoT>
PointFeature<pcl::ESFSignature640,PointT>* ESF<PointT,SignatureT,PointFeatureConcretoT>::generarDescriptor(Nube<PointT>* n){
	PointFeatureESF<PointT>* featureESF (new PointFeatureESF<PointT>);
	featureESF->procesarDescriptorPCL(n);
	return featureESF;
}
*/

template<class PointT,class SignatureT,template<class> class PointFeatureConcretoT>
std::string ESF<PointT,SignatureT,PointFeatureConcretoT>::getPathModeloEntrenado(){
	return this->pathModeloEntrenado;
}




/************************************** Estrategia GRSD **************************************/
template<class PointT,class SignatureT,template<class> class PointFeatureConcretoT>
GRSD<PointT,SignatureT,PointFeatureConcretoT>::GRSD(){
	this->pathModeloEntrenado = ROOT_MODELO + TRAIN_MODEL_GRSD_DIR_DEFAULT + TRAIN_MODEL_NAME_DEFAULT;
	std::cout << "GRSD->pathModeloEntrenado: "<< this->pathModeloEntrenado << std::endl;
}



template<class PointT,class SignatureT,template<class> class PointFeatureConcretoT>
std::string GRSD<PointT,SignatureT,PointFeatureConcretoT>::getPathModeloEntrenado(){
	return this->pathModeloEntrenado;
}


/*
template<class PointT,class SignatureT,template<class> class PointFeatureConcretoT>
PointFeature<pcl::GRSDSignature21,PointT>* GRSD<PointT,SignatureT,PointFeatureConcretoT>::generarDescriptor(Nube<PointT>* n){
	std::cout << "Generar descriptor GRSD Subclase! " << std::endl;
	PointFeatureGRSD<PointT>* featureGRSD (new PointFeatureGRSD<PointT>);
	featureGRSD->procesarDescriptorPCL(n);
	return featureGRSD;

}
*/


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

template class EstrategiaDescriptorsAbstract<pcl::PointXYZRGB>;
//PointT,SignatureT,PointFeatureT
/*
template PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* EstrategiaDescriptorsAbstract::generarDescriptor<pcl::PointXYZRGB,pcl::ESFSignature640,PointFeatureESF>();
template PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* EstrategiaDescriptorsAbstract::generarDescriptor<pcl::PointXYZRGB,pcl::GRSDSignature21,PointFeatureGRSD>();
*/

template class ESF<pcl::PointXYZRGB, pcl::ESFSignature640,PointFeatureESF>;
template class GRSD<pcl::PointXYZRGB, pcl::GRSDSignature21,PointFeatureGRSD>;
/*
template class EstrategiaDescriptorsAbstract<pcl::PointXYZRGB, pcl::ESFSignature640,PointFeatureESF>;
template class EstrategiaDescriptorsAbstract<pcl::PointXYZRGB, pcl::GRSDSignature21,PointFeatureGRSD>;

template class ESF<pcl::PointXYZRGB>;
template class GRSD<pcl::PointXYZRGB>;
*/





