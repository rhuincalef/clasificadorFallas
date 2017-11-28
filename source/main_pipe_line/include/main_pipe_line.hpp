// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include "../../utils/include/utils.hpp"

#include "../../descriptor/include/pointfeaturederivadas.hpp"
#include "../../descriptor/include/descriptor.hpp"
#include "../../ML/include/estrategia_clasificacion.hpp"


#ifndef MainPipeLine_DEF
#define MainPipeLine_DEF
template <class SignatureT>
class MainPipeLine{

public:
	//Constructor 
	MainPipeLine();
	
	//template <class SignatureT> PointFeature<SignatureT> computarNube(std::string pcdNoEscaneado);
	PointFeature<SignatureT> computarNube(std::string pcdNoEscaneado);
	TipoMuestra clasificar(PointFeature<SignatureT> descriptor);


private:
	std::string dirAlmacenamientoCapturas;
	EstrategiaDescriptorsAbstract* estratDescriptor = NULL;
	EstrategiaClasificacionMLAbstract* estratClasificacion = NULL;


//protected:
};
#endif



