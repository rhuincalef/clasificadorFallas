// Clases: FormateadorDatasetAbstract, FormateadorDatasetSVM
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

#ifndef FormateadorDatasetSVM_DEF
#define FormateadorDatasetSVM_DEF

template<class SignatureT>
class FormateadorDatasetSVM : public FormateadorDatasetAbstract<SignatureT,svm_problem>
{
  
//private:
public:
	//Constructor 
	FormateadorDatasetSVM();
	
	void generarMuestraSVM(PointFeature<SignatureT> descriptor,pcl::SVMData* muestraSVM);
	
	//svm_problem adaptarDescriptor(PointFeature<SignatureT> descriptor);

	/*void dumpearDescriptor(PointFeature<SignatureT> descriptor,std::string dirSalidaTmp,
								std::string nombreTmp);
	*/
};
#endif