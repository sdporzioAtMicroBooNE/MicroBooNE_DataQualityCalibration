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
#include <TPaveLabel.h>

using namespace std;

void X_histo_same_canvas(){
int year;
int month;
int plane;
int first_date;
int last_date;
std::cout << "Enter year : ";
std::cin >> year;
std::cout << "Enter month : ";
std::cin >> month;
std::cout << "Enter plane : ";
std::cin >> plane;
std::cout << "Enter starting date : ";
std::cin >> first_date;
std::cout << "Enter ending date : ";
std::cin >> last_date;

std::vector<int> date_vec;
for(int i=first_date; i<last_date+1; i++){
    date_vec.push_back(i);
}

///////////////////////////////////////////////

/*int second_month;
int sec_first_date;
int sec_second_date;

std::cout << "Enter second month : ";
std::cin >> second_month;
std::cout << "Enter first date of second month : ";
std::cin >> sec_first_date;
std::cout << "Enter second date of second month : ";
std::cin >> sec_second_date;

std::vector<int> sec_date_vec;
for(int j=sec_first_date; j<sec_second_date+1; j++){
    sec_date_vec.push_back(j);
}*/
//////////////////////////////////////////////

//////////////////////////////////////////////

/*int third_month;
int third_first_date;
int third_second_date;

std::cout << "Enter third month : ";
std::cin >> third_month;
std::cout << "Enter first date of third month : ";
std::cin >> third_first_date;
std::cout << "Enter second date of third month : ";
std::cin >> third_second_date;

std::vector<int> third_date_vec;
for(int k=third_first_date; k<third_second_date+1; k++){
    third_date_vec.push_back(k);
}*/

/////////////////////////////////////////////

//////////////////////////////////////////////////

/*int fourth_month;
int fourth_first_date;
int fourth_second_date;

std::cout << "Enter fourth month : ";
std::cin >> fourth_month;
std::cout << "Enter first date of fourth month : ";
std::cin >> fourth_first_date;
std::cout << "Enter second date of fourth month : ";
std::cin >> fourth_second_date;

std::vector<int> fourth_date_vec;
for(int k=fourth_first_date; k<fourth_second_date+1; k++){
    fourth_date_vec.push_back(k);
}*/


/////////////////////////////////////////////////

TH1F *my_hist[14];

TFile new_file_1(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[0],plane));
my_hist[0]=(TH1F*)new_file_1.Get("dq_dx_x_error_hist");
my_hist[0]->SetTitle(Form("%d/%d/%d",year,month,date_vec[0]));
std::cout << "*********** open" << std::endl;

TFile new_file_2(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[1],plane));
my_hist[1]=(TH1F*)new_file_2.Get("dq_dx_x_error_hist");
my_hist[1]->SetTitle(Form("%d/%d/%d",year,month,date_vec[1]));
std::cout << "*********** open" << std::endl;

TFile new_file_3(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[2],plane));
my_hist[2]=(TH1F*)new_file_3.Get("dq_dx_x_error_hist");
my_hist[2]->SetTitle(Form("%d/%d/%d",year,month,date_vec[2]));
std::cout << "*********** open" << std::endl;

TFile new_file_4(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[3],plane));
my_hist[3]=(TH1F*)new_file_4.Get("dq_dx_x_error_hist");
my_hist[3]->SetTitle(Form("%d/%d/%d",year,month,date_vec[3]));
std::cout << "*********** open" << std::endl;

TFile new_file_5(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[4],plane));
my_hist[4]=(TH1F*)new_file_5.Get("dq_dx_x_error_hist");
my_hist[4]->SetTitle(Form("%d/%d/%d",year,month,date_vec[4]));
std::cout << "*********** open" << std::endl;

TFile new_file_6(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[5],plane));
my_hist[5]=(TH1F*)new_file_6.Get("dq_dx_x_error_hist");
my_hist[5]->SetTitle(Form("%d/%d/%d",year,month,date_vec[5]));
std::cout << "*********** open" << std::endl;

TFile new_file_7(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[6],plane));
my_hist[6]=(TH1F*)new_file_7.Get("dq_dx_x_error_hist");
my_hist[6]->SetTitle(Form("%d/%d/%d",year,month,date_vec[6]));
std::cout << "*********** open" << std::endl;

TFile new_file_8(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[7],plane));
my_hist[7]=(TH1F*)new_file_8.Get("dq_dx_x_error_hist");
my_hist[7]->SetTitle(Form("%d/%d/%d",year,month,date_vec[7]));
std::cout << "*********** open" << std::endl;

TFile new_file_9(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[8],plane));
my_hist[8]=(TH1F*)new_file_9.Get("dq_dx_x_error_hist");
my_hist[8]->SetTitle(Form("%d/%d/%d",year,month,date_vec[8]));
std::cout << "*********** open" << std::endl;

TFile new_file_10(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[9],plane));
my_hist[9]=(TH1F*)new_file_10.Get("dq_dx_x_error_hist");
my_hist[9]->SetTitle(Form("%d/%d/%d",year,month,date_vec[9]));
std::cout << "*********** open" << std::endl;

TFile new_file_11(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[10],plane));
my_hist[10]=(TH1F*)new_file_11.Get("dq_dx_x_error_hist");
my_hist[10]->SetTitle(Form("%d/%d/%d",year,month,date_vec[10]));
std::cout << "*********** open" << std::endl;

TFile new_file_12(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[11],plane));
my_hist[11]=(TH1F*)new_file_12.Get("dq_dx_x_error_hist");
my_hist[11]->SetTitle(Form("%d/%d/%d",year,month,date_vec[11]));
std::cout << "*********** open" << std::endl;

TFile new_file_13(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[12],plane));
my_hist[12]=(TH1F*)new_file_13.Get("dq_dx_x_error_hist");
my_hist[12]->SetTitle(Form("%d/%d/%d",year,month,date_vec[12]));
std::cout << "*********** open" << std::endl;

TFile new_file_14(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[13],plane));
my_hist[13]=(TH1F*)new_file_14.Get("dq_dx_x_error_hist");
my_hist[13]->SetTitle(Form("%d/%d/%d",year,month,date_vec[13]));
std::cout << "*********** open" << std::endl;

/*TFile new_file_15(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[14],plane));
my_hist[14]=(TH1F*)new_file_15.Get("dq_dx_x_error_hist");
my_hist[14]->SetTitle(Form("%d/%d/%d",year,month,date_vec[14]));
std::cout << "*********** open" << std::endl;

TFile new_file_16(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,month,date_vec[15],plane));
my_hist[15]=(TH1F*)new_file_16.Get("dq_dx_x_error_hist");
my_hist[15]->SetTitle(Form("%d/%d/%d",year,month,date_vec[15]));
std::cout << "*********** open" << std::endl;*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*TFile new_file_16(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,second_month,sec_date_vec[0],plane));
my_hist[15]=(TH1F*)new_file_16.Get("dq_dx_x_error_hist");
my_hist[15]->SetTitle(Form("%d/%d/%d",year,second_month,sec_date_vec[0]));
std::cout << "*********** open" << std::endl;*/

/*TFile new_file_5(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,second_month,sec_date_vec[1],plane));
my_hist[4]=(TH1F*)new_file_5.Get("dq_dx_x_error_hist");
my_hist[4]->SetTitle(Form("%d/%d/%d",year,second_month,sec_date_vec[1]));
std::cout << "*********** open" << std::endl;

TFile new_file_6(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,second_month,sec_date_vec[2],plane));
my_hist[5]=(TH1F*)new_file_6.Get("dq_dx_x_error_hist");
my_hist[5]->SetTitle(Form("%d/%d/%d",year,second_month,sec_date_vec[2]));
std::cout << "*********** open" << std::endl;

TFile new_file_7(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,second_month,sec_date_vec[3],plane));
my_hist[6]=(TH1F*)new_file_7.Get("dq_dx_x_error_hist");
my_hist[6]->SetTitle(Form("%d/%d/%d",year,second_month,sec_date_vec[3]));
std::cout << "*********** open" << std::endl;

TFile new_file_8(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,second_month,sec_date_vec[4],plane));
my_hist[7]=(TH1F*)new_file_8.Get("dq_dx_x_error_hist");
my_hist[7]->SetTitle(Form("%d/%d/%d",year,second_month,sec_date_vec[4]));
std::cout << "*********** open" << std::endl;

TFile new_file_9(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,second_month,sec_date_vec[5],plane));
my_hist[8]=(TH1F*)new_file_9.Get("dq_dx_x_error_hist");
my_hist[8]->SetTitle(Form("%d/%d/%d",year,second_month,sec_date_vec[5]));
std::cout << "*********** open" << std::endl;

TFile new_file_10(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,second_month,sec_date_vec[6],plane));
my_hist[9]=(TH1F*)new_file_10.Get("dq_dx_x_error_hist");
my_hist[9]->SetTitle(Form("%d/%d/%d",year,second_month,sec_date_vec[6]));
std::cout << "*********** open" << std::endl;

TFile new_file_11(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,second_month,sec_date_vec[7],plane));
my_hist[10]=(TH1F*)new_file_11.Get("dq_dx_x_error_hist");
my_hist[10]->SetTitle(Form("%d/%d/%d",year,second_month,sec_date_vec[7]));
std::cout << "*********** open" << std::endl;

TFile new_file_12(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,second_month,sec_date_vec[8],plane));
my_hist[11]=(TH1F*)new_file_12.Get("dq_dx_x_error_hist");
my_hist[11]->SetTitle(Form("%d/%d/%d",year,second_month,sec_date_vec[8]));
std::cout << "*********** open" << std::endl;

TFile new_file_16(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,second_month,sec_date_vec[9],plane));
my_hist[15]=(TH1F*)new_file_16.Get("dq_dx_x_error_hist");
my_hist[15]->SetTitle(Form("%d/%d/%d",year,second_month,sec_date_vec[9]));
std::cout << "*********** open" << std::endl;

TFile new_file_14(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,second_month,sec_date_vec[9],plane));
my_hist[13]=(TH1F*)new_file_14.Get("dq_dx_x_error_hist");
my_hist[13]->SetTitle(Form("%d/%d/%d",year,second_month,sec_date_vec[9]));
std::cout << "*********** open" << std::endl;

TFile new_file_15(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,second_month,sec_date_vec[10],plane));
my_hist[14]=(TH1F*)new_file_15.Get("dq_dx_x_error_hist");
my_hist[14]->SetTitle(Form("%d/%d/%d",year,second_month,sec_date_vec[10]));
std::cout << "*********** open" << std::endl;

TFile new_file_16(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,second_month,sec_date_vec[11],plane));
my_hist[15]=(TH1F*)new_file_16.Get("dq_dx_x_error_hist");
my_hist[15]->SetTitle(Form("%d/%d/%d",year,second_month,sec_date_vec[11]));
std::cout << "*********** open" << std::endl;*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*TFile new_file_13(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,third_month,third_date_vec[0],plane));
my_hist[12]=(TH1F*)new_file_13.Get("dq_dx_x_error_hist");
my_hist[12]->SetTitle(Form("%d/%d/%d",year,third_month,third_date_vec[0]));
std::cout << "*********** open" << std::endl;

TFile new_file_14(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,third_month,third_date_vec[1],plane));
my_hist[13]=(TH1F*)new_file_14.Get("dq_dx_x_error_hist");
my_hist[13]->SetTitle(Form("%d/%d/%d",year,third_month,third_date_vec[1]));
std::cout << "*********** open" << std::endl;

TFile new_file_15(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,third_month,third_date_vec[2],plane));
my_hist[14]=(TH1F*)new_file_15.Get("dq_dx_x_error_hist");
my_hist[14]->SetTitle(Form("%d/%d/%d",year,third_month,third_date_vec[2]));
std::cout << "*********** open" << std::endl;

TFile new_file_16(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,third_month,third_date_vec[3],plane));
my_hist[15]=(TH1F*)new_file_16.Get("dq_dx_x_error_hist");
my_hist[15]->SetTitle(Form("%d/%d/%d",year,third_month,third_date_vec[3]));
std::cout << "*********** open" << std::endl;*/

/*TFile new_file_14(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,third_month,third_date_vec[4],plane));
my_hist[13]=(TH1F*)new_file_14.Get("dq_dx_x_error_hist");
my_hist[13]->SetTitle(Form("%d/%d/%d",year,third_month,third_date_vec[4]));
std::cout << "*********** open" << std::endl;

TFile new_file_15(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,third_month,third_date_vec[5],plane));
my_hist[14]=(TH1F*)new_file_15.Get("dq_dx_x_error_hist");
my_hist[14]->SetTitle(Form("%d/%d/%d",year,third_month,third_date_vec[5]));
std::cout << "*********** open" << std::endl;

TFile new_file_16(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,third_month,third_date_vec[6],plane));
my_hist[15]=(TH1F*)new_file_16.Get("dq_dx_x_error_hist");
my_hist[15]->SetTitle(Form("%d/%d/%d",year,third_month,third_date_vec[6]));
std::cout << "*********** open" << std::endl;*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*TFile new_file_12(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,fourth_month,fourth_date_vec[0],plane));
my_hist[11]=(TH1F*)new_file_12.Get("dq_dx_x_error_hist");
my_hist[11]->SetTitle(Form("%d/%d/%d",year,fourth_month,fourth_date_vec[0]));
std::cout << "*********** open" << std::endl;

TFile new_file_13(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,fourth_month,fourth_date_vec[1],plane));
my_hist[12]=(TH1F*)new_file_13.Get("dq_dx_x_error_hist");
my_hist[12]->SetTitle(Form("%d/%d/%d",year,fourth_month,fourth_date_vec[1]));
std::cout << "*********** open" << std::endl;

TFile new_file_14(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,fourth_month,fourth_date_vec[2],plane));
my_hist[13]=(TH1F*)new_file_14.Get("dq_dx_x_error_hist");
my_hist[13]->SetTitle(Form("%d/%d/%d",year,fourth_month,fourth_date_vec[2]));
std::cout << "*********** open" << std::endl;

TFile new_file_15(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,fourth_month,fourth_date_vec[3],plane));
my_hist[14]=(TH1F*)new_file_15.Get("dq_dx_x_error_hist");
my_hist[14]->SetTitle(Form("%d/%d/%d",year,fourth_month,fourth_date_vec[3]));
std::cout << "*********** open" << std::endl;

TFile new_file_16(Form("/pnfs/uboone/persistent/users/vmeddage/final_calibration_root_files/X_correction_factors_%d_%d_%d_plane_%d.root",year,fourth_month,fourth_date_vec[4],plane));
my_hist[15]=(TH1F*)new_file_16.Get("dq_dx_x_error_hist");
my_hist[15]->SetTitle(Form("%d/%d/%d",year,fourth_month,fourth_date_vec[4]));
std::cout << "*********** open" << std::endl;*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TCanvas c("c","Plane 2",400,300);
c.SetTitle("Plane 2");
c.Divide(4,4);

for(int j=0; j<14; j++){
    c.cd(j+1);
    gPad->SetTickx(2);
    gPad->SetTicky(2);
    my_hist[j]->Draw();
}
TFile *file = new TFile("/uboone/data/users/vmeddage/canvas.root","recreate");
c.Write();
std::cout << "***************** canvas was written ****************" << std::endl;
file->Close();
std::cout << "****************** File closed *****************" << std::endl;
}
