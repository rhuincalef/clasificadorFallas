#include "../../utils/include/utils.hpp"

#include "../include/estrategia_clasificacion.hpp"

EstrategiaClasificacionMLAbstract::EstrategiaClasificacionMLAbstract(){

}

EstrategiaClasificacionMLAbstract::EstrategiaClasificacionMLAbstract(std::string formateador,std::string dirSalidaTmp){

}

int EstrategiaClasificacionMLAbstract::leerDatasetTmp(std::string pathDatasetTmp){
  return 0;
}

TipoMuestra EstrategiaClasificacionMLAbstract::clasificar(std::string pathDatasetTmp) {
  return TIPO_BACHE;
}


EstrategiaClasificacionSVM::EstrategiaClasificacionSVM(std::string pathModeloEntrenado,std::string formateador,std::string dirSalidaTmp){  
}


