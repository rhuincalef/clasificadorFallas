// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include "../../utils/include/utils.hpp"
#include "../include/pointfeature.hpp"
#include "../include/pointfeaturederivadas.hpp"

#include "../../nube/include/nube.hpp"


#ifndef EstrategiaDescriptorsAbstract_DEF
#define EstrategiaDescriptorsAbstract_DEF

/*
	Se declara  como tipo plantilla el PointFeatureConcretoT, que representa una instancia generica de las
	subclases de PointFeature.
*/
//template<class PointT,class SignatureT,template<class> class PointFeatureConcretoT>
template<class PointT1>
class EstrategiaDescriptorsAbstract{

protected:
	std::string pathModeloEntrenado;
	
public:
	//Constructor 
	EstrategiaDescriptorsAbstract();
	
	/*
	template<class PointT,class SignatureT,template<class> class PointFeatureConcretoT>
		PointFeature<SignatureT,PointT>* generarDescriptor(Nube<PointT>* n);
	*/
	template<class PointT,class SignatureT,template<class> class PointFeatureConcretoT>
	PointFeature<SignatureT,PointT>* generarDescriptor(Nube<PointT>* n){

		std::cout << "EstrategiaDescriptorsAbstract.generarDescriptor() SUPERCLASE!!!" << std::endl;
		//PointFeatureGRSD<PointT>* featureGRSD (new PointFeatureGRSD<PointT>);
		PointFeatureConcretoT<PointT>* feature (new PointFeatureConcretoT<PointT>);
		feature->procesarDescriptorPCL(n);
		return feature;
	
	}

	//Se establece como virutal este metodo para sobreescribirlo en las clases derivadas y poder
	//acceder al metodo correspondiente para pathModeloEntrenado;
	virtual std::string getPathModeloEntrenado();

};
#endif

#ifndef ESF_DEF
#define ESF_DEF


template<class PointT,class SignatureT,template<class> class PointFeatureConcretoT>
class ESF : public EstrategiaDescriptorsAbstract<PointT>
{
  
protected:
	std::string pathModeloEntrenado;


public:
	//Constructor 
	ESF();

	std::string getPathModeloEntrenado();
	
	//PointFeature<pcl::ESFSignature640,PointT>* generarDescriptor(Nube<PointT>* n);

};
#endif



#ifndef GRSD_DEF
#define GRSD_DEF

template<class PointT,class SignatureT,template<class> class PointFeatureConcretoT>
class GRSD : public EstrategiaDescriptorsAbstract<PointT>
{
  
protected:
	std::string pathModeloEntrenado;

public:
	//Constructor 
	GRSD();

	std::string getPathModeloEntrenado();
	
	//PointFeature<pcl::GRSDSignature21,PointT>* generarDescriptor(Nube<PointT>* n);
	

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
