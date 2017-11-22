// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include "../../utils/include/utils.hpp"

#ifndef EstrategiaClasificacionMLAbstract_DEF
#define EstrategiaClasificacionMLAbstract_DEF
class EstrategiaClasificacionMLAbstract{

public:
	//Constructor 
	EstrategiaClasificacionMLAbstract();
	EstrategiaClasificacionMLAbstract(std::string formateador,std::string dirSalidaTmp);
	TipoMuestra clasificar(std::string pathDatasetTmp); 

private:
	std::string formateador; //TODO CORREGIR ESTE TIPO POR LA CLASE QUE CORRESPONDE!
	int leerDatasetTmp(std::string pathDatasetTmp);

};
#endif

#ifndef EstrategiaClasificacionSVM_DEF
#define EstrategiaClasificacionSVM_DEF
class EstrategiaClasificacionSVM : public EstrategiaClasificacionMLAbstract
{
  
private:
	std::string pathModeloEntrenado;
public:
	//Constructor 
	EstrategiaClasificacionSVM(std::string pathModeloEntrenado,
								std::string formateador,
								std::string dirSalidaTmp);
};
#endif