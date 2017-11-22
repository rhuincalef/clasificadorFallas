// Mediciones
#include <stdio.h>
#include <pcl/console/time.h>
// using for print_highlight, print_value, print_info
#include <pcl/console/print.h>

#include "source/ML/include/estrategia_clasificacion.hpp"

int main(int argc,char** argv)
{
	std::cout << "Iniciado main pipeLine..." << std::endl;
	//EstrategiaClasificacionSVM::EstrategiaClasificacionSVM();
	//::EstrategiaClasificacionSVM* estr(new ::EstrategiaClasificacionSVM("a","b","c"));
	std::string param1 = "a";
	std::string param2 = "a";
	std::string param3 = "a";
	EstrategiaClasificacionSVM* estr(new EstrategiaClasificacionSVM(param1,param2,param3));

	std::cout << "Fin main xx pipeLine..." << std::endl;
	return 0;
}


