#define Y_Z_calibration_mon_2_to_5_cxx
#include "Y_Z_calibration_mon_2_to_5.h"
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

void Y_Z_calibration_mon_2_to_5::Loop()
{
	int plane_number;
	std::cout << "Enter plane number: ";
	std::cin >> plane_number;

	ifstream infile2;
  printf("Opening runs file.\n");
	infile2.open("/uboone/app/users/sporzio/Calibration/Input_GoodRunsList/fakeGoodRuns_ALL_Run3.txt");
  printf("Runs file opened.\n");
	std::vector<int> good_run_vec;
	int good_runs;
	infile2>>good_runs;
	while(good_runs!=-1){
		good_run_vec.push_back(good_runs);
		infile2>>good_runs;
    std::cout << good_runs << std::endl;
	}
	infile2.close();
  printf("Runs file processed.\n");

	TH2F *dq_dx_z_vs_y_hist = new TH2F("dq_dx_z_vs_y_hist",Form("plane_%d",plane_number),208,0,1040,48,-120,120);
	dq_dx_z_vs_y_hist->GetXaxis()->SetTitle("Z Coordinate(cm)");
	dq_dx_z_vs_y_hist->GetYaxis()->SetTitle("Y Coordinate(cm)");
	dq_dx_z_vs_y_hist->SetStats(0);
	dq_dx_z_vs_y_hist->Draw("COLZ");

	TH2F *error_dq_dx_z_vs_y_hist = new TH2F("error_dq_dx_z_vs_y_hist",Form("plane_%d",plane_number),208,0,1040,48,-120,120);
	error_dq_dx_z_vs_y_hist->GetXaxis()->SetTitle("Z Coordinate (cm)");
	error_dq_dx_z_vs_y_hist->GetYaxis()->SetTitle("Y Coordinate (cm)");
	error_dq_dx_z_vs_y_hist->SetStats(0);
	error_dq_dx_z_vs_y_hist->Draw("COLZ");

	TH2F *corrected_dq_dx_hist = new TH2F("corrected_dq_dx_hist",Form("plane_%d",plane_number),208,0,1040,48,-120,120);
	corrected_dq_dx_hist->GetXaxis()->SetTitle("Z Coordinate (cm)");
	corrected_dq_dx_hist->GetYaxis()->SetTitle("Y Coordinate (cm)");
	corrected_dq_dx_hist->SetStats(0);
	corrected_dq_dx_hist->Draw("COLZ");

	///////////////// Make any changes to the Y and Z bin sizes here ///////////////

	const double y_bin_size = 5.0; // 48 bins in y direction
	const double z_bin_size = 5.0; // 208 bins in z direction

	///////////////////////////////////////////////////////////////////////////////

	vector<vector<vector<float>>> dq_dx_value;
	vector<float> all_dq_dx_value;
	vector<vector<vector<float>>> dq_dx_frac_error;
	dq_dx_value.resize(208);
	dq_dx_frac_error.resize(208);
	for(int i = 0; i < dq_dx_value.size(); i++){
		dq_dx_value[i].resize(48);
		dq_dx_frac_error[i].resize(48);
	}

	TFile *file = new TFile(Form("/uboone/data/users/sporzio/Calibration/Input_Intermediate/correctionFactors_YZ_plane%d.root",plane_number),"recreate");
	int n_cross=0;
	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		if(jentry%100==0) cout<<jentry<<"/"<<nentries<<endl;

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

		if(month==10 || month==11 || month==12){

			for(int i=0; i<cross_trks; ++i){
				n_cross++;

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

				if(!((TMath::Abs(trackthetaxz[i])>1.31) && (TMath::Abs(trackthetaxz[i])<1.83))){
					if(!((TMath::Abs(trackthetayz[i])< upper_angle) && (TMath::Abs(trackthetayz[i])> lower_angle))){
						for(int j=0; j<TMath::Min(ntrkhits[i][plane_number],3000); ++j){
							if((trkhitx[i][plane_number][j]<260)&&(trkhitx[i][plane_number][j]>0)){
								if((trkhity[i][plane_number][j]<120)&&(trkhity[i][plane_number][j]>-120)){
									if((trkhitz[i][plane_number][j]<1040)&&(trkhitz[i][plane_number][j]>0)){
										int z_bin = int(trkhitz[i][plane_number][j])/z_bin_size; 
										int y_bin;
										if(trkhity[i][plane_number][j]<0) y_bin=int(trkhity[i][plane_number][j])/y_bin_size+23;
										if(trkhity[i][plane_number][j]>=0) y_bin=int(trkhity[i][plane_number][j])/y_bin_size+24;
										dq_dx_value[z_bin][y_bin].push_back(trkdqdx[i][plane_number][j]);
									} // Z containment
								} // Y containment
							} // X containiment
							//} // dqdx < 1000
					} // loop over hits of the track in the given plane
				} // theta yz angle cut
			} // theta xz angle cut
		} // loop over crossing tracks in the event
	} // getting year/month of entry  
} // loop over jentries

std::cout << "*************** Calculating the local median dQ/dx values for each Y-Z cell ******************" << std::endl;

////////////////////// Getting inforamtion from dq_dx_value vector ////////////////////

for(int i=0; i<dq_dx_value.size(); i++){
	for(int j=0; j<dq_dx_value[i].size(); j++){
		if(dq_dx_value[i][j].size()>5){

			for(int k=0; k<dq_dx_value[i][j].size(); k++){
				all_dq_dx_value.push_back(dq_dx_value[i][j][k]); 
			}

			float local_median_dq_dx=TMath::Median(dq_dx_value[i][j].size(),&dq_dx_value[i][j][0]);
			dq_dx_z_vs_y_hist->SetBinContent(i+1,j+1,local_median_dq_dx);
		}
	}
}

float global_median_dq_dx=TMath::Median(all_dq_dx_value.size(),&all_dq_dx_value[0]);

/////////////////////////////////////////////////////////////////////////////////////


std::cout << "********************** Calculating fractional dQ/dx corrections for each Y-Z cell ********************" << std::endl;

//////////////////// Calculating the fractional errors in each YZ cell /////////////

for(int i=0; i<dq_dx_value.size(); i++){
	for(int j=0; j<dq_dx_value[i].size(); j++){
		if(dq_dx_value[i][j].size()>5){
			float local_median_dq_dx=TMath::Median(dq_dx_value[i][j].size(),&dq_dx_value[i][j][0]);
			float fractional_dq_dx=float(global_median_dq_dx)/local_median_dq_dx; 
			error_dq_dx_z_vs_y_hist->SetBinContent(i+1,j+1,fractional_dq_dx);
			dq_dx_frac_error[i][j].push_back(fractional_dq_dx);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////


std::cout << "******************** Calculating corrected dQ/dx value for each Y-Z cell **********************" << std::endl;

//////////////// How corrected YZ dqdx distribution looks like ///////////////////

for(int i=0; i<dq_dx_value.size(); i++){
	for(int j=0; j<dq_dx_value[i].size(); j++){
		if(dq_dx_value[i][j].size()>5){
			float local_median_dq_dx=TMath::Median(dq_dx_value[i][j].size(),&dq_dx_value[i][j][0]);
			float corrected_dq_dx=local_median_dq_dx*dq_dx_frac_error[i][j][0];
			corrected_dq_dx_hist->SetBinContent(i+1,j+1,corrected_dq_dx);
		} 
	}
}

/////////////////////////////////////////////////////////////////////////////////

dq_dx_z_vs_y_hist->Write();
error_dq_dx_z_vs_y_hist->Write();
corrected_dq_dx_hist->Write();

std::cout << "Number of crossing tracks : " << n_cross << std::endl;

file->Close();
std::cout << "*************** ext_data_test.C macro has ended ******************" << std::endl;  

}


