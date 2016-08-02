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
	
	TFile *f1 = new TFile("/home/gwendolyn/Things/Fall2015_Research/code_build/Y.root");
	TFile *f2 = new TFile("/home/gwendolyn/Things/Fall2015_Research/code_build/Sr.root");
	TTree *t1 = (TTree*)f1->Get("Y");
	TTree *t2 = (TTree*)f2->Get("Sr");
	t1->SetBranchAddress("Eabs", &YEabs);
	t2->SetBranchAddress("Eabs", &SrEabs);
	
	TFile *f = new TFile("tree1.root","recreate");
	TTree *tree = new TTree("tree","added absorbed energies");
	tree->Branch("YEabs",&YEabs,"YEabs");
	tree->Branch("SrEabs",&SrEabs,"SrEabs");
	tree->Branch("AddedEabs",&AddedEabs,"AddedEabs");
	
	//fill the tree
	for (int i = 0; i < 200000; i++) {
		//get variables from other .root files
		t1->GetEntry(i);
		t2->GetEntry(i);
		AddedEabs = YEabs + SrEabs;
		
		//add them to the new ttree
		tree->Fill();
	}
	tree->Write();
}