{
	#include "TCanvas.h"
	#include "TRandom.h"
	#include "TH2.h"
	#include "TF2.h"
	#include "TMath.h"
	#include "TROOT.h"
	#include <fstream>
	#include <string>
	
	TCanvas *c1 = new TCanvas("c1","primaryEn",200,10,700,500);
	c1->SetGrid();
	
	const Int_t n = 3;
	Double_t x[n] = {400.,1020.,1358.}; //endpoint gray value for C, Cs, Sr-Y
	Double_t ex[n] = {20.,34.641,32.404};
	Double_t y[n] = {156.,500.,2260}; //endpoint energy for C, Cs, Sr-Y (Cs is an estimate)
	Double_t ey[n] = {12.490,34.059,47.539};
	
	TGraphErrors *gr = new TGraphErrors(n,x,y,ex,ey);
	gr->SetLineColor(2);
	gr->SetLineWidth(3);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->SetTitle("primaryEn");
	gr->GetXaxis()->SetTitle("Gray value (data)");
	gr->GetYaxis()->SetTitle("primaryEn (keV) (simulation)");
	gr->GetXaxis()->SetLimits(0,1600);
	gr->GetYaxis()->SetLimits(0,5500);
	gr->Draw("AP");
	//gr->Fit("pol1","","",0,1600);

	// TCanvas::Update() draws the frame, after which one can change it
	c1->Update();
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();
	
	
	
	
	TCanvas *c2 = new TCanvas("c2","eAbs",200,10,700,500);
	c2->SetGrid();
	
	const Int_t n2 = 3;
	Double_t x2[n2] = {400.,1020.,1358.}; //endpoint gray value for C, Cs, Sr-Y
	Double_t ex2[n2] = {20.,34.641,32.404};
	Double_t y2[n2] = {143.,518.5,796.}; //endpoint energy for C, Cs, Sr-Y
	Double_t ey2[n2] = {11.958,22.771,28.213};
	
	TGraphErrors *gr2 = new TGraphErrors(n2,x2,y2,ex2,ey2);
	gr2->SetLineColor(2);
	gr2->SetLineWidth(3);
	gr2->SetMarkerColor(4);
	gr2->SetMarkerStyle(21);
	gr2->SetTitle("eAbs");
	gr2->GetXaxis()->SetTitle("Gray value (data)");
	gr2->GetYaxis()->SetTitle("eAbs (keV) (simulation)");
	gr2->GetXaxis()->SetLimits(0,1400);
	gr2->Draw("AP");
	gr2->Fit("pol1","","",0,1400);
	
	c2->Update();
	c2->GetFrame()->SetBorderSize(12);
	c2->Modified();
}