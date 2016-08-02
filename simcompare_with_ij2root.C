/* Notes on the macros: 
 * 
 * * * * ij2root.C macro * * * *
 * Converts our imageJ ascii data to root file.  Currently this is for data in the form of
 * event number, area, mean, min, max, x, y, intden, raw intden;
 * If you change the output of the imageJ results table, you will need to edit the 
 * script below to reflect those changes.  Specifically, the definition of the ntuple, 
 * the "skip first line" command, the read-in line, and the ntuple->Fill line.
 * 
 * Also, if your datafile has an extension longer than 3 characters, you'll need to edit 
 * the line that is commented "crop the .txt part" (or change your extension!).
 * 
 * The output file is stored in the same directory as the input file with the same name 
 * except with an extension of ".root". 
 * 
 * Run root -l and then .x ij2root.C("/path/to/filename.txt")
 * 
 * * * * sim-compare.C macro * * * *
 * Compares simulation data to real data
 * 
 * * * * simcompare_with_ij2root.C macro * * * *
 * The first point of this macro was to combine the other two, eliminating a step in the analysis process. 
 * The second point was to get some sort of calibration: the camera data has units of "pixels" or something mysterious, 
 * while the simulation data has normal units. If the data sets match reasonably well, units can be found for the camera data.
 * 
 * Run the same way as ij2root.C: root -l first, then .x simcompare_with_ij2root.C("path/to/filename.txt")
 */

gROOT->SetStyle("Plain");
gStyle->SetOptStat(0000000);
gStyle->SetOptTitle(kFALSE);


#include <fstream>
#include <string>
#include <cmath>
#include "Riostream.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TH2.h"
#include "TF2.h"
#include "TMath.h"
#include "TROOT.h"

void simcompare_with_ij2root(string filetxt){
	//this part is from ij2root
	string fileroot, ignore;
	cout<<"Filename is "<<filetxt<<"\n";  //checking that it got the right filename
	int strlength = filetxt.length();  //getting the length of the filename
	cout<<"length is "<<strlength<<"\n";  //just checking!
	fileroot = filetxt;  //making a copy 
	fileroot.replace(fileroot.length()-3, fileroot.length(),"root"); //change "txt" to "root" and store in our copy
	cout<<fileroot<<"\n";  //double checking the new filename
	ifstream in;  //here's our read-in file
	in.open(filetxt.c_str());  //open() requires a character array
	
	Float_t num, area, mean, min, max, x, y, intden, intden2;
	Int_t nlines = 0;
	TFile *f = new TFile(fileroot.c_str(),"RECREATE"); //here's our output root file, also wants a char

	TNtuple *ntuple = new TNtuple("ntuple","data from ImageJ","area:mean:min:max:x:y:intden:intden2");
	getline(in,ignore); //skip first line
	
	while (1) {
		in >> num >> area >> mean >> min >> max >> x >> y >> intden >> intden2;
		if (!in.good()) break;
		//cout<<num<<"\t"<< area<<"\t" << mean<<"\t" << min<<"\t" << max<<"\t" << x<<"\t" << y<<"\t" << intden<<"\t" << intden2<<"\n";
		ntuple->Fill(area, mean, min, max, x, y, intden, intden2); //fill the branches
		nlines++;
	}
	printf(" found %d points\n",nlines);

	in.close();

	f->Write();
	
	
	//this part is from sim-compare
	
	TFile *f = new TFile("/home/gwendolyn/Things/Fall2015_Research/code_build/C.root"); //simulation data
	TFile *f2 = new TFile("/media/gwendolyn/SLIMER DATA/Run067_1/Results-067_1-th170.root"); //real data
	
	TTree *t1 = (TTree*)f->Get("C");  //simulation
	TTree *t2 = (TTree*)f2->Get("ntuple");  //data
	
	int n1 = t1->GetEntries();
	int n2 = t2->GetEntries();

	//for Sr and Y, change double pEn, eAbsorbed to float
	double pEn, eAbsorbed;
	float area, max;
	
	// NOTE: For any data except Sr with Y, change AddedEabs to Eabs. For Sr with Y, change Eabs to AddedEabs.
	
//	t1->SetBranchAddress("PrimaryEn", &pEn);
	t1->SetBranchAddress("Eabs", &eAbsorbed);

	t2->SetBranchAddress("area", &area);
	t2->SetBranchAddress("max", &max);
	
	TH1D *hEn = new TH1D("hEn","Energy Absorbed",500,0,1500);
	TH1F *hArea = new TH1F("hArea","Area of Events",100,0,3000);
	TH1F *hMax = new TH1F("hMax","Peak Height of Events",500,0,1500);
	TH1F *hMaxCal = new TH1F("hMaxCal","Cal Peak Height of Events",500,0,1500);
	TH1F *hAreaCal = new TH1F("hAreaCal","Calibrated Area of Events",180,0,180);
	
	TF1 *function = new TF1("function","[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]*exp(-x/[5])+[6]",0,1500);
	TF1 *function2 = new TF1("function2","[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]*exp(-x/[5])+[6]",0,1500);
	TF1 *function3 = new TF1("function3","[0]*exp(-x/[1])+[2]*exp(-x/[3])+[4]*exp(-x/[5])+[6]",0,1500);
	function->SetParameters(5783,9,3283,43,1194,100,-18);
	function2->SetParameters(270,2,51000,45,4883,153,-9);
	function3->SetParameters(1945,69,1945,69,4710,9,-9);
	
	for(int i = 0; i<n1; i++) {
		t1->GetEntry(i);
		if (eAbsorbed > 0) 
			hEn->Fill(eAbsorbed);
	}

//----------------------------------------------------------------------------------
	
	double a = 125;
	double b = .66;
	for (x = 0; x < n2; x++) {
		t2->GetEntry(x);
		hArea->Fill(area);
		//if (area >= 100) {
			hMax->Fill(max);
			hMaxCal->Fill(b*max - a);  //first value: energy from spectrum; second value: x-value from data
		//}
	}
	
	Double_t res[1500];
	cout << hEn->Chi2Test(hMaxCal,"UW CHI2/NDF",res) << endl;
	
	
//----------------------------------------------------------------------------------
	
	for(i = 0; i<n2; i++) {
		t2->GetEntry(i);
		hAreaCal->Fill(area*0.145/2776.);
	}
	
	//scaling
	int temp = 0;
	for (int i = 0; i < n2; i++) {
		temp = hMax->GetBinContent(i);
	}
		
	new TCanvas();	
	
//	hEn->SetLineWidth(2);
//	hMax->SetLineWidth(2);
//	hMaxCal->SetLineWidth(2);
	
	hEn->SetXTitle("Energy (keV)");
	hEn->SetYTitle("Counts per 3 keV");
	hEn->SetLineColor(3);
	hEn->Draw();
	//hEn->Fit(function,"W","SAME",0,400);
	
	hMax->SetLineColor(4);
	hMax->Draw("same");
	//hMax->Fit(function2,"W","SAME",200,900);
	
	hMaxCal->SetLineColor(5);
	hMaxCal->Draw("same");
	//hMaxCal->Fit(function3,"W","SAME",0,400);

	TLegend *legend = new TLegend(.75,.80,.95,.95);
	legend->AddEntry(hEn,"Simulation data");
	legend->AddEntry(hMax,"Experimental data");
	legend->AddEntry(hMaxCal,"Calibrated experimental data");
	legend->SetFillColor(0);
	legend->Draw("same");
	
	double integral0 = hEn->Integral(0,1500);
	double integral1 = hMax->Integral(0,1500);
	double integral2 = hMaxCal->Integral(0,1500);
	
	cout << "Integral of hEn: " << integral0 << endl;
	cout << "Integral of hMax: " << integral1 << endl;
	cout << "Integral of hMaxCal: " << integral2 << endl;	
}

