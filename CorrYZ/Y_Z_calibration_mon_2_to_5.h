//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Feb  6 17:16:44 2018 by ROOT version 5.34/32
// from TTree Event/Event Tree from Reco
// found on file: /uboone/data/users/vmeddage/final_run_1_calibration.root
//////////////////////////////////////////////////////////

#ifndef Y_Z_calibration_mon_2_to_5_h
#define Y_Z_calibration_mon_2_to_5_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Y_Z_calibration_mon_2_to_5 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           event;
   Double_t        evttime;
   Int_t           run;
   Int_t           subrun;
   Int_t           year_month_date;
   Int_t           hour_min_sec;
   Int_t           cross_trks;
   Int_t           all_trks;
   Float_t         xprojectedlen[615];   //[all_trks]
   Float_t         trackthetaxz[3];   //[cross_trks]
   Float_t         trackthetayz[3];   //[cross_trks]
   Int_t           TrkID[3];   //[cross_trks]
   Float_t         trkstartcosxyz[3][3];   //[cross_trks]
   Float_t         trkendcosxyz[3][3];   //[cross_trks]
   Int_t           ntrkhits[3][3];   //[cross_trks]
   Float_t         trkdqdx[3][3][3000];   //[cross_trks]
   Float_t         trkdedx[3][3][3000];   //[cross_trks]
   Float_t         trkresrange[3][3][3000];   //[cross_trks]
   Float_t         trkhitx[3][3][3000];   //[cross_trks]
   Float_t         trkhity[3][3][3000];   //[cross_trks]
   Float_t         trkhitz[3][3][3000];   //[cross_trks]

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_evttime;   //!
   TBranch        *b_run;   //!
   TBranch        *b_surbrun;   //!
   TBranch        *b_year_month_date;   //!
   TBranch        *b_hour_min_sec;   //!
   TBranch        *b_cross_trks;   //!
   TBranch        *b_all_trks;   //!
   TBranch        *b_xprojectedlen;   //!
   TBranch        *b_trackthetaxz;   //!
   TBranch        *b_trackthetayz;   //!
   TBranch        *b_TrkID;   //!
   TBranch        *b_trkstartcosxyz;   //!
   TBranch        *b_trkendcosxyz;   //!
   TBranch        *b_ntrkhits;   //!
   TBranch        *b_trkdqdx;   //!
   TBranch        *b_trkdedx;   //!
   TBranch        *b_trkresrange;   //!
   TBranch        *b_trkhitx;   //!
   TBranch        *b_trkhity;   //!
   TBranch        *b_trkhitz;   //!

   Y_Z_calibration_mon_2_to_5(TTree *tree=0);
   virtual ~Y_Z_calibration_mon_2_to_5();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Y_Z_calibration_mon_2_to_5_cxx
Y_Z_calibration_mon_2_to_5::Y_Z_calibration_mon_2_to_5(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/uboone/data/users/sporzio/Calibration/InputFiles/mergedXyzCorrections.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/uboone/data/users/sporzio/Calibration/InputFiles/mergedXyzCorrections.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/uboone/data/users/sporzio/Calibration/InputFiles/mergedXyzCorrections.root:/XYZcorrection");
      dir->GetObject("Event",tree);

   }
   Init(tree);
}

Y_Z_calibration_mon_2_to_5::~Y_Z_calibration_mon_2_to_5()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Y_Z_calibration_mon_2_to_5::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Y_Z_calibration_mon_2_to_5::LoadTree(Long64_t entry)
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

void Y_Z_calibration_mon_2_to_5::Init(TTree *tree)
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

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("evttime", &evttime, &b_evttime);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("subrun", &subrun, &b_surbrun);
   fChain->SetBranchAddress("year_month_date", &year_month_date, &b_year_month_date);
   fChain->SetBranchAddress("hour_min_sec", &hour_min_sec, &b_hour_min_sec);
   fChain->SetBranchAddress("cross_trks", &cross_trks, &b_cross_trks);
   fChain->SetBranchAddress("all_trks", &all_trks, &b_all_trks);
   fChain->SetBranchAddress("xprojectedlen", xprojectedlen, &b_xprojectedlen);
   fChain->SetBranchAddress("trackthetaxz", trackthetaxz, &b_trackthetaxz);
   fChain->SetBranchAddress("trackthetayz", trackthetayz, &b_trackthetayz);
   fChain->SetBranchAddress("TrkID", TrkID, &b_TrkID);
   fChain->SetBranchAddress("trkstartcosxyz", trkstartcosxyz, &b_trkstartcosxyz);
   fChain->SetBranchAddress("trkendcosxyz", trkendcosxyz, &b_trkendcosxyz);
   fChain->SetBranchAddress("ntrkhits", ntrkhits, &b_ntrkhits);
   fChain->SetBranchAddress("trkdqdx", trkdqdx, &b_trkdqdx);
   fChain->SetBranchAddress("trkdedx", trkdedx, &b_trkdedx);
   fChain->SetBranchAddress("trkresrange", trkresrange, &b_trkresrange);
   fChain->SetBranchAddress("trkhitx", trkhitx, &b_trkhitx);
   fChain->SetBranchAddress("trkhity", trkhity, &b_trkhity);
   fChain->SetBranchAddress("trkhitz", trkhitz, &b_trkhitz);
   Notify();
}

Bool_t Y_Z_calibration_mon_2_to_5::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Y_Z_calibration_mon_2_to_5::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Y_Z_calibration_mon_2_to_5::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Y_Z_calibration_mon_2_to_5_cxx
