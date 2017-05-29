#include "h5utils.h"

const std::pair<int,int> get_nx_ny(const H5::H5File & fichier)
{
	// Nom du dataset a extraire
	const H5std_string DATASET_NAME( "CMa" );
	H5::DataSet dataset = fichier.openDataSet( DATASET_NAME );
	
	// Get dataspace of the dataset.
	H5::DataSpace dataspace = dataset.getSpace();

	// Recuperation de nx et ny :
	hsize_t dims_out[2];
	int ndims = dataspace.getSimpleExtentDims( dims_out, NULL);
	const int nx= (unsigned long)(dims_out[0]);
	const int ny= (unsigned long)(dims_out[1]);
	std::pair<int,int> p2(nx,ny);
	return p2;
}


/**
 * @brief get_donnees_CM : renvoie les donnees du dataset CMa du fichier
 * @param fichier : fichier hdf5 contenant le dataset
 * @return vector contenant les donnees
 */
std::vector<unsigned char> get_donnees_CM(const H5::H5File & fichier)
{
	
	// Nom du dataset a extraire
	const H5std_string DATASET_NAME( "CMa" );
	H5::DataSet dataset = fichier.openDataSet( DATASET_NAME );
	
	// Get dataspace of the dataset.
	H5::DataSpace dataspace = dataset.getSpace();

	// Recuperation de nx et ny :
	hsize_t dims_out[2];
	int ndims = dataspace.getSimpleExtentDims( dims_out, NULL);
	const int nx= (unsigned long)(dims_out[0]);
	const int ny= (unsigned long)(dims_out[1]);
	
	// Recuperation des donnees
	std::vector<unsigned char> donnees;
	donnees.resize(nx*ny);
	// important: donnees[i* 3712 + j]= data[i][j]
	dataset.read(&donnees[0], H5::PredType::NATIVE_UCHAR);

	return donnees;
}



std::vector<std::vector<int>> get_palette_CM(const H5::H5File & fichier)
{
	std::vector<int> triplet_rgb;
	std::vector<std::vector<int>> palette_cm;
	
	// Nom du dataset a extraire
	const H5std_string DATASET_NAME( "01-PALETTE" );
	H5::DataSet dataset = fichier.openDataSet( DATASET_NAME );
	
	// Get dataspace of the dataset.
	H5::DataSpace dataspace = dataset.getSpace();

	// Recuperation de nx et ny :
	hsize_t dims_out[2];
	int ndims = dataspace.getSimpleExtentDims( dims_out, NULL);
	const int nx= (unsigned long)(dims_out[0]);
	const int ny= (unsigned long)(dims_out[1]);
	std::cout<< "Dimensions: "<< nx<< "*"<< ny << std::endl;
	unsigned char data_out[nx][ny];
	for (int i=0;i<nx;i++)
		for(int j=0;j<ny;j++)
		{
			data_out[i][j]=0;
		}
	
	// Lecture des donnees
	dataset.read(data_out,H5::PredType::NATIVE_UCHAR);
	
	for (unsigned short int i=0;i<nx;i++)
	{
		triplet_rgb.clear();
		for (unsigned short int j=0;j<ny;j++)
		{
			triplet_rgb.push_back((int) data_out[i][j]);
		}
		palette_cm.push_back(triplet_rgb);
		//std::cout<< palette_cm[i][0] << " "<< palette_cm[i][1]<<' '<< palette_cm[i][2]<<std::endl;
	}
	
	return palette_cm;
}


std::vector<Point3D> get_donnees_3D(const H5::H5File &fichier)
{
	std::vector<Point3D> resultat;
	const H5std_string DATASET_NAME( "data" );
	const H5std_string GROUP_NAME("/dataset10/data1");
	H5::DataSet * dataset;

	try
	{
		H5::Group group3D(fichier.openGroup(GROUP_NAME));
		// to determine if the dataset exists in the group
		dataset= new H5::DataSet(group3D.openDataSet(DATASET_NAME));
	}
	catch( H5::GroupIException not_found_error )
	{
		std::cout << " Dataset is not found." << std::endl;
	}
	std::cout << "dataset \""<<GROUP_NAME<< "/"<< DATASET_NAME<< "\" is open" << std::endl;

	H5::DataSpace dataspace = dataset->getSpace();// Get dataspace of the dataset.
	// Recuperation des dimensions:
	int ndims = dataspace.getSimpleExtentNdims();
	std::cout<< "Nombre de dimensions: "<< ndims << std::endl;
	hsize_t dims_out[ndims];
	ndims = dataspace.getSimpleExtentDims( dims_out, NULL);
	const int nz= (unsigned long)(dims_out[0]);
	const int nx= (unsigned long)(dims_out[1]);
	const int ny= (unsigned long)(dims_out[2]);
	std::cout<< "nx=" << nx << std::endl;;
	std::cout<< "ny=" << ny << std::endl;	
	std::cout<< "nz=" << nz << std::endl;
	
	//double donnees3D[nz][nx][ny];

	//std::cout<< "initialistaion donnees3D OK"<< std::endl;
	//dataset->read(donnees3D, H5::PredType::NATIVE_DOUBLE);	

	std::vector<double> donnees(nz*nx*ny);
	dataset->read(&donnees[0], H5::PredType::NATIVE_DOUBLE);
	
	for (int k=0;k<nz;k++)
		for (int i=0;i<nx;i++)
			for(int j=0;j<ny;j++)
			{
				double val= donnees[ (k+1) * (i*nx+j) ];
				Point3D point;
				point.px=i;
				point.py=j;
				point.pz=k;
				point.value= val;
				if (val!=0 && val>-99) resultat.push_back(point);
				
			}
	
	std::cout<< "Nombre de pixels non nuls: "<< resultat.size()<< std::endl;
	
	return resultat;
}
