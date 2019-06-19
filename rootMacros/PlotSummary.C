//////////////////////////////////////////////////////////////////////
//
// PlotSummary.C
//   Tao Ye - May 2019
//
//////////////////////////////////////////////////////////////////////

#include "device_list.h"

#include "PlotCorrelation.C"

#include "PlotInjBPMS.C"
#include "PlotInjBPMSAq.C"
#include "PlotInjBPMSDr.C"
#include "PlotInjBPMSAelli.C"

#include "CheckBCM.C"
#include "CheckBCMdd.C"
#include "CheckBPM.C"
#include "PlotBPMDiffCorrelation.C"
#include "CheckSAM.C"
#include "CheckSAMCorrelation.C"
#include "CheckRegression.C"
#include "CheckPairSAM.C"

#include "PlotErrorCounters.C"
#include "Integrated.C"

void PlotSummary(Int_t run_num){
  run_number = run_num;
  path = TString(getenv("QW_ROOTFILES"))+"/";
  prefix = "prexRespin2_pass2";
  file_name = Form("%s_%d.root",prefix.Data(),run_number);
  TFile* rootfile = TFile::Open(path+file_name);
  output_path = Form("./summary/run%d/",run_number);
  //  output_path = "./";
  TString pdf_filename;
  //===== Error Counter from Evt Tree =====   
  PlotErrorCounters();
  //===== BCM  Plots =====
  CheckBCM();
  CheckBCMdd();

  gSystem->Exec(Form("convert $(ls -rt %s*bcm*.png) %srun%d_summary_bcm.pdf",
  		     output_path.Data(),
		     output_path.Data(),
  		     run_number));

  gSystem->Exec(Form("rm %s*bcm*.png",output_path.Data()));

  //===== BPM Plots =======
  CheckBPM();
  PlotBPMDiffCorrelation();

  gSystem->Exec(Form("convert $(ls -rt %s*bpm*.png ) %srun%d_summary_bpm.pdf",
  		     output_path.Data(),
		     output_path.Data(),
  		     run_number));

  gSystem->Exec(Form("rm %s*bpm*.png",output_path.Data()));

  //===== SAM Plots =======
  CheckSAM();
  CheckSAMCorrelation();
  gSystem->Exec(Form("convert $(ls -rt %s*sam*.png) %srun%d_summary_sam.pdf",
  		     output_path.Data(),
		     output_path.Data(),
  		     run_number));

  gSystem->Exec(Form("rm %s*sam*.png",output_path.Data()));

  //===== Check Regression =====   
  CheckRegression();
  CheckPairSAM();

  // ===== Integrated Convergence 
  Integrated();
  //==== Injector BPMs Dx Dy Dr and Ellipticity ====
  PlotInjBPMS();
  PlotInjBPMSAq();
  PlotInjBPMSDr();
  PlotInjBPMSAelli();
  pdf_filename = Form("run%d_injector_BPM.pdf",run_number);
  gSystem->Exec(Form("convert $(ls -rt %srun%d*injector_BPM*.png) %s%s",
		     output_path.Data(),
		     run_number,
		     output_path.Data(),
		     pdf_filename.Data()));

  gSystem->Exec(Form("rm %srun%d*injector_BPM*.png",
		     output_path.Data(),
		     run_number)); 


  gSystem->Exec(Form("pdfunite $(ls -rt %s/*_summary_*.pdf) %s/run%d_all.pdf",
		     output_path.Data(),
  		     output_path.Data(),run_number));

}

