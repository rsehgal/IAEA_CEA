/*
**	Filename : Test_POCA.cpp
**	2024-06-19
**	username : rsehgal
*/
#include <iostream>
#include "Track.h"
#include "T.h"
#include <iostream>
#include <Point3D.h>
#include <TGraph.h>
#include "Helpers.h"
#include <vector>
#include <TApplication.h>
#include <TCanvas.h>

int main(int argc, char *argv[])
{
    // TApplication *fApp = new TApplication("fApp", NULL, NULL);
    {
        /*
        Track in(Point3D(10., 0., 10.), Point3D(5., 5., 10.));
        Track out(Point3D(5., -5., 10.), Point3D(10., 0., 10.));
        //Point3D poca = POCA(in, out);
        //std::cout << "======= POCA Point ================" << std::endl;
        //poca.Print();
        Point3D poca2 = POCA_V2(in, out);
        std::cout << "======= POCA2 Point ================" << std::endl;
        poca2.Print();
        */
    }

    T t;
    std::vector<Point3D *> vecOfPoint3D = t.GetMuonTrack(2);
    /*std::vector<Point3D*> vecOfPoint3D;
    vecOfPoint3D.push_back(new Point3D(5.,-5.,10.));
    vecOfPoint3D.push_back(new Point3D(10.,0.,10.));
    vecOfPoint3D.push_back(new Point3D(10.,0.,10.));
    vecOfPoint3D.push_back(new Point3D(5.,5.,10.));
    */
    std::vector<Track *> vecOfTracks = GetIncomingAndOutgoingTracks(vecOfPoint3D);
    Track incoming = *vecOfTracks[0];
    Track outgoing = *vecOfTracks[1];
    std::cout << "===== Incoming =======" << std::endl;
    incoming.Print();
    std::cout << "====== Outgoing =========" << std::endl;
    outgoing.Print();
    Point3D poca = POCA_V2(incoming, outgoing);
    std::cout << "======= POCA Point ================" << std::endl;
    poca.Print();
    // fApp->Run();
}
