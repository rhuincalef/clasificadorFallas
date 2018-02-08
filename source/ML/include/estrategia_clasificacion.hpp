// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include "../../utils/include/utils.hpp"
#include "formateador_dataset.hpp"
#include "../../descriptor/include/pointfeaturederivadas.hpp"

#ifndef FormateadorClasificadorTypes_DEF
#define FormateadorClasificadorTypes_DEF
static const char* FormateadorClasificadorTypes[] = { "svm"};
#endif

#ifndef EstrategiaClasificacionAbstract_DEF
#define EstrategiaClasificacionAbstract_DEF

class EstrategiaClasificacionAbstract {


};
#endif

#ifndef EstrategiaClasificacionMLAbstract_DEF
#define EstrategiaClasificacionMLAbstract_DEF

//template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
class EstrategiaClasificacionMLAbstract: public EstrategiaClasificacionAbstract {

public:
	//Constructor 
	EstrategiaClasificacionMLAbstract();
	
	//TipoMuestra clasificar(std::string pathModeloEntrenado, ProblemaT descriptor);

	//Clasificar correspondiente a la SVM
	/*
	template <class SignatureT,class PointT,class ProblemaT,class ModeloT>
	TipoMuestra clasificar(std::string pathModeloEntrenado, PointFeature<SignatureT,PointT>* descriptor);
	*/
	

	//Sub-metodos
	/*
	template <class SignatureT,class PointT,class ProblemaT>
		ProblemaT adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor);
	*/
	template <class SignatureT,class PointT,class ProblemaT,class MuestraT>
	ProblemaT adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor){
		std::cout << "estrategiaClasificacion.adaptarDescriptor() SUPERCLASE!!!" << std::endl;
		ProblemaT p = this->formateador->template adaptarDescriptor<SignatureT,PointT,ProblemaT,MuestraT>(descriptor);
		std::cout << "Fin estrategiaClasificacion.adaptarDescriptor() ..." << std::endl<< std::endl;
		return p;
	}

	virtual svm_model* cargarModelo(std::string pathModeloEntrenado);
	virtual TipoMuestra predecir(svm_model* modelo,svm_problem problema);

	
	
	template <class SignatureT,class PointT,class ProblemaT,class ModeloT,class MuestraT>
	TipoMuestra clasificar(std::string pathModeloEntrenado,
							PointFeature<SignatureT,PointT>* descriptor){
	
		std::cout << "Inicio EstrategiaClasificacionMLAbstract.clasificar() SUPERCLASE ..." << std::endl;
		ProblemaT problema = this->template adaptarDescriptor<SignatureT,PointT,ProblemaT,MuestraT>(descriptor);
		//svm_model* modelo;
		ModeloT* modelo;
		modelo = this->cargarModelo(pathModeloEntrenado);

		this->predecir(modelo,problema);
	}

	void setFormateador(FormateadorDatasetAbstract* f);
	FormateadorDatasetAbstract* getFormateador();

	static Parametrizador
 	getParametrizador();

protected:
	//FormateadorDatasetAbstract<SignatureT,ProblemaT,PointT,pcl::SVMData>* formateador;
	FormateadorDatasetAbstract* formateador = NULL;

private:
	static Parametrizador parametrizador_;
	static bool configurado_;

	static void
	configurarParametrizador();

};
#endif

#ifndef EstrategiaClasificacionSVM_DEF
#define EstrategiaClasificacionSVM_DEF

//template<class SignatureT,class PointT>
//class EstrategiaClasificacionSVM : public EstrategiaClasificacionMLAbstract<SignatureT,svm_problem,svm_model,PointT>
template <class SignatureT,class ProblemaT,class ModeloT,class PointT>
class EstrategiaClasificacionSVM : public EstrategiaClasificacionMLAbstract
{
  
public:
	//Constructor 
	EstrategiaClasificacionSVM();

	//Metodos principales
	//TipoMuestra clasificar(std::string pathModeloEntrenado, svm_problem descriptor);



	//Sub-metodos
	TipoMuestra predecir(svm_model* modelo,svm_problem problema);

	svm_model* cargarModelo(std::string pathModeloEntrenado);

	//svm_problem adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor);	

};
#endif