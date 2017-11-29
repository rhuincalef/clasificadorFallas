// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include "../../utils/include/utils.hpp"
#include "../include/pointfeature.hpp"
#include "../include/pointfeaturederivadas.hpp"

#include "../../nube/include/nube.hpp"

#ifndef EstrategiaDescriptorsAbstract_DEF
#define EstrategiaDescriptorsAbstract_DEF

template<class PointT,class SignatureT>
class EstrategiaDescriptorsAbstract{
protected:
	std::string pathModeloEntrenado;
	
public:
	//Constructor 
	EstrategiaDescriptorsAbstract();
	//template <class PointT,class SignatureT> PointFeature<SignatureT> generarDescriptor(Nube<PointT>* n);
	PointFeature<SignatureT> generarDescriptor(Nube<PointT>* n);

	std::string getPathModeloEntrenado();

};
#endif

#ifndef ESF_DEF
#define ESF_DEF

template <class PointT>
class ESF : public EstrategiaDescriptorsAbstract<PointT,pcl::ESFSignature640>
{
  
protected:
	std::string pathModeloEntrenado;
public:
	//Constructor 
	ESF();

	//template <class PointT> PointFeature<pcl::ESFSignature640> generarDescriptor(Nube<PointT>* n);
	
};
#endif



#ifndef GRSD_DEF
#define GRSD_DEF
template <class PointT>
class GRSD : public EstrategiaDescriptorsAbstract<PointT,pcl::GRSDSignature21>
{
  

public:
	//Constructor 
	GRSD();

	//template <class PointT> PointFeature<pcl::GRSDSignature21> generarDescriptor(Nube<PointT>* n);

};
#endif


#ifndef FPFH_DEF
#define FPFH_DEF
template <class PointT>
class FPFH : public EstrategiaDescriptorsAbstract<PointT,pcl::FPFHSignature33>
{
public:
	//Constructor 
	FPFH();

	//template <class PointT> PointFeature<pcl::FPFHSignature33> generarDescriptor(Nube<PointT>* n);

};
#endif

