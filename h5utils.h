#ifndef H5UTILS_H
#define H5UTILS_H

#include <vector>
#include <iostream>

#include "H5Cpp.h"
#include "Point3D.h"

const std::pair<int,int> get_nx_ny(const H5::H5File & fichier);
std::vector<unsigned char> get_donnees_CM(const H5::H5File & fichier);
std::vector<std::vector<int>> get_palette_CM(const H5::H5File & fichier);

std::vector<Point3D> get_donnees_3D(const H5::H5File & fichier);


#endif // H5UTILS_H
