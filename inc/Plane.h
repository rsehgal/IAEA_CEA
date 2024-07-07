/*
**	Filename : Plane.h
**	2024-07-06
**	username : rsehgal
*/
#ifndef Plane_h
#define Plane_h
#include <iostream>
struct Plane
{
  short sClusterSize;
  double sClusterPos;

  Plane() {}
  Plane(short clusterSize, double clusterPos) : sClusterSize(clusterSize), sClusterPos(clusterPos)
  {
  }

  Plane(Plane &pl)
  {
    sClusterSize = pl.sClusterSize;
    sClusterPos = pl.sClusterPos;
  }

  void Print()
  {
    std::cout << "ClusterSize : " << sClusterSize << " : ClusterPos : " << sClusterPos << std::endl;
  }
};

#endif
