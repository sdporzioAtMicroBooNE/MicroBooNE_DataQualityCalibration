#define Global_median_with_XYZ_corrections_cxx
#include "Global_median_with_XYZ_corrections.h"
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
using namespace std;

void Global_median_with_XYZ_corrections::Loop()
{
 std::cout << "*************************** Starting to calculate global median dQ/dx values for each day ***********************************" << std::endl;
 const double x_bin_size=10.0; 
 const double y_bin_size=5.0; 
 const double z_bin_size=5.0; 
 ifstream infile3;
 infile3.open("../GoodRunsList/goodRuns_Run3.txt");
 std::vector<int> good_run_vec;
 int good_runs;
 infile3>>good_runs;
 while(good_runs!=-1){
       good_run_vec.push_back(good_runs);
       infile3>>good_runs;
 }
 infile3.close();
 std::vector<int> month_vector;
 ifstream infile2;
 infile2.open("second_crossing_tracks_with_angcut.txt");
 std::string string_1,string_2;
 int p0,p1,p2;
 for(int i=4; i<11; i++) month_vector.push_back(i);
 ofstream outfile;
 outfile.open("second_global_dqdx_all_planes.txt");
 for(int i=0; i<month_vector.size(); i++){
     std::cout << "********************* MONTH : " << month_vector[i] << " ************************" << std::endl;
     ifstream infile;
     infile.open(Form("dates_of_month_%d.txt",month_vector[i]));
     int my_date;
     infile>>my_date;
     while(my_date!=-1){
           infile2>>string_1>>string_2>>p0>>p1>>p2;
	   outfile<<month_vector[i]<<"/"<<my_date<<" : ";
	   std::cout << "********** DATE : " << my_date << std::endl;
	   if(p0>20 && p1>30 && p2>40){
	   for(int plane_number=0; plane_number<3; plane_number++){
	       std::cout << "Plane : " << plane_number << std::endl;
	       TFile my_file_1(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/YZ_correction_factors_2016_month_2_month_3_month_4_month_5_plane_%d.root",plane_number));
	       TFile my_file_2(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/YZ_correction_factors_2016_month_6_month_7_plane_%d.root",plane_number));
	       TFile my_file_3(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/YZ_correction_factors_2016_month_8_month_9_month_10_plane_%d.root",plane_number));
	       TH2F *four_month_y_z_hist  = (TH2F*)my_file_1.Get("error_dq_dx_z_vs_y_hist");
	       TH2F *two_month_y_z_hist   = (TH2F*)my_file_2.Get("error_dq_dx_z_vs_y_hist");
	       TH2F *three_month_y_z_hist = (TH2F*)my_file_3.Get("error_dq_dx_z_vs_y_hist");
	       TFile x_file(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_2016_%d_%d_plane_%d.root",month_vector[i],my_date,plane_number));
	       TH1F *x_hist=(TH1F*)x_file.Get("dq_dx_x_error_hist");
	       float upper_angle;
               float lower_angle;
               if(plane_number==2){
                  upper_angle=1.745;lower_angle=1.396;
               }
               if(plane_number==1){
                  upper_angle=0.873;lower_angle=0.175;
               }
               if(plane_number==0){
                  upper_angle=2.792;lower_angle=2.007;
               }
	       vector<float> all_dq_dx_value;
	       if(fChain == 0) return;
               Long64_t nentries = fChain->GetEntriesFast();
               Long64_t nbytes = 0, nb = 0;
               for(Long64_t jentry=0; jentry<nentries;jentry++) {
                   Long64_t ientry = LoadTree(jentry);
                   if (ientry < 0) break;
                   nb = fChain->GetEntry(jentry);   nbytes += nb;
		   bool run_good=false;
		   for(int i_1=0; i_1<good_run_vec.size(); i_1++){
		       if(run==good_run_vec[i_1]){
		          run_good=true;
			  break;
		       } 
		   }
		   if(run_good==false) continue;
		   int year=year_month_date/10000;
                   int month_date=year_month_date%10000;
                   int month=month_date/100;
                   int date=month_date%100;
		   if(month==month_vector[i] && date==my_date){
		      for(int k=0; k<cross_trks; ++k){
		          if(!((TMath::Abs(trackthetaxz[k])>1.31) && (TMath::Abs(trackthetaxz[k])<1.83))){
			        if(!((TMath::Abs(trackthetayz[k])< upper_angle) && (TMath::Abs(trackthetayz[k])> lower_angle))){
				      for(int j=0; j<TMath::Min(ntrkhits[k][plane_number],3000); ++j){
				          if((trkhitx[k][plane_number][j]<260)&&(trkhitx[k][plane_number][j]>0)){
					      if((trkhity[k][plane_number][j]<120)&&(trkhity[k][plane_number][j]>-120)){
					          if((trkhitz[k][plane_number][j]<1040)&&(trkhitz[k][plane_number][j]>0)){
						      int z_bin = int(trkhitz[k][plane_number][j])/z_bin_size; 
				                      int x_bin=int(trkhitx[k][plane_number][j])/x_bin_size;
			                              int y_bin;
						      if(trkhity[k][plane_number][j]<0) y_bin=int(trkhity[k][plane_number][j])/y_bin_size+23;
			                              if(trkhity[k][plane_number][j]>=0) y_bin=int(trkhity[k][plane_number][j])/y_bin_size+24;
						      float yz_correction_factor;
						      if(month==2 || month==3 || month==4 || month==5) yz_correction_factor=four_month_y_z_hist->GetBinContent(z_bin+1,y_bin+1);
						      if(month==6 || month==7) yz_correction_factor=two_month_y_z_hist->GetBinContent(z_bin+1,y_bin+1); 
						      if(month==8 || month==9 || month==10) yz_correction_factor=three_month_y_z_hist->GetBinContent(z_bin+1,y_bin+1);
						      float x_correcton_factor=x_hist->GetBinContent(x_bin+1);
						      float corrected_dq_dx=trkdqdx[k][plane_number][j]*yz_correction_factor*x_correcton_factor;
						      if(corrected_dq_dx!=0) all_dq_dx_value.push_back(corrected_dq_dx);
						  } // z containment...
					      } // y containment...
					  } // x containment...
				      } // loop over hits of the track...
				} // yz angle cut...
			  } // xz angle cut...
		      } // loop over crsoong trks...
		   } // month,date if condition....
               } // loop over jentries...
           
	       if(all_dq_dx_value.size()){
	          float global_median_dq_dx=-1.0;
		  global_median_dq_dx=TMath::Median(all_dq_dx_value.size(),&all_dq_dx_value[0]); 
		  outfile<<global_median_dq_dx<<"  ";
	       }
	   
	   } // loop over plane numbers...
	   } // crossing track number condition in each plane...
           infile>>my_date;
	   outfile<<std::endl;
        } // while loop to get date...
    } // loop over months...
    infile2.close();
    std::cout << "*********************** DONE WITH CALCULATING GLOBAL MEDIANS FOR ALL DATES & ALL PLANES *******************************" << std::endl;
}


