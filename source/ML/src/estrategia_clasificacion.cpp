#include "../../utils/include/utils.hpp"

#include "../include/estrategia_clasificacion.hpp"


//Constructores 
template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
EstrategiaClasificacionMLAbstract<SignatureT, ProblemaT,ModeloT,PointT>::EstrategiaClasificacionMLAbstract(){

}

template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
ProblemaT EstrategiaClasificacionMLAbstract<SignatureT, ProblemaT,ModeloT,PointT>::adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor){
	
	std::cout << "estrategiaClasificacion.adaptarDescriptor() SUPERCLASE!!!" << std::endl;
	//std::cout << "Inicio estrategiaClasificacion.adaptarDescriptor() ..." << std::endl;
	ProblemaT p = this->formateador->adaptarDescriptor(descriptor);
	std::cout << "Fin estrategiaClasificacion.adaptarDescriptor() ..." << std::endl<< std::endl;
	return p;
}

/*
template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
ModeloT* EstrategiaClasificacionMLAbstract<SignatureT, ProblemaT,ModeloT,PointT>::cargarModelo(std::string pathModeloEntrenado){

}
*/


template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
svm_model* EstrategiaClasificacionMLAbstract<SignatureT, ProblemaT,ModeloT,PointT>::cargarModelo(std::string pathModeloEntrenado){
	std::cout << "cargarModelo() SUPERCLASE!!!" << std::endl;
}


template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
TipoMuestra EstrategiaClasificacionMLAbstract<SignatureT, ProblemaT,ModeloT,PointT>::clasificar(std::string pathModeloEntrenado, ProblemaT descriptor){

	std::cout << "estrategiaClasificacion de SUPERCLASE!!!" << std::endl;
	std::cout << "Inicio estrategiaClasificacion.clasificar() ..." << std::endl;
	//svm_model* modelo;
	ModeloT* modelo;
	modelo = this->cargarModelo(pathModeloEntrenado);


	this->predecir(modelo,descriptor);

	/*	
	int result = (int) svm_predict(modelo, *(descriptor.x) );
	switch(result) {
		case TIPO_BACHE: 
			std::cout << "Muestra clasificada como: BACHE" << std::endl;
			return TIPO_BACHE;

	    case TIPO_GRIETA:
			std::cout << "Muestra clasificada como: GRIETA" << std::endl; 
	        return TIPO_GRIETA;
	}
	*/
}


template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
TipoMuestra EstrategiaClasificacionMLAbstract<SignatureT, ProblemaT,ModeloT,PointT>::predecir(svm_model* modelo,
																								svm_problem problema){

}


/************************** Estrategia clasificacion SVM **************************/


template <class SignatureT,class PointT>
EstrategiaClasificacionSVM<SignatureT,PointT>::EstrategiaClasificacionSVM(){
	this->formateador = new SVMFormatter<SignatureT,PointT>();
	std::cout << "Instanciada la EstrategiaClasificacionSVM" << std::endl;
}



/*
	Carga el modelo.dat a memoira y lo retorna
*/
//struct svm_model *svm_load_model(const char *model_file_name);
//

template <class SignatureT,class PointT>
svm_model* EstrategiaClasificacionSVM<SignatureT,PointT>::cargarModelo(std::string pathModeloEntrenado){
	
	//struct svm_model* modelo;
	svm_model* modelo;
	std::cout << "Inicio de EstrategiaClasificacionSVM.cargarModelo()..." << std::endl;
	if ( (modelo=svm_load_model(pathModeloEntrenado.c_str() )) ==0) 
	{
		//fprintf(stderr,"can't open model file %s\n",argv[i+1]);
		std::cout << "No se puede abrir el modelo entrenado!: "<< pathModeloEntrenado.c_str()  << std::endl; 
		exit(1);
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
template <class SignatureT,class PointT>
TipoMuestra EstrategiaClasificacionSVM<SignatureT,PointT>::predecir(svm_model* modelo,
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


template <class SignatureT,class PointT>
TipoMuestra EstrategiaClasificacionSVM<SignatureT,PointT>::clasificar(std::string pathModeloEntrenado,
																		svm_problem descriptor){
	
	/*
	//struct svm_model* modelo;
	//ModeloT* modelo;
	std::cout << "Inicio estrategiaClasificacion.clasificar() ..." << std::endl;
	svm_model* modelo;
	modelo = cargarModelo(pathModeloEntrenado);

	int result = (int) svm_predict(modelo, *(descriptor.x) );
	switch(result) {
		case TIPO_BACHE: 
			std::cout << "Muestra clasificada como: BACHE" << std::endl;
			return TIPO_BACHE;

	    case TIPO_GRIETA:
			std::cout << "Muestra clasificada como: GRIETA" << std::endl; 
	        return TIPO_GRIETA;
	}
	*/
}

/*
	Instanciacion explicita del metodo que tiene template. Se aplica para metodos y clases que tienen la 
	definicion de sus templates en archivos .hpp y .cpp separados. 

	Se definen las especializaciones de los tipos genericos de las clases templates,
	SOLAMENTE para aquellos metodos que tengan una implementacion(aunque sea de cuerpo vacio).
	Si existen metodos genericos que no tengan implementacion se retornara error de linkeo.
*/

template class EstrategiaClasificacionMLAbstract<pcl::ESFSignature640,svm_problem,svm_model,pcl::PointXYZRGB>;
template class EstrategiaClasificacionMLAbstract<pcl::GRSDSignature21,svm_problem,svm_model,pcl::PointXYZRGB>;
//template class EstrategiaClasificacionMLAbstract<pcl::FPFHSignature33,svm_problem,svm_model,pcl::PointXYZRGB>;

template class EstrategiaClasificacionSVM<pcl::ESFSignature640,pcl::PointXYZRGB>;
template class EstrategiaClasificacionSVM<pcl::GRSDSignature21,pcl::PointXYZRGB>;
//template class EstrategiaClasificacionSVM<pcl::FPFHSignature33,pcl::PointXYZRGB>;



