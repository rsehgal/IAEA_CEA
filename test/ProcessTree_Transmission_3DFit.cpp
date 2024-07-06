/*
**	Filename : ProcessTree_Transmission.cpp
**	2024-06-24
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
#include <TH2F.h>
#include <TTree.h>
#include <TFile.h>
#include <TF1.h>
#include "Global.h"
#include <TStyle.h>
int main(int argc, char *argv[])
{
  TApplication *fApp = new TApplication("fApp", NULL, NULL);
  Point3D pt;
  TFile *outfile = new TFile("Transmission.root", "RECREATE");
  TTree *fTree = new TTree("TransmissionTree", "TransmissionTree");
  gStyle->SetPalette(kRainBow);

  double fittedAngleIn = 0.;
  double diffX=0.;
  double diffY=0.;
  fTree->Branch("Pt", &pt);
  fTree->Branch("fitteAngleIn", &fittedAngleIn);
  fTree->Branch("diffX", &diffX);
  fTree->Branch("diffY", &diffY);
  T t(argv[1]);
  unsigned int numOfEvents = std::atoi(argv[2]);

  std::cout << "Total Entries : " << t.fChain->GetEntries() << std::endl;
  TH2F *histActual0 = new TH2F("ReconsActual_0", "ReconsActual_0", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);
  TH2F *histActual3 = new TH2F("ReconsActual_3", "ReconsActual_3", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);
  nbinsx = 200;
  nbinsy = 200;
  TH2F *histExtrapolated = new TH2F("ReconsExtrapolated", "ReconsExtralpolated", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);

  TH2F *histExtra0 = new TH2F("Hit on Plane 0", "Hit on Plane 0", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);
  TH2F *histExtra1 = new TH2F("Hit on Plane 1", "Hit on Plane 1", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);
  TH2F *histExtra2 = new TH2F("Hit on Plane 2", "Hit on Plane 2", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);
  TH2F *histExtra3 = new TH2F("Hit on Plane 3", "Hit on Plane 3", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);
  // t.Loop();

  unsigned long int nentries = t.fChain->GetEntries();
  // nentries = 100000;
  if (numOfEvents > 0)
    nentries = numOfEvents;

  for (unsigned int i = 0; i < nentries; i++)
  {
    if (!(i % 100000) && i != 0)
      std::cout << "Number of Events processed : " << i << std::endl;
    std::vector<Point3D *> vecOfPoint3D = t.GetMuonTrack(i);
    Track tr(vecOfPoint3D);
    Point3D extrapolatedHit0 = tr.GetHitPointAtLayer(0);
    Point3D extrapolatedHit1 = tr.GetHitPointAtLayer(1);
    Point3D extrapolatedHit2 = tr.GetHitPointAtLayer(2);
    Point3D extrapolatedHit3 = tr.GetHitPointAtLayer(3);

    diffX = vecOfPoint3D[0]->GetX()-extrapolatedHit0.GetX();
    diffY = vecOfPoint3D[0]->GetY()-extrapolatedHit0.GetY();

    fittedAngleIn = Track(extrapolatedHit0, extrapolatedHit3).GetZenithAngle();
    extrapolatedHit0.SetScattering(fittedAngleIn);
    pt = extrapolatedHit0;
    histExtrapolated->Fill(extrapolatedHit0.GetX(), extrapolatedHit0.GetY());
    histExtra0->Fill(extrapolatedHit0.GetX(), extrapolatedHit0.GetY());
    histExtra1->Fill(extrapolatedHit1.GetX(), extrapolatedHit1.GetY());
    histExtra2->Fill(extrapolatedHit2.GetX(), extrapolatedHit2.GetY());
    histExtra3->Fill(extrapolatedHit3.GetX(), extrapolatedHit3.GetY());
    fTree->Fill();
  }

  outfile->cd();

  histExtrapolated->Draw();
  // histActual->Write();
  histExtrapolated->Write();

  TCanvas *can = new TCanvas("Transmission","Transmission");
  can->Divide(2,2);

  can->cd(1);
  histExtra0->Draw("colz");
  can->cd(2);
  histExtra1->Draw("colz");
  can->cd(3);
  histExtra2->Draw("colz");
  can->cd(4);
  histExtra3->Draw("colz");

  fTree->Write();
  can->Write();
  outfile->Close();
  fApp->Run();

  return 0;
}
