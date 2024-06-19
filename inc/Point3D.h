/*
**	Filename : Point3D.h
**	2024-06-19
**	username : rsehgal
*/
#ifndef Point3D_h
#define Point3D_h

#pragma once
#include <TROOT.h>

class Point3D {
	double fX;
	double fY;
	double fZ;

public:
	Point3D();
	Point3D(const Point3D &pt);
	double GetX()const{return fX;}
	double GetY()const{return fY;}
	double GetZ()const{return fZ;}
	Point3D(double x, double y, double z);
	void SetZero();
	void Set(double x, double y, double z);
	void Divide(int n);
	double Distance(Point3D p2);
	void Print();
	virtual ~Point3D();
	unsigned int GetLayer();
	Point3D* InCm();

	//Point3D operator += (Point3D obj);
	//Point3D* operator += (Point3D *obj);
	//Point3D operator /= (int n);

	ClassDef(Point3D,1)
};


#endif 
