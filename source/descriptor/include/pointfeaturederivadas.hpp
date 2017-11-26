#include "pointfeature.hpp"

#ifndef PointFeatureESF_DEF
#define PointFeatureESF_DEF

/*
//Nota el constructor de la clase derivada llama por defecto al constructor de la clase
//padre por defecto(sin parametros). Si se desea enviar valores se debe separar por : el nombre de la
//clase base y enviar los parametros dentro:
class base
{
  public:
  base (int arg)
  {
  }
};

class derived : public base
{
  public:
  derived () : base (number)
  {
  }
};
*/

class PointFeatureESF : public PointFeature<pcl::ESFSignature640> {

public:
	//Constructor 
	PointFeatureESF();

	template<typename PointT> pcl::PointCloud<pcl::ESFSignature640>::Ptr procesarDescriptorPCL(Nube<PointT> n);

private:
	pcl::PointCloud<pcl::ESFSignature640>::Ptr descPCL;

};
#endif


#ifndef PointFeatureGRSD_DEF
#define PointFeatureGRSD_DEF

class PointFeatureGRSD : public PointFeature<pcl::GRSDSignature21> {

public:
	//Constructor 
	PointFeatureGRSD();
	template<typename PointT> pcl::PointCloud<pcl::GRSDSignature21>::Ptr procesarDescriptorPCL(Nube<PointT> n);

private:
	pcl::PointCloud<pcl::GRSDSignature21>::Ptr descPCL;

};
#endif
