#include "../../utils/include/utils.hpp"

#include "../include/formateador_dataset.hpp"


/**************************** Clase Abstract ****************************/
FormateadorDatasetAbstract::FormateadorDatasetAbstract(){

}


//Genera las features de una muestra y las guarda en un vector
template <class SignatureT> void FormateadorDatasetAbstract::generarMuestraSVM(
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


/**************************** FormateadorDatasetSVM ****************************/
FormateadorDatasetSVM::FormateadorDatasetSVM(){

}



void FormateadorDatasetSVM::almacenarSVMTmp(pcl::SVMData muestraSVM, 
												std::string dirSalidaTmp,
												std::string nombreTmp){
				
	std::cout << std::endl;
	std::cout << "En almacenar() para archivo "<< nombreArchivo <<" con colMuestras.size(): "<< colMuestras.size() << std::endl;
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

