// Descriptor ESF con downsampling + diff. Alto y Ancho -->

#include "../include/pointfeature.hpp"
#include "../include/pointfeaturederivadas.hpp"
#include "../../utils/include/utils.hpp"
#include <pcl/features/moment_of_inertia_estimation.h>


/************************************ PointFeature ************************************/

template <class SignatureT,class PointT>
PointFeature<SignatureT,PointT>::PointFeature(){
	diffAltoAncho = 0;
}



template <class SignatureT,class PointT>
double PointFeature<SignatureT,PointT>::getDiffAltoAncho(){
  return this->diffAltoAncho;
}


template <class SignatureT,class PointT>
typename pcl::PointCloud<SignatureT> PointFeature<SignatureT,PointT>::getDescriptorPCL(){
    std::cout << "getDescriptorPCL() SUPERCLASE" << std::endl;
    return this->descPCL;
}

template <class SignatureT,class PointT>
int PointFeature<SignatureT,PointT>::getTamanioDescriporPCL(){
    std::cout << "getTamanioDescriporPCL() SUPERCLASE" << std::endl;
    return this->tamanioDescriptor;
}





/*
template <class SignatureT,class PointT>
void PointFeature<SignatureT,PointT>::calcularAltoAncho(pcl::PointCloud<PointT>::Ptr cloud,
                                                        TipoDimensiones* dimensiones){
*/
template <class SignatureT,class PointT>
void PointFeature<SignatureT,PointT>::calcularAltoAncho(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud,
                                                        TipoDimensiones* dimensiones){
  PointT min_point_OBB;
  PointT max_point_OBB;
  PointT position_OBB;
  Eigen::Vector3f mass_center;
  Eigen::Matrix3f rotational_matrix_OBB;
  pcl::MomentOfInertiaEstimation <PointT> feature_extractor;
  
  feature_extractor.setInputCloud(cloud);
  feature_extractor.compute();
  feature_extractor.getOBB (min_point_OBB, max_point_OBB, position_OBB, rotational_matrix_OBB);
  feature_extractor.getMassCenter (mass_center);


  Eigen::Quaternionf quat (rotational_matrix_OBB);
  Eigen::Vector3f position (position_OBB.x, position_OBB.y, position_OBB.z);
  //viewer->addCube (position, quat, max_point_OBB.x - min_point_OBB.x, max_point_OBB.y - min_point_OBB.y, max_point_OBB.z - min_point_OBB.z, "OBB");
  Eigen::Vector3f p1 (min_point_OBB.x, min_point_OBB.y, min_point_OBB.z);
  Eigen::Vector3f p2 (min_point_OBB.x, min_point_OBB.y, max_point_OBB.z);
  Eigen::Vector3f p3 (max_point_OBB.x, min_point_OBB.y, max_point_OBB.z);
  Eigen::Vector3f p4 (max_point_OBB.x, min_point_OBB.y, min_point_OBB.z);
  Eigen::Vector3f p5 (min_point_OBB.x, max_point_OBB.y, min_point_OBB.z);
  Eigen::Vector3f p6 (min_point_OBB.x, max_point_OBB.y, max_point_OBB.z);
  Eigen::Vector3f p7 (max_point_OBB.x, max_point_OBB.y, max_point_OBB.z);
  Eigen::Vector3f p8 (max_point_OBB.x, max_point_OBB.y, min_point_OBB.z);
  p1 = rotational_matrix_OBB * p1 + position;
  p2 = rotational_matrix_OBB * p2 + position;
  p3 = rotational_matrix_OBB * p3 + position;
  p4 = rotational_matrix_OBB * p4 + position;
  p5 = rotational_matrix_OBB * p5 + position;
  p6 = rotational_matrix_OBB * p6 + position;
  p7 = rotational_matrix_OBB * p7 + position;
  p8 = rotational_matrix_OBB * p8 + position;
  pcl::PointXYZ pt1 (p1 (0), p1 (1), p1 (2));
  pcl::PointXYZ pt2 (p2 (0), p2 (1), p2 (2));
  pcl::PointXYZ pt3 (p3 (0), p3 (1), p3 (2));
  pcl::PointXYZ pt4 (p4 (0), p4 (1), p4 (2));
  pcl::PointXYZ pt5 (p5 (0), p5 (1), p5 (2));
  pcl::PointXYZ pt6 (p6 (0), p6 (1), p6 (2));
  pcl::PointXYZ pt7 (p7 (0), p7 (1), p7 (2));
  pcl::PointXYZ pt8 (p8 (0), p8 (1), p8 (2));


  float alto = 0;
  float ancho = 0;
  float profundidad = 0;

  ancho = sqrt(pow(pt1.x - pt5.x,2) + pow(pt1.y-pt5.y,2) + pow(pt1.z-pt5.z,2) );
  //alto = fabs(pt1.y - pt4.y);
  alto = sqrt(pow(pt1.x - pt4.x,2) + pow(pt1.y-pt4.y,2) + pow(pt1.z-pt4.z,2));
  //profundidad = fabs(pt1.z - pt2.z);
  profundidad = sqrt(pow(pt1.x - pt2.x,2) + pow(pt1.y-pt2.y,2) + pow(pt1.z-pt2.z,2));

  //Linea horizontal en X
  std::cout << "Nuevo ANCHO_MAX: " << ancho << std::endl;

  //Linea vertical en Y
  std::cout << "Nuevo ALTO_MAX_POWER: " << alto << std::endl;
  
  //Linea de profundidad en Z
  std::cout << "Nuevo PROF_MAX: " << profundidad << std::endl;

  dimensiones->ancho = ancho;
  dimensiones->alto = alto;
  dimensiones->profundidad = profundidad;
  
}

template <class SignatureT,class PointT>
void PointFeature<SignatureT,PointT>::computarDescriptor(Nube<pcl::PointXYZRGB>* n){
  //std::cout << "Invoque a C() de SUPERCLASE!!! " << std::endl;
}



template <class SignatureT,class PointT>
void PointFeature<SignatureT,PointT>::procesarDescriptorPCL(Nube<PointT>* n){

  pcl::console::TicToc tt;
  tt.tic();

  this->computarDescriptor(n);

  std::cout << "ESF descriptor Time(seg): " << tt.toc()/1000 << std::endl;
  //Calculo de alto y ancho V2
  TipoDimensiones dimensiones;
  calcularAltoAncho(n->getDownsamplingCloud(),&dimensiones);
  this->diffAltoAncho = fabs(dimensiones.alto - dimensiones.ancho);
  std::cout << "Calculada la diferencia alto-ancho para la muestra: "<< this->diffAltoAncho << std::endl;
}




/******************************************** Metodos ESF **********************************************/

template <class PointT>
PointFeatureESF<PointT>::PointFeatureESF(){
  this->tamanioDescriptor = 640;
  std::cout << "Llamado constructor de descriptor ESF()!: " << this->tamanioDescriptor << std::endl;
}



template <class PointT>
pcl::PointCloud<pcl::ESFSignature640> PointFeatureESF<PointT>::getDescriptorPCL(){
    std::cout << "getDescriptorPCL() ESF subclase" << std::endl;
    return this->descPCL;
}


template <class PointT>
int PointFeatureESF<PointT>::getTamanioDescriporPCL(){
    std::cout << "getTamanioDescriporPCL() subclase" << std::endl;
    return this->tamanioDescriptor;
}



//Este metodo computa el descriptor de PCL de cada subclase de PointFeature
template <class PointT>
void PointFeatureESF<PointT>::computarDescriptor(Nube<pcl::PointXYZRGB>* n){
  std::cout << "Invoque a computarDescriptor() de PointFeatureESF!!! " << std::endl;
  pcl::console::TicToc tt;
  tt.tic();
  // ESF estimation object.
  pcl::ESFEstimation<PointT, pcl::ESFSignature640> esf;

  esf.setInputCloud(n->getDownsamplingCloud());
  std::cout << "1"<< std::endl;
  std::cout << this->descPCL << std::endl;
  esf.compute(this->descPCL);
  //esf.compute(descPCL);
  std::cout << "2"<< std::endl;
  std::cout << "Computado descriptor!!!" << std::endl;
  std::cout << this->descPCL << std::endl;
  std::cout << "this->descPCL->points.size(): " << std::endl;
  std::cout << this->descPCL.points.size() << std::endl;
  
  std::cout << "ESF descriptor Time(seg): " << tt.toc()/1000 << std::endl;
}



/******************************************** Metodos GRSD **********************************************/

template <class PointT>
PointFeatureGRSD<PointT>::PointFeatureGRSD(){
  std::cout << "Llamado constructor de descriptor GRSD()!"<< this->tamanioDescriptor  << std::endl;
  this->tamanioDescriptor = 21;
}

template <class PointT>
pcl::PointCloud<pcl::GRSDSignature21> PointFeatureGRSD<PointT>::getDescriptorPCL(){
    std::cout << "getDescriptorPCL() GRSD subclase" << std::endl;
    return this->descPCL;
}


template <class PointT>
int PointFeatureGRSD<PointT>::getTamanioDescriporPCL(){
    std::cout << "getTamanioDescriporPCL() subclase" << std::endl;
    return this->tamanioDescriptor;
}




template <class PointT>
void PointFeatureGRSD<PointT>::computarDescriptor(Nube<pcl::PointXYZRGB>* n){
  std::cout << "Invoque a computarDescriptor() de GRSD!!! " << std::endl;

  pcl::console::TicToc tt;
  tt.tic();
  typename pcl::search::KdTree<PointT>::Ptr kdtree(new pcl::search::KdTree<PointT>);
  // GRSD estimation object.
  pcl::GRSDEstimation<PointT, pcl::Normal, pcl::GRSDSignature21> grsd;
  grsd.setInputCloud(n->getDownsamplingCloud());
  //grsd.setInputNormals(normals);
  grsd.setInputNormals(n->getNormalsCloud());
  grsd.setSearchMethod(kdtree);
  // Search radius, to look for neighbors. Note: the value given here has to be
  // larger than the radius used to estimate the normals.
  grsd.setRadiusSearch(0.05);
  //grsd.compute(*descPCL);
  grsd.compute(this->descPCL);
  std::cout << "GRSD descriptor Time(seg): " << tt.toc()/1000 << std::endl;
}



/*
  Instanciacion explicita del metodo que tiene template. Se aplica para metodos y clases que tienen la 
  definicion de sus templates en archivos .hpp y .cpp separados. 

  Se definen las especializaciones de los tipos genericos de las clases templates,
  SOLAMENTE para aquellos metodos que tengan una implementacion(aunque sea de cuerpo vacio).
  Si existen metodos genericos que no tengan implementacion se retornara error de linkeo.
*/

template class PointFeature<pcl::ESFSignature640,pcl::PointXYZRGB>;
template class PointFeature<pcl::GRSDSignature21,pcl::PointXYZRGB>;
template class PointFeature<pcl::FPFHSignature33,pcl::PointXYZRGB>;


template class PointFeatureESF<pcl::PointXYZRGB>;
template class PointFeatureGRSD<pcl::PointXYZRGB>;
//template class PointFeatureFPFH<pcl::PointXYZRGB>;


