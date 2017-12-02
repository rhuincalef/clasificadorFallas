// Clases: FormateadorDatasetAbstract, SVMFormatter
#include <iostream>
#include "../../utils/include/utils.hpp"
#include "../../descriptor/include/pointfeaturederivadas.hpp"

//#include "../../lib_svm/include/svm.h"



#ifndef FormateadorDatasetAbstract_DEF
#define FormateadorDatasetAbstract_DEF
/*
template<class SignatureT,class ProblemaT,class PointT>
class FormateadorDatasetAbstract{
*/
template<class SignatureT,typename ProblemaT,class PointT,class MuestraT>
class FormateadorDatasetAbstract{

public:
	//Constructor 
	FormateadorDatasetAbstract();
	//SignatureT ab(ProblemaT a);
	void almacenarDatasetTmp(pcl::SVMData muestraSVM,
								std::string dirSalidaTmp,
								std::string nombreTmp);


	/*template <class PointT>
	 void dumpearDescriptor(PointFeature<SignatureT,PointT> descriptor,
														std::string dirSalidaTmp,
														std::string nombreTmp);
	*/

	ProblemaT adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor);

	virtual void adaptarDescriptorAFormatoEspecifico(pcl::SVMData muestraSVM,svm_problem* prob);

	virtual void generarMuestra(PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* descriptor,pcl::SVMData* muestraSVM);
	virtual void generarMuestra(PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* descriptor,pcl::SVMData* muestraSVM);
	/*
	*/
};

#endif


#ifndef FormateadorSVM_DEF
#define FormateadorSVM_DEF

//template<class SignatureT,class ProblemaT,class PointT>
//class SVMFormatter: public FormateadorDatasetAbstract<SignatureT,ProblemaT,PointT> {
template<class SignatureT,class PointT>
class SVMFormatter: public FormateadorDatasetAbstract<SignatureT,svm_problem,PointT,pcl::SVMData> {

public:
	SVMFormatter();
	void generarMuestra(PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* descriptor,pcl::SVMData* muestraSVM);
	void generarMuestra(PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* descriptor,pcl::SVMData* muestraSVM);

	
	virtual void adaptarDescriptorAFormatoEspecifico(pcl::SVMData muestraSVM,svm_problem* prob);

	//void generarMuestraSVM(PointFeature<SignatureT,PointT>* descriptor,pcl::SVMData* muestraSVM);
	//svm_problem adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor);
	
};
#endif


