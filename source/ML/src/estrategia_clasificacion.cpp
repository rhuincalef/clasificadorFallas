#include "../include/estrategia_clasificacion.hpp"


//Constructores 
//template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
EstrategiaClasificacionMLAbstract::EstrategiaClasificacionMLAbstract(){

}

/*
//template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
template <class SignatureT,class PointT,class ProblemaT>
ProblemaT EstrategiaClasificacionMLAbstract::adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor){
	std::cout << "estrategiaClasificacion.adaptarDescriptor() SUPERCLASE!!!" << std::endl;
	ProblemaT p = this->formateador->template adaptarDescriptor<SignatureT,PointT,ProblemaT>(descriptor);
	std::cout << "Fin estrategiaClasificacion.adaptarDescriptor() ..." << std::endl<< std::endl;
	return p;
}
*/

/*
template <class SignatureT,class PointT,class ProblemaT,class ModeloT>
TipoMuestra EstrategiaClasificacionMLAbstract::clasificar(std::string pathModeloEntrenado,
															PointFeature<SignatureT,PointT>* descriptor){
	
	std::cout << "Inicio EstrategiaClasificacionMLAbstract.clasificar() SUPERCLASE ..." << std::endl;

	ProblemaT problema = this->template adaptarDescriptor<SignatureT,PointT,ProblemaT>(descriptor);
	//svm_model* modelo;
	ModeloT* modelo;
	modelo = this->cargarModelo(pathModeloEntrenado);

	this->predecir(modelo,descriptor);

}
*/

svm_model* EstrategiaClasificacionMLAbstract::cargarModelo(std::string pathModeloEntrenado){
	std::cout << "cargarModelo() SUPERCLASE!!!" << std::endl;
}

TipoMuestra EstrategiaClasificacionMLAbstract::predecir(svm_model* modelo,svm_problem problema){
	std::cout << "estrategiaClasificacion.predecir() de SUPERCLASE!!!" << std::endl;	
}

void EstrategiaClasificacionMLAbstract::setFormateador(FormateadorDatasetAbstract* f){
	this->formateador = f;
}

FormateadorDatasetAbstract* EstrategiaClasificacionMLAbstract::getFormateador(){
	return this->formateador;
}

Parametrizador EstrategiaClasificacionMLAbstract::parametrizador_;

bool EstrategiaClasificacionMLAbstract::configurado_ = false;

void EstrategiaClasificacionMLAbstract::configurarParametrizador()
{
  if (EstrategiaClasificacionMLAbstract::configurado_)
    return;
  EstrategiaClasificacionMLAbstract::parametrizador_.setNombre("clasificador");
  Parametro p1;
  p1.setNombre("tipo");
  p1.setTipoValorEsperado("string");
  std::vector<std::string> v;
  for (int i = 0; i < sizeof FormateadorClasificadorTypes / sizeof FormateadorClasificadorTypes[0]; ++i)
  {
  	v.push_back(FormateadorClasificadorTypes[i]);
  }
  p1.setValorEsperado(v);
  EstrategiaClasificacionMLAbstract::parametrizador_.agregar(p1);
  Parametro p2;
  p2.setNombre("path_modelo");
  p2.setTipoValorEsperado("string");
  EstrategiaClasificacionMLAbstract::parametrizador_.agregar(p2);
  EstrategiaClasificacionMLAbstract::configurado_ = true;
}

Parametrizador EstrategiaClasificacionMLAbstract::getParametrizador()
{
  EstrategiaClasificacionMLAbstract::configurarParametrizador();
  return EstrategiaClasificacionMLAbstract::parametrizador_;
}

/************************** Estrategia clasificacion SVM **************************/


//template <class SignatureT,class PointT>
template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
EstrategiaClasificacionSVM<SignatureT,ProblemaT,ModeloT,PointT>::EstrategiaClasificacionSVM(){

	//template<class PointT,class SignatureT,class ProblemaT,class MuestraT>
	this->formateador = new SVMFormatter<PointT,SignatureT,ProblemaT,pcl::SVMData>();
	std::cout << "Instanciada la EstrategiaClasificacionSVM" << std::endl;

}



/*
	Carga el modelo.dat a memoira y lo retorna
*/
//struct svm_model *svm_load_model(const char *model_file_name);
//


template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
svm_model* EstrategiaClasificacionSVM<SignatureT,ProblemaT,ModeloT,PointT>::cargarModelo(
																			std::string pathModeloEntrenado){
	
	//struct svm_model* modelo;
	svm_model* modelo;
	std::cout << "Inicio de EstrategiaClasificacionSVM.cargarModelo()..." << std::endl;
	if ( (modelo=svm_load_model(pathModeloEntrenado.c_str() )) ==0) 
	{
		//fprintf(stderr,"can't open model file %s\n",argv[i+1]);
		std::cout << "No se puede abrir el modelo entrenado!: "<< pathModeloEntrenado.c_str()  << std::endl; 
		//exit(1);
		return 1;
	}
	std::cout << "Leido el modelo: "<< pathModeloEntrenado << std::endl; 
	std::cout << "Fin de EstrategiaClasificacionSVM.cargarModelo()..." << std::endl << std::endl;
	return modelo;
}





/*
  struct svm_problem
  {
    int l; //Cantidad de muestras de training
    double *y; //Arreglo de labels de las muestras

    struct svm_node **x; //Arreglo de svm_node, donde cada svm_node es un vector de entrenamiento para la SVM
  };
	//double svm_predict (const struct svm_model *model, const struct svm_node *x);
*/

template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
TipoMuestra EstrategiaClasificacionSVM<SignatureT,ProblemaT,ModeloT,PointT>::predecir(svm_model* modelo,
																		svm_problem problema){
	std::cout << "En EstrategiaClasificacionSVM.predecir()" << std::endl;

	//int result = (int) svm_predict(modelo, *(descriptor.x) );
	/*
	struct svm_model modelo2;
	modelo2 = modelo;
	int result = (int) svm_predict(&modelo2, *(problema.x) );
	*/
	int result = (int) svm_predict(modelo, *(problema.x) );
	switch(result) {
		case TIPO_BACHE: 
			std::cout << "Muestra clasificada como: BACHE" << std::endl;
			return TIPO_BACHE;

	    case TIPO_GRIETA:
			std::cout << "Muestra clasificada como: GRIETA" << std::endl; 
	        return TIPO_GRIETA;
	}
	std::cout << "Fin EstrategiaClasificacionSVM.predecir()" << std::endl;	
}


/*	
template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
TipoMuestra EstrategiaClasificacionSVM<SignatureT,ProblemaT,ModeloT,PointT>::clasificar(
																	std::string pathModeloEntrenado){
	

	std::cout << "Inicio estrategiaClasificacion.clasificar() ..." << std::endl;

	ProblemaT problema = this->estratClasificacion->template adaptarDescriptor<>(descriptor);
	//svm_model* modelo;
	ModeloT* modelo;
	modelo = this->cargarModelo(pathModeloEntrenado);

	this->predecir(modelo,descriptor);
}
*/

/*
	Instanciacion explicita del metodo que tiene template. Se aplica para metodos y clases que tienen la 
	definicion de sus templates en archivos .hpp y .cpp separados. 

	Se definen las especializaciones de los tipos genericos de las clases templates,
	SOLAMENTE para aquellos metodos que tengan una implementacion(aunque sea de cuerpo vacio).
	Si existen metodos genericos que no tengan implementacion se retornara error de linkeo.
*/

template class EstrategiaClasificacionSVM<pcl::ESFSignature640,svm_problem,svm_model,pcl::PointXYZRGB>;
template class EstrategiaClasificacionSVM<pcl::GRSDSignature21,svm_problem,svm_model,pcl::PointXYZRGB>;


/*
template class EstrategiaClasificacionMLAbstract<pcl::ESFSignature640,svm_problem,svm_model,pcl::PointXYZRGB>;
template class EstrategiaClasificacionMLAbstract<pcl::GRSDSignature21,svm_problem,svm_model,pcl::PointXYZRGB>;

template class EstrategiaClasificacionSVM<pcl::ESFSignature640,pcl::PointXYZRGB>;
template class EstrategiaClasificacionSVM<pcl::GRSDSignature21,pcl::PointXYZRGB>;
*/



