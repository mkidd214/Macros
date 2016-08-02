#include "plotResultsAgain.h"

int plotResultsAgain() {
	PLOTTER plotter;
	cout << plotter.checker << endl;
	
	//comment out or add histogram initializations as necessary
	plotter.hPeakH0 = new TH1D("hPeakH0","Sr peak height", 250, 0, 1500); //originally 500,0,1000; 250,0,500 is another good setting
	plotter.hArea0 = new TH1D("hArea0","C14 peak area",200, 0, 200); //originally 100,0,2000
	plotter.hIntDen0 = new TH1D("hIntDen0","C14 intden",200, 0, 100000); //originally 200,0,100000
	
	plotter.hPeakH1 = new TH1D("hPeakH1","C14 peak height with paper mask",250, 0, 500); //originally 500,0,1000; 250,0,500 is another good setting
	plotter.hArea1 = new TH1D("hArea1","C14 peak area with paper mask",200, 0, 200); //originally 100,0,2000
	plotter.hIntDen1 = new TH1D("hIntDen1","C14 intden with paper mask",200, 0, 100000); //originally 200,0,100000
	
	plotter.hPeakH2 = new TH1D("hPeakH2","10XS 14C subtracted",500, 0, 1000); //originally 500,0,1000
	plotter.hArea2 = new TH1D("hArea2","10XS 14C subtracted",100, 0, 2000); //originally 100,0,2000
	plotter.hIntDen2 = new TH1D("hIntDen2","10XS 14C subtracted",200, 0, 100000); //originally 200,0,100000

//	plotter.hPeakH3 = new TH1D("hPeakH3","Am-241 4X New Camera",500, 0, 1000);
//	plotter.hArea3 = new TH1D("hArea3","Am-241 4X New Camera",100, 0, 2000);
//	plotter.hIntDen3 = new TH1D("hIntDen3","Am-241 4X New Camera",200, 0, 100000);
	
//	TH1D *hPeakH4 = new TH1D("hPeakH4","Am-241 10X New Camera",500, 0, 1000);
//	plotter.hArea4 = new TH1D("hArea4","Am-241 10X New Camera",100, 0, 4000);
//	plotter.hIntDen4 = new TH1D("hIntDen4","Am-241 10X New Camera",200, 0, 200000);
	
	plotter.openFiles();
	plotter.fillHistograms(); //does everything except histogram 2, which contains the subtracted values
	plotter.subtract(); //fills histogram 2
	plotter.setTitles();
	plotter.doCanvases();
}

