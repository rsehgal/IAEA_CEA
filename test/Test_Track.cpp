/*
**	Filename : Test_Track.cpp
**	2024-06-19
**	username : rsehgal
*/
#include <iostream>
#include "Track.h"
#include "Point3D.h"
#include <TApplication.h>
#include "Helpers.h"
#include <TCanvas.h>
int main(int argc, char *argv[])
{
    TApplication *fApp = new TApplication("fApp", NULL, NULL);
    Track t(Point3D(1., 2., -5.), Point3D(1., 2., 5.));
    t.Print();
    std::vector<TGraph *> vecOfGraphs = GetMuonTrack_Graph(&t);
    TCanvas *can = new TCanvas("Muon_Track", "Muon_Track");
    can->Divide(2, 1);
    for (unsigned int i = 0; i < vecOfGraphs.size(); i++)
    {
        can->cd(i + 1);
        if (i == 0)
            vecOfGraphs[i]->SetTitle("XZ Projection of Muon Track");
        else
            vecOfGraphs[i]->SetTitle("YZ Projection of Muon Track");
        vecOfGraphs[i]->SetMarkerStyle(8);
        vecOfGraphs[i]->Draw("apl");
    }

    fApp->Run();

    return 0;
}
