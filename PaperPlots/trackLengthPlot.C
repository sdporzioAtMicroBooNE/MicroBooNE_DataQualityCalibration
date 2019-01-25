#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>

void trackLengthPlot()
{
  // OPEN FILE AND TREE
  TFile f("/uboone/data/users/sporzio/_Archived/18-09-27_XYZCalibration_Run3_Part1of2_FinalHistograms/Anatrees/anatrees_for_calibration_r13696to15500.root");
  TTree* T=nullptr;
  f.GetObject("XYZcorrection/Event",T);

  // DRAW PROJECTED TRACK LENGTH
  // Style
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas();
  c1->SetLogy();
  c1->SetGrid(1,1);
  // Dump branch to histogram
  TH1F *hist = new TH1F("hist","hist",100,0,400); 
  T->Draw("xprojectedlen>>hist");
  // Cosmetics
  hist->SetMarkerColor(2);
  hist->SetMarkerStyle(20);
  hist->SetMarkerSize(1);
  hist->SetLineColor(kRed);
  hist->SetTitle("");
  hist->GetYaxis()->SetTitle("Number of tracks");
  hist->GetXaxis()->SetTitle("X projected track length [cm]");
  hist->GetXaxis()->SetRangeUser(0,400);
  hist->GetYaxis()->SetRangeUser(1e-1,1e8);
  // Draw histogram
  hist->Draw("PE0");
  // Draw transparent box
  gPad->Update();
  TBox *tb = new TBox(250,1e-1,270,1e8);
  tb->SetFillColorAlpha(kOrange,0.5);
  tb->Draw("SAME");
  // Save canvas to file
  c1->Print("Plots/run3_projectedCosmicTrackLength.pdf");
  return;
}