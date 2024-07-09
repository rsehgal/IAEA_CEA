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
  TH2F *hist                 = new TH2F("Recons", "Recons", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);
  unsigned long int nentries = t.fChain->GetEntries();
  unsigned int numOfEvents   = std::atoi(argv[2]);
  if (numOfEvents > 0) nentries = numOfEvents;

  for (unsigned int evNo = 0; evNo < nentries; evNo++) {
    if (!(evNo % 100000) && evNo != 0)
      std::cout << "Number of Events processed : " << evNo << " / " << nentries << std::endl;
    std::vector<Point3D *> vecOfPoint3D = t.GetMuonTrack(evNo);

    if (vecOfPoint3D.size() != 4) continue;

    Track tr(vecOfPoint3D);
    std::vector<Track *> vecOfTracks = GetIncomingAndOutgoingTracks(vecOfPoint3D);
    Track incoming                   = *vecOfTracks[0];
    Track outgoing                   = *vecOfTracks[1];
    // Point3D poca = POCA_V2(incoming, outgoing);
    Point3D pocaPt = POCA_V2(incoming, outgoing);
    if (pocaPt.GetScattering() > 0.04) {
      hist->Fill(pocaPt.GetX(), pocaPt.GetY());
    }

    vecOfPoint3D.clear();
  }

  hist->Draw("colz");
  fApp->Run();
  return 0;
}
