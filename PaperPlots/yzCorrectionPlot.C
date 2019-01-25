#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void yzCorrectionPlot()
{
  // OPEN FILE AND TREE
  TFile f("/uboone/app/users/sporzio/CalibrationXYZ/Output/YZ/correctionFactors_YZ_plane2_part2.root");
  TH2F *hist = (TH2F*)f.Get("error_dq_dx_z_vs_y_hist");

  // DRAW PROJECTED TRACK LENGTH
  // Style
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas();
  c1->SetGrid(1,1);
  gStyle->SetPalette(55);
  gStyle->SetTitleFont(22),"t";
  hist->SetLabelFont(22,"xyz");// roman font for axis labels 
  hist->SetTitleFont(22,"xyz");// roman font for axis titles 
  // Cosmetics
  hist->SetContour(1000);
  hist->GetZaxis()->SetRangeUser(0,3.5);
  hist->SetTitle("Collection Plane");
  hist->GetYaxis()->SetTitle("Y Coordinate (cm)");
  hist->GetXaxis()->SetTitle("Z Coordinate (cm)");
  gPad->SetTicks();
  // Draw histogram
  hist->Draw("COLZ");
  // Save canvas to file
  c1->Print("Plots/run3_dqdxCorrection_yz.pdf");
  return;
}