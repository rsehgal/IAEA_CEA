/*
**	Filename : Point3D.h
**	2024-06-19
**	username : rsehgal
*/
#ifndef Point3D_h
#define Point3D_h

#pragma once
#include <TROOT.h>

class Point3D
{
	double fX;
	double fY;
	double fZ;

	double fScattering;

public:
	Point3D();
	Point3D(const Point3D &pt);
	double GetX() const { return fX; }
	double GetY() const { return fY; }
	double GetZ() const { return fZ; }
	void SetScattering(double val) ;
	double GetScattering() const;
	Point3D(double x, double y, double z);
	Point3D(double x, double y, double z, double s);
	void SetZero();
	void Set(double x, double y, double z);
	void Set(double x, double y, double z, double s);
	void Divide(int n);
	double Distance(Point3D p2);
	void Print();
	virtual ~Point3D();
	unsigned int GetLayer();
	Point3D *InCm();
	double Dot(Point3D p);
	double Mag2();
	double Mag();
	Point3D Unit();
	void SetX(double val){
		fX = val;
	}
	void SetY(double val){
		fY = val;
	}
	void SetZ(double val){
		fZ = val;
	}

	Point3D operator+(Point3D);
	Point3D operator-(Point3D);
	Point3D operator*(double val);
	Point3D operator/(double val);

	// Point3D operator += (Point3D obj);
	// Point3D* operator += (Point3D *obj);
	// Point3D operator /= (int n);

	ClassDef(Point3D, 1)
};

#endif
