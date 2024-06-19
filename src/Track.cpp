/*
 * Track.cpp
 *
 *  Created on: Jul 5, 2016
 *      Author: rsehgal
 */

#include "Track.h"
#include "Point3D.h"
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

