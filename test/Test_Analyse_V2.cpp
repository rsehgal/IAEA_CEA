/*
**	Filename : Test_Analyse_V2.cpp
**	2024-07-09
**	username : rsehgal
*/
#include <iostream>
#include "Detector.h"
#include "T.h"
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
#include "colors.h"

int main(int argc, char *argv[])
{
  TApplication *fApp = new TApplication("fApp", NULL, NULL);
  gStyle->SetPalette(kRainBow);
  T t(argv[1]);

  TH2F *hist = new TH2F("Recons_Smart_Scattering", "Recons_Smart_Scattering", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);
  TH2F *histAbsorption =
      new TH2F("Recons_Smart_Absorption", "Recons_Smart_Absorption", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);
  /*unsigned int evNo = std::atoi(argv[2]);
  std::vector<std::unique_ptr<Detector>> vecOfDet = t.GetMuonTrack_V2(evNo);
  for (unsigned int i = 0; i < vecOfDet.size(); i++)
  {
      std::cout << "===============================================" << std::endl;
      vecOfDet[i]->Print();
  }
  */
  unsigned long int nentries = t.fChain->GetEntries();
  unsigned int numOfEvents   = std::atoi(argv[2]);
  if (numOfEvents > 0) nentries = numOfEvents;

  Point3D pocaPt;
  Point3D projectedPt;

  std::string outfileName = "Poca_Smart_" + std::to_string(nentries) + ".root";
  TFile *outfile          = new TFile(outfileName.c_str(), "RECREATE");
  TTree *fTreeScattering  = new TTree("Poca_ScatteringTree", "Poca_ScatteringTree");
  fTreeScattering->Branch("PocaPt", &pocaPt);
  TTree *fTreeAbsorption = new TTree("Poca_AbsorptionTree", "Poca_AbsorptionTree");
  fTreeAbsorption->Branch("ProjectedPt", &projectedPt);

  // std::vector<std::unique_ptr<Detector>> vecOfDet;
  for (unsigned int evNo = 0; evNo < nentries; evNo++) {
    if (!(evNo % 100000) && evNo != 0)
      std::cout << "Number of Events processed : " << evNo << " / " << nentries << std::endl;
    std::vector<std::unique_ptr<Detector>> vecOfDet = t.GetMuonTrack_V2(evNo);

    std::vector<Point3D *> vecOfPoint3D = t.GetVectorOfPoint3D(vecOfDet);
    Track tr(vecOfPoint3D);
    std::vector<Track *> vecOfTracks = GetIncomingAndOutgoingTracks(vecOfPoint3D);
    Track incoming                   = *vecOfTracks[0];

    if (t.ScatteringCandidate(vecOfDet)) {
      /*std::cout << RED << "Scattering Candidate found : Event no : " << evNo << RESET << std::endl;
      for (unsigned int i = 0; i < vecOfDet.size(); i++) {
        std::cout << "===============================================" << std::endl;
        vecOfDet[i]->Print();
      }
      break;
      */

      Track outgoing = *vecOfTracks[1];
      // Point3D poca = POCA_V2(incoming, outgoing);
      pocaPt = POCA_V2(incoming, outgoing);
      if (pocaPt.GetScattering() > 0.04) {
        hist->Fill(pocaPt.GetX(), pocaPt.GetY());
        fTreeScattering->Fill();
      }
    }

    if (t.AbsorptionCandidate(vecOfDet)) {
      
      Point3D *hitPt = vecOfDet[2]->GetPoint3D();
      //Taking projection on Different Z : 0, -50, -100, -150, -200
      projectedPt    = incoming.GetHitPointAtZ(0.);//*hitPt;
      histAbsorption->Fill(projectedPt.GetX(), projectedPt.GetY());
      fTreeAbsorption->Fill();
      projectedPt    = incoming.GetHitPointAtZ(-50.);
      fTreeAbsorption->Fill();
      projectedPt    = incoming.GetHitPointAtZ(-100.);
      fTreeAbsorption->Fill();
      projectedPt    = incoming.GetHitPointAtZ(-150.);
      fTreeAbsorption->Fill();
      projectedPt    = incoming.GetHitPointAtZ(-200.);
      fTreeAbsorption->Fill();
      

    }
    vecOfDet.clear();
  }

  new TCanvas("Scattering", "Scattering");
  hist->Draw("colz");
  new TCanvas("Absorption", "Absorption");
  histAbsorption->Draw("colz");

  outfile->cd();
  fTreeScattering->Write();
  fTreeAbsorption->Write();
  outfile->Close();
  fApp->Run();
  return 0;
}
