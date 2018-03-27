//Sinara YANG
//This functions are used for dijkstra algorithm.


#pragma once

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iomanip>
#include <iostream>
#include <vector>
#include <iterator>

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
#include <OpenMesh\Core\Mesh\PolyMesh_ArrayKernelT.hh>


typedef OpenMesh::PolyMesh_ArrayKernelT<> OpenMesh_Mesh;

int DijkstraAlgorithm(OpenMesh_Mesh mesh, std::vector<OpenMesh_Mesh::Point> subsampled_points, OpenMesh_Mesh::Point start_point, std::vector<std::vector<double>> *distance);

#endif