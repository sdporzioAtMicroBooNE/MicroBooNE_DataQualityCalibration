#include "TROOT.h"
#include "TRandom.h"
#include "TTree.h"
#include "TFile.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TH1D.h"
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

UInt_t startRun = 16000;
UInt_t endRun = 17055; //16115

//UInt_t nRuns = endRun = startRun;
UInt_t nRuns = endRun - startRun;


UInt_t startChannel = 0; //must be multiples of 8
UInt_t endChannel = 8256; //8256 4303
UInt_t nChannels = endChannel - startChannel;
UInt_t ASIC_nbins = nChannels/8;

std::string inputFile = "/uboone/data/users/ogoodwin/ASICtree_run3p2.root";

int main(){
  std::cout<<nRuns<<std::endl;
  gROOT->Reset();
  TChain *treed = new TChain("analysistree/anatree");
  TH1F* hitAmpHist = new TH1F("HitAmpHist","HitAmpHist",100,0,3000);
  
  TH2F* sumHitAmpHist = new TH2F("sumHitAmpHist",";Channel Number; Run Number", nChannels,startChannel-0.5,endChannel-0.5,nRuns,startRun-0.5,endRun-0.5);
  TH2F* numHitAmpHist = new TH2F("numHitAmpHist",";Channel Number; Run Number", nChannels,startChannel-0.5,endChannel-0.5,nRuns,startRun-0.5,endRun-0.5);
  TH2F* avgHitAmpHist = new TH2F("avgHitAmpHist",";Channel Number; Run Number", nChannels,startChannel-0.5,endChannel-0.5,nRuns,startRun-0.5,endRun-0.5);
  TH2F* ASICavgHitAmpHist = new TH2F("ASICavgHitAmpHist",";Channel Number; Run Number", ASIC_nbins,startChannel-0.5,endChannel-0.5,nRuns,startRun-0.5,endRun-0.5);
  TH2F* ASICavgHitAmpHist_ord = new TH2F("ASICavgHitAmpHist_ord",";Channel Number; Run Number", ASIC_nbins,0,ASIC_nbins/2,nRuns,startRun-0.5,endRun-0.5);
  //TH1F* ASICavgHitAmpHist_runave = new TH1F("ASICavgHitAmpHist_runave ","Channel Number",ASIC_nbins,startChannel-0.5,endChannel-0.5);
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



  TFile *f = TFile::Open("20150818_uBooneChanMap.root");
  TTree *t1 = (TTree*)f->Get("ubooneChanMap");
 
  Short_t larch;
  Short_t asic;
  Int_t nentries;
  t1->SetBranchAddress("larch",&larch);
  t1->SetBranchAddress("asic",&asic);
  nentries= t1 ->GetEntries();
  for (Int_t i=0; i<nentries; i++) {
    t1->GetEntry(i);
      //cout<<larch<<endl;
   }




  // Fill sum and num histograms
  int Size = treed->GetEntries();
  for(Int_t i=0; i<Size; i++){
    treed->GetEntry(i);
    if(i % 500 == 0){ std::cout << "entry " << i << " out of " << Size << std::endl; }

    if((run < startRun) || (run > endRun)) continue;

    for(UInt_t j=0; j<no_hits; j++)
    {
      if (hit_ph[j]>10000){
        cout<<"hit_value"<<hit_ph[j]<<endl;
        cout<<"hit channel"<<hit_channel[j]<<endl;
        //cout<<"run"<<(float)run<endl;

      }
      else{ //only fill reasonable hits
      sumHitAmpHist->Fill((float)hit_channel[j],(float)run,(float)hit_ph[j]);
      numHitAmpHist->Fill((float)hit_channel[j],(float)run,1.0); 
      hitAmpHist->Fill((float)hit_ph[j]);
      }     
    }
  }

  // Calculate averages
  for(UInt_t k = 0; k < nRuns; k++) {
    for(UInt_t h = 0; h < nChannels; h++) {
      if (numHitAmpHist->GetBinContent(h+1,k+1) > 0.0  && sumHitAmpHist->GetBinContent(h+1,k+1)/numHitAmpHist->GetBinContent(h+1,k+1)>0){

        avgHitAmpHist->SetBinContent(h+1,k+1,sumHitAmpHist->GetBinContent(h+1,k+1)/numHitAmpHist->GetBinContent(h+1,k+1));

       
        // if(avgHitAmpHist->GetBinContent(h+1,k+1)>1000){
        //   //std::cout<<sumHitAmpHist->GetBinContent(h+1,k+1)<<std::endl;
        //   //std::cout<<"run="<<h<<"Channel="<<k<<"avgHitAmpHist="<<avgHitAmpHist->GetBinContent(h+1,k+1)<<"numHits="<<numHitAmpHist->GetBinContent(h+1,k+1)<<std::endl;
        // }

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
    for(UInt_t h = 0; h < nChannels; h++) { //8256
      if (avgHitAmpHist->GetBinContent(h+1,k+1) > 0.0) {
        sum += avgHitAmpHist->GetBinContent(h+1,k+1);
        num += 1.0;
	       
      }

      if ((h+1) % 8 == 0) {
        if (num > 0.0 ) {
          t1->GetEntry(h+1);
          if (sum/num>10000){
            cout<<"high value"<<endl;
            cout<<"sum/num= "<<sum/num<<endl;
            cout<<"sum="<<sum;
            cout<<"num="<<num;
            cout<<"counter= (x)"<<counter<<endl;
            cout<<"k+1 (y)="<<k+1<<endl;
            //removing high hits has sorted this
          }
          ASICavgHitAmpHist->SetBinContent(counter,k+1,sum/num);
          if (ASICavgHitAmpHist_ord->GetBinContent(asic*2,k+1,sum/num)==0){
            //cout<<"unfilled"<<endl;
            ASICavgHitAmpHist_ord->SetBinContent(asic*2,k+1,sum/num);
          }
          else{
            //cout<<"filled"<<endl;
            ASICavgHitAmpHist_ord->SetBinContent((asic*2)+1,k+1,sum/num);
          }
          
          
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
  //TProfile  *Prof=ASICavgHitAmpHist->ProfileX();
  TH1D *ASICavgHitAmpHist_runave = ASICavgHitAmpHist->ProjectionX();
  TH1D *ASICavgHitAmpHist__ord_runave = ASICavgHitAmpHist_ord->ProjectionX();
  cout << nRuns << endl;
  float a = 1;
  float scale=a/float(nRuns);
  cout<<scale<<endl;
  ASICavgHitAmpHist_runave->Scale(scale);
  ASICavgHitAmpHist__ord_runave->Scale(scale);
  TString outputname;
  outputname.Form("./output_run3p2_16000_onwards.root");

  TFile *fout = new TFile(outputname,"RECREATE");
  sumHitAmpHist->SetDirectory(fout);
  numHitAmpHist->SetDirectory(fout);
  avgHitAmpHist->SetDirectory(fout);
  ASICavgHitAmpHist->SetDirectory(fout);
  hitAmpHist->SetDirectory(fout);
  ASICavgHitAmpHist_ord->SetDirectory(fout);
  ASICavgHitAmpHist__ord_runave->SetDirectory(fout);
  ASICavgHitAmpHist_runave->SetDirectory(fout);
  sumHitAmpHist->SaveAs("sumHitAmpHist.pdf");
  numHitAmpHist->SaveAs("numHitAmpHist.pdf");
  avgHitAmpHist->SaveAs("avgHitAmpHist.pdf");
  ASICavgHitAmpHist->SaveAs("ASICavgHitAmpHist.pdf");



  std::cout << "Writing: " << outputname << std::endl;

  fout->Write();
  fout->Close();
}
