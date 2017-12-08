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

template<class PointT>
class PointFeatureESF: public PointFeature<pcl::ESFSignature640,PointT> {

public:
	//Constructor 
	PointFeatureESF();

	
	//void computarDescriptor(Nube<pcl::PointXYZRGB>* n);
	void computarDescriptor(Cluster<pcl::PointXYZRGB>* n);
	
	pcl::PointCloud<pcl::ESFSignature640> getDescriptorPCL();

	int getTamanioDescriporPCL();
	

private:
	pcl::PointCloud<pcl::ESFSignature640> descPCL;

};
#endif


#ifndef PointFeatureGRSD_DEF
#define PointFeatureGRSD_DEF

//template<class SignatureT,class PointT>

template<class PointT>
class PointFeatureGRSD : public PointFeature<pcl::GRSDSignature21,PointT> {

public:
	//Constructor 
	PointFeatureGRSD();	

	void computarDescriptor(Cluster<pcl::PointXYZRGB>* n);
	//void computarDescriptor(Nube<pcl::PointXYZRGB>* n);
	
	pcl::PointCloud<pcl::GRSDSignature21> getDescriptorPCL();

	int getTamanioDescriporPCL();
	

private:
	pcl::PointCloud<pcl::GRSDSignature21> descPCL;

};
#endif
