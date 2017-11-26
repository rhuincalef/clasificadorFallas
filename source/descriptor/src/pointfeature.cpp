// Descriptor ESF con downsampling + diff. Alto y Ancho -->

#include "../include/pointfeature.hpp"
#include "../include/pointfeaturederivadas.hpp"


template <typename PointT> PointFeature<PointT>::PointFeature(){
	diffAltoAncho = 0;
}

/******************************************** Metodos ESF **********************************************/
PointFeatureESF::PointFeatureESF(){
	
}

template <class PointT>
pcl::PointCloud<pcl::ESFSignature640>::Ptr PointFeatureESF::procesarDescriptorPCL(Nube<PointT> n){
	pcl::console::TicToc tt;
	tt.tic();
	// ESF estimation object.
  	pcl::ESFEstimation<pcl::PointXYZRGB, pcl::ESFSignature640> esf;

	esf.setInputCloud(n.getDownsamplingCloud());
	esf.compute(*descPCL);
	std::cout << "ESF descriptor Time(seg): " << tt.toc()/1000 << std::endl;
}


/*

template <typename PointT> PointFeatureESF<PointT>::PointFeatureESF(){
	
}

pcl::PointCloud<pcl::ESFSignature640>::Ptr ESF::procesarDescriptorPCL(Nube n){
	pcl::console::TicToc tt;
	tt.tic();
	// ESF estimation object.
  	pcl::ESFEstimation<pcl::PointXYZRGB, pcl::ESFSignature640> esf;

	esf.setInputCloud(n.getDownsamplingCloud());
	esf.compute(*descPCL);
	std::cout << "ESF descriptor Time(seg): " << tt.toc()/1000 << std::endl;
}


*/

/******************************************** Metodos GRSD **********************************************/
/*
template <typename PointT> PointFeatureGRSD<PointT>::PointFeatureGRSD(){

}

pcl::PointCloud<pcl::GRSDSignature21>::Ptr GRSD::procesarDescriptorPCL(Nube n){
	
	pcl::console::TicToc tt;
	tt.tic();

	pcl::search::KdTree<pcl::PointXYZRGB>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZRGB>);
	// GRSD estimation object.
	pcl::GRSDEstimation<pcl::PointXYZRGB, pcl::Normal, pcl::GRSDSignature21> grsd;
	grsd.setInputCloud(nube.getDownsamplingCloud());
	//grsd.setInputNormals(normals);
	grsd.setInputNormals(nube.getNormalsCloud());
	grsd.setSearchMethod(kdtree);
	// Search radius, to look for neighbors. Note: the value given here has to be
	// larger than the radius used to estimate the normals.
	grsd.setRadiusSearch(0.05);

	grsd.compute(*descPCL);

	std::cout << "GRSD descriptor Time(seg): " << tt.toc()/1000 << std::endl;

}
*/