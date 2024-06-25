/*
 * Track.cpp
 *
 *  Created on: Jul 5, 2016
 *      Author: rsehgal
 */

#include "Track.h"
#include "Point3D.h"
#include <TGraph.h>
#include <TF1.h>
#include "Global.h"
Track::Track()
{
	// TODO Auto-generated constructor stub
	fP1 = Point3D(0., 0., 0.);
	fP2 = Point3D(0., 0., 0.);
	CalculateDirCosine();
}

Track::~Track()
{
	// TODO Auto-generated destructor stub
}

Track::Track(Point3D p1, Point3D p2)
{
	fP1 = p1;
	fP2 = p2;
	CalculateDirCosine();
}
Track::Track(Point3D p1, Point3D p2, double col)
{
	color = col;
	fP1 = p1;
	fP2 = p2;
}
Track::Track(std::vector<Point3D *> pocaPointVec)
{
	for (unsigned short i = 0; i < pocaPointVec.size(); i++)
	{
		fPocaPointVec.push_back(pocaPointVec[i]);
	}
	fP1 = *fPocaPointVec[0];
	fP2 = *fPocaPointVec[fPocaPointVec.size() - 1];
	CalculateDirCosine();
}

void Track::CalculateDirCosine()
{
	fDirCosine = (fP2 - fP1).Unit();
	fDirection = (fP2 - fP1).Unit();
	fDirectionRatio = (fP2 - fP1);
	fTrackLength = fDirectionRatio.Mag();
}

void Track::operator=(const Track &newVal)
{
	this->fP1 = newVal.fP1;
	this->fP2 = newVal.fP2;
	this->fDirCosine = newVal.fDirCosine;
	this->fDirection = newVal.fDirection;
	this->fDirectionRatio = newVal.fDirectionRatio;
}

double Track::GetZenithAngle()
{
	Track ref(Point3D(0., 0., 0.), Point3D(0., 0., -10));
	return this->Angle(ref);
}

TF1 *Track::GetFitFormula(std::vector<double> xvec, std::vector<double> yvec)
{
	TGraph *gr = new TGraph(xvec.size(), &xvec[0], &yvec[0]);
	TF1 *formula = new TF1("pol1", "pol1", -300., 600.);
	gr->Fit(formula, "q");
	return formula;
}

TF1 *Track::GetFitFormulaXZ()
{
	std::vector<double> xvec;
	std::vector<double> zvec;
	for (unsigned short i = 0; i < fPocaPointVec.size(); i++)
	{
		xvec.push_back(fPocaPointVec[i]->GetX());
		zvec.push_back(fPocaPointVec[i]->GetZ());
	}
	return GetFitFormula(xvec, zvec);
}
TF1 *Track::GetFitFormulaYZ()
{
	std::vector<double> yvec;
	std::vector<double> zvec;
	for (unsigned short i = 0; i < fPocaPointVec.size(); i++)
	{
		yvec.push_back(fPocaPointVec[i]->GetY());
		zvec.push_back(fPocaPointVec[i]->GetZ());
	}
	return GetFitFormula(yvec, zvec);
}
std::vector<TF1 *> Track::GetFitFormulaVector()
{
	std::vector<TF1 *> vecOfFitFormula;
	vecOfFitFormula.push_back(GetFitFormulaXZ());
	vecOfFitFormula.push_back(GetFitFormulaYZ());
	return vecOfFitFormula;
}
Point3D Track::GetHitPointAtPlane(unsigned short planeIndex)
{
	double z = vecOfZPos[planeIndex];
	std::vector<TF1 *> vecOfFitFormula = GetFitFormulaVector();
	double x = vecOfFitFormula[0]->GetX(z);
	double y = vecOfFitFormula[1]->GetX(z);
	return Point3D(x,y,z);
}
