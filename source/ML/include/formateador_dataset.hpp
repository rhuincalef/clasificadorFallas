// Clases: FormateadorDatasetAbstract, SVMFormatter
#include <iostream>
#include "../../utils/include/utils.hpp"
#include "../../descriptor/include/pointfeaturederivadas.hpp"
#include "../../parser/include/parametrizador.hpp"

#ifndef FormateadorPointTypes_DEF
#define FormateadorPointTypes_DEF
static const char* FormateadorPointTypes[] = { "PointXYZ", "PointXYZRGB"};
#endif

#ifndef FormateadorDatasetAbstract_DEF
#define FormateadorDatasetAbstract_DEF

class FormateadorDatasetAbstract{

public:
  //Constructor 
  FormateadorDatasetAbstract();

/*
template<class SignatureT,class ProblemaT,class PointT,class MuestraT>
ProblemaT adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor){
	//Se genera la muestra en una estructura de SVMData con el descriptor PointFeature
	std::cout << "Inicio FormateadorDatasetAbstract.adaptarDescriptor() SUPERCLASE!!! ..." << std::endl;
	ProblemaT prob;
	//pcl::SVMData muestraSVM;
	MuestraT muestra;
	this->generarMuestra(descriptor,&muestra);	
	this->adaptarDescriptorAFormatoEspecifico(muestra,&prob);
	return prob;
}
*/

  template <class SignatureT,class PointT,class ProblemaT,class MuestraT>
  ProblemaT adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor);
	
  /*
  template <class S,class PR,class PT,class M>
  PR generica(PointFeature<S,PT>* b);
  */
  //A generica(PointFeature<A,B>* b);

  //Sub-metodos
  virtual void adaptarDescriptorAFormatoEspecifico(pcl::SVMData muestraSVM,svm_problem* prob);
	
  virtual void generarMuestra(PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* descriptor,pcl::SVMData* muestraSVM);
  virtual void generarMuestra(PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* descriptor,pcl::SVMData* muestraSVM);

  static Parametrizador
  getParametrizador();

private:
  static Parametrizador parametrizador_;
  static bool configurado_;

  static void
  configurarParametrizador();

};
/*
template <class SignatureT,class PointT,class ProblemaT,class MuestraT>
ProblemaT FormateadorDatasetAbstract::adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor){

	//Se genera la muestra en una estructura de SVMData con el descriptor PointFeature
	std::cout << "Inicio FormateadorDatasetAbstract.adaptarDescriptor() SUPERCLASE!!! ..." << std::endl;
	ProblemaT prob;
	//pcl::SVMData muestraSVM;
	MuestraT muestra;
	this->generarMuestra(descriptor,&muestra);	
	this->adaptarDescriptorAFormatoEspecifico(muestra,&prob);
	return prob;
}
*/

/*
template<class A,class B>
A FormateadorDatasetAbstract::generica(PointFeature<A,B>* b){

}
*/
#endif


#ifndef FormateadorSVM_DEF
#define FormateadorSVM_DEF

template<class PointT,class SignatureT,class ProblemaT,class MuestraT>
class SVMFormatter: public FormateadorDatasetAbstract {

public:
  SVMFormatter();

  void
  generarMuestra(PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* descriptor,
								pcl::SVMData* muestraSVM);
  void
  generarMuestra(PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* descriptor,
								pcl::SVMData* muestraSVM);

  void
  adaptarDescriptorAFormatoEspecifico(pcl::SVMData muestraSVM,svm_problem* prob);
	
};
#endif


