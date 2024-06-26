void PocaTree(char *filename)
{
  // TFile *f = new TFile("Poca_full.root", "r");
  TFile *f = new TFile(filename, "r");
  TTree *PocaTree = (TTree *)f->Get("PocaTree");
  // Declaration of leaves types
  Double_t fX;
  Double_t fY;
  Double_t fZ;
  Double_t fScattering;
  gStyle->SetPalette(kRainBow);

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
  int zhigh = 300;

  TH2F *hist2 = new TH2F("Recons2D", "Recons2D", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);
  TH2F *hist2YZ = new TH2F("Recons2D_YZ", "Recons2D_YZ", nbinsy, ylow, yhigh, nbinsz, zlow, zhigh);
  TH2F *hist2XZ = new TH2F("Recons2D_XZ", "Recons2D_XZ", nbinsx, xlow, xhigh, nbinsz, zlow, zhigh);
  TH3F *hist3 = new TH3F("Recons3D", "Recons3D", nbinsx, xlow, xhigh, nbinsy,
                         ylow, yhigh, nbinsz, zlow, zhigh);

  Long64_t nbytes = 0;
  unsigned int counter = 0;
  for (Long64_t i = 0; i < nentries; i++)
  {
    nbytes += PocaTree->GetEntry(i);
    // std::cout << fScattering << " : " << fX <<" : " << fY << std::endl;
    // if(fScattering < 0.32 || fScattering > 0.36)
    // if(fScattering > 0.2  && fScattering < 1.)
    if (fZ > 0. && fZ < 250.)
    {
      if (fScattering > 0.04)
      {
        counter++;
        hist2->Fill(fX, fY);
        hist2YZ->Fill(fY, fZ);
        hist2XZ->Fill(fX, fZ);
        hist3->Fill(fX, fY, fZ);
      }
    }
  }
  new TCanvas("Reconstruction 2D", "Reconstruction 2D");
  hist2->Draw();
  new TCanvas("Reconstruction 2D YZ", "Reconstruction 2D YZ");
  hist2YZ->Draw();
  new TCanvas("Reconstruction 2D XZ", "Reconstruction 2D XZ");
  hist2XZ->Draw();

  new TCanvas("Reconstruction 3D", "Reconstruction 3D");
  hist3->Draw();
  TH2F *hist2New = new TH2F("Recons2DFiltered", "Recons2DFiltered", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);
  TH3F *hist3New =
      new TH3F("Recons3DFiltered", "Recons3DFiltered", nbinsx, xlow, xhigh,
               nbinsy, ylow, yhigh, nbinsz, zlow, zhigh);

  for (unsigned int i = 0; i < hist2->GetNbinsX(); i++)
  {
    for (unsigned int j = 0; j < hist2->GetNbinsY(); j++)
    {
      double binCon = hist2->GetBinContent(i, j);
      if (binCon < 5.)
      {
        hist2New->SetBinContent(i, j, 0.);
      }
      else
      {
        hist2New->SetBinContent(i, j, binCon);
      }
    }
  }

  for (unsigned int i = 0; i < hist3->GetNbinsX(); i++)
  {
    for (unsigned int j = 0; j < hist3->GetNbinsY(); j++)
    {
      for (unsigned int k = 0; k < hist3->GetNbinsZ(); k++)
      {
        double binCon = hist3->GetBinContent(i, j, k);
        if (binCon < 5.)
        {
          hist3New->SetBinContent(i, j, k, 0.);
        }
        else
        {
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
