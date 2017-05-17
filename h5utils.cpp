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

