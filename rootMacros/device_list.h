#ifndef _DEVICE_LIST_H_
#define _DEVICE_LIST_H_

// File IO control variable
TString path;
TString prefix;
TString file_name;
TString output_path;
TString plot_title;
Int_t run_number;
TString run_seg;
TFile *japanOutput;

//  Beamline Monitors

vector<const char*> vBCM={"bcm_an_us", "bcm_an_ds", 
			  "bcm_an_ds3","bcm0l02"};

vector<const char*> vBPM={"bpm4a","bpm4e","bpm8","bpm12","bpm14"};

vector<const char*> vBPMXY={"bpm4aX","bpm4aY",
			    "bpm4eX","bpm4eY",
			    "bpm8X","bpm8Y",
			    "bpm12X","bpm12Y",
			    "bpm14X","bpm14Y"};


vector<const char*> vDitherBPM={"bpm4aX","bpm4aY",
				"bpm4eX","bpm4eY",
				"bpm12X"};

vector<const char*> vCavBPM={"cav4b","cav4c","cav4d"};

vector<const char*> vSAM={"sam2","sam4","sam6","sam8"};

vector<const char*> vSAMUnity={"sam1","sam3","sam5","sam7"};

vector<const char*> vMainDet={"usl","dsl","usr","dsr"};

vector<const char*> vAT={"atl1","atl2","atr1","atr2"};

vector<const char*> vBlkM = {"asym_bcm_an_ds3","asym_sam2","asym_sam4"};  // Block Monitors


//Injector Plots
//make matrix to hold data points, injector daq can only hold 22 bpms max. 

vector<const char*> vInjBPM = {"bpm2i01","bpm2i02","bpm1i02","bpm1i04",
			       "bpm1i06", "bpm0i01","bpm0i01a","bpm0i02",
			       "bpm0i02a","bpm0i05","bpm0i07","bpm0l01",
			       "bpm0l02","bpm0l03","bpm0l04","bpm0l05",
			       "bpm0l06","bpm0l07","bpm0l10", "bpm0r02",
			       "bpm0r05"};
  
/* vector<const char*> detnams = {"bpm2i01","bpm2i02","bpm1i02","bpm1i04", */
/* 			 "bpm1i06","bpm0i01","bpm0i01a","bpm0i02", */
/* 			 "bpm0i02a","bpm0i05", "bpm0i07","bpm0l01", */
/* 			 "bpm0l02","bpm0l03","bpm0l04","bpm0l05", */
/* 			 "bpm0l06","bpm0l07","bpm0l08","bpm0l09", */
/* 			 "bpm0l10","bpm0r03","bpm0r05"}; */


#endif

