// Mediciones
#include <stdio.h>
#include <pcl/console/time.h>
// using for print_highlight, print_value, print_info
#include <pcl/console/print.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

//#include "source/ML/include/estrategia_clasificacion.hpp"
//#include "source/ML/include/estrategia_clasificacion.hpp"
//#include "source/main_pipe_line/include/main_pipe_line.hpp"


/*
TipoMuestra testESF(MainPipeLine<pcl::PointXYZRGB,pcl::ESFSignature640,svm_problem,svm_model>* pipeline, std::string muestraPcd){

	PointFeature<pcl::ESFSignature640> features; 
	features = pipeline->computarNube(muestraPcd);
	return pipeline->clasificar(features);
}

TipoMuestra testESF(MainPipeLine<pcl::ESFSignature640>* pipeline, std::string muestraPcd){

	PointFeature<pcl::ESFSignature640> features; 
	features = pipeline->computarNube(muestraPcd);
	return pipeline->clasificar(features);
}
*/


//Ejemplo de invocacion -->
// ./mainPipeLine ejemplos/bache_pav_6_1.pcd

int main(int argc,char** argv)
{
	std::cout << "Iniciado main pipeLine..." << std::endl;
	
	/*
	MainPipeLine<pcl::PointXYZRGB,pcl::ESFSignature640,svm_problem,svm_model>* pipeLineESF = new MainPipeLine<pcl::PointXYZRGB,pcl::ESFSignature640,svm_problem,svm_model>;
	TipoMuestra tipo = testESF(pipeLineESF,argv[1]);
	std::cout << "El tipo de muestra clasificado con ESF es: "<< tipo << std::endl;

	MainPipeLine<pcl::GRSDSignature21>* pipeLineGRSD = new MainPipeLine<pcl::GRSDSignature21>;
	TipoMuestra tipo = testGRSD(pipeLineGRSD,argv[1]);
	std::cout << "El tipo de muestra clasificado con GRSD es: "<< tipo << std::endl;
	*/
	std::cout << "Fin main xx pipeLine..." << std::endl;
}


