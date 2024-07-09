/*
**	Filename : Detector.h
**	2024-07-06
**	username : rsehgal
*/
#ifndef Detector_h
#define Detector_h
#include "Plane.h"
#include <memory>
#include "Point3D.h"

class Detector
{
    std::unique_ptr<Plane> fXPlane;
    std::unique_ptr<Plane> fYPlane;

public:
    Detector();
    Detector(std::unique_ptr<Plane> xplane, std::unique_ptr<Plane> yplane);
    Detector(short xClusterSize, double xClusterPos, short yClusterSize, double yClusterPos);
    void Print();
    bool HitDetected();
    Point3D* GetPoint3D();

};
#endif
