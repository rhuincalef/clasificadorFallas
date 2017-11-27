// Clases: FormateadorDatasetAbstract, FormateadorDatasetSVM
#include <iostream>
#include "../../utils/include/utils.hpp"
#include "../../descriptor/include/pointfeaturederivadas.hpp"

//#include "../../lib_svm/include/svm.h"



#ifndef FormateadorDatasetAbstract_DEF
#define FormateadorDatasetAbstract_DEF
class FormateadorDatasetAbstract{

public:
	//Constructor 
	FormateadorDatasetAbstract();

	void almacenarDatasetTmp(pcl::SVMData muestraSVM,
								std::string dirSalidaTmp,
								std::string nombreTmp);



	template <class SignatureT,class ProblemaT> ProblemaT adaptarDescriptor(PointFeature<SignatureT> descriptor);


	template <class SignatureT> void dumpearDescriptor(PointFeature<SignatureT> descriptor,
														std::string dirSalidaTmp,
														std::string nombreTmp);

};
#endif

#ifndef FormateadorDatasetSVM_DEF
#define FormateadorDatasetSVM_DEF
class FormateadorDatasetSVM : public FormateadorDatasetAbstract
{
  
//private:
public:
	//Constructor 
	FormateadorDatasetSVM();
	
	template <class SignatureT> void generarMuestraSVM(PointFeature<SignatureT> descriptor,
															pcl::SVMData* muestraSVM);
	
	template <class SignatureT> svm_problem adaptarDescriptor(PointFeature<SignatureT> descriptor);

	template <class SignatureT> void dumpearDescriptor(PointFeature<SignatureT> descriptor,
														std::string dirSalidaTmp,
														std::string nombreTmp);
	
};
#endif