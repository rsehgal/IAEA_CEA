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
using Vec_t = Point3D;
extern std::vector<TGraph *> GetMuonTrack_Graph(std::vector<Point3D *> vecOfPoint3D);
extern Vec_t POCA(Vec_t p, Vec_t u, Vec_t q, Vec_t v, Vec_t &p1, Vec_t &q1);

#endif
