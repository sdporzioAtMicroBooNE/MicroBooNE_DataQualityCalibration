#define X_calibration_cxx
#include "X_calibration.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TStyle.h>
#include <iostream>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <math.h> 
#include <string>
#include <TImage.h>
#include <iomanip>

void X_calibration::Loop()
{
  std::cout << "///////////////////////////////////// Generating X correction histogrmas for different dates and all planes ///////////////////////////////////" << std::endl;
  ifstream infile2;
  infile2.open("/uboone/app/users/sporzio/Calibration/Input_GoodRunsList/good_runs_run3_both.txt");
  std::vector<int> good_run_vec;
  int good_runs;
  infile2>>good_runs;
  while(good_runs!=-1)
  {
   good_run_vec.push_back(good_runs);
   infile2>>good_runs;
  }
  infile2.close();
  const double x_bin_size=10.0; 
  const double y_bin_size=5.0; 
  const double z_bin_size=5.0; 
  std::vector<int> month_vector;
  ofstream outfile;
  outfile.open("/uboone/app/users/sporzio/Calibration/Output/external_onBeamData_crossNumbers.txt");
  // for(int i=1; i<5; i++) month_vector.push_back(i);
  month_vector.push_back(10);
  month_vector.push_back(11);
  month_vector.push_back(12);
  month_vector.push_back(1);
  month_vector.push_back(2);
  month_vector.push_back(3);
  for(int i=0; i<month_vector.size(); i++){
    std::cout  << "********** MONTH : " << month_vector[i] << " ******************" << std::endl;
    outfile<<month_vector[i]<<"/";
    ifstream infile;
    infile.open(Form("/uboone/app/users/sporzio/Calibration/Input_GoodRunsList/DaysInMonths/dates_of_month_%d.txt",month_vector[i]));
    int my_date;
    infile>>my_date;
    while(my_date!=-1)
    {
      std::cout << "Date : " << my_date << std::endl;
      outfile<<my_date<<" : ";
      for(int plane_number=0; plane_number<3; plane_number++)
      {
        std::cout << "  Plane : " << plane_number << std::endl;
        TFile my_file_1(Form("/uboone/app/users/sporzio/Calibration/Output/YZ/correctionFactors_YZ_plane%d_part1.root",plane_number));
        TFile my_file_2(Form("/uboone/app/users/sporzio/Calibration/Output/YZ/correctionFactors_YZ_plane%d_part2.root",plane_number));
        TH2F *part1_month_hist = (TH2F*)my_file_1.Get("error_dq_dx_z_vs_y_hist");
        TH2F *part2_month_hist = (TH2F*)my_file_2.Get("error_dq_dx_z_vs_y_hist");
        TFile* x_file=new TFile(Form("/uboone/app/users/sporzio/Calibration/Output/X/correctionFactors_X_%d_%d_plane_%d.root",month_vector[i],my_date,plane_number),"recreate");

        TH1F *dq_dx_x_hist = new TH1F("dq_dx_x_hist",Form("plane_%d",plane_number),26,0,260);
        dq_dx_x_hist->GetXaxis()->SetTitle("X Coordinate(cm)");
        dq_dx_x_hist->SetStats(0);

        TH1F *dq_dx_x_error_hist = new TH1F("dq_dx_x_error_hist",Form("plane_%d",plane_number),26,0,260);
        dq_dx_x_error_hist->GetXaxis()->SetTitle("X Coordinate (cm)");
        dq_dx_x_error_hist->SetStats(0);

        TH1F *corrected_dq_dx_x_hist = new TH1F("corrected_dq_dx_x_hist",Form("plane_%d",plane_number),26,0,260);
        corrected_dq_dx_x_hist->GetXaxis()->SetTitle("X Coordinate (cm)");
        corrected_dq_dx_x_hist->SetStats(0);

        float upper_angle;
        float lower_angle;
        if(plane_number==2){ upper_angle=1.745; lower_angle=1.396; }
        if(plane_number==1){ upper_angle=0.873;lower_angle=0.175; }
        if(plane_number==0){ upper_angle=2.792;lower_angle=2.007; }

        vector<vector<float>> dq_dx_value;
        vector<float> all_dq_dx_value;
        vector<vector<float>> dq_dx_frac_error;
        dq_dx_value.resize(26);
        dq_dx_frac_error.resize(26);
        int ang_cross=0;
        if(fChain == 0) return;
        Long64_t nentries = fChain->GetEntriesFast();
        Long64_t nbytes = 0, nb = 0;
        for(Long64_t jentry=0; jentry<nentries;jentry++)
        {
          Long64_t ientry = LoadTree(jentry);
          if (ientry < 0) break;
          nb=fChain->GetEntry(jentry);   nbytes += nb;

          bool run_good=false;
          for(int i_1=0; i_1<good_run_vec.size(); i_1++)
          {
            if(run==good_run_vec[i_1])
            {
              run_good=true;
              break;
            } 
          }
          if(run_good==false) continue;

          int year=year_month_date/10000;
          int month_date=year_month_date%10000;
          int month=month_date/100;
          int date=month_date%100;

          // std::cout << month << "-" << month_vector[i] << "   " << date << "-" << my_date << std::endl;

          if(int(month)==int(month_vector[i]) && int(date)==int(my_date))
          {
            // std::cout << "here 2 ok" << std::endl;
            for(int k=0; k<cross_trks; ++k)
            {
            // std::cout << "doing something with " << k << std::endl;
            if(!((TMath::Abs(trackthetaxz[k])>1.31) && (TMath::Abs(trackthetaxz[k])<1.83))){
            if(!((TMath::Abs(trackthetayz[k])<upper_angle) && (TMath::Abs(trackthetayz[k])>lower_angle))){
            ang_cross++;
            for(int j=0; j<TMath::Min(ntrkhits[k][plane_number],3000); ++j){
            if((trkhitx[k][plane_number][j]<260)&&(trkhitx[k][plane_number][j]>0)){
            if((trkhity[k][plane_number][j]<120)&&(trkhity[k][plane_number][j]>-120)){
            if((trkhitz[k][plane_number][j]<1040)&&(trkhitz[k][plane_number][j]>0)){
            int z_bin=int(trkhitz[k][plane_number][j])/z_bin_size; 
            int x_bin=int(trkhitx[k][plane_number][j])/x_bin_size;
            int y_bin;
            if(trkhity[k][plane_number][j]<0) y_bin=int(trkhity[k][plane_number][j])/y_bin_size+23;
            if(trkhity[k][plane_number][j]>=0) y_bin=int(trkhity[k][plane_number][j])/y_bin_size+24;
            float yz_correction_factor;
            if(month==10 || month==11 || month==12) yz_correction_factor=part1_month_hist->GetBinContent(z_bin+1,y_bin+1);
            if(month==1 || month==2 || month==3 || month==4) yz_correction_factor=part2_month_hist->GetBinContent(z_bin+1,y_bin+1);
            float corrected_dq_dx=trkdqdx[k][plane_number][j]*yz_correction_factor;
            if(corrected_dq_dx!=0) dq_dx_value[x_bin].push_back(corrected_dq_dx);
            } // z coordinate
            } // y coordinate
            } // x coordinate
            } // loop over hits
            } // yz angle cut
            } // xz angle cut
            } // loop over crossing  tracks
            } // getting year/month/date
            } // loop over jentries

            outfile<<ang_cross << "  ";
            for(int i=0; i<dq_dx_value.size(); i++){
            if(dq_dx_value[i].size()>5){
            for(int k=0; k<dq_dx_value[i].size(); k++){
            all_dq_dx_value.push_back(dq_dx_value[i][k]);
            }
            float local_median_dq_dx=TMath::Median(dq_dx_value[i].size(),&dq_dx_value[i][0]);
            dq_dx_x_hist->SetBinContent(i+1,local_median_dq_dx);
            }
            }

            float global_median_dq_dx=TMath::Median(all_dq_dx_value.size(),&all_dq_dx_value[0]); 

            for(int i=0; i<dq_dx_value.size(); i++){
            if(dq_dx_value[i].size()>5){
            float local_median_dq_dx=TMath::Median(dq_dx_value[i].size(),&dq_dx_value[i][0]);
            float fractional_dq_dx=float(global_median_dq_dx)/local_median_dq_dx;
            dq_dx_x_error_hist->SetBinContent(i+1,fractional_dq_dx);
            dq_dx_frac_error[i].push_back(fractional_dq_dx);
            }
            }

            for(int i=0; i<dq_dx_value.size(); i++){
            if(dq_dx_value[i].size()>5){
            float local_median_dq_dx=TMath::Median(dq_dx_value[i].size(),&dq_dx_value[i][0]);
            float corrected_dq_dx=local_median_dq_dx*dq_dx_frac_error[i][0];
            corrected_dq_dx_x_hist->SetBinContent(i+1,corrected_dq_dx);
          }
        } // Loop over entries
        dq_dx_x_hist->Write();
        dq_dx_x_error_hist->Write();
        corrected_dq_dx_x_hist->Write();
        x_file->Write();
        x_file->Close();
      } // loop over plane numbers
      infile>>my_date;
      outfile<<std::endl;
    } // while loop for dates
  } // loop over months
  std::cout << "//////////////////////////////////// Done with generating all the x correction histograms /////////////////////////////////////" << std::endl;
}

