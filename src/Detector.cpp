/*
**	Filename : Detector.cpp
**	2024-07-06
**	username : rsehgal
*/
#include <iostream>
#include "Detector.h"
#include "Plane.h"

Detector::Detector()
{
}

Detector::Detector(std::unique_ptr<Plane> xplane, std::unique_ptr<Plane> yplane)
    : fXPlane(std::move(xplane)), fYPlane(std::move(yplane))
{
}

void Detector::Print()
{
    if (fXPlane)
    {
        std::cout << "XPlane : ";
        fXPlane->Print();
    }
    if (fYPlane)
    {
        std::cout << "YPlane : ";
        fYPlane->Print();
    }
}

bool Detector::HitDetected()
{
    return (fXPlane->sClusterSize > 1 && fYPlane->sClusterSize > 1);
}