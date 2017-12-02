#include "../../utils/include/utils.hpp"

#include "../include/formateador_dataset.hpp"



/**************************** Clase Abstract ****************************/

/*
template<class SignatureT,typename ProblemaT,class PointT>
FormateadorDatasetAbstract<SignatureT,ProblemaT,PointT>::FormateadorDatasetAbstract(){
*/
template<class SignatureT,typename ProblemaT,class PointT,class MuestraT>
FormateadorDatasetAbstract<SignatureT,ProblemaT,PointT,MuestraT>::FormateadorDatasetAbstract(){

}




template<class SignatureT,typename ProblemaT,class PointT,class MuestraT>
ProblemaT FormateadorDatasetAbstract<SignatureT,ProblemaT,PointT, MuestraT>::adaptarDescriptor(PointFeature<SignatureT,PointT>* descriptor){

	//Se genera la muestra en una estructura de SVMData con el descriptor PointFeature
	std::cout << "Inicio FormateadorDatasetAbstract.adaptarDescriptor() SUPERCLASE!!! ..." << std::endl;
	ProblemaT prob;
	//pcl::SVMData muestraSVM;
	MuestraT muestra;
	this->generarMuestra(descriptor,&muestra);	
	this->adaptarDescriptorAFormatoEspecifico(muestra,&prob);
	return prob;
}


template<class SignatureT,typename ProblemaT,class PointT,class MuestraT>
void FormateadorDatasetAbstract<SignatureT,ProblemaT,PointT, MuestraT>::generarMuestra(PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* descriptor,pcl::SVMData* muestraSVM){
	std::cout << "generarMuestra() SUPERCLASE!!!" << std::endl;
}


template<class SignatureT,typename ProblemaT,class PointT,class MuestraT>
void FormateadorDatasetAbstract<SignatureT,ProblemaT,PointT, MuestraT>::generarMuestra(PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* descriptor,pcl::SVMData* muestraSVM){
	std::cout << "generarMuestra() SUPERCLASE!!!" << std::endl;
}


template<class SignatureT,typename ProblemaT,class PointT,class MuestraT>
void FormateadorDatasetAbstract<SignatureT,ProblemaT,PointT, MuestraT>::adaptarDescriptorAFormatoEspecifico(pcl::SVMData muestraSVM,svm_problem* prob){
	std::cout << "adaptarDescriptorAFormatoEspecifico() SUPERCLASE!!!" << std::endl;
}

/*
void FormateadorDatasetAbstract::almacenarDatasetTmp(pcl::SVMData muestraSVM, 
												std::string dirSalidaTmp,
												std::string nombreTmp){
				
	std::cout << std::endl;
	std::cout << "En almacenar() para archivo "<< dirSalidaTmp << "/" << nombreTmp << std::endl;
	std::ofstream myfile;
	//myfile.open (nombreArchivo);
	//Se abre el stream al archivo para apendear contenido
	std::string nombreArchivo = dirSalidaTmp + "/" + nombreTmp;
	myfile.open (nombreArchivo, std::ofstream::app);
	std::cout << "Archivo abierto: "<< nombreArchivo << std::endl;

	myfile << muestraSVM.label << " ";
	for (int j=0; j < muestraSVM.SV.size();j++)
	{	
		int index = muestraSVM.SV[j].idx;
		float value = muestraSVM.SV[j].value;
		std::cout << "index: " << index << ", value: " << value << std::endl;

		//Se almacenan los descriptores con valores mayores a cero
		if (value >0)
		{
			myfile << index << ":" << value;
			if (index!=-1)
			{
				myfile  << " ";
			}
		}
	}
	
	//myfile << "#" << nombrePcds[i].c_str() << " ";
	//Si quedan elementos para leer del problema
	if (i+1 < colMuestras.size())
	{
		myfile << "\n";
	}
	std::cout << "escribiendo muestra en archivo: "<< nombreArchivo << std::endl;
	
	myfile << "\n";
	myfile.close();
	std::cout << " Generado archivo de salida " << nombreArchivo << std::endl;
}
*/





/**************************** SVMFormatter ****************************/


template<class SignatureT,class PointT>
SVMFormatter<SignatureT,PointT>::SVMFormatter(){

}

template<class SignatureT,class PointT>
void SVMFormatter<SignatureT,PointT>::adaptarDescriptorAFormatoEspecifico(pcl::SVMData muestraSVM,svm_problem* prob){
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


/*
template <class SignatureT,class PointT>
svm_problem SVMFormatter<SignatureT,PointT>::adaptarDescriptor(
													PointFeature<SignatureT,PointT>* descriptor){

	std::cout << "Inicio SVMFormatter.adaptarDescriptor() ..." << std::endl;
	//ProblemaT prob;
	svm_problem prob;

	//Se genera la muestra en una estructura de SVMData con el descriptor PointFeature
	pcl::SVMData muestraSVM;
	generarMuestraSVM(descriptor,&muestraSVM);


	//Se cambia el 
	std::vector<pcl::SVMData> training_set; 
	training_set.push_back(muestraSVM);

	prob.l = int (training_set.size ()); // n of elements/points
	prob.y = Malloc (double, prob.l);
	prob.x = Malloc (struct svm_node *, prob.l);

	for (int i = 0; i < prob.l; i++)
	{
	*/
	/*
	//NO DESCOMENTAR!
	if (pcl_isfinite (training_set[i].label) && labelled_training_set_)
	{
	  prob.y[i] = training_set[i].label;
	  labelled_training_set_ = 1;
	}
	else
	  labelled_training_set_ = 0;
	*/
	/*
	prob.x[i] = Malloc (struct svm_node, training_set[i].SV.size() + 1);

	int k = 0;
	for (size_t j = 0; j < training_set[i].SV.size(); j++)
	  if (training_set[i].SV[j].idx != -1 && pcl_isfinite (training_set[i].SV[j].value))
	  {
	    prob.x[i][k].index = training_set[i].SV[j].idx;
	*/

	    /*
	    //No DESCOMENTAR!
	    if (training_set[i].SV[j].idx < scaling_.max && scaling_.obj[ training_set[i].SV[j].idx ].index == 1)
	      prob.x[i][k].value = training_set[i].SV[j].value / scaling_.obj[ training_set[i].SV[j].idx ].value;
	    else
	      prob.x[i][k].value = training_set[i].SV[j].value;
	    */

	/*
	    prob.x[i][k].value = training_set[i].SV[j].value;
	    k++;
	  }
	  
	prob.x[i][k].index = -1;
	}
	std::cout << "Fin SVMFormatter.adaptarDescriptor() ..." << std::endl;
	return prob;
};
*/


//Genera las features de una muestra y las guarda en un vector





/*
template <> 
void SVMFormatter<pcl::ESFSignature640,pcl::PointXYZRGB>::generarMuestra(
													PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* descriptor,
													pcl::SVMData* muestraSVM){
*/
template <class SignatureT,class PointT> 
void SVMFormatter<SignatureT,PointT>::generarMuestra(
													PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* descriptor,
													pcl::SVMData* muestraSVM){

	std::cout << "Inicio SVMFormatter->generarMuestra()..." << std::endl;
	muestraSVM->label = 1;//Label por defecto. No influye en la prediccion del resultado final.
	std::cout << "1..." << std::endl;
	std::vector<pcl::SVMDataPoint> vectorFeatures;

	// Indexador lleva la cuenta global de los features de cada punto de cada nube de puntos
	int indexador = 0;
	//pcl::PointCloud<pcl::ESFSignature640>::Ptr descriptores = descriptor->getDescriptorPCL();
	pcl::PointCloud<pcl::ESFSignature640>* descriptores = descriptor->getDescriptorPCL();
	std::cout << "2..." << std::endl;
	std::cout << descriptores << std::endl;


	//Recorrer para cada punto del descriptor, cada histograma y por
	//cada histograma iterar cada valor.
	//for (int j= 0; j < descriptores.points.size() ; ++j)
	for (int j= 0; j < descriptores->points.size() ; ++j)
	{	
		
		for (int k = 0; k < 640; ++k)
		{
			pcl::SVMDataPoint dataPoint;
			indexador = 640*j + k;			
			dataPoint.idx = indexador;
			dataPoint.value = descriptores->points[j].histogram[k];
			//dataPoint.value = descriptores.points[j].histogram[k];
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


template <class SignatureT,class PointT> 
void SVMFormatter<SignatureT,PointT>::generarMuestra(
													PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* descriptor,
													pcl::SVMData* muestraSVM){

	muestraSVM->label = 1;//Label por defecto. No influye en la prediccion del resultado final.
	std::vector<pcl::SVMDataPoint> vectorFeatures;

	// Indexador lleva la cuenta global de los features de cada punto de cada nube de puntos
	int indexador = 0;
	//typename pcl::PointCloud<pcl::GRSDSignature21>::Ptr descriptores = descriptor->getDescriptorPCL();

	typename pcl::PointCloud<pcl::GRSDSignature21>* descriptores =  descriptor->getDescriptorPCL();

	//Recorrer para cada punto del descriptor, cada histograma y por
	//cada histograma iterar cada valor.
	for (int j= 0; j < descriptores->points.size() ; ++j)
	//for (int j= 0; j < descriptores.points.size() ; ++j)
	{	
		
		for (int k = 0; k < 21; ++k)
		{
			pcl::SVMDataPoint dataPoint;
			indexador = 21*j + k;			
			dataPoint.idx = indexador;
			dataPoint.value = descriptores->points[j].histogram[k];
			//dataPoint.value = descriptores.points[j].histogram[k];
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
	Este metodo dumpea el PointFeature de una muestra en disco, en un directorio de salida temporal,
	y con un nombre. 
*/
/*
template <class SignatureT> void SVMFormatter::dumpearDescriptor(PointFeature<SignatureT> descriptor,
														std::string dirSalidaTmp,
														std::string nombreTmp){
	//Se convierte la muestra a un formato de muestra SVM
	pcl::SVMData muestraSVM;
	generarMuestraSVM(descriptor,&muestraSVM);

	//Se guarda la muestra en un archivo tmp en disco 
	almacenarSVMTmp(muestraSVM, dirSalidaTmp, nombreTmp);
}
*/


/*
	Instanciacion explicita del metodo que tiene template. Se aplica para metodos y clases que tienen la 
	definicion de sus templates en archivos .hpp y .cpp separados. 

	Se definen las especializaciones de los tipos genericos de las clases templates,
	SOLAMENTE para aquellos metodos que tengan una implementacion(aunque sea de cuerpo vacio).
	Si existen metodos genericos que no tengan implementacion se retornara error de linkeo.
*/
template class SVMFormatter<pcl::ESFSignature640,pcl::PointXYZRGB>;
template class SVMFormatter<pcl::GRSDSignature21,pcl::PointXYZRGB>;
//template class SVMFormatter<pcl::FPFHSignature33,pcl::PointXYZRGB>;

template class FormateadorDatasetAbstract<pcl::ESFSignature640, svm_problem, pcl::PointXYZRGB,pcl::SVMData>;
template class FormateadorDatasetAbstract<pcl::GRSDSignature21, svm_problem,pcl::PointXYZRGB,pcl::SVMData>;
//template class FormateadorDatasetAbstract<pcl::FPFHSignature33, svm_problem,pcl::PointXYZRGB,pcl::SVMData>;


