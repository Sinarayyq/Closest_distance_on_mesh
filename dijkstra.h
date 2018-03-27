//Sinara YANG
//This function is used to sequence subsampled points according to the distances between them and the start point
//using dijkstra algorithm.


#pragma once

#ifndef DIJKSTRA_H
#define DIJKSTRA_H



#include <iostream>
#include <math.h>
#include <fstream>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>


//Parameter declaration:
//                 mesh -- OpenMesh format, please modify MAX parameter in ListUDG class of dijkstra.cpp if there are over 5000 vertices
//    subsampled_points -- subsampled points on mesh, about 200 points
//          start_point -- OpenMesh format, must be on mesh and one of subsampled points
//             distance -- distance[i][0] is the distances(double) between subsampled_points and start point
//                         distance[i][1] is the sequence number of subsampled_points
//                         you can get closest point by subsampled_points[distance[1][1]]  (subsampled_points[distance[0][1]] is the start point)
//                         you can get closest distance by distance[1][0]                  (distance[0][0]] is always zero)
int DijkstraAlgorithm(OpenMesh_Mesh mesh, std::vector<OpenMesh_Mesh::Point> subsampled_points, OpenMesh_Mesh::Point start_point, std::vector<std::vector<double>> *distance);




#endif