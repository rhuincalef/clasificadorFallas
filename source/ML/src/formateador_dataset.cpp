#include "../../utils/include/utils.hpp"

#include "../include/formateador_dataset.hpp"



/**************************** Clase Abstract ****************************/
FormateadorDatasetAbstract::FormateadorDatasetAbstract(){

}

template <class SignatureT> void FormateadorDatasetAbstract::dumpearDescriptor(PointFeature<SignatureT> descriptor,
														std::string dirSalidaTmp,
														std::string nombreTmp){
}


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
	/*
	//myfile << "#" << nombrePcds[i].c_str() << " ";
	//Si quedan elementos para leer del problema
	if (i+1 < colMuestras.size())
	{
		myfile << "\n";
	}
	std::cout << "escribiendo muestra en archivo: "<< nombreArchivo << std::endl;
	*/
	myfile << "\n";
	myfile.close();
	std::cout << " Generado archivo de salida " << nombreArchivo << std::endl;
}



/**************************** FormateadorDatasetSVM ****************************/
FormateadorDatasetSVM::FormateadorDatasetSVM(){

}

//Genera las features de una muestra y las guarda en un vector
	template <class SignatureT> void FormateadorDatasetSVM::generarMuestraSVM(
													PointFeature<SignatureT> descriptor,
													pcl::SVMData* muestraSVM){

	muestraSVM->label = 1;//Label por defecto. No influye en la prediccion del resultado final.
	std::vector<pcl::SVMDataPoint> vectorFeatures;

	// Indexador lleva la cuenta global de los features de cada punto de cada nube de puntos
	int indexador = 0;
	pcl::PointCloud<SignatureT> descriptores = descriptor.getDescriptorPCL();
	//Recorrer para cada punto del descriptor, cada histograma y por
	//cada histograma iterar cada valor.
	for (int j= 0; j < descriptores.points.size() ; ++j)
	{	
		
		for (int k = 0; k < 640; ++k)
		{
			pcl::SVMDataPoint dataPoint;
			indexador = 640*j + k;			
			dataPoint.idx = indexador;
			dataPoint.value = descriptores.points[j].histogram[k];
			vectorFeatures.push_back(dataPoint);
		 //End For - Histogram Signatures 
		}

		/*************************************************************************************************************/
	}/* End for muestras*/

	
	//Calculo ancho-alto
	pcl::SVMDataPoint diffAltoAncho;
	diffAltoAncho.idx = ++indexador;
	diffAltoAncho.value = descriptor.getDiffAltoAncho();
	vectorFeatures.push_back(diffAltoAncho);
	muestraSVM->SV = vectorFeatures;
}

/* 
	Este metodo adapta al formato de svm_problem una muestra de tipo SVMData, para que esta pueda ser
	empleada por el metodo svm_predict() con un struct svm_model* modelo. 
*/
//pcl::SVM::adaptInputToLibSVM (std::vector<SVMData> training_set, svm_problem &prob)
//template <class SignatureT> svm_problem adaptarDescriptor(PointFeature<SignatureT> descriptor)
template <class SignatureT> svm_problem adaptarDescriptor(PointFeature<SignatureT> descriptor)
{

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
	/*
	if (pcl_isfinite (training_set[i].label) && labelled_training_set_)
	{
	  prob.y[i] = training_set[i].label;
	  labelled_training_set_ = 1;
	}
	else
	  labelled_training_set_ = 0;
	*/

	prob.x[i] = Malloc (struct svm_node, training_set[i].SV.size() + 1);

	int k = 0;
	for (size_t j = 0; j < training_set[i].SV.size(); j++)
	  if (training_set[i].SV[j].idx != -1 && pcl_isfinite (training_set[i].SV[j].value))
	  {
	    prob.x[i][k].index = training_set[i].SV[j].idx;
	    /*
	    if (training_set[i].SV[j].idx < scaling_.max && scaling_.obj[ training_set[i].SV[j].idx ].index == 1)
	      prob.x[i][k].value = training_set[i].SV[j].value / scaling_.obj[ training_set[i].SV[j].idx ].value;
	    else
	      prob.x[i][k].value = training_set[i].SV[j].value;
	    */
	    prob.x[i][k].value = training_set[i].SV[j].value;
	    k++;
	  }
	  
	prob.x[i][k].index = -1;
	}
	return prob;
};


/*
	Este metodo dumpea el PointFeature de una muestra en disco, en un directorio de salida temporal,
	y con un nombre. 
*/
template <class SignatureT> void FormateadorDatasetSVM::dumpearDescriptor(PointFeature<SignatureT> descriptor,
														std::string dirSalidaTmp,
														std::string nombreTmp){
	//Se convierte la muestra a un formato de muestra SVM
	pcl::SVMData muestraSVM;
	generarMuestraSVM(descriptor,&muestraSVM);

	//Se guarda la muestra en un archivo tmp en disco 
	almacenarSVMTmp(muestraSVM, dirSalidaTmp, nombreTmp);
}

