// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include "../../utils/include/utils.hpp"
#include "../include/pointfeature.hpp"
#include "../include/pointfeaturederivadas.hpp"

#include "../../nube/include/nube.hpp"


#ifndef EstrategiaDescriptorsAbstract_DEF
#define EstrategiaDescriptorsAbstract_DEF

//template<class PointT,class SignatureT>
//template<class PointT,class SignatureT,class PointFeatureConcretoT >
template<class PointT,class SignatureT,template<class> class PointFeatureConcretoT>
class EstrategiaDescriptorsAbstract{
protected:
	std::string pathModeloEntrenado;
	
public:
	//Constructor 
	EstrategiaDescriptorsAbstract();
	
	PointFeature<SignatureT,PointT>* generarDescriptor(Nube<PointT>* n);

	std::string getPathModeloEntrenado();

};
#endif

#ifndef ESF_DEF
#define ESF_DEF

//template <class SignatureT,class PointT> PointFeatureESF<PointT>;

//class ESF : public EstrategiaDescriptorsAbstract<PointT,pcl::ESFSignature640>
template <class PointT>
//class ESF : public EstrategiaDescriptorsAbstract<PointT,pcl::ESFSignature640,PointFeatureESF<PointT>>
class ESF : public EstrategiaDescriptorsAbstract<PointT,pcl::ESFSignature640,PointFeatureESF>
{
  
protected:
	std::string pathModeloEntrenado;
public:
	//Constructor 
	ESF();

	PointFeature<pcl::ESFSignature640,PointT>* generarDescriptor(Nube<PointT>* n);

	//template <class PointT> PointFeature<pcl::ESFSignature640> generarDescriptor(Nube<PointT>* n);	
};
#endif



#ifndef GRSD_DEF
#define GRSD_DEF
//class GRSD : public EstrategiaDescriptorsAbstract<PointT,pcl::GRSDSignature21>
template <class PointT>
class GRSD : public EstrategiaDescriptorsAbstract<PointT,pcl::GRSDSignature21,PointFeatureGRSD>
{
  

public:
	//Constructor 
	GRSD();
	PointFeature<pcl::GRSDSignature21,PointT>* generarDescriptor(Nube<PointT>* n);

	//template <class PointT> PointFeature<pcl::GRSDSignature21> generarDescriptor(Nube<PointT>* n);

};
#endif

/*
#ifndef FPFH_DEF
#define FPFH_DEF
//class FPFH : public EstrategiaDescriptorsAbstract<PointT,pcl::FPFHSignature33>
template <class PointT>
class FPFH : public EstrategiaDescriptorsAbstract<PointT,pcl::FPFHSignature33,PointFeatureFPFH<PointT>>
{
public:
	//Constructor 
	FPFH();
	//PointFeature<pcl::FPFHSignature33,PointT> generarDescriptor(Nube<PointT>* n);



	//template <class PointT> PointFeature<pcl::FPFHSignature33> generarDescriptor(Nube<PointT>* n);

};
#endif
*/
