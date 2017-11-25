//Se agrega esta macro de preprocesador para que no se defina el TipoMuestra mas de una vez con cada #include 
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
  float anchoMin;
  float anchoMax;
  float altoMin;
  float altoMax;
} TipoDimensiones;
#endif
