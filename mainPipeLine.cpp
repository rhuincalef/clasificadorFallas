// Mediciones
#include <stdio.h>
#include <pcl/console/time.h>
// using for print_highlight, print_value, print_info
#include <pcl/console/print.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>


#include "source/ML/include/estrategia_clasificacion.hpp"
#include "source/main_pipe_line/include/main_pipe_line.hpp"


/*
TipoMuestra testESF(MainPipeLine<pcl::PointXYZRGB,pcl::ESFSignature640,svm_problem,svm_model,PointFeatureESF>* pipeline,
								 std::string muestraPcd){

	std::cout << "En testESF!" << std::endl;
	PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* features; 
	features = pipeline->computarNube(muestraPcd);
	return pipeline->clasificar(features);
}


*/

//Ejemplo de invocacion -->
// ./mainPipeLine REAL_BACHE.pcd
// ./mainPipeLine REAL_GRIETA.pcd

int main(int argc,char** argv)
{
	std::cout << "Iniciado main pipeLine..." << std::endl;
	
	MainPipeLine<pcl::PointXYZRGB>* pipeLine = new MainPipeLine<pcl::PointXYZRGB>;


	std::string dirAlmacenamientoCapturas = "dirAlmacCapturas/" ;

	
	PlanarAndEuclidean<pcl::PointXYZRGB>* estratSegmentacion = new PlanarAndEuclidean<pcl::PointXYZRGB>;
	ESF<pcl::PointXYZRGB,pcl::ESFSignature640,PointFeatureESF>* estratDescriptor = new ESF<pcl::PointXYZRGB,pcl::ESFSignature640,PointFeatureESF>();
	EstrategiaClasificacionSVM<pcl::ESFSignature640,svm_problem,svm_model,pcl::PointXYZRGB>* estratClasificacion = new EstrategiaClasificacionSVM<pcl::ESFSignature640,svm_problem,svm_model,pcl::PointXYZRGB>();
	
	if (not(dirAlmacenamientoCapturas != "" && boost::filesystem::exists (dirAlmacenamientoCapturas)))
	{
		PCL_ERROR ("Fail to open input directory!\n");
		return -1;
	}

	pipeLine->setDirAlmacenamientoCapturasClasificadas(dirAlmacenamientoCapturas);
	pipeLine->setEstrategiaSegmentacion(estratSegmentacion);
	pipeLine->setEstrategiaDescriptor(estratDescriptor);
	pipeLine->setEstrategiaClasificacion(estratClasificacion);

	std::vector<std::string> capturas = pipeLine->leerDirCaptura();

	for (int i = 0; i < capturas.size(); ++i)
	{
		std::cout << "Clasificando capturas["<<i << "] = " << capturas[i] << std::endl;
		//pipeLine->leerCaptura(capturas[i],p);
		typename std::vector <pcl::PointCloud<pcl::PointXYZRGB>> clusters = pipeline->computarNube(capturas[i]);

		for (int i = 0; i < clusters.size(); ++i)
		{
			std::cout << "Clasificando clusters[" << i << "] = " << clusters[i] << std::endl;
			//INVOCACION A METODO TEMPLATE CON TIPOS GENERICOS NO DEFINIDOS EN LA CLASE
			PointFeature<SignatureT,PointT>* pointFeature = this->estratDescriptor->template generarDescriptor<pcl::PointXYZRGB,
																												pcl::ESFSignature640,
																												PointFeatureESF>(n);
			std::cout << "Fin de Main.ComputarNube(). Genere el descriptor" << std::endl<< std::endl;			
			TipoMuestra tipo = this->clasificar(pointFeature);
			switch(tipo) {
				case TIPO_BACHE: 
					std::cout << "El cluster se clasifico como: BACHE" << std::endl;
					break;
			    case TIPO_GRIETA:
					std::cout << "El cluster se clasifico como: GRIETA" << std::endl; 
			        break;
			}
			std::cout << "---------------------------------------------------"<< std::endl<< std::endl;			

		}
	}

	std::cout << "El tipo de muestra clasificado con ESF es: "<< tipo << std::endl;
	std::cout << "Fin main xx pipeLine..." << std::endl;
}


