// CheckDiffCorrelation.C : 
//	ROOT script for diff_bpm correlation
//
// author : Tao Ye <tao.ye@stonybrook.edu>
// 	 05-2019

#include "device_list.h"

void PlotBPMDiffCorrelation(){
  
  TTree *mul_tree = (TTree*)gROOT->FindObject("mul");
  TString draw_opts[] = {"COLZ","fit","scat"};
  
  Int_t nbpmXY = vBPMXY.size();
  TCanvas* c_square = new TCanvas("","",nbpmXY*600,nbpmXY*600);

  c_square->Divide(nbpmXY,nbpmXY);
  for(int iopt=0;iopt<3;iopt++){
    c_square->cd();
    PlotCorrelation(vBPMXY,vBPMXY,
		    "mul",
		    "diff_","diff_",
		    draw_opts[iopt],
		    "ErrorFlag==0");
    
    plot_title  = Form("run%d_diff_bpm_mutual_correlation_%s.png",
		       run_number,draw_opts[iopt].Data());
    TText *label = new TText(0.0,0.005,plot_title);     
    label->SetTextFont(23);
    label->SetTextSize(70);
    label->SetNDC();
    c_square->cd();
    label->Draw("same");
    c_square->SaveAs(output_path+plot_title);
    c_square->Clear("D");
  }


}
