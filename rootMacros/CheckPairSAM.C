// CheckPairSAM.C : 
//	ROOT script for SAM resolution check for japan Ouputs
//
//  author: Tao Ye 
//  	06-2019

#include "device_list.h"

void CheckPairSAM(){

  TTree *mul_tree = (TTree*)gROOT ->FindObject("mul");
  TTree *mulc_tree = (TTree*)gROOT ->FindObject("mulc_lrb");
  mulc_tree->AddFriend(mul_tree);

  mulc_tree->SetAlias("AqDS", "asym_bcm_an_ds3/ppm");
  mulc_tree->SetAlias("AqUS", "asym_bcm_an_us/ppm");
  TString user_cut ="ErrorFlag==0";   // FIXME : It should be device_Error_Code
  TString filename;
  TText *label;
  TCanvas *c0 = new TCanvas("c0","c0",2400,1200);
  c0->Divide(4,2);
  c0->cd(1);
  mulc_tree->Draw("cor_sam2/ppm:AqDS",user_cut);
  c0->cd(2);
  mulc_tree->Draw("cor_sam4/ppm:AqDS",user_cut);
  c0->cd(3);
  mulc_tree->Draw("cor_sam6/ppm:AqDS",user_cut);
  c0->cd(4);
  mulc_tree->Draw("cor_sam8/ppm:AqDS",user_cut);

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  c0->cd(5);

  TH1 *hfit;
  Double_t low, up;

  mulc_tree->Draw("cor_sam2/ppm:AqDS>>ha2",user_cut,"prof");
  hfit = (TH2D*)gDirectory->FindObject("ha2");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);

  c0->cd(6);
  mulc_tree->Draw("cor_sam6/ppm:AqDS>>ha6",user_cut,"prof");
  hfit = (TH2D*)gDirectory->FindObject("ha6");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);

  c0->cd(7);
  mulc_tree->Draw("cor_sam4/ppm:AqDS>>ha4",user_cut,"prof");
  hfit = (TH2D*)gDirectory->FindObject("ha4");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);

  c0->cd(8);
  mulc_tree->Draw("cor_sam8/ppm:AqDS>>ha8",user_cut,"prof");
  hfit = (TH2D*)gDirectory->FindObject("ha8");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);
  
  filename = Form("run%s_paired_sam_AqDS.png",run_seg.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c0->cd();
  label->Draw("same");
  c0->SaveAs(output_path+filename);


  c0->cd(1);
  mulc_tree->Draw("cor_sam2/ppm:AqUS",user_cut);
  c0->cd(2);
  mulc_tree->Draw("cor_sam4/ppm:AqUS",user_cut);
  c0->cd(3);
  mulc_tree->Draw("cor_sam6/ppm:AqUS",user_cut);
  c0->cd(4);
  mulc_tree->Draw("cor_sam8/ppm:AqUS",user_cut);

  c0->cd(5);
  mulc_tree->Draw("cor_sam2/ppm:AqUS>>ha2",user_cut,"prof");
  hfit = (TH2D*)gDirectory->FindObject("ha2");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);

  c0->cd(6);
  mulc_tree->Draw("cor_sam6/ppm:AqUS>>ha6",user_cut,"prof");
  hfit = (TH2D*)gDirectory->FindObject("ha6");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);

  c0->cd(7);
  mulc_tree->Draw("cor_sam4/ppm:AqUS>>ha4",user_cut,"prof");
  hfit = (TH2D*)gDirectory->FindObject("ha4");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);

  c0->cd(8);
  mulc_tree->Draw("cor_sam8/ppm:AqUS>>ha8",user_cut,"prof");
  hfit = (TH2D*)gDirectory->FindObject("ha8");
  low = hfit->GetMean()-2*hfit->GetRMS();
  up = hfit->GetMean()+2*hfit->GetRMS();
  hfit->Fit("pol1","QR","",low,up);
  
  filename = Form("run%s_paired_sam_AqUS.png",run_seg.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c0->cd();
  label->Draw("same");
  c0->SaveAs(output_path+filename);


  gStyle->SetOptStat(1);
  gStyle->SetOptFit(1);
  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.25);
  gStyle->SetStatX(0.95);
  gStyle->SetStatY(0.95);

  TCanvas *c1 = new TCanvas("c1","c1",2400,1600);
  c1->Divide(3,2);
  c1->cd(1);
  mulc_tree->Draw("cor_sam4/ppm",user_cut);
  c1->cd(2);
  mulc_tree->Draw("cor_sam8/ppm",user_cut);
  c1->cd(3);
  mulc_tree->Draw("cor_sam4/ppm : cor_sam8/ppm",user_cut);
  c1->cd(4);
  mulc_tree->Draw("cor_sam4/ppm : cor_sam8/ppm",user_cut,"prof");
  c1->cd(5);
  mulc_tree->Draw("(cor_sam4-cor_sam8)/ppm",user_cut);
  c1->cd(6);
  mulc_tree->Draw("(cor_sam4+cor_sam8)/ppm",user_cut);

  filename = Form("run%s_paired_sam_48.png",run_seg.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c1->cd();
  label->Draw("same");
  c1->SaveAs(output_path+filename);

  TCanvas *c2 = new TCanvas("c2","c2",2400,1600);
  c2->Divide(3,2);

  c2->cd(1);
  mulc_tree->Draw("cor_sam2/ppm",user_cut);
  c2->cd(2);
  mulc_tree->Draw("cor_sam6/ppm",user_cut);
  c2->cd(3);
  mulc_tree->Draw("cor_sam2/ppm : cor_sam6/ppm",user_cut);
  c2->cd(4);
  mulc_tree->Draw("cor_sam2/ppm : cor_sam6/ppm",user_cut,"prof");
  c2->cd(5);
  mulc_tree->Draw("(cor_sam2-cor_sam6)/ppm",user_cut);
  c2->cd(6);
  mulc_tree->Draw("(cor_sam2+cor_sam6)/ppm",user_cut);

  filename = Form("run%s_paired_sam_26.png",run_seg.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.03);
  label->SetNDC();
  c2->cd();
  label->Draw("same");
  c2->SaveAs(output_path+filename);

  TCanvas *c4 = new TCanvas("c4","c4",2400,600);
  c4->Divide(4,1);
  c4->cd(1);
  mulc_tree->Draw("(cor_sam2+cor_sam6)/2/ppm ",user_cut);
  c4->cd(2);
  mulc_tree->Draw("(cor_sam4+cor_sam8)/2/ppm",user_cut);
  c4->cd(3);
  mulc_tree->Draw("(cor_sam2+cor_sam6)/2/ppm : (cor_sam4+cor_sam8)/2/ppm ",user_cut);
  c4->cd(4);
  mulc_tree->Draw("(cor_sam2+cor_sam6)/2/ppm - (cor_sam4+cor_sam8)/2/ppm ",user_cut);

  filename = Form("run%s_paired_sam_dd.png",run_seg.Data());
  label = new TText(0.0,0.01,filename);     
  label->SetTextSize(0.05);
  label->SetNDC();
  c4->cd();
  label->Draw("same");
  c4->SaveAs(output_path+filename);

  gSystem->Exec(Form("convert $(ls -rt %s/*paired_sam*.png) %s/run%s_summary_paired_sam.pdf",
		     output_path.Data(),
		     output_path.Data(),run_seg.Data()));
  gSystem->Exec(Form("rm %s/*paired_sam*.png ",output_path.Data()));
}

