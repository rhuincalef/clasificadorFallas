// Clases: FormateadorDatasetAbstract, FormateadorDatasetSVM
#include <iostream>
#include "../../utils/include/utils.hpp"

#ifndef FormateadorDatasetAbstract_DEF
#define FormateadorDatasetAbstract_DEF
class FormateadorDatasetAbstract{

public:
	//Constructor 
	FormateadorDatasetAbstract();

	template <class SignatureT> void dumpearDescriptor(PointFeature<SignatureT> descriptor,
														std::string dirSalidaTmp,
														std::string nombreTmp);

	template <class SignatureT> void FormateadorDatasetAbstract::generarMuestraSVM(
													PointFeature<SignatureT> descriptor,
													pcl::SVMData* muestraSVM);



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
	
	//Genera las features de una muestra y las guarda en un vector
	void FormateadorDatasetSVM::almacenarSVMTmp(pcl::SVMData muestraSVM,
												std::string dirSalidaTmp,
												std::string nombreTmp);

};
#endif