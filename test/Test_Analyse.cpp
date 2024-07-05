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
#include <Track.h>
#include <TF1.h>
#include "Global.h"
int main(int argc, char *argv[])
{
  TApplication *fApp = new TApplication("fApp", NULL, NULL);
  T t(argv[1]);
  std::cout << "Total Entries : " << t.fChain->GetEntries() << std::endl;
  t.Loop();
  return 0;
  unsigned int evNo = std::atoi(argv[2]);
  std::vector<Point3D *> vecOfPoint3D = t.GetMuonTrack(evNo);
  Track *tr = new Track(vecOfPoint3D);
  TF1 *formulaXZ = tr->GetFitFormulaXZ();
  TF1 *formulaYZ = tr->GetFitFormulaYZ();

  Point3D hitPointAtPlane0 = tr->GetHitPointAtPlane(0);
  std::cout << "============= using Fitting =============" << std::endl;
  vecOfPoint3D[0]->Print();
  //double z = vecOfZPos[0];
  //std::cout << "(" << formulaXZ->GetX(z) << " ," << formulaYZ->Eval(z) << " ," << z << ")" << std::endl;
  hitPointAtPlane0.Print();
  std::cout << "========================================" << std::endl;
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

    if (i == 0)
      formulaXZ->Draw("same");
    else
      formulaYZ->Draw("same");
  }

  
  std::vector<Track *> vecOfTracks = GetIncomingAndOutgoingTracks(vecOfPoint3D);
  std::cout << "====== Incoming ================" << std::endl;
  vecOfTracks[0]->Print();
  std::cout << "====== Outgoing ================" << std::endl;
  vecOfTracks[1]->Print();

  std::cout << "-------------------------------------" << std::endl;
  double estX = formulaXZ->GetX(vecOfZPos[0]/cm);
  double estY = formulaYZ->GetX(vecOfZPos[0]/cm);

  std::cout <<"XZ : Chi2 : NDF :: " << formulaXZ->GetChisquare()<<" : " <<formulaXZ->GetNDF() << std::endl;
  std::cout <<"YZ : Chi2 : NDF :: " << formulaYZ->GetChisquare()<<" : " <<formulaYZ->GetNDF() << std::endl;
  std::cout << "Estimated : (" << estX <<" , "<< estY <<")" << std::endl; 


  fApp->Run();

  return 0;
}
