/*
**	Filename : Test_ClusterSize.cpp
**	2024-06-25
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
#include <string>
#include <TLegend.h>
int main(int argc, char *argv[])
{
    TApplication *fApp = new TApplication("fApp", NULL, NULL);

    T t(argv[1]);
    std::vector<TH1F *> vecOfClusSizeHist;
    for (unsigned short i = 0; i < 8; i++)
    {
        std::string histName = "Cluster_Size" + std::to_string(i);
        vecOfClusSizeHist.push_back(new TH1F(histName.c_str(), histName.c_str(), 100, 0, 100));
    }

    unsigned long int nentries = t.fChain->GetEntries();
    unsigned int numOfEvents = std::atoi(argv[2]);
    if (numOfEvents > 0)
        nentries = numOfEvents;
    for (unsigned int i = 0; i < nentries; i++)
    {
        std::vector<unsigned short> vecOfClusterSize = t.GetVectorOfClusterSize(i);
        for (unsigned short j = 0; j < vecOfClusterSize.size(); j++)
        {
            vecOfClusSizeHist[j]->Fill(vecOfClusterSize[j]);
        }
    }

    for (unsigned short j = 0; j < 8; j++)
    {
        if (j % 2)
        {
            vecOfClusSizeHist[j]->SetLineColor(1);
            vecOfClusSizeHist[j]->SetTitle("X_Plane");
        }
        else
        {
            vecOfClusSizeHist[j]->SetLineColor(2);
            vecOfClusSizeHist[j]->SetTitle("Y_Plane");
        }

        vecOfClusSizeHist[j]->SetLineWidth(2);
        vecOfClusSizeHist[j]->GetXaxis()->SetTitle("Cluster Size");
        vecOfClusSizeHist[j]->GetXaxis()->SetTitleSize(0.06);
        vecOfClusSizeHist[j]->GetXaxis()->SetLabelSize(0.06);

        vecOfClusSizeHist[j]->GetYaxis()->SetTitle("Count");
        vecOfClusSizeHist[j]->GetYaxis()->SetTitleSize(0.06);
        vecOfClusSizeHist[j]->GetYaxis()->SetLabelSize(0.06);
    }

    TCanvas *canClusterSize = new TCanvas("ClusterSize", "ClusterSize");
    canClusterSize->Divide(2, 2);

    TLegend *legend = new TLegend(0.1, 0.7, 0.3, 0.9); // Position (x1, y1, x2, y2)
    // legend->SetHeader("Legend Title", "C"); // Option "C" allows centering header
    legend->AddEntry(vecOfClusSizeHist[0], "X Plane", "l");
    legend->AddEntry(vecOfClusSizeHist[1], "Y Plane", "l");

    for (unsigned short j = 0; j < 8; j++)
    {
        unsigned short detectorIndex = j / 2;
        canClusterSize->cd(detectorIndex + 1);
        vecOfClusSizeHist[j]->Draw("histsames");
        legend->Draw("same");
    }

    fApp->Run();
}