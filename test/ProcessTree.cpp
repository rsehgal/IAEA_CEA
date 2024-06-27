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
#include <TH2F.h>
#include <TTree.h>
#include <TFile.h>
#include <TStyle.h>
#include "Global.h"
int main(int argc, char *argv[])
{
  TApplication *fApp = new TApplication("fApp", NULL, NULL);
  Point3D pocaPt;
  T t(argv[1]);
  unsigned int numOfEvents = std::atoi(argv[2]);
  std::cout << "Total Entries : " << t.fChain->GetEntries() << std::endl;
  TH2F *hist = new TH2F("Recons", "Recons", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);
  // t.Loop();
  unsigned long int nentries = t.fChain->GetEntries();
  // nentries = 200000;

  if (numOfEvents > 0)
    nentries = numOfEvents;

  std::string outfileName = "Poca_" + std::to_string(nentries)+".root";
  TFile *outfile = new TFile(outfileName.c_str(), "RECREATE");
  TTree *fTree = new TTree("PocaTree", "PocaTree");

  gStyle->SetPalette(kRainBow);
  double angleIn = 0.;
  double angleOut = 0.;
  fTree->Branch("Poca", &pocaPt);
  fTree->Branch("AngleIncoming", &angleIn);
  fTree->Branch("AngleOutgoing", &angleOut);

  // TH1F *diffX = new TH1F("DiffX", "DiffY", 100, 0., 2.);
  // TH1F *diffY = new TH1F("DiffX", "DiffY", 100, 0., 2.);
  std::vector<Point3D> vecOfPocaPt;
  for (unsigned int i = 0; i < nentries; i++)
  {
    if (!(i % 100000) && i != 0)
      std::cout << "Number of Events processed : " << i << std::endl;
    std::vector<Point3D *> vecOfPoint3D = t.GetMuonTrack(i);
    Track tr(vecOfPoint3D);

    /*
        Point3D actualHit = *vecOfPoint3D[0];
        Point3D extrapolatedHit = tr.GetHitPointAtPlane(0);
        Point3D diffPoint = (actualHit - extrapolatedHit);
        diffX->Fill(diffPoint.GetX());
        diffY->Fill(diffPoint.GetY());
    */
    std::vector<Track *> vecOfTracks = GetIncomingAndOutgoingTracks(vecOfPoint3D);
    Track incoming = *vecOfTracks[0];
    Track outgoing = *vecOfTracks[1];
    // Point3D poca = POCA_V2(incoming, outgoing);
    pocaPt = POCA_V2(incoming, outgoing);
    angleIn = incoming.GetZenithAngle();
    angleOut = outgoing.GetZenithAngle();
    // pocaPt.Print();
    if (pocaPt.GetScattering() > 0.003)
    {
      hist->Fill(pocaPt.GetX(), pocaPt.GetY());
      fTree->Fill();
      vecOfPocaPt.push_back(pocaPt);
    }
  }

  unsigned short numOfSlices = 8;
  std::vector<TH2F *> vecOfSlices = GetVectorOfSlices(vecOfPocaPt, numOfSlices);

  hist->Draw();
  outfile->cd();

  // TCanvas *canDiff = new TCanvas("DiffCanvas", "DiffCanvas");
  // canDiff->Divide(2, 1);
  // canDiff->cd(1);
  // diffX->Draw();
  // canDiff->cd(2);
  // diffY->Draw();

  /*for(unsigned int i =0 ; i < vecOfPocaPt.size(); i++){
    vecOfPocaPt[i].Print();
  }*/
  TH2F *histScattering = GetMeanScatteringHist(vecOfPocaPt);
  TCanvas *canScattering = new TCanvas("Scattering", "Scattering");
  canScattering->cd();
  histScattering->Draw();

  // diffX->Write();
  // diffY->Write();
  hist->Write();
  histScattering->Write();

  for (unsigned int i = 0; i < vecOfSlices.size(); i++)
  {
    vecOfSlices[i]->Write();
  }
  fTree->Write();
  outfile->Close();
  fApp->Run();

  return 0;
}
