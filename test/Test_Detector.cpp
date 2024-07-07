/*
**	Filename : Test_Detector.cpp
**	2024-07-06
**	username : rsehgal
*/
#include<iostream>
#include "Detector.h"
#include "Plane.h"
#include <memory>
int main(int argc, char *argv[]){
    std::unique_ptr<Plane> xplane = std::make_unique<Plane>(1,345);
    std::unique_ptr<Plane> yplane = std::make_unique<Plane>(7,231);
    
    std::unique_ptr<Detector> det = std::make_unique<Detector>(
        std::move(xplane),std::move(yplane));
    det->Print();

    std::cout << "Hit Detected : " << det->HitDetected() << std::endl;
    return 0;
}
