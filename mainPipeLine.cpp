// Mediciones
#include <stdio.h>
#include <pcl/console/time.h>
// using for print_highlight, print_value, print_info
#include <pcl/console/print.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>


#include "source/ML/include/estrategia_clasificacion.hpp"
#include "source/main_pipe_line/include/main_pipe_line.hpp"



TipoMuestra testESF(MainPipeLine<pcl::PointXYZRGB,pcl::ESFSignature640,svm_problem,svm_model,PointFeatureESF>* pipeline,
								 std::string muestraPcd){

	std::cout << "En testESF!" << std::endl;
	PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* features; 
	features = pipeline->computarNube(muestraPcd);
	return pipeline->clasificar(features);
}


TipoMuestra testGRSD(MainPipeLine<pcl::PointXYZRGB,pcl::GRSDSignature21,svm_problem,svm_model,PointFeatureGRSD>* pipeline,
								 std::string muestraPcd){

	std::cout << "En testGRSD!" << std::endl;
	PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>* features; 
	features = pipeline->computarNube(muestraPcd);
	return pipeline->clasificar(features);
}


//Ejemplo de invocacion -->
// ./mainPipeLine REAL_BACHE.pcd
// ./mainPipeLine REAL_GRIETA.pcd


int main(int argc,char** argv)
{
	std::cout << "Iniciado main pipeLine..." << std::endl;
	
	/*
	MainPipeLine<pcl::PointXYZRGB,pcl::ESFSignature640,svm_problem,svm_model,PointFeatureESF>* pipeLineESF = new MainPipeLine<pcl::PointXYZRGB,pcl::ESFSignature640,svm_problem,svm_model,PointFeatureESF>;
	TipoMuestra tipo = testESF(pipeLineESF,argv[1]);
	std::cout << "El tipo de muestra clasificado con ESF es: "<< tipo << std::endl;
	*/

	MainPipeLine<pcl::PointXYZRGB,pcl::GRSDSignature21,svm_problem,svm_model,PointFeatureGRSD>* pipeLineGRSD = new MainPipeLine<pcl::PointXYZRGB,pcl::GRSDSignature21,svm_problem,svm_model,PointFeatureGRSD>;
	TipoMuestra tipo = testGRSD(pipeLineGRSD,argv[1]);
	std::cout << "El tipo de muestra clasificado con GRSD es: "<< tipo << std::endl;
	
	
	std::cout << "Fin main xx pipeLine..." << std::endl;
}


