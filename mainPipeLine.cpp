// Mediciones
#include <stdio.h>
#include <pcl/console/time.h>
// using for print_highlight, print_value, print_info
#include <pcl/console/print.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>


#include "source/ML/include/estrategia_clasificacion.hpp"
#include "source/main_pipe_line/include/main_pipe_line.hpp"
#include <string> 

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


	//std::string dirAlmacenamientoCapturas = "dirAlmacCapturas/" ;
	std::string dirAlmacenamientoCapturas = "/home/rodrigo/TESINA-2016-KINECT/MACHINE_LEARNING/clasificadorFallas/build/dirAlmacCapturas";


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

		std::string cap = capturas[i];
		typename pcl::PointCloud<PointT>::Ptr p (new pcl::PointCloud<PointT>);
	
		if (pcl::io::loadPCDFile<PointT>(cap, *p) != 0)
		{
		  std::cerr << "Failed to read PCD test file." << std::endl;
		  return -1;
		}
		Nube<PointT>* n = new Nube<PointT>(p);
		n->setNombre(splitear(cap));

		std::vector <pcl::PointCloud<pcl::PointXYZRGB>> clusters = pipeLine->computarNube(n);
		//std::vector <Cluster<pcl::PointXYZRGB>> clusters = pipeLine->computarNube(cap);
		for (int i = 0; i < clusters.size(); ++i)
		{	
			Cluster<pcl::PointXYZRGB> c  = new Cluster<pcl::PointXYZRGB>(clusters[i]);
			std::string aux = std::to_string("_cluster_") + std::to_string(i);
			c->setNombre(aux);
			n->agregarCluster(c); 
		}


		std::vector<Cluster<pcl::PointXYZRGB>> clustersReales = n->getClusters();
		for (int i = 0; i < clustersReales.size(); ++i)
		{
			std::cout << "Clasificando clusters[" << i << "] = " << clusters[i] << std::endl;
			pcl::PCDWriter writer;
  			//writer.write<pcl::PointXYZRGB>( "lala.pcd", clusters[i], false);
  			writer.write<pcl::PointXYZRGB>( "cluster" + std::to_string(i) + ".pcd", clusters[i], false);

			//Nube<pcl::PointXYZRGB>* n = new Nube<pcl::PointXYZRGB>(clusters[i]);



			PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* pointFeature = pipeLine->getEstrategiaDescriptor()->template generarDescriptor<pcl::PointXYZRGB,
																												pcl::ESFSignature640,
																												PointFeatureESF>(n);
			std::cout << "Fin de Main.ComputarNube(). Genere el descriptor" << std::endl<< std::endl;			
			//TipoMuestra tipo = pipeLine->clasificar(pointFeature);
			TipoMuestra tipo = pipeLine->template clasificar<pcl::ESFSignature640,
																svm_problem,svm_model>(pointFeature);
			switch(tipo) {
				case TIPO_BACHE: 
					std::cout << "El cluster se clasifico como: BACHE" << std::endl;
					break;
			    case TIPO_GRIETA:
					std::cout << "El cluster se clasifico como: GRIETA" << std::endl; 
			        break;
			}

			std::cout << std::endl;

			//TODO: VER SI ALMACENAR EN CLUSTER ALTO,ANCHO Y PROFUNIDAD CALCULADO AL GENERAR POINTFEATURE
			pipeLine->almacenarCluster(n,clustersReales[i],pointFeature->getAlto(),pointFeature->getAncho());

			std::cout << "---------------------------------------------------"<< std::endl<< std::endl;			
		}
	}

	std::cout << "Fin main xx pipeLine..." << std::endl;
}


