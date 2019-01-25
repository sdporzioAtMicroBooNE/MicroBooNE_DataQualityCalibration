#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>


void dqdxTimeCorrectionPlot()
{
  // OPEN FILE
  ifstream inFile;
  inFile.open("/uboone/app/users/sporzio/CalibrationXYZ/Output/T/dqdx_correction.txt");
  std::vector<std::string> date;
  std::vector<float> median;
  std::vector<float> index;
  // GET DATA
  std::string _line;
  while(getline(inFile, _line))
  {
    stringstream _ss(_line);
    std::string _index, _date, _median;
    getline(_ss,_index,',');
    getline(_ss,_date,',');
    getline(_ss,_median,',');
    index.push_back(std::stof(_index));
    date.push_back(_date);
    median.push_back(std::stof(_median));
  }

  // MAKE PLOT
  // Style
  gStyle->SetOptStat(0);
  // gROOT->SetStyle("Default");
  gStyle->SetTextFont(7);
  gStyle->SetLabelFont(22,"xyz");// roman font for axis labels 
  // gStyle->SetLabelSize(0.04,"xyz");// size of axis labels (rel. to pad size) 
  gStyle->SetTitleFont(22,"xyz");// roman font for axis titles 
  gStyle->SetTitleSize(0.045,"xyz");// size of axis titles 
  TCanvas *c1 = new TCanvas("c1","c1",900,600);
  c1->SetGrid(1,1);
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(12);
  // Dump branch to histogram
  TGraph *tg = new TGraph(index.size(),&index[0],&median[0]);
  // Cosmetics
  tg->SetMarkerColor(1);
  tg->SetMarkerStyle(20);
  tg->SetMarkerSize(0.75);
  tg->SetTitle("");
  tg->GetYaxis()->SetTitle("Time-Dependent Correction");
  tg->GetXaxis()->SetTitle("Day");
  tg->GetXaxis()->SetRangeUser(0,140);
  tg->GetYaxis()->SetRangeUser(0.8,1.2);
  gPad->SetTicks();
  // Draw histogram
  tg->Draw("AP");
  // Draw line
  TLine *line = new TLine(0,1,140,1);
  line->SetLineColor(kRed);
  line->SetLineStyle(7);
  line->SetLineWidth(3);
  // line->Draw("SAME");
  // Save canvas to file
  c1->Print("Plots/run3_dqdxCorrection_time.pdf");

  return;
}