// Descriptor ESF con downsampling + diff. Alto y Ancho -->


#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>
//#include <pcl/features/fpfh.h>
//#include <pcl/features/vfh.h>
//#include <pcl/features/grsd.h>
#include <pcl/features/esf.h>
#include <pcl/features/normal_3d_omp.h>

// Mediciones
#include <pcl/console/time.h>
// using for print_highlight, print_value, print_info
#include <pcl/console/print.h>


#include <boost/filesystem.hpp>
// command parse
#include <pcl/console/parse.h>
#include <math.h>

#include <pcl/features/principal_curvatures.h>

#include <pcl/ml/svm_wrapper.h>
//#include <pcl/filters/uniform_sampling.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/surface/convex_hull.h>

#include <pcl/common/distances.h>
#include <pcl/surface/gp3.h>
#include <pcl/features/moment_of_inertia_estimation.h>

#include "../../utils/include/utils.hpp"

#include "../include/descriptor.hpp"

EstrategiaDescriptorsAbstract::EstrategiaDescriptorsAbstract(){

}

ESF::ESF(){

}


