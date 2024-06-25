#define T_cxx
#include "T.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include "Point3D.h"
#include "Global.h"

std::vector<Point3D*> T::GetMuonTrack(unsigned int trackIndex)
{
   std::vector<Point3D*> vecOfPoint3D;
   int val = GetEntry(trackIndex);
   for (unsigned short i = 0; i < 4; i++)
   {

      //std::cout << MGv3_ClusPos[2*i][0] << "," << MGv3_ClusPos[2*i + 1][0] << std::endl;
      //std::cout << std::endl
        //        << "=========================================" << std::endl;
      vecOfPoint3D.push_back(new Point3D(MGv3_ClusPos[2*i][0],MGv3_ClusPos[2*i+1][0],vecOfZPos[i]));
   }
   return vecOfPoint3D;

}

std::vector<unsigned short> T::GetVectorOfClusterSize(unsigned int trackIndex){
   std::vector<unsigned short> vecOfClusterSize;
   int val = GetEntry(trackIndex);
   for(unsigned short i = 0 ; i < 8 ; i++){
      vecOfClusterSize.push_back(MGv3_ClusSize[i][0]);
   }
   return vecOfClusterSize;
}

void T::Loop()
{
   //   In a ROOT session, you can do:
   //      root> .L T.C
   //      root> T t
   //      root> t.GetEntry(12); // Fill t data members with entry number 12
   //      root> t.Show();       // Show values of entry 12
   //      root> t.Show(16);     // Read and show values of entry 16
   //      root> t.Loop();       // Loop on all entries
   //

   //     This is the loop skeleton where:
   //    jentry is the global entry number in the chain
   //    ientry is the entry number in the current Tree
   //  Note that the argument to GetEntry must be:
   //    jentry for TChain::GetEntry
   //    ientry for TTree::GetEntry and TBranch::GetEntry
   //
   //       To read only selected branches, Insert statements like:
   // METHOD1:
   //    fChain->SetBranchStatus("*",0);  // disable all branches
   //    fChain->SetBranchStatus("branchname",1);  // activate branchname
   // METHOD2: replace line
   //    fChain->GetEntry(jentry);       //read all branches
   // by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0)
      return;

   Long64_t nentries = fChain->GetEntriesFast();
   nentries = 1;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry = 0; jentry < nentries; jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0)
         break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      for (unsigned short i = 0; i < 8; i += 2)
      {
         for(unsigned short j=0;j<300;j++){
            std::cout << MGv3_ClusSize[i][j] <<",";
         }
         std::cout <<"----------------------------------------" << std::endl;
         for(unsigned short j=0;j<300;j++){
            std::cout << MGv3_ClusPos[i][j] <<",";
         }
         std::cout << MGv3_ClusPos[i][0] << "," << MGv3_ClusPos[i + 1][0] << std::endl;

         std::cout << std::endl
                   << "=========================================" << std::endl;
      }
   }
}
