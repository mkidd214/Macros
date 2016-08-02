#ifndef PLOTRESULTSAGAIN_H
#define PLOTRESULTSAGAIN_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "TH1I.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TFile.h"
#include "TLine.h"
#include "TF1.h"
#include "TH2.h"
#include "TF2.h"
#include "TMath.h"
#include "TROOT.h"
#include "TRandom.h"

// COMMENT HERE ABOUT WHAT RUN IS SET UP
//Ignoring the subtracted histogram (not commenting it out everywhere because that's too much trouble, but not drawing it). The first histogram is Run 046, a dark run with black cloth in place of the source. It uses the 10XS objective. The second histogram is Run 015, a dark run with no black cloth. It uses the 20XS objective. Run 046 was taken with 10000 images, while Run 015 was taken with 500. The purpose of this comparison is to see if the objectives are substantially different when one has a cloth and the other does not.  


using namespace std;

class PLOTTER {
public:
	//comment out or add variable sets as necessary
	ifstream infile0; double area0, intden0, peakH0, frame0, x0, y0; int counter0 = 0;
	ifstream infile1; double area1, intden1, peakH1, frame1, x1, y1; int counter1 = 0;
	ifstream infile2; double area2, intden2, peakH2, frame2, x2, y2; int counter2 = 0; //subtracted values; shouldn't need an infile
//	ifstream infile3; double area3, intden3, peakH3, frame3, x3, y3; int counter3 = 0;
//	ifstream infile4; double area4, intden4, peakH4, frame4, x4, y4; int counter4 = 0;
	
	//comment out or add histogram allocations as necessary
	//remember that the second value in quotations needs to change for different runs
	TH1D *hPeakH0; TH1D *hArea0; TH1D *hIntDen0;
	TH1D *hPeakH1; TH1D *hArea1; TH1D *hIntDen1;
	TH1D *hPeakH2; TH1D *hArea2; TH1D *hIntDen2; //subtracted
//	TH1D *hPeakH3; TH1D *hArea3; TH1D *hIntDen3;
//	TH1D *hPeakH4; TH1D *hArea4; TH1D *hIntDen4;
	
	int counter = 0; //different from counter0, counter1, and so on
	bool checker;
	string ignore;
	float ig;
	double skew120, skew121;    //not used anywhere else; why does this exist?
	double scale = 0.200*2304;  //not used anywhere else; why does this exist?
	
	void openFiles();
	void fillHistograms();
	void subtract(); //this function takes the difference between two histograms and puts it in a third histogram
	void setTitles();
	void doCanvases();
	
	plotter();
	~plotter();
};

void PLOTTER::plotter() {
	checker = true;
}

void PLOTTER::~plotter() {}

void PLOTTER::openFiles() {
	checker = true; 
	
	//comment out or add file openings as necessary
	infile0.open("/media/gwendolyn/SLIMER DATA/Run067_1/Results-067_1-th140.txt");
	if(!infile0) {
		cout << "File 0 not found.\n";
		checker = false;
	}
	infile1.open("/media/gwendolyn/SLIMER DATA/Run068_1/Results-068_1-th140.txt");
	if(!infile1) {
		cout << "File 1 not found.\n";
		checker = false;
	}
	
	//shouldn't need to open an infile2, since histogram 2 has the subtracted values
	
//	infile3.open("/media/gwendolyn/SLIMER DATA/Run002_1/Results-002_1-th170.txt");
//	if(!infile2) {
//		cout << "File 2 not found.\n";
//		checker = false;
//	}
//	infile4.open("/media/gwendolyn/SLIMER DATA/Run003_1/Results-003_1-th170.txt");
//	if(!infile3) {
//		cout << "File 3 not found!\n";
//		checker = false;
//	}

	cout << checker << endl;
}

void PLOTTER::fillHistograms() {
	if (checker != true) {
		cout << "Missing too many files! Aborting...\n";
		return;
	}
	else {
		//comment out or add line ignores as necessary
		getline(infile0,ignore);     //each one of these ignores the first line of the file
		getline(infile1,ignore);
		//shouldn't need an infile2, since histogram 2 is the subtracted values
//		getline(infile3,ignore);
//		getline(infile4,ignore);
		
		//comment out or add do-while loops to fill the histograms as necessary
/*file0*/	do {
			infile0 >> frame0 >> area0 >> ig >> ig >> peakH0 >> x0 >> y0 >> intden0 >> ig;
			counter0++;
			hArea0->Fill(area0);
			hPeakH0->Fill(peakH0);
			hIntDen0->Fill(intden0);
		}while(!infile0.eof());
		infile0.close();
/*file1*/	do {
			infile1 >> frame1 >> area1 >> ig >> ig >> peakH1 >> x1 >> y1 >> intden1 >> ig;
			counter1++;
			hArea1->Fill(area1);
			hPeakH1->Fill(peakH1);
			hIntDen1->Fill(intden1);
		}while(!infile1.eof());
		infile1.close();
		
		//this loop scales a histogram
		/*int temp = 0; int tem = 0;
		for (int i = 0; i < 500; i++) {
			temp = (hPeakH0->GetBinContent(i))*4.9353;
			hPeakH0->SetBinContent(i,temp);
			
			tem = (hArea0->GetBinContent(i))*4.9353;
			hArea0->SetBinContent(i,tem);
		}*/

//SKIP HISTOGRAM 2, because it's supposed to have the subtracted values	
	
		
/*file3		do {
			infile3 >> frame3 >> area3 >> ig >> ig >> peakH3 >> x3 >> y3 >> intden3 >> ig;
			counter3++;
			hArea3.Fill(area3);
			hPeakH3.Fill(peakH3);
			hIntDen3.Fill(intden3);
		}while(!infile3.eof());
		infile3.close();*/
/*file4		do {
			infile4 >> frame4 >> area4 >> ig >> ig >> peakH4 >> x2 >> y2 >> intden4 >> ig;
			counter4++;
			hArea4.Fill(area4);
			hPeakH4.Fill(peakH4);
			hIntDen4.Fill(intden4);
		}while(!infile4.eof());
		infile4.close();*/
	}
}

//This function subtracts one histogram from another and puts it in HISTOGRAM 2. 
void PLOTTER::subtract() {
	double temp0, temp1, temp2;
	for(int i = 0; i<100; i++) {
		temp0 = hArea0->GetBinContent(i);
		temp1 = hArea1->GetBinContent(i);	
		temp2 = temp0 - temp1;
		hArea2->SetBinContent(i, temp2);
	}

	for(i = 0; i<200; i++) {
		temp0 = hPeakH0->GetBinContent(i);
		temp1 = hPeakH1->GetBinContent(i);	
		temp2 = (temp0 - temp1);
		hPeakH2->SetBinContent(i, temp2);
	}

	for(i = 0; i<200; i++) {
		temp0 = hIntDen0->GetBinContent(i);
		temp1 = hIntDen1->GetBinContent(i);	
		temp2 = temp0 - temp1;
		hIntDen2->SetBinContent(i, temp2);
	}
}

void PLOTTER::setTitles() {
	//again with the commenting/adding
	hArea0->GetXaxis()->SetTitle("Area (px^2)");
	hArea1->GetXaxis()->SetTitle("Area (px^2)");
	hArea2->GetXaxis()->SetTitle("Area (px^2)");
//	hArea3->GetXaxis()->SetTitle("Area (px^2)");
//	hArea4->GetXaxis()->SetTitle("Area (px^2)");
	
	hIntDen0->GetXaxis()->SetTitle("Integrated Density");
	hIntDen1->GetXaxis()->SetTitle("Integrated Density"); 
	hIntDen2->GetXaxis()->SetTitle("Integrated Density");
//	hIntDen3->GetXaxis()->SetTitle("Integrated Density");
//	hIntDen4->GetXaxis()->SetTitle("Integrated Density");
	
	hPeakH0->GetXaxis()->SetTitle("Peak Height");
	hPeakH1->GetXaxis()->SetTitle("Peak Height");
	hPeakH2->GetXaxis()->SetTitle("Peak Height");
//	hPeakH3->GetXaxis()->SetTitle("Peak Height");
//	hPeakH4->GetXaxis()->SetTitle("Peak Height");
}

void PLOTTER::doCanvases() {
	//makes the lenged show up instead of the RMS junk it usually puts
	gROOT->SetStyle("Plain");
	gStyle->SetOptStat(0000000);
	gStyle->SetOptTitle(kFALSE);
	
	//this segment draws the first two runs (just area), and the subtracted run (just area)
/*	new TCanvas();
	hArea0->Draw("");
	hArea1->SetLineColor(2);
	hArea1->Draw("same");
	//hArea2->SetLineColor(3);
	//hArea2->Draw("same");
	TLegend *legend0 = new TLegend(.75,.80,.95,.95);
	legend0->AddEntry(hArea0,"C14 peak area without paper mask");
	legend0->AddEntry(hArea1,"C14 peak area with paper mask");
	//legend0->AddEntry(hArea2,"10XS subtracted");
	legend0->SetFillColor(0);
	legend0->Draw("same");
	gPad->SetLogy();
*/
	
	//this segment draws the first two runs (just height), and the subtracted run (just height)
	new TCanvas();
	hPeakH0->Draw("");
	//hPeakH1->SetLineColor(2);
	//hPeakH1->Draw("same");
	TLegend *legend1 = new TLegend(.75,.80,.95,.95);
	legend1->AddEntry(hPeakH0,"C14 peak height");
	//legend1->AddEntry(hPeakH1,"C14 peak height with paper mask");
	//legend1->AddEntry(hPeakH2,"10XS subtracted");
	legend1->SetFillColor(0);
	legend1->Draw("same");
	gPad->SetLogy();
	
	double integral0 = hPeakH0->Integral(0,500);
	double integral1 = hPeakH1->Integral(0,500);
	
	//cout << "Integral of C14 without paper mask: " << integral0 << endl;
	//cout << "Integral of C14 with paper mask: " << integral1 << endl;
}

#endif