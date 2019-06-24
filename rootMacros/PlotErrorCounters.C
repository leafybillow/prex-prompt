// author : Tao Ye
// date : 05-2019
// description: A script for error code plots 

#include "DeviceErrorCounter.C"
#include "ErrorFlagDecoder.C"
#include "device_list.h"

void PlotErrorCounters(){
  TString plot_title;

  TCanvas* c1 = new TCanvas("c1","c1",2400,1200);
  TCanvas* c2 = new TCanvas("c2","c2",2400,1800);
  c2->Divide(2,2);

  c1->cd();
  Bool_t kStatus = ErrorFlagDecoder();
  plot_title = Form("run%s_ErrorCounter_global.png",run_seg.Data());
  c1->SaveAs(output_path+ plot_title);

  if(kStatus){
    TString sam_array[8]={"sam1","sam2","sam3","sam4",
			  "sam5","sam6","sam7","sam8"};
    TString bcm_array[4]={"bcm_an_us","bcm_an_ds","bcm_an_ds3","bcm0l02"};
  
    TString bpm4a_array[4]={"bpm4aXM","bpm4aXP","bpm4aYP","bpm4aYM"};
    TString bpm4e_array[4]={"bpm4eXM","bpm4eXP","bpm4eYP","bpm4eYM"};
    TString bpm8_array[4]={"bpm8XM","bpm8XP","bpm8YP","bpm8YM"};
    TString bpm12_array[4]={"bpm12XM","bpm12XP","bpm12YP","bpm12YM"};
    TString bpm14_array[4]={"bpm14XM","bpm14XP","bpm14YP","bpm14YM"};

  
    TString* channels[7]={sam_array,sam_array+4,
			  bpm4a_array,bpm4e_array,
			  bpm12_array,bpm14_array,
			  bpm8_array};

    for(int i=0;i<4;i++){
      c2->cd(i+1);
      DeviceErrorCounter(bcm_array[i]);
    }
    plot_title = Form("run%s_ErrorCounter_bcm.png",run_seg.Data());
    c2->SaveAs(output_path+ plot_title);

    for(int ich=0;ich<7;ich++){
      for(int i=0;i<4;i++){
	c2->cd(i+1);
	DeviceErrorCounter(channels[ich][i]);
      }
      plot_title = Form("run%s_ErrorCounter_%d.png",run_seg.Data(),ich);
      c2->SaveAs(output_path+ plot_title);
    }
  } // END of if there is any good event

  TString pdf_filename = Form("run%s_ErrorCounters.pdf",run_seg.Data());
  gSystem->Exec(Form("convert $(ls -rt %srun%s*ErrorCounter*.png) %s%s",
		     output_path.Data(),
		     run_seg.Data(),
		     output_path.Data(),
		     pdf_filename.Data()));
  gSystem->Exec(Form("rm %srun%s*ErrorCounter*.png",
		     output_path.Data(),
		     run_seg.Data())); 

}
