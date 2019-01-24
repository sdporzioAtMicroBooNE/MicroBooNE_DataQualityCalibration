#include "TROOT.h"
#include "TRandom.h"
#include "TTree.h"
#include "TFile.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TH3F.h"
#include "TProfile2D.h"
#include "TChain.h"
#include "TStyle.h"
#include "TString.h"
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

UInt_t startRun = 4951;
UInt_t endRun = 6999;
UInt_t nRuns = endRun - startRun;
std::string inputFile = "/uboone/data/users/mrmooney/data/ConfigCheck/newesttest_data.root";

int main(){

  gROOT->Reset();
  TChain *treed = new TChain("analysistree/anatree");
  TH2F* sumHitAmpHist = new TH2F("sumHitAmpHist",";Channel Number; Run Number", 8256,-0.5,8255.5,nRuns,startRun-0.5,endRun-0.5);
  TH2F* numHitAmpHist = new TH2F("numHitAmpHist",";Channel Number; Run Number", 8256,-0.5,8255.5,nRuns,startRun-0.5,endRun-0.5);
  TH2F* avgHitAmpHist = new TH2F("avgHitAmpHist",";Channel Number; Run Number", 8256,-0.5,8255.5,nRuns,startRun-0.5,endRun-0.5);
  TH2F* ASICavgHitAmpHist = new TH2F("ASICavgHitAmpHist",";Channel Number; Run Number", 1032,-0.5,8255.5,nRuns,startRun-0.5,endRun-0.5);

  UInt_t run = 0;
  UInt_t no_hits = 0;
  Short_t hit_channel[1000000] = {0};
  Float_t hit_ph[1000000] = {0};

  TString filename;
  filename.Form(inputFile.c_str());

  std::cout << "Filename: " << filename << std::endl;
  treed->Add(filename);
  treed->SetBranchStatus("*",0);
  treed->SetBranchAddress("no_hits",&no_hits);
  treed->SetBranchStatus("no_hits", kTRUE);
  treed->SetBranchAddress("hit_channel",hit_channel);
  treed->SetBranchStatus("hit_channel", kTRUE);
  treed->SetBranchAddress("hit_ph",hit_ph);
  treed->SetBranchStatus("hit_ph", kTRUE);
  treed->SetBranchAddress("run",&run);
  treed->SetBranchStatus("run", kTRUE);

  // Fill sum and num histograms
  int Size = treed->GetEntries();
  for(Int_t i=0; i<Size; i++){
    treed->GetEntry(i);
    if(i % 500 == 0){ std::cout << "entry " << i << " out of " << Size << std::endl; }

    if((run < startRun) || (run > endRun)) continue;

    for(UInt_t j=0; j<no_hits; j++)
    {
      sumHitAmpHist->Fill((float)hit_channel[j],(float)run,(float)hit_ph[j]);
      numHitAmpHist->Fill((float)hit_channel[j],(float)run,1.0);      
    }
  }

  // Calculate averages
  for(UInt_t k = 0; k < nRuns; k++) {
    for(int h = 0; h < 8256; h++) {
      if (numHitAmpHist->GetBinContent(h+1,k+1) > 0.0) {
        std::cout << numHitAmpHist->GetBinContent(h+1,k+1) << std::endl;
        avgHitAmpHist->SetBinContent(h+1,k+1,sumHitAmpHist->GetBinContent(h+1,k+1)/numHitAmpHist->GetBinContent(h+1,k+1));
      }
      else {
        avgHitAmpHist->SetBinContent(h+1,k+1,0.0);
      }
    }
  }

  // Calculate ASIC averages
  for(UInt_t k = 0; k < nRuns; k++) {
    double num = 0.0;
    double sum = 0.0;
    int counter = 1;
    for(int h = 0; h < 8256; h++) {
      if (avgHitAmpHist->GetBinContent(h+1,k+1) > 0.0) {
        sum += avgHitAmpHist->GetBinContent(h+1,k+1);
        num += 1.0;
      }

      if ((h+1) % 8 == 0) {
        if (num > 0.0) {
          ASICavgHitAmpHist->SetBinContent(counter,k+1,sum/num);
        }
        else {
          ASICavgHitAmpHist->SetBinContent(counter,k+1,0.0);
        }

        num = 0.0;
        sum = 0.0;
        counter++;
      }
    }
  }

  TString outputname;
  outputname.Form("./output.root");
  TFile *fout = new TFile(outputname,"RECREATE");
  sumHitAmpHist->SetDirectory(fout);
  numHitAmpHist->SetDirectory(fout);
  avgHitAmpHist->SetDirectory(fout);
  ASICavgHitAmpHist->SetDirectory(fout);

  std::cout << "Writing: " << outputname << std::endl;

  fout->Write();
  fout->Close();
}
