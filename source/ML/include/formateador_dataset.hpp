// Clases: FormateadorDatasetAbstract, SVMFormatter
#include <iostream>
#include "../../utils/include/utils.hpp"
#include "../../descriptor/include/pointfeaturederivadas.hpp"

//#include "../../lib_svm/include/svm.h"



#ifndef FormateadorDatasetAbstract_DEF
#define FormateadorDatasetAbstract_DEF
template<class SignatureT,typename ProblemaT>
class FormateadorDatasetAbstract{

public:
	//Constructor 
	FormateadorDatasetAbstract();

	void almacenarDatasetTmp(pcl::SVMData muestraSVM,
								std::string dirSalidaTmp,
								std::string nombreTmp);


	void dumpearDescriptor(PointFeature<SignatureT> descriptor,
														std::string dirSalidaTmp,
														std::string nombreTmp);

	ProblemaT adaptarDescriptor(PointFeature<SignatureT> descriptor);
};

#endif


#ifndef FormateadorSVM_DEF
#define FormateadorSVM_DEF

template<class SignatureT>
class SVMFormatter: public FormateadorDatasetAbstract<SignatureT,svm_problem> {

public:
	SVMFormatter();
	void generarMuestraSVM(PointFeature<SignatureT> descriptor,pcl::SVMData* muestraSVM);
 	
 	//TODO: VER ESTO...
	svm_problem adaptarDescriptor(PointFeature<SignatureT> descriptor);
};
#endif

/*
#ifndef SVMFormatter_DEF
#define SVMFormatter_DEF

//template<class SignatureT,typename ProblemaT> class SVMFormatter;

template<class SignatureT,typename ProblemaT>
class SVMFormatter : public FormateadorDatasetAbstract<SignatureT,ProblemaT>{
//class SVMFormatter <SignatureT,ProblemaT>: public FormateadorDatasetAbstract<SignatureT,ProblemaT>{
	//Constructor 
	SVMFormatter();
	void generarMuestraSVM(PointFeature<SignatureT> descriptor,pcl::SVMData* muestraSVM);
	ProblemaT adaptarDescriptor(PointFeature<SignatureT> descriptor);
};

#endif
*/