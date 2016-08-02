#include "TFile.h"
#include "TTree.h"
#include <vector>
#if defined (__MAKECINT__)
#pragma link C++ class vector<Double_t>+;
#endif

void vectortest() {
	vector<Double_t> *MyType = new vector<Double_t>;
	TTree *T = new TTree("T","test");
	T->Branch("longs",&MyType);
	T->Print();
}