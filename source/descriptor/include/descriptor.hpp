// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include "../../utils/include/utils.hpp"

#ifndef EstrategiaDescriptorsAbstract_DEF
#define EstrategiaDescriptorsAbstract_DEF
class EstrategiaDescriptorsAbstract{

public:
	//Constructor 
	EstrategiaDescriptorsAbstract();

//private:

};
#endif

#ifndef ESF_DEF
#define ESF_DEF
class ESF : public EstrategiaDescriptorsAbstract
{
  
private:
	std::string pathModeloEntrenado;
public:
	//Constructor 
	ESF();
	
};
#endif



#ifndef GRSD_DEF
#define GRSD_DEF
class GRSD : public EstrategiaDescriptorsAbstract
{
  
private:
	std::string pathModeloEntrenado;
public:
	//Constructor 
	GRSD();
	
};
#endif


#ifndef FPFH_DEF
#define FPFH_DEF
class FPFH : public EstrategiaDescriptorsAbstract
{
  
private:
	std::string pathModeloEntrenado;
public:
	//Constructor 
	FPFH();
	
};
#endif

