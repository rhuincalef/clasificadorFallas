#include "../../utils/include/utils.hpp"

#include "../include/estrategia_clasificacion.hpp"


//Constructores 
template <class SignatureT,class ProblemaT,class ModeloT>
EstrategiaClasificacionMLAbstract<SignatureT, ProblemaT,ModeloT>::EstrategiaClasificacionMLAbstract(){

}


/************************** Estrategia clasificacion SVM **************************/


/*
template <class SignatureT,class ProblemaT,class ModeloT>
EstrategiaClasificacionSVM<SignatureT,ProblemaT,ModeloT>::EstrategiaClasificacionSVM(){
*/
template <class SignatureT>
EstrategiaClasificacionSVM<SignatureT>::EstrategiaClasificacionSVM(){
	this->formateador = new FormateadorDatasetSVM<SignatureT>();
}

//template <class SignatureT,class ProblemaT>
//ProblemaT EstrategiaClasificacionSVM<SignatureT>::adaptarDescriptor(PointFeature<SignatureT> descriptor){
/*
template <class SignatureT,class ProblemaT,class ModeloT>
ProblemaT EstrategiaClasificacionSVM<SignatureT,ProblemaT,ModeloT>::adaptarDescriptor(PointFeature<SignatureT> descriptor){
*/


template <class SignatureT,class ProblemaT> ProblemaT EstrategiaClasificacionSVM<SignatureT>::adaptarDescriptor(PointFeature<SignatureT> descriptor){
	return this->formateador->adaptarDescriptor(descriptor);
}




/*
	Carga el modelo.dat a memoira y lo retorna
*/
//struct svm_model *svm_load_model(const char *model_file_name);
//
//svm_model* EstrategiaClasificacionSVM::cargarModelo(std::string pathModeloEntrenado){
template <class SignatureT,class ModeloT>
ModeloT* EstrategiaClasificacionSVM<SignatureT>::cargarModelo(std::string pathModeloEntrenado){
	struct svm_model* modelo;
	if ( (modelo=svm_load_model(pathModeloEntrenado.c_str() )) ==0) 
	{
		//fprintf(stderr,"can't open model file %s\n",argv[i+1]);
		std::cout << "No se puede abrir el modelo entrenado!" << std::endl; 
		exit(1);
	}
	
	std::cout << "Leido el modelo: "<< pathModeloEntrenado << std::endl; 
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
//TipoMuestra EstrategiaClasificacionSVM::clasificar(std::string pathModeloEntrenado, svm_problem descriptor){

template <class SignatureT,class ProblemaT>
TipoMuestra EstrategiaClasificacionSVM<SignatureT>::clasificar(std::string pathModeloEntrenado, ProblemaT descriptor){

	struct svm_model* modelo;
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

}

/*
Instanciacion explicita del metodo que tiene template. Se aplica para metodos y clases que tienen la 
definicion de sus templates en archivos .hpp y .cpp separados. 
*/
template class EstrategiaClasificacionSVM<pcl::ESFSignature640,svm_problem,svm_model>;
template class EstrategiaClasificacionSVM<pcl::GRSDSignature21,svm_problem,svm_model>;
template class EstrategiaClasificacionSVM<pcl::FPFHSignature33,svm_problem,svm_model>;



