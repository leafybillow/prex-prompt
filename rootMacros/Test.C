#include "device_list.h"


#include "CheckBCMdd.C"
#include "CheckEventCut.C"
#include "PlotDeviceEvent.C"
#include "PlotBlocks.C"
#include "PlotInjBPMS.C"
#include "PlotInjBPMSAq.C"
#include "PlotInjBPMSDr.C"
#include "PlotCorrelation.C"
#include "PlotErrorCounters.C"
#include "Integrated.C"
#include "CheckBPM.C"
#include "CheckSAM.C"
#include "CheckRegression.C"
#include "CheckPairSAM.C"

void Test(Int_t run_num){

  run_number = run_num;
  path = "./japanOutput/";
  prefix = "prexRespin2_pass2";
  file_name = Form("%s_%d.root",prefix.Data(),run_number);
  TFile* rootfile = TFile::Open(path+file_name);
  output_path = "./";

  // CheckEventCut();
  //  PlotDeviceEvent();
  // CheckBPM();
  CheckPairSAM();
}

