#include "../../utils/include/utils.hpp"
#include "../include/nube.hpp"


template <typename PointT>

Nube<PointT>::Nube()
{
  typename pcl::PointCloud<PointT>::Ptr downsampling_cloud (new pcl::PointCloud<PointT>);
  this->downsampling_cloud = downsampling_cloud;
  typename pcl::PointCloud<PointT>::Ptr original_cloud (new pcl::PointCloud<PointT>);
  this->original_cloud = original_cloud;
  typename pcl::PointCloud<PointT>::Ptr no_outlier_cloud (new pcl::PointCloud<PointT>);
  this->no_outlier_cloud = no_outlier_cloud;
  pcl::PointCloud<pcl::Normal>::Ptr normals_cloud (new pcl::PointCloud<pcl::Normal>);
  this->normals_cloud = normals_cloud;
}

template <typename PointT>
Nube<PointT>::Nube(typename pcl::PointCloud<PointT>::Ptr input) : Nube()
{
  this->original_cloud = input;
  this->setAllClouds ();

}

template <typename PointT>
Nube<PointT>::Nube(const pcl::PointCloud<PointT> &input) : Nube()
{
  *this->original_cloud = input;
  this->setAllClouds ();
}




template <typename PointT>
void Nube<PointT>::setNombre(std::string n){
	this->nombre = n;
}

template <typename PointT>
std::string Nube<PointT>::getNombre(){
	return this->nombre;
}



template <typename PointT>
typename std::vector<Cluster<PointT>> Nube<PointT>::getClusters(){
	return this->clusters;
}
 


template <typename PointT>
void  Nube<PointT>::agregarCluster(Cluster<PointT> c){
	this->clusters.push_back(c);
}


//Constructor que simula incializar una muestra pcd cropeada,downsampleada y con normales (Prueba de training cropeada)
template <typename PointT> Nube<PointT>::Nube(std::string fullPathCaptura){

	//Se computa la nube completa
	//original_cloud (new pcl::PointCloud<PointT>);
	//downsampling_cloud (new pcl::PointCloud<PointT>);
	
	//this->original_cloud = new pcl::PointCloud<PointT>();
	/*
	this->downsampling_cloud =  new pcl::PointCloud<PointT>;
	*/
	
	/*
	original_cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
	downsampling_cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
	*/
	//pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	//normals_cloud (new pcl::PointCloud<pcl::Normal>); 
	
	/*
	this->normals_cloud = new pcl::PointCloud<PointT>;
	*/

	//Se computa la nube completa
	typename pcl::PointCloud<PointT>::Ptr abc (new pcl::PointCloud<PointT>);

	/*
	original_cloud (new pcl::PointCloud<PointT>);
	downsampling_cloud (new pcl::PointCloud<PointT>);
	normals_cloud (new pcl::PointCloud<pcl::Normal>);
	*/
	//std::cout << "Construyendo nube nueva..." << std::endl;
	//if (pcl::io::loadPCDFile<PointT> (fullPathCaptura, *original_cloud) == -1) //* load the file
	if (pcl::io::loadPCDFile<PointT> (fullPathCaptura, *abc) == -1) //* load the file
	{
		//std::cout << "No se pudo leer el archivo: "<< fullPathCaptura << std::endl;
		return;
	}
	//std::cout << "Leida muestra " << std::endl;
	this->original_cloud = abc;
	this->downsampling_cloud = abc;
	//std::cout << "Leida muestra 2" << std::endl;
	pcl::PointCloud<pcl::Normal>::Ptr normals_cloud1 (new pcl::PointCloud<pcl::Normal>);

	////std::cout << "Leida muestra " << fullPathCaptura << " con " << original_cloud->points.size () << std::endl;

	//pcl::copyPointCloud(*original_cloud, *downsampling_cloud);
	

	//std::cout << "Copiada muestra a downsampling_cloud " << fullPathCaptura << " con " << downsampling_cloud->points.size () << std::endl;
	//pcl::NormalEstimationOMP<pcl::PointXYZRGB, pcl::Normal> normalEstimation(0);

	pcl::NormalEstimationOMP<PointT, pcl::Normal> normalEstimation(0);
	//std::cout << "Instanciado NormalEstimationOMP " << std::endl;
	normalEstimation.setInputCloud(original_cloud);
	//std::cout << "Seteado original_cloud" << std::endl;

	// For every point, use all neighbors in a radius of 3cm.
	normalEstimation.setRadiusSearch(0.008);
	// A kd-tree is a data structure that makes searches efficient. More about it later.
	// The normal estimation object will use it to find nearest neighbors.
	//pcl::search::KdTree<pcl::PointXYZRGB>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZRGB>);
	typename pcl::search::KdTree<PointT>::Ptr kdtree(new pcl::search::KdTree<PointT>);
	normalEstimation.setSearchMethod(kdtree);

	
	//std::cout << "Por computar..." << std::endl;
	// Calculate the normals.
	normalEstimation.compute(*normals_cloud1);
	this->normals_cloud = normals_cloud1;
	//std::cout << "Computada normals_cloud!!" << std::endl;

	//std::cout << "Computadas las normales para Nube con: " << normals_cloud->points.size() << " puntos." << std::endl;
}

template<typename PointT> typename pcl::PointCloud<PointT>::Ptr
Nube<PointT>::getOriginalCloud()
{
  return this->original_cloud;
}

template<class PointT> typename pcl::PointCloud<PointT>::Ptr
Nube<PointT>::getDownsamplingCloud()
{
  return this->downsampling_cloud;
}

template<class PointT> typename pcl::PointCloud<pcl::Normal>::Ptr
Nube<PointT>::getNormalsCloud()
{
  return this->normals_cloud;
}


template<typename PointT> typename pcl::PointCloud<PointT>::Ptr
Nube<PointT>::getNoOutlierCloud()
{
  return this->no_outlier_cloud;
}

template<typename PointT> void
Nube<PointT>::setAllClouds()
{
  // Create the filtering object
  typename pcl::StatisticalOutlierRemoval<PointT> sor;
  sor.setInputCloud (this->original_cloud);
  // setMeanK - Set the number of nearest neighbors to use for mean distance estimation.
  sor.setMeanK (50);
  sor.setStddevMulThresh (1);
  sor.filter (*this->no_outlier_cloud);
  // The mapping tells you to what points of the old cloud the new ones correspond,
  // but we will not use it. Avoiding Nan
  std::vector<int> mapping;
  pcl::removeNaNFromPointCloud(*this->no_outlier_cloud, *this->no_outlier_cloud, mapping);
  pcl::VoxelGrid<PointT> voxel_grid_filter;
  voxel_grid_filter.setInputCloud(this->original_cloud);
  //voxel_grid_filter.setInputCloud(this->no_outlier_cloud);
  voxel_grid_filter.setLeafSize(0.01f, 0.01f, 0.01f);
  voxel_grid_filter.filter(*this->downsampling_cloud);
  pcl::NormalEstimationOMP<PointT, pcl::Normal> normalEstimation(0);
  normalEstimation.setInputCloud(this->downsampling_cloud);
  // For every point, use all neighbors in a radius of 3cm.
  //normalEstimation.setRadiusSearch(0.008);
  normalEstimation.setRadiusSearch(0.03);
  // A kd-tree is a data structure that makes searches efficient. More about it later.
  // The normal estimation object will use it to find nearest neighbors.
  typename pcl::search::KdTree<PointT>::Ptr kdtree(new pcl::search::KdTree<PointT>);
  normalEstimation.setSearchMethod(kdtree);
  // Calculate the normals.
  normalEstimation.compute(*this->normals_cloud);
}


template<typename PointT> void
Nube<PointT>::setNombreCompleto(std::string cap){
	this->nombreCompleto = cap;
}



template<typename PointT> std::string
Nube<PointT>::trimearIdFalla(){
	std::vector<std::string> result;
	std::string r = "DEF";
	boost::split(result,this->nombreCompleto,boost::is_any_of("/"));
	if (result.size() > 1)
	{
		r = result[result.size()-2];
		std::cout << "Retornando el id falla: " << r << std::endl;
	}
	return r;
}


/*
	Instanciacion explicita del metodo que tiene template. Se aplica para metodos y clases que tienen la 
	definicion de sus templates en archivos .hpp y .cpp separados. 

	Se definen las especializaciones de los tipos genericos de las clases templates,
	SOLAMENTE para aquellos metodos que tengan una implementacion(aunque sea de cuerpo vacio).
	Si existen metodos genericos que no tengan implementacion se retornara error de linkeo.
*/
template class Nube<pcl::PointXYZRGB>;
template class Nube<pcl::PointXYZ>;

/*
*/
template<class PointT>
Cluster<PointT>::Cluster(){
  this->alto = 0;
  this->ancho = 0;
  this->profundidad = 0;
  this->tipo = "";
}

template<class PointT>
Cluster<PointT>::Cluster(typename pcl::PointCloud<PointT>::Ptr input,std::string nombre): Cluster(){
	this->original_cloud = input;
	this->nombre = nombre;
}

template<class PointT>
void Cluster<PointT>::setOriginalCloud(typename pcl::PointCloud<PointT>::Ptr p){
	this->original_cloud = p;
}

template<class PointT>
void Cluster<PointT>::setNombre(std::string nombre){
	this->nombre = nombre;
}


template<class PointT>
std::string Cluster<PointT>::getNombre(){
	return this->nombre;
}

template<class PointT>
typename pcl::PointCloud<PointT>::Ptr Cluster<PointT>::getOriginalCloud(){
	return this->original_cloud;
}

template<class PointT>
void Cluster<PointT>::computarNormales(){
	pcl::NormalEstimationOMP<PointT, pcl::Normal> normalEstimation(0);
	pcl::PointCloud<pcl::Normal>::Ptr normales (new pcl::PointCloud<pcl::Normal>);
	this->normals_cloud = normales;
	
	normalEstimation.setInputCloud(this->original_cloud);
	// For every point, use all neighbors in a radius of 3cm.
	//normalEstimation.setRadiusSearch(0.008);
	normalEstimation.setRadiusSearch(0.03);
	// A kd-tree is a data structure that makes searches efficient. More about it later.
	// The normal estimation object will use it to find nearest neighbors.
	typename pcl::search::KdTree<PointT>::Ptr kdtree(new pcl::search::KdTree<PointT>);
	normalEstimation.setSearchMethod(kdtree);
	// Calculate the normals.
	normalEstimation.compute(*this->normals_cloud);
}

template<class PointT>
pcl::PointCloud<pcl::Normal>::Ptr Cluster<PointT>::getNormalsCloud(){
	return this->normals_cloud;
}




template<class PointT>
double Cluster<PointT>::getAlto(){
	return this->alto;
}

template<class PointT>
void Cluster<PointT>::setAlto(double a){
	this->alto = a;
}

template<class PointT>
double Cluster<PointT>::getAncho(){
	return this->ancho;
}

template<class PointT>
void Cluster<PointT>::setAncho(double a){
	this->ancho = a;
}

template<class PointT>
double Cluster<PointT>::getProfundidad(){
	return this->profundidad;
}

template<class PointT>
void Cluster<PointT>::setProfundidad(double a){
	this->profundidad = a;
}



template<class PointT>
std::string Cluster<PointT>::getTipo(){
	return this->tipo;
}

template<class PointT>
void Cluster<PointT>::setTipo(std::string t){
	this->tipo = t;
}



template class Cluster<pcl::PointXYZRGB>;
template class Cluster<pcl::PointXYZ>;


