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
#include <TGraph2D.h>
int main(int argc, char *argv[])
{
  TApplication *fApp = new TApplication("fApp", NULL, NULL);
  T t(argv[1]);
  std::cout << "Total Entries : " << t.fChain->GetEntries() << std::endl;
  
  //Reading specific event
  unsigned int evNo = std::atoi(argv[2]);

  //Getting the Muon Track
  std::vector<Point3D *> vecOfPoint3D = t.GetMuonTrack(evNo);
  std::vector<double> xvec;
  std::vector<double> yvec;
  std::vector<double> zvec;

  Track tr(vecOfPoint3D);

  for (unsigned int i = 0; i < vecOfPoint3D.size(); i++)
  {
    xvec.push_back(vecOfPoint3D[i]->GetX());
    yvec.push_back(vecOfPoint3D[i]->GetY());
    zvec.push_back(vecOfPoint3D[i]->GetZ());
  }

  TGraph2D *gr = new TGraph2D(vecOfPoint3D.size(), &xvec[0], &yvec[0], &zvec[0]);
  TF2 *fitFcn = new TF2("fitFcn", plane, 0, 500, 0, 50, 3); // Adjust the range as needed
  gr->Fit("fitFcn", "q");

  std::cout <<"Chi2 : " << fitFcn->GetChisquare() << " : " << fitFcn->GetNDF() << std::endl;

  double x = GetX(fitFcn,*vecOfPoint3D[0]);
  double y = GetY(fitFcn,*vecOfPoint3D[0]);

  Point3D fittedPt(x,y,vecOfPoint3D[0]->GetZ());

  std::cout << "======== Actual Point ========" << std::endl;
  vecOfPoint3D[0]->Print();
  std::cout << "======== Fitted Point ========" << std::endl;
  fittedPt.Print();
  std::cout << "======== Fitted Point Using Track ========" << std::endl;
  tr.GetHitPointAtLayer(0).Print();
  //std::cout << "(" << x << " , " << y << ")" << std::endl;

  fApp->Run();

  return 0;
}
