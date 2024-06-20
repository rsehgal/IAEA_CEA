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

std::vector<TGraph*> GetMuonTrack_Graph(Track *tr){
	Point3D start = tr->GetP1();
	Point3D end = tr->GetP2();
	std::vector<Point3D*> vecOfPoint3D = {&start,&end};
	return GetMuonTrack_Graph(vecOfPoint3D);
	
}
std::vector<TGraph *> GetMuonTrack_Graph(std::vector<Point3D *> vecOfPoint3D)
{
	std::vector<double> vecOfXPos;
	std::vector<double> vecOfYPos;
	std::vector<double> zPosVec;
	std::vector<TGraph *> vecOfGraphs;
	for (unsigned int i = 0; i < vecOfPoint3D.size(); i++)
	{
		vecOfXPos.push_back(vecOfPoint3D[i]->GetX());
		vecOfYPos.push_back(vecOfPoint3D[i]->GetY());
		zPosVec.push_back(vecOfPoint3D[i]->GetZ());
	}
	vecOfGraphs.push_back(new TGraph(vecOfPoint3D.size(), &vecOfXPos[0], &zPosVec[0]));
	vecOfGraphs.push_back(new TGraph(vecOfPoint3D.size(), &vecOfYPos[0], &zPosVec[0]));
	return vecOfGraphs;
}

std::vector<Track*> GetIncomingAndOutgoingTracks(std::vector<Point3D*> vecOfPoint3D){
	std::vector<Track*> vecOfTracks = {GetIncomingTrack(vecOfPoint3D),GetOutgoingTrack(vecOfPoint3D)};
	return vecOfTracks;
}

 Track* GetIncomingTrack(std::vector<Point3D*> vecOfPoint3D){
	return (new Track(*vecOfPoint3D[2],*vecOfPoint3D[3]));
 }

  Track* GetOutgoingTrack(std::vector<Point3D*> vecOfPoint3D){
	return (new Track(*vecOfPoint3D[0],*vecOfPoint3D[1]));
  }

Point3D POCA_V2( Track track1,  Track track2) {
    Point3D p1 = track1.GetP1();
    Point3D p2 = track1.GetP2();
    Point3D p3 = track2.GetP1();
    Point3D p4 = track2.GetP2();

    Point3D dp1(p2.GetX() - p1.GetX() , p2.GetY() - p1.GetY(), p2.GetZ() - p1.GetZ());
    Point3D dp2 = {p4.GetX() - p3.GetX(), p4.GetY() - p3.GetY(), p4.GetZ() - p3.GetZ()};
    Point3D r = {p1.GetX() - p3.GetX(), p1.GetY() - p3.GetY(), p1.GetZ() - p3.GetZ()};

    double a = dp1.GetX() * dp1.GetX() + dp1.GetY() * dp1.GetY() + dp1.GetZ() * dp1.GetZ();
    double b = dp1.GetX() * dp2.GetX() + dp1.GetY() * dp2.GetY() + dp1.GetZ() * dp2.GetZ();
    double c = dp2.GetX() * dp2.GetX() + dp2.GetY() * dp2.GetY() + dp2.GetZ() * dp2.GetZ();
    double d = dp1.GetX() * r.GetX() + dp1.GetY() * r.GetY() + dp1.GetZ() * r.GetZ();
    double e = dp2.GetX() * r.GetX() + dp2.GetY()* r.GetY() + dp2.GetZ() * r.GetZ();

    double sc = (b * e - c * d) / (a * c - b * b);
    double tc = (a * e - b * d) / (a * c - b * b);

	double scattering = track1.Angle(track2);

    Point3D poca((p1.GetX() + sc * dp1.GetX()),
				(p1.GetY() + sc * dp1.GetY()),
                (p1.GetZ() + sc * dp1.GetZ()),
				scattering);

    return poca;
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

Vec_t POCA( Track incoming, Track outgoing){
	Vec_t p1(0.,0.,0.),q1(0.,0.,0.);
	//std::cout<<"INComing Track : "; incoming.Print();
	//std::cout<<"OUTGoing Track : "; outgoing.Print();
	return POCA(incoming.GetP1(),incoming.GetDirCosine(),outgoing.GetP1(), outgoing.GetDirCosine(),p1,q1);
	//return POCA_V3(incoming,outgoing);
}