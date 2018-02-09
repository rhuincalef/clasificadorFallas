// Mediciones
#include <stdio.h>
#include <string>
#include <unordered_map>

#include "source/parser/include/parseador.hpp"
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

std::string splitear(std::string nombre){
    std::vector<std::string> result;
    std::vector<std::string> strs;
    boost::split(strs,nombre,boost::is_any_of("."));
    if (strs.size() > 1)
    {
      boost::split(result,strs[0],boost::is_any_of("/"));
    }
    std::cout << "Cadena spliteada: "<< result[result.size()-1] << std::endl;
    return result[result.size()-1];    
}


//Ejemplo de invocacion -->
// ./mainPipeLine REAL_BACHE.pcd
// ./mainPipeLine REAL_GRIETA.pcd

int main(int argc,char** argv)
{
	std::cout << "Iniciado main pipeLine..." << std::endl;
	ParseadorJSON parseador;
	MainPipeLine<pcl::PointXYZRGB>* pipeLine = new MainPipeLine<pcl::PointXYZRGB>;

	Parametrizador parametrizador = MainPipeLine<pcl::PointXYZRGB>::getParametrizador();
	int index = parseador.find_argument(argc, argv, "-f");
	bool ok = parseador.openRapid(argv[index+1]);
	if (not ok)
	{
		std::cout << "Error apertura archivo JSON!" << std::endl;
		return -1;
	}
	std::unordered_map<std::string, std::string> values;
  	bool result = parseador.parser_rapid(&parametrizador, values);
  	if (not result)
  	{
  		std::cout << "Error de parseo archivo JSON!" << std::endl;
		return -1;
  	}
	//std::string dirAlmacenamientoCapturas = "dirAlmacCapturas/" ;
	std::string dirAlmacenamientoCapturas = DIR_ENTRADA;
	std::string dir_salida = DIR_GUARDADO_CLUSTER;
	for (auto i = values.begin(); i != values.end(); ++i)
	{
		if ("dir_entrada" == i->first)
			dirAlmacenamientoCapturas = i->second;
		if ("dir_salida" == i->first)
			dir_salida = i->second;
	}
  	std::cout << "dir_entrada: "<< dirAlmacenamientoCapturas << std::endl;
  	std::cout << "dir_salida: "<< dir_salida << std::endl;

	PlanarAndEuclidean<pcl::PointXYZRGB>* estratSegmentacion = new PlanarAndEuclidean<pcl::PointXYZRGB>;
	parametrizador = PlanarAndEuclidean<pcl::PointXYZRGB>::getParametrizador();
	result = parseador.parser_rapid(&parametrizador, values);
  	if (not result)
  	{
  		std::cout << "Error de parseo archivo JSON! estratSegmentacion!" << std::endl;
		return -1;
  	}
	for (auto i = values.begin(); i != values.end(); ++i)
	{
		if (i->first == "dist_thresh")
			estratSegmentacion->setDistanceThreshold(std::stod(i->second));
		if (i->first == "min_cluster_size")
			estratSegmentacion->setMinClusterSize(std::stoi(i->second));
		if (i->first == "max_cluster_size")
			estratSegmentacion->setMaxClusterSize(std::stoi(i->second));
		if (i->first == "max_it")
			estratSegmentacion->setMaxIterations(std::stoi(i->second));
	}
	ESF<pcl::PointXYZRGB,pcl::ESFSignature640,PointFeatureESF>* estratDescriptor = new ESF<pcl::PointXYZRGB,pcl::ESFSignature640,PointFeatureESF>();
	EstrategiaClasificacionSVM<pcl::ESFSignature640,svm_problem,svm_model,pcl::PointXYZRGB>* estratClasificacion = new EstrategiaClasificacionSVM<pcl::ESFSignature640,svm_problem,svm_model,pcl::PointXYZRGB>();
	parametrizador = EstrategiaClasificacionSVM<pcl::ESFSignature640,svm_problem,svm_model,pcl::PointXYZRGB>::getParametrizador();
	result = parseador.parser_rapid(&parametrizador, values);
  	if (not result)
  	{
  		std::cout << "Error de parseo archivo JSON! EstrategiaClasificacionSVM!" << std::endl;
		return -1;
  	}
	for (auto i = values.begin(); i != values.end(); ++i)
	{
		if (i->first == "path_modelo")
			pipeLine->setPathModeloEntrenado(i->second);
	}
	if (not(pipeLine->getPathModeloEntrenado() != "" && boost::filesystem::exists (pipeLine->getPathModeloEntrenado())))
	{
		std::cout << "Falla al abrir PathModeloEntrenado!" << std::endl;
		return -1;
	}
	
	if (not(dirAlmacenamientoCapturas != "" && boost::filesystem::exists (dirAlmacenamientoCapturas)))
	{
		std::cout << "Falla al abrir dir_entrada!" << std::endl;
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
		typename pcl::PointCloud<pcl::PointXYZRGB>::Ptr p (new pcl::PointCloud<pcl::PointXYZRGB>);
	
		if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(cap, *p) != 0)
		{
		  std::cerr << "Failed to read PCD test file." << std::endl;
		  return -1;
		}
		Nube<pcl::PointXYZRGB>* n = new Nube<pcl::PointXYZRGB>(p);
		n->setNombre(splitear(cap));
		std::cout << "" << std::endl;

		std::vector <pcl::PointCloud<pcl::PointXYZRGB>> clusters = pipeLine->computarNube(n);
		for (int i = 0; i < clusters.size(); ++i)
		{	
			pcl::PointCloud<pcl::PointXYZRGB>::Ptr c1 (new pcl::PointCloud<pcl::PointXYZRGB>);
			*c1 = clusters[i];
			std::string aux = "_cluster_" + std::to_string(i);
			Cluster<pcl::PointXYZRGB> c (c1,aux);
			n->agregarCluster(c); 
		}

		std::vector< Cluster<pcl::PointXYZRGB> > clustersReales = n->getClusters();
		for (int i = 0; i < clustersReales.size(); ++i)
		{
			std::cout << "Clasificando clusters[" << i << "] = " << clusters[i] << std::endl;  			
			PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>* pointFeature = pipeLine->getEstrategiaDescriptor()->template generarDescriptor<pcl::PointXYZRGB,
																												pcl::ESFSignature640,
																												PointFeatureESF>(&clustersReales[i]);

			TipoDimensiones dimensiones;
			pointFeature->calcularDimensiones(clustersReales[i].getOriginalCloud(),
																&dimensiones);
			clustersReales[i].setAlto(dimensiones.alto);
			clustersReales[i].setAncho(dimensiones.ancho);
			clustersReales[i].setProfundidad(dimensiones.profundidad);

			std::cout << "Fin de Main.ComputarNube(). Genere el descriptor" << std::endl<< std::endl;
			TipoMuestra tipo = pipeLine->template clasificar<pcl::ESFSignature640,
																svm_problem,svm_model>(pointFeature);
			switch(tipo) {
				case TIPO_BACHE: 
					std::cout << "El cluster se clasifico como: BACHE" << std::endl;
					clustersReales[i].setTipo("Bache");
					break;
			    case TIPO_GRIETA:
					std::cout << "El cluster se clasifico como: GRIETA" << std::endl; 
					clustersReales[i].setTipo("Grieta");
			        break;
			}

			std::cout << std::endl;
			pipeLine->almacenarCluster(n,clustersReales[i], dir_salida);

			std::cout << "---------------------------------------------------"<< std::endl<< std::endl;			
		}
	}

	std::cout << "Fin main xx pipeLine..." << std::endl;
}


/*
TODO:
Desde dir_entrado o dirAlmacenamientoCapturas:
	- trim de ruta obteniendo id falla
	- crear carpeta con id falla en dir_salida
	- almacenar en esta ruta cluster + json clasificados
	- guardar todas las fallas (clasificadas o no)
*/