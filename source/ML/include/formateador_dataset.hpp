// Clases: FormateadorDatasetAbstract, SVMFormatter
#include <iostream>
#include "../../utils/include/utils.hpp"
#include "../../descriptor/include/pointfeaturederivadas.hpp"

//#include "../../lib_svm/include/svm.h"



#ifndef FormateadorDatasetAbstract_DEF
#define FormateadorDatasetAbstract_DEF
template<class SignatureT,class ProblemaT,class PointT>
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
	/*
	*/
};

#endif


#ifndef FormateadorSVM_DEF
#define FormateadorSVM_DEF

//template<class SignatureT,class ProblemaT,class PointT>
//class SVMFormatter: public FormateadorDatasetAbstract<SignatureT,ProblemaT,PointT> {
template<class SignatureT,class PointT>
class SVMFormatter: public FormateadorDatasetAbstract<SignatureT,svm_problem,PointT> {

public:
	SVMFormatter();

	
	void generarMuestraSVM(PointFeature<SignatureT,PointT>* descriptor,pcl::SVMData* muestraSVM);
	//ProblemaT adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor);
	svm_problem adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor);
	
};
#endif


