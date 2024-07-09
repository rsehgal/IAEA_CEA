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
    T t(argv[1]);
    /*unsigned int evNo = std::atoi(argv[2]);
    std::vector<std::unique_ptr<Detector>> vecOfDet = t.GetMuonTrack_V2(evNo);
    for (unsigned int i = 0; i < vecOfDet.size(); i++)
    {
        std::cout << "===============================================" << std::endl;
        vecOfDet[i]->Print();
    }
    */
    unsigned long int nentries = t.fChain->GetEntries();
    //std::vector<std::unique_ptr<Detector>> vecOfDet;
    for (unsigned int evNo = 0; evNo < nentries; evNo++)
    {
       std::vector<std::unique_ptr<Detector>> vecOfDet = t.GetMuonTrack_V2(evNo);
        if (t.ScatteringCandidate(vecOfDet))
        {
            for (unsigned int i = 0; i < vecOfDet.size(); i++)
            {
                std::cout << "===============================================" << std::endl;
                vecOfDet[i]->Print();
            }
            break;
        }
        vecOfDet.clear();
    }

    return 0;
}
