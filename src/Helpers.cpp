/*
**	Filename : Helpers.cpp
**	2024-06-19
**	username : rsehgal
*/
#include <iostream>
#include "Helpers.h"
#include <TGraph.h>
#include "Point3D.h"
#include <vector>
#include "Global.h"
std::vector<TGraph *> GetMuonTrack_Graph(std::vector<Point3D *> vecOfPoint3D)
{
	std::vector<double> vecOfXPos;
	std::vector<double> vecOfYPos;
	std::vector<TGraph *> vecOfGraphs;
	for (unsigned int i = 0; i < vecOfPoint3D.size(); i++)
	{
		vecOfXPos.push_back(vecOfPoint3D[i]->GetX());
		vecOfYPos.push_back(vecOfPoint3D[i]->GetY());
	}
	vecOfGraphs.push_back(new TGraph(vecOfPoint3D.size(), &vecOfXPos[0], &vecOfZPos[0]));
	vecOfGraphs.push_back(new TGraph(vecOfPoint3D.size(), &vecOfYPos[0], &vecOfZPos[0]));
	return vecOfGraphs;
}
