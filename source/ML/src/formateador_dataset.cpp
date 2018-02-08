#include "../include/formateador_dataset.hpp"

/************************************************** Clase Abstract ******************************************/

FormateadorDatasetAbstract::FormateadorDatasetAbstract(){

}

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

void
FormateadorDatasetAbstract::generarMuestra(PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* descriptor,pcl::SVMData* muestraSVM){
	std::cout << "generarMuestra() SUPERCLASE!!!" << std::endl;
}



void
FormateadorDatasetAbstract::generarMuestra(PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* descriptor,pcl::SVMData* muestraSVM){
	std::cout << "generarMuestra() SUPERCLASE!!!" << std::endl;
}

void
FormateadorDatasetAbstract::adaptarDescriptorAFormatoEspecifico(pcl::SVMData muestraSVM,svm_problem* prob){
	std::cout << "adaptarDescriptorAFormatoEspecifico() SUPERCLASE!!!" << std::endl;
}

Parametrizador FormateadorDatasetAbstract::parametrizador_;

bool FormateadorDatasetAbstract::configurado_ = false;

void FormateadorDatasetAbstract::configurarParametrizador()
{
  if (FormateadorDatasetAbstract::configurado_)
    return;
  FormateadorDatasetAbstract::parametrizador_.setNombre("point_feature");
  Parametro p1;
  p1.setNombre("point_type");
  p1.setTipoValorEsperado("string");
  std::vector<std::string> v;
  for (int i = 0; i < sizeof FormateadorPointTypes / sizeof FormateadorPointTypes[0]; ++i)
  {
  	v.push_back(FormateadorPointTypes[i]);
  }
  p1.setValorEsperado(v);
  FormateadorDatasetAbstract::parametrizador_.agregar(p1);
  FormateadorDatasetAbstract::configurado_ = true;
}

Parametrizador FormateadorDatasetAbstract::getParametrizador()
{
  FormateadorDatasetAbstract::configurarParametrizador();
  return FormateadorDatasetAbstract::parametrizador_;
}

/***************************************************** SVMFormatter ***************************************/


/*template<class SignatureT,class PointT>
SVMFormatter<SignatureT,PointT>::SVMFormatter(){
*/

// pcl::SVMData = MuestraT
template<class PointT,class SignatureT,class ProblemaT,class MuestraT>
SVMFormatter<PointT,SignatureT,ProblemaT,MuestraT>::SVMFormatter(){
}

template<class PointT,class SignatureT,class ProblemaT,class MuestraT>
void SVMFormatter<PointT,SignatureT,ProblemaT,MuestraT>::adaptarDescriptorAFormatoEspecifico(pcl::SVMData muestraSVM,svm_problem* prob){
	std::vector<pcl::SVMData> training_set; 
	training_set.push_back(muestraSVM);

	prob->l = int (training_set.size ()); // n of elements/points
	prob->y = Malloc (double, prob->l);
	prob->x = Malloc (struct svm_node *, prob->l);

	for (int i = 0; i < prob->l; i++)
	{

		prob->x[i] = Malloc (struct svm_node, training_set[i].SV.size() + 1);
		int k = 0;
		for (size_t j = 0; j < training_set[i].SV.size(); j++)
		  if (training_set[i].SV[j].idx != -1 && pcl_isfinite (training_set[i].SV[j].value))
		  {
		    prob->x[i][k].index = training_set[i].SV[j].idx;


	    prob->x[i][k].value = training_set[i].SV[j].value;
	    k++;
	  }
	  
	prob->x[i][k].index = -1;
	}
	std::cout << "Fin SVMFormatter.adaptarDescriptor() ..." << std::endl;
	//return prob;
}




/* 
	Este metodo adapta al formato de svm_problem una muestra de tipo SVMData, para que esta pueda ser
	empleada por el metodo svm_predict() con un struct svm_model* modelo. 
*/
//pcl::SVM::adaptInputToLibSVM (std::vector<SVMData> training_set, svm_problem &prob)
/*
template <class SignatureT> 
svm_problem SVMFormatter<SignatureT>::adaptarDescriptor(PointFeature<SignatureT> descriptor)
*/



//template <class SignatureT,class PointT> 
template<class PointT,class SignatureT,class ProblemaT,class MuestraT>
void SVMFormatter<PointT,SignatureT,ProblemaT,MuestraT>::generarMuestra(
													PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* descriptor,
													pcl::SVMData* muestraSVM){
	
	//this->_generarMuestraSVMEspecifica(descriptor,muestraSVM);

	std::cout << "Inicio SVMFormatter->generarMuestra()..." << std::endl;
	muestraSVM->label = 1;//Label por defecto. No influye en la prediccion del resultado final.
	std::cout << "1..." << std::endl;
	std::vector<pcl::SVMDataPoint> vectorFeatures;

	// Indexador lleva la cuenta global de los features de cada punto de cada nube de puntos
	int indexador = 0;
	pcl::PointCloud<pcl::ESFSignature640> descriptores = descriptor->getDescriptorPCL();
	//pcl::PointCloud<pcl::ESFSignature640>::Ptr descriptores = descriptor->getDescriptorPCL();
	//pcl::PointCloud<pcl::ESFSignature640>* descriptores = descriptor->getDescriptorPCL();
	std::cout << "2..." << std::endl;
	std::cout << descriptores << std::endl;

	std::cout << "descriptores->points.size(): " << descriptores.points.size() << std::endl; 

	//Recorrer para cada punto del descriptor, cada histograma y por
	//cada histograma iterar cada valor.
	//for (int j= 0; j < descriptores->points.size() ; ++j)
	for (int j= 0; j < descriptores.points.size() ; ++j)
	{	
		for (int k = 0; k < 640; ++k)
		{
			pcl::SVMDataPoint dataPoint;
			indexador = 640*j + k;			
			dataPoint.idx = indexador;
			dataPoint.value = descriptores.points[j].histogram[k];
			//dataPoint.value = descriptores->points[j].histogram[k];
			vectorFeatures.push_back(dataPoint);
		 //End For - Histogram Signatures 
		}

	}
	std::cout << "Despues del for...()..." << std::endl;
	//Calculo ancho-alto
	pcl::SVMDataPoint diffAltoAncho;
	diffAltoAncho.idx = ++indexador;
	diffAltoAncho.value = descriptor->getDiffAltoAncho();
	vectorFeatures.push_back(diffAltoAncho);
	muestraSVM->SV = vectorFeatures;
	std::cout << "Fin SVMFormatter->generarMuestra()..." << std::endl;
}

/*
*/

template<class PointT,class SignatureT,class ProblemaT,class MuestraT>
void SVMFormatter<PointT,SignatureT,ProblemaT,MuestraT>::generarMuestra(
													PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* descriptor,
													pcl::SVMData* muestraSVM){

	muestraSVM->label = 1;//Label por defecto. No influye en la prediccion del resultado final.
	std::vector<pcl::SVMDataPoint> vectorFeatures;

	// Indexador lleva la cuenta global de los features de cada punto de cada nube de puntos
	int indexador = 0;
	pcl::PointCloud<pcl::GRSDSignature21> descriptores = descriptor->getDescriptorPCL();
	//Recorrer para cada punto del descriptor, cada histograma y por
	//cada histograma iterar cada valor.
	//for (int j= 0; j < descriptores->points.size() ; ++j)
	for (int j= 0; j < descriptores.points.size() ; ++j)
	{	
		
		for (int k = 0; k < 21; ++k)
		{
			pcl::SVMDataPoint dataPoint;
			indexador = 21*j + k;			
			dataPoint.idx = indexador;
			//dataPoint.value = descriptores->points[j].histogram[k];
			dataPoint.value = descriptores.points[j].histogram[k];
			vectorFeatures.push_back(dataPoint);
		 //End For - Histogram Signatures 
		}

	}
	//Calculo ancho-alto
	pcl::SVMDataPoint diffAltoAncho;
	diffAltoAncho.idx = ++indexador;
	diffAltoAncho.value = descriptor->getDiffAltoAncho();
	vectorFeatures.push_back(diffAltoAncho);
	muestraSVM->SV = vectorFeatures;
}

/*
// pcl::SVMData = MuestraT
template<class PointT,class SignatureT,class ProblemaT,class MuestraT>
void SVMFormatter<PointT,SignatureT,ProblemaT,MuestraT>::_generarMuestraSVMEspecifica(
															PointFeature<SignatureT,PointT>* descriptor,
															MuestraT* muestraSVM){

	std::cout << "En _generarMuestraSVMEspecifica() " << std::endl;	
	
	muestraSVM->label = 1;//Label por defecto. No influye en la prediccion del resultado final.
	std::vector<pcl::SVMDataPoint> vectorFeatures;

	// Indexador lleva la cuenta global de los features de cada punto de cada nube de puntos
	int indexador = 0;
	//typename pcl::PointCloud<pcl::GRSDSignature21>::Ptr descriptores = descriptor->getDescriptorPCL();

	typename pcl::PointCloud<SignatureT>* descriptores =  descriptor->getDescriptorPCL();

	int tamanioDescriptor = descriptor->getTamanioDescriporPCL();

	std::cout << "descriptor->getTamanioDescriporPCL(): "<< tamanioDescriptor << std::endl;	
	//Recorrer para cada punto del descriptor, cada histograma y por
	//cada histograma iterar cada valor.
	for (int j= 0; j < descriptores->points.size() ; ++j)
	{	
		
		//for (int k = 0; k < 21; ++k)
		for (int k = 0; k < tamanioDescriptor; ++k)
		{
			pcl::SVMDataPoint dataPoint;
			//indexador = 21*j + k;			
			indexador = tamanioDescriptor*j + k;			
			dataPoint.idx = indexador;
			dataPoint.value = descriptores->points[j].histogram[k];
			vectorFeatures.push_back(dataPoint);
		 //End For - Histogram Signatures 
		}

	}
	//Calculo ancho-alto
	pcl::SVMDataPoint diffAltoAncho;
	diffAltoAncho.idx = ++indexador;
	diffAltoAncho.value = descriptor->getDiffAltoAncho();
	vectorFeatures.push_back(diffAltoAncho);
	muestraSVM->SV = vectorFeatures;
}
*/


/*
	Instanciacion explicita del metodo que tiene template. Se aplica para metodos y clases que tienen la 
	definicion de sus templates en archivos .hpp y .cpp separados. 

	Se definen las especializaciones de los tipos genericos de las clases templates,
	SOLAMENTE para aquellos metodos que tengan una implementacion(aunque sea de cuerpo vacio).
	Si existen metodos genericos que no tengan implementacion se retornara error de linkeo.
*/

template class SVMFormatter<pcl::PointXYZRGB,pcl::ESFSignature640,svm_problem,pcl::SVMData>;
template class SVMFormatter<pcl::PointXYZRGB,pcl::GRSDSignature21,svm_problem,pcl::SVMData>;



/*
template class vector<int>;                    // class
template int& vector<int>::operator[](int);    // member
template int convert<int,double>(double);      // function
*/

//template <class SignatureT,class PointT,class ProblemaT,class MuestraT>
template svm_problem FormateadorDatasetAbstract::adaptarDescriptor<pcl::ESFSignature640,pcl::PointXYZRGB,svm_problem,pcl::SVMData>(
																	PointFeature<pcl::ESFSignature640,
																		pcl::PointXYZRGB>* descriptor);
template svm_problem FormateadorDatasetAbstract::adaptarDescriptor<pcl::GRSDSignature21,pcl::PointXYZRGB,svm_problem,pcl::SVMData>(
																	PointFeature<pcl::GRSDSignature21,
																		pcl::PointXYZRGB>* descriptor);




