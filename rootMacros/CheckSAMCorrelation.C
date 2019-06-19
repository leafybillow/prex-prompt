// CheckSAMCorrelation.C : 
//	ROOT script for checking SAM correlation
//
// author : Tao Ye <tao.ye@stonybrook.edu>
// 	 05-2019

#include "device_list.h"

void CheckSAMCorrelation(){
  
  TString treeName = "mul";
  TString draw_opts[] = {"COLZ","fit","scat"};

  Int_t nsam = vSAM.size();
  Int_t nbpm = vDitherBPM.size();

  const char* vtag_dv ="asym_sam";
  const char* vtag_iv ="asym_sam";

  int switch_key = 2;

  TCanvas* c_this = new TCanvas("","",2400,2400);

  for(int iopt=0;iopt<3;iopt++){
    int ny = nsam;
    int nx = nbpm;

    Int_t canvas_width = 2400/(nx+1);
    c_this->SetCanvasSize(2400,ny*canvas_width);
    c_this->cd();
    PlotCorrelation(switch_key,treeName,draw_opts[iopt]);
    plot_title  = Form("run%d_%s_vs_%s-%s.png",
		       run_number,vtag_dv,vtag_iv,
		       draw_opts[iopt].Data());
    TText *label = new TText(0.0,0.005,plot_title);     
    label->SetTextFont(23);
    label->SetTextSize(70);
    label->SetNDC();
    c_this->cd();
    label->Draw("same");
    c_this->SaveAs(output_path+plot_title);
    c_this->Clear("D");
  } // end of draw_opts loop
    

}
