/*
**	Filename : Test_Analyse.cpp
**	2024-06-18
**	username : rsehgal
*/
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
  TApplication *fApp = new TApplication("fApp", NULL, NULL);
  T t;
  // t.Loop();
  std::vector<Point3D *> vecOfPoint3D = t.GetMuonTrack(20);
  for (unsigned int i = 0; i < vecOfPoint3D.size(); i++)
  {
    std::cout << "------------------------------------" << std::endl;
    vecOfPoint3D[i]->Print();
  }
  std::vector<TGraph *> vecOfGraphs = GetMuonTrack_Graph(vecOfPoint3D);
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
    vecOfGraphs[i]->Draw("ap");
  }

  fApp->Run();

  return 0;
}
