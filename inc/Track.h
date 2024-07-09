/*
**	Filename : Track.h
**	2024-06-19
**	username : rsehgal
*/
#ifndef Track_h
#define Track_h

#include "Point3D.h"
#include <iostream>
class TF1;
class Track
{
  Point3D fP1;
  Point3D fP2;
  Point3D fDirCosine;
  Point3D fDirection;
  Point3D fDirectionRatio;
  double fTrackLength;
  double color;

  //vector for track fitting
  std::vector<Point3D*> fPocaPointVec;

public:
  Track();
  Track(Point3D p1, Point3D p2);
  Track(std::vector<Point3D*> pocaPointVec);
  Track(Point3D p1, Point3D p2, double col);
  double GetColor() const { return color; }
  void CalculateDirCosine();
  Point3D GetP1() { return fP1; }
  Point3D GetP2() { return fP2; }
  TF1* GetFitFormula(std::vector<double> xvec, std::vector<double> yvec);
  TF1* GetFitFormulaXZ();
  TF1* GetFitFormulaYZ();
  void SetP1(Point3D val)
  {
    fP1 = val;
    CalculateDirCosine();
  }
  void SetP2(Point3D val)
  {
    fP2 = val;
    CalculateDirCosine();
  }
  void Set(Point3D p1, Point3D p2)
  {
    fP1 = p1;
    fP2 = p2;
    CalculateDirCosine();
  }
  Point3D GetDirCosine() { return fDirCosine; }
  Point3D GetDirection() { return fDirection; }
  Point3D GetDirectionRatio() { return fDirectionRatio; }
  double GetTrackLength() const { return fTrackLength; }
  void Print()
  {
    fP1.Print();
    std::cout << " : ";
    fP2.Print();
  }

  double Angle(Track tr)
  {
    Point3D incoming = fP1 - fP2;
    Point3D outgoing = tr.fP1 - tr.fP2;
    double cosTheta = incoming.Dot(outgoing) / (incoming.Mag() * outgoing.Mag());
    return std::acos(cosTheta);
  }

  // Overloading operator
  void operator=(const Track &newVal);
  double GetZenithAngle();
  std::vector<TF1*> GetFitFormulaVector();
  Point3D GetHitPointAtPlane(unsigned short planeIndex);
  Point3D GetHitPointAtLayer(unsigned short planeIndex);
  Point3D GetHitPointAtZ(double zval);
  ~Track();
};

#endif
