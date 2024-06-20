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
int main(int argc, char *argv[])
{
  TApplication *fApp = new TApplication("fApp", NULL, NULL);
  T t;
  std::cout << "Total Entries : " << t.fChain->GetEntries() << std::endl;
  TH2F *hist = new TH2F("Recons","Recons",100,0,800,100,0,800);
  // t.Loop();
  unsigned long int nentries = t.fChain->GetEntries();
  nentries = 1000000;
  for (unsigned int i = 0 ; i < nentries ; i++ ){
    if(!(i%10000) && i!=0)
      std::cout << "Number of Events processed : " << i << std::endl;
    std::vector<Point3D *> vecOfPoint3D = t.GetMuonTrack(i);
    std::vector<Track*> vecOfTracks = GetIncomingAndOutgoingTracks(vecOfPoint3D);
    Track incoming = *vecOfTracks[0];
    Track outgoing = *vecOfTracks[1];
    Point3D poca = POCA_V2(incoming, outgoing);
    //poca.Print();
    hist->Fill(poca.GetX(),poca.GetY());
  }
  
  hist->Draw();
  fApp->Run();

  return 0;
}
