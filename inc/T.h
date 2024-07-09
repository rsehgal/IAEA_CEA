//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 18 19:26:07 2024 by ROOT version 6.30/02
// from TTree T/event
// found on file: iaea1_Pb_run03_analyse.root
//////////////////////////////////////////////////////////

#ifndef T_h
#define T_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "Point3D.h"
#include <string>
#include "Detector.h"
// Header file for the classes stored in the TTree if any.


class T {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           evn;
   Double_t        evttime;
   Int_t           MGv3_NClus[8];
   Int_t           MGv3_Spark[8];
   Double_t        MGv3_ClusAmpl[8][300];
   Double_t        MGv3_ClusSize[8][300];
   Double_t        MGv3_ClusPos[8][300];
   Double_t        MGv3_ClusMaxStripAmpl[8][300];
   Double_t        MGv3_ClusMaxSample[8][300];
   Double_t        MGv3_ClusTOT[8][300];
   Double_t        MGv3_ClusT[8][300];
   Double_t        MGv3_StripMaxAmpl[8][61];
   Int_t           MGv3_ClusMaxStrip[8][300];

   // List of branches
   TBranch        *b_evn;   //!
   TBranch        *b_evttime;   //!
   TBranch        *b_MGv3_NClus;   //!
   TBranch        *b_MGv3_Spark;   //!
   TBranch        *b_MGv3_ClusAmpl;   //!
   TBranch        *b_MGv3_ClusSize;   //!
   TBranch        *b_MGv3_ClusPos;   //!
   TBranch        *b_MGv3_ClusMaxStripAmpl;   //!
   TBranch        *b_MGv3_ClusMaxSample;   //!
   TBranch        *b_MGv3_ClusTOT;   //!
   TBranch        *b_MGv3_ClusT;   //!
   TBranch        *b_MGv3_StripMaxAmpl;   //!
   TBranch        *b_MGv3_ClusMaxStrip;   //!

   T(TTree *tree=0);
   T(std::string filename);
   virtual ~T();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   std::vector<Point3D*> GetMuonTrack(unsigned int trackIndex);
   std::vector<Point3D *> GetMuonTrack_VetoByLowestLayer(unsigned int trackIndex);
   std::vector<unsigned short> GetVectorOfClusterSize(unsigned int trackIndex);
   std::vector<std::unique_ptr<Detector>> GetMuonTrack_V2(unsigned int trackIndex);
   bool ScatteringCandidate(const std::vector<std::unique_ptr<Detector>> &vecOfDet);
   std::vector<Point3D*> GetVectorOfPoint3D(const std::vector<std::unique_ptr<Detector>> &vecOfDet);
};

#endif

#ifdef T_cxx
T::T(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../iaea3_Pb_run04_analyse.root");
      if (!f || !f->IsOpen()) {
         //f = new TFile("../iaea1_Pb_run03_analyse.root");
         //f = new TFile("../iaea3_Pb_run02_analyse.root");
         f = new TFile("../iaea3_Pb_run04_analyse.root");
         //iaea3_Pb_run02_analyse
      }
      f->GetObject("T",tree);

   }
   Init(tree);
}

T::T(std::string filename){
   TFile *f = new TFile(filename.c_str(),"r");
   TTree *tree = (TTree*)f->Get("T");
   Init(tree);
}

T::~T()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t T::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t T::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void T::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evn", &evn, &b_evn);
   fChain->SetBranchAddress("evttime", &evttime, &b_evttime);
   fChain->SetBranchAddress("MGv3_NClus", MGv3_NClus, &b_MGv3_NClus);
   fChain->SetBranchAddress("MGv3_Spark", MGv3_Spark, &b_MGv3_Spark);
   fChain->SetBranchAddress("MGv3_ClusAmpl", MGv3_ClusAmpl, &b_MGv3_ClusAmpl);
   fChain->SetBranchAddress("MGv3_ClusSize", MGv3_ClusSize, &b_MGv3_ClusSize);
   fChain->SetBranchAddress("MGv3_ClusPos", MGv3_ClusPos, &b_MGv3_ClusPos);
   fChain->SetBranchAddress("MGv3_ClusMaxStripAmpl", MGv3_ClusMaxStripAmpl, &b_MGv3_ClusMaxStripAmpl);
   fChain->SetBranchAddress("MGv3_ClusMaxSample", MGv3_ClusMaxSample, &b_MGv3_ClusMaxSample);
   fChain->SetBranchAddress("MGv3_ClusTOT", MGv3_ClusTOT, &b_MGv3_ClusTOT);
   fChain->SetBranchAddress("MGv3_ClusT", MGv3_ClusT, &b_MGv3_ClusT);
   fChain->SetBranchAddress("MGv3_StripMaxAmpl", MGv3_StripMaxAmpl, &b_MGv3_StripMaxAmpl);
   fChain->SetBranchAddress("MGv3_ClusMaxStrip", MGv3_ClusMaxStrip, &b_MGv3_ClusMaxStrip);
   Notify();
}

Bool_t T::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void T::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t T::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef T_cxx
