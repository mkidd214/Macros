{
	#include "TCanvas.h"
	#include "TRandom.h"
	#include "TH2.h"
	#include "TF2.h"
	#include "TMath.h"
	#include "TROOT.h"
	#include <fstream>
	#include <string>
	
	double YEabs, SrEabs, AddedEabs;
	TFile *f1 = new TFile("~/Downloads/Y.root");
	TFile *f2 = new TFile("~/Downloads/Sr.root");
	TTree *t1 = (TTree*)f1->Get("file");
	TTree *t2 = (TTree*)f2->Get("file");
	t1->SetBranchAddress("Eabs", &YEabs);
	t2->SetBranchAddress("Eabs", &SrEabs);
	
	TChain chain("file"); // name of the tree is the argument
	chain.Add("~/Downloads/Y.root");
	chain.Add("~/Downloads/Sr.root");
	
	chain.SetBranchAddress("Eabs", &TotalEabs);

	TFile *f = new TFile("tree1.root","recreate");
	TTree *tree = new TTree("tree","added absorbed energies");
	tree->Branch("AddedEabs",&temp,"temp/D");
	
	TH1D *hTot = new TH1D("hTot","Total",1000,0,1000);
	TH1D *hSr = new TH1D("hSr","Sr",1000,0,1000);	
	TH1D *hY = new TH1D("hY","Y",1000,0,1000);
		
	int nEntries = chain.GetEntries();
	
	//fill the histogram
	for (int i = 0; i < nEntries; i++) {
		//get variables from other .root files
		chain->GetEntry(i);
		temp = TotalEabs;
		hTot->Fill(TotalEabs);
		tree->Fill();

	}
	
	nEntries = t1->GetEntries();
	for (i = 0; i < nEntries; i++) {
		//get variables from other .root files
		t1->GetEntry(i);
		t2->GetEntry(i);
		hSr->Fill(SrEabs);
		hY->Fill(YEabs);
	}
	

new TCanvas();
hTot->SetLineColor(1);
hSr->SetLineColor(2);
hY->SetLineColor(3);
hTot->Draw();
hSr->Draw("same");
hY->Draw("same");

tree->Write();

}
