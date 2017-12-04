//Se agrega esta macro de preprocesador para que no se defina el TipoMuestra mas de una vez con cada #include 
#include <string>

#ifndef _TIPO_MUESTRA
#define _TIPO_MUESTRA

enum TipoMuestra {
	TIPO_BACHE = 1,
	TIPO_GRIETA  = 2
};
#endif

#ifndef _TIPO_ESTADISTICAS
#define _TIPO_ESTADISTICAS

struct TipoEstadisticas{
	int cantMuestrasTotal = 0;
	int cantMuestrasTraining = 0;
	int cantMuestrasTesting = 0;
	float tiempoTotalProcesamiento = 0.0;//Minutos
};
#endif


#ifndef _TIPO_DIMENSIONES
#define _TIPO_DIMENSIONES

typedef struct {
  float ancho;
  float alto;
  float profundidad;
  /*
  float anchoMin;
  float anchoMax;
  float altoMin;
  float altoMax;
  */
} TipoDimensiones;
#endif


//Paths a los modelos entrenados (previamente a la ejecucion del script) para levantar el modelo entrenado
// segun el tipo de descriptor  
//
#ifndef MODEL_TRAINED_PATHS_DEF
#define MODEL_TRAINED_PATHS_DEF

//TODO: CAMBIAR EL ROOT DEL DIR RAIZ CON LOS MODELOS ENTRENADOS
const std::string ROOT_MODELO = "/home/rodrigo/TESINA-2016-KINECT/MACHINE_LEARNING/clasificadorFallas/";

const std::string TRAIN_MODEL_NAME_DEFAULT = "modelo.dat";

const std::string TRAIN_MODEL_ESF_DIR_DEFAULT = "modelo_esf/";
const std::string TRAIN_MODEL_GRSD_DIR_DEFAULT = "modelo_grsd/";

#endif





