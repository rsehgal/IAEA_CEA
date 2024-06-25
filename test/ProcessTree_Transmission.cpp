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
int main(int argc, char *argv[])
{
  TApplication *fApp = new TApplication("fApp", NULL, NULL);
  Point3D pocaPt;
  TFile *outfile = new TFile("Poca.root", "RECREATE");
  TTree *fTree = new TTree("PocaTree", "PocaTree");

  double angleIn = 0.;
  double angleOut = 0.;
  fTree->Branch("Poca", &pocaPt);
  fTree->Branch("AngleIncoming", &angleIn);
  fTree->Branch("AngleOutgoing", &angleOut);
  T t(argv[1]);
  unsigned int nbinsx = 50;
  unsigned int nbinsy = 50;
  std::cout << "Total Entries : " << t.fChain->GetEntries() << std::endl;
  TH2F *histActual0 = new TH2F("ReconsActual_0", "ReconsActual_0", nbinsx, 0, 600, nbinsy, 0, 600);
  TH2F *histActual3 = new TH2F("ReconsActual_3", "ReconsActual_3", nbinsx, 0, 600, nbinsy, 0, 600);
  TH2F *histExtrapolated = new TH2F("ReconsExtrapolated", "ReconsExtralpolated", 200, 0, 600, 200, 0, 600);
  // t.Loop();
  unsigned long int nentries = t.fChain->GetEntries();
  //nentries = 100000;

  TH1F *diffX = new TH1F("DiffX", "DiffY", 100, 0., 2.);
  TH1F *diffY = new TH1F("DiffY", "DiffY", 100, 0., 2.);
  for (unsigned int i = 0; i < nentries; i++)
  {
    if (!(i % 100000) && i != 0)
      std::cout << "Number of Events processed : " << i << std::endl;
    std::vector<Point3D *> vecOfPoint3D = t.GetMuonTrack(i);
    Track tr(vecOfPoint3D);

    Point3D actualHit0 = *vecOfPoint3D[0];
    Point3D actualHit3 = *vecOfPoint3D[3];

    std::vector<Track *> vecOfTracks = GetIncomingAndOutgoingTracks(vecOfPoint3D);
    Track incoming = *vecOfTracks[0];
    Track outgoing = *vecOfTracks[1];

    angleIn = incoming.GetZenithAngle();
    angleOut = outgoing.GetZenithAngle();

    pocaPt.Set(actualHit0.GetX(),actualHit0.GetY(),actualHit0.GetZ());

    fTree->Fill();
    if (angleIn > 0.1)
    {
      histActual0->Fill(actualHit0.GetX(), actualHit0.GetY());
      histActual3->Fill(actualHit3.GetX(), actualHit3.GetY());

    }
    // histExtrapolated->Fill(extrapolatedHit.GetX(),extrapolatedHit.GetY());
  }

  outfile->cd();

  TCanvas *canDiff = new TCanvas("DiffCanvas", "DiffCanvas");
  canDiff->Divide(2, 1);
  canDiff->cd(1);
  diffX->Draw();
  canDiff->cd(2);
  diffY->Draw();
  diffX->Write();
  diffY->Write();

  TCanvas *transCanvas = new TCanvas("Transmission_Canvas", "Transmision_Canvas");
  transCanvas->Divide(2, 1);
  transCanvas->cd(1);
  histActual0->Draw();
  transCanvas->cd(2);
  histActual3->Draw();

  // histExtrapolated->Draw();
  // histActual->Write();
  // histExtrapolated->Write();

  fTree->Write();
  outfile->Close();
  fApp->Run();

  return 0;
}
