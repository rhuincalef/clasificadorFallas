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

	//void procesarDescriptorPCL(Nube<PointT>* n);
	void procesarDescriptorPCL(Cluster<PointT>* n);

	void calcularAltoAncho(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud,TipoDimensiones* dimensiones);

	virtual void computarDescriptor(Cluster<pcl::PointXYZRGB>* n);
	//virtual void computarDescriptor(Nube<pcl::PointXYZRGB>* n);
	

	double getDiffAltoAncho();
	virtual typename pcl::PointCloud<SignatureT> getDescriptorPCL();

	virtual int getTamanioDescriporPCL();

	double getAlto();
	double getAncho();
	
protected:
	typename pcl::PointCloud<SignatureT> descPCL;
	double diffAltoAncho;
	//AGREGADO
	double alto;
	double ancho;
	int tamanioDescriptor;

};
#endif
