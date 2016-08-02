{
	#include "TCanvas.h"
	#include "TRandom.h"
	#include "TH2.h"
	#include "TF2.h"
	#include "TMath.h"
	#include "TROOT.h"
	#include <fstream>
	#include <string>

	TFile *f = new TFile("/home/gwendolyn/Things/Fall2015_Research/code_build/Y.root");
	TFile *f2 = new TFile("/home/gwendolyn/Things/Fall2015_Research/code_build/Sr.root");
	
	TFile *file = new TFile("/home/gwendolyn/Things/Fall2015_Research/code_build/Added.root","new"); //creates a new file to put the three histograms into

	TTree *t1 = (TTree*)f->Get("Y");
	TTree *t2 = (TTree*)f2->Get("Sr");

	double pEn1, eabs1;
	double pEn2, eabs2;

	t1->SetBranchAddress("PrimaryEn", &pEn1);
	t2->SetBranchAddress("PrimaryEn", &pEn2);
	
	t1->SetBranchAddress("Eabs", &eabs1);
	t2->SetBranchAddress("Eabs", &eabs2);

	TH1D *hEn = new TH1D("hEn","Added PrimaryEnergies",500,0,3000);
	TH1D *YEn = new TH1D("YEn","Y PrimaryEn",500,0,3000);
	TH1D *SrEn = new TH1D("SrEn","Sr PrimaryEn",500,0,3000);

	TH1D *hEabs = new TH1D("hEabs","Added Energy Absorbed",500,0,1000);
	TH1D *YEabs = new TH1D("YEabs","Y Energy Absorbed",500,0,1000);
	TH1D *SrEabs = new TH1D("SrEabs","Sr Energy Absorbed",500,0,1000);
	
	for (int i = 0; i < 50000; i++) {
		t1->GetEntry(i);
		t2->GetEntry(i);
		YEn->Fill(pEn1);
		SrEn->Fill(pEn2);
		YEabs->Fill(eabs1);
		SrEabs->Fill(eabs2);
	}
	
	hEn->SetLineColor(1);
	hEn->Add(YEn);
	hEn->Add(SrEn);
	hEn->Draw();
	
	SrEn->SetLineColor(3);
	SrEn->Draw("same");
	
	YEn->SetLineColor(2);
	YEn->Draw("same");
	
	hEn->Draw("same");
	
	hEabs->Add(YEabs);
	hEabs->Add(SrEabs);
	
	file->Write();
}