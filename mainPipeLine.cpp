// Mediciones
#include <stdio.h>
#include <pcl/console/time.h>
// using for print_highlight, print_value, print_info
#include <pcl/console/print.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include "gtest/gtest.h"

#include "source/ML/include/estrategia_clasificacion.hpp"
#include "source/parser/include/parametrizador.hpp"
#include "source/segmentation/include/segmentation.hpp"

int main(int argc,char** argv)
{
	std::cout << "Iniciado main pipeLine..." << std::endl;
	//EstrategiaClasificacionSVM::EstrategiaClasificacionSVM();
	//::EstrategiaClasificacionSVM* estr(new ::EstrategiaClasificacionSVM("a","b","c"));
	std::string param1 = "a";
	std::string param2 = "a";
	std::string param3 = "a";
	EstrategiaClasificacionSVM* estr(new EstrategiaClasificacionSVM(param1,param2,param3));

	//Foo<pcl::PointXYZRGB> my_clase;
	Parametro p1;
	p1.setNombre("thresh");
	Parametro p2;
	p2.setNombre("max_it");
	Parametrizador param;
	param.agregar(p1);
	param.agregar(p2);

	PlanarAndEuclidean<pcl::PointXYZRGB> ec;

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
	if (pcl::io::loadPCDFile<pcl::PointXYZRGB> (argv[1], *cloud) == -1) //* load the file
	{
		std::cout << "No se pudo leer el archivo: "<< argv[1] << std::endl;
	}
	int tam_nube_original = 0;
	tam_nube_original = cloud->points.size();
	std::cout << "tam_nube_original: " << tam_nube_original << std::endl;
	ec.setNube(*cloud);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr nueva_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	*nueva_cloud = ec.getNube();
	int tam_nueva_cloud = 0;
	//int tam_nueva_cloud = ec.getSizeNube();
	tam_nueva_cloud = nueva_cloud->points.size();
	std::cout << "tam_nueva_cloud: " << tam_nueva_cloud << std::endl;


	std::cout << "Parametro::p1::nombre " << p1.getNombre() << std::endl;
	std::cout << "Parametro::p2::nombre " << p2.getNombre() << std::endl;
	std::cout << "Parametrizador cant param " << param.getParametros().size() << std::endl;
	std::cout << "Fin main xx pipeLine..." << std::endl;
}


