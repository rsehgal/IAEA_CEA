/*
**	Filename : Test_Plane.cpp
**	2024-07-06
**	username : rsehgal
*/
#include<iostream>
#include "Plane.h"
#include <memory>
int main(int argc, char *argv[]){
     std::unique_ptr<Plane> p_unique = std::make_unique<Plane>(6,546);
     p_unique->Print();
    Plane p(4,405.);
    p.Print();
}
