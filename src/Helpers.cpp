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

using Vec_t = Point3D;
using Precision = double;

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

Vec_t POCA(Vec_t p, Vec_t u, Vec_t q, Vec_t v, Vec_t &p1, Vec_t &q1){

	  Precision pDotv=p.Dot(v);
	  Precision qDotv=q.Dot(v);
	  Precision pDotu=p.Dot(u);
	  Precision qDotu=q.Dot(u);
	  Precision uDotv=u.Dot(v);
	  Precision vMag2=v.Mag2();
	  Precision uMag2=u.Mag2();


	Precision s=0.,t=0.;
	//s = (-(p.Dot(v)-q.Dot(v))/u.Dot(v))+(-1.*v.Mag2()*(u.Dot(v)*(p.Dot(u)-q.Dot(u))- (v.Mag2()*(p.Dot(v)-q.Dot(v)))))/(u.Dot(v)*(-1*(u.Dot(v) * u.Dot(v)) + v.Mag2()*u.Mag2()));
	Precision a = -(pDotv-qDotv)/uDotv;
	Precision b1 = uDotv*(pDotu-qDotu);
	Precision b2 = uMag2*(pDotv-qDotv);
	Precision b = b1 - b2;
	Precision c = (-uDotv*uDotv + vMag2*uMag2);
	Precision d = (-vMag2*b)/(uDotv*c);
	s = a+d;
	// std::cout<<"B1 : "<<b1<<" : B2 : "<<b2<<std::endl;
	// std::cout<<"A : "<<a<<" : B : "<<b<<" : C : "<<c<<" : D : "<<d<<std::endl;
	// std::cout<<"S : "<<s<<std::endl;


	double numer = (uDotv*(pDotu-qDotu) - uMag2*(pDotv-qDotv));
	double deno = (uDotv*uDotv - uMag2*vMag2);
	t = numer / deno;
	// std::cout<<"T : "<<t<<std::endl;

	//Vec_t
	p1 = p + u*s;
	//Vec_t
	q1 = q + v*t;

	//std::cout <<"S : " << s <<" : T : " << t << std::endl;
	return (p1+q1)/2.;
	//return s;
	}
