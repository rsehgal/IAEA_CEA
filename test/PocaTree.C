{
  //////////////////////////////////////////////////////////
  //   This file has been automatically generated
  //     (Thu Jun 20 16:23:51 2024 by ROOT version6.30/02)
  //   from TTree PocaTree/PocaTree
  //   found on file: Poca.root
  //////////////////////////////////////////////////////////

  // Reset ROOT and connect tree file
  /*   gROOT->Reset();
     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Poca.root");
     if (!f) {
        f = new TFile("Poca.root");
     }
      f->GetObject("PocaTree",tree);
  */

  TFile *f = new TFile("Poca_full.root", "r");
  TTree *PocaTree = (TTree *)f->Get("PocaTree");
  // Declaration of leaves types
  Double_t fX;
  Double_t fY;
  Double_t fZ;
  Double_t fScattering;

  // Set branch addresses.
  // PocaTree->SetBranchAddress("Poca",&Poca);
  PocaTree->SetBranchAddress("fX", &fX);
  PocaTree->SetBranchAddress("fY", &fY);
  PocaTree->SetBranchAddress("fZ", &fZ);
  PocaTree->SetBranchAddress("fScattering", &fScattering);

  //     This is the loop skeleton
  //       To read only selected branches, Insert statements like:
  // PocaTree->SetBranchStatus("*",0);  // disable all branches
  // TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

  Long64_t nentries = PocaTree->GetEntries();

  int nbinsx = 200;
  int xlow = 0;
  int xhigh = 800;

  int nbinsy = 200;
  int ylow = 0;
  int yhigh = 800;

  int nbinsz = 50;
  int zlow = 0;
  int zhigh = 200;

      TH2F *hist2 = new TH2F("Recons2D", "Recons2D", nbinsx,xlow,xhigh,nbinsy,ylow,yhigh);
  TH3F *hist3 = new TH3F("Recons3D", "Recons3D", nbinsx, xlow, xhigh, nbinsy,
                         ylow, yhigh, nbinsz, zlow, zhigh);

  Long64_t nbytes = 0;
  unsigned int counter = 0;
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += PocaTree->GetEntry(i);
    // std::cout << fScattering << " : " << fX <<" : " << fY << std::endl;
    // if(fScattering < 0.32 || fScattering > 0.36)
    // if(fScattering > 0.2  && fScattering < 1.)
    if (fZ > 0. && fZ < 100.) {
      if (fScattering > 0.04) {
        counter++;
        hist2->Fill(fX, fY);
        hist3->Fill(fX, fY, fZ);
      }
    }
  }
  new TCanvas("Reconstruction 2D", "Reconstruction 2D");
  hist2->Draw();
  new TCanvas("Reconstruction 3D", "Reconstruction 3D");
  hist3->Draw();
      TH2F *hist2New = new TH2F("Recons2DFiltered", "Recons2DFiltered", nbinsx,xlow,xhigh,nbinsy,ylow,yhigh);
  TH3F *hist3New =
      new TH3F("Recons3DFiltered", "Recons3DFiltered", nbinsx, xlow, xhigh,
               nbinsy, ylow, yhigh, nbinsz, zlow, zhigh);

for (unsigned int i = 0; i < hist2->GetNbinsX(); i++) {
    for (unsigned int j = 0; j < hist2->GetNbinsY(); j++) {
        double binCon = hist2->GetBinContent(i, j);
        if (binCon < 5.) {
          hist2New->SetBinContent(i, j, 0.);
        } else {
          hist2New->SetBinContent(i, j, binCon);
        }
      }
    }

  for (unsigned int i = 0; i < hist3->GetNbinsX(); i++) {
    for (unsigned int j = 0; j < hist3->GetNbinsY(); j++) {
      for (unsigned int k = 0; k < hist3->GetNbinsZ(); k++) {
        double binCon = hist3->GetBinContent(i, j, k);
        if (binCon < 2.) {
          hist3New->SetBinContent(i, j, k, 0.);
        } else {
          hist3New->SetBinContent(i, j, k, binCon);
        }
      }
    }
  }
  new TCanvas("Recons2DFiltered", "Recons2DFiltered");
  hist2New->Draw();

  new TCanvas("Recons3DFiltered", "Recons3DFiltered");
  hist3New->Draw();
  std::cout << "Counter : " << counter << std::endl;
}
