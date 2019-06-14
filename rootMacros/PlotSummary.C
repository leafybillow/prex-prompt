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

#include "PlotErrorCounters.C"
#include "Integrated.C"

void PlotSummary(Int_t run_num){
  run_number = run_num;
  path = TString(getenv("QW_ROOTFILES"))+"/";
  prefix = "prexRespin2_pass2";
  file_name = Form("%s_%d.root",prefix.Data(),run_number);
  TFile* rootfile = TFile::Open(path+file_name);
  output_path = Form("~/PREX/prompt/hallaweb_online/summary/run%d/",run_number);
  //  output_path = "./";
  TString pdf_filename;
  //===== Error Counter from Evt Tree =====   
  PlotErrorCounters();

  //===== BCM  Plots =====
  CheckBCM();
  CheckBCMdd();
  //===== BPM Plots =======
  CheckBPM();
  PlotBPMDiffCorrelation();
  //===== SAM Plots =======
  CheckSAM();
  CheckSAMCorrelation();
  //===== SubBlocks Plots =====   
  // PlotBlocks1D();
  // PlotBlocks();
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

  // Collate Plots
  
  gSystem->Exec(Form("convert $(ls -rt %s*bcm*.png) %srun%d_chapter_bcm.pdf",
  		     output_path.Data(),
		     output_path.Data(),
  		     run_number));

  gSystem->Exec(Form("rm %s*bcm*.png",output_path.Data()));

  gSystem->Exec(Form("convert $(ls -rt %s*sam*.png) %srun%d_chapter_sam.pdf",
  		     output_path.Data(),
		     output_path.Data(),
  		     run_number));

  gSystem->Exec(Form("rm %s*sam*.png",output_path.Data()));

  gSystem->Exec(Form("convert $(ls -rt %s*bpm*.png ) %srun%d_chapter_bpm.pdf",
  		     output_path.Data(),
		     output_path.Data(),
  		     run_number));

  gSystem->Exec(Form("rm %s*bpm*.png",output_path.Data()));


  gSystem->Exec(Form("pdfunite %s/*_chapter_*.pdf %s/run%d_all.pdf",
		     output_path.Data(),
  		     output_path.Data(),run_number));

}

