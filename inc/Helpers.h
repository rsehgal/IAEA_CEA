/*
**	Filename : Helpers.h
**	2024-06-19
**	username : rsehgal
*/
#ifndef Helpers_h
#define Helpers_h

#include <TGraph.h>
#include "Point3D.h"
#include <vector>
#include "Track.h"
#include  <TH2F.h>
using Vec_t = Point3D;
extern std::vector<TGraph *> GetMuonTrack_Graph(std::vector<Point3D *> vecOfPoint3D);
extern std::vector<TGraph*> GetMuonTrack_Graph(Track *tr);
extern Vec_t POCA(Vec_t p, Vec_t u, Vec_t q, Vec_t v, Vec_t &p1, Vec_t &q1);
extern Vec_t POCA( Track incoming, Track outgoing);
extern Point3D POCA_V2( Track track1,  Track track2);
extern std::vector<Track*> GetIncomingAndOutgoingTracks(std::vector<Point3D*> vecOfPoint3D);
extern Track* GetIncomingTrack(std::vector<Point3D*> vecOfPoint3D);
extern Track* GetOutgoingTrack(std::vector<Point3D*> vecOfPoint3D);
extern TH2F* GetMeanScatteringHist(std::vector<Point3D> vecOfPocaPt);
extern std::vector<TH2F*> GetVectorOfSlices(std::vector<Point3D> vecOfPocaPt, unsigned short numOfSlices=1);
#endif
