/*
**	Filename : Helpers.h
**	2024-06-19
**	username : rsehgal
*/
#ifndef Helpers_h
#define Helpers_h

#include <TGraph.h>
#include "Point3D.h"
#include <vector>
extern std::vector<TGraph *> GetMuonTrack_Graph(std::vector<Point3D *> vecOfPoint3D);

#endif
