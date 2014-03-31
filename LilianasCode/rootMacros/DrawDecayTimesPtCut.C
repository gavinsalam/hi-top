/*
 *  DrawDecayTimesPtCut.C
 *  
 *
 *  Created by Liliana Apolinário on 31/03/14.
 *  Copyright 2014 Liliana Apolinário. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>


// ----------------------------------
// funcao para escolher estilos gerais
// ----------------------------------
void init() {

	gROOT->SetStyle("Plain");
	gStyle->SetCanvasColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetPalette(1);
	//gStyle->SetOptStat(10001111);
	gStyle->SetOptStat(0);
}

void movePadsY(TPaveStats* p1, TPaveStats* p2, Color_t color1, Color_t color2){

	Double_t y1 = p1->GetY1NDC();
	Double_t y2 = p1->GetY2NDC();
			
	p2->SetY2NDC(y1-0.03);
	p2->SetY1NDC(y1-0.03-(y2-y1));
	
	y1 = p2->GetY1NDC();
	y2 = p2->GetY2NDC();
			
	p1->SetLineColor(color1);
	p1->SetTextColor(color1);

	p2->SetLineColor(color2);
	p2->SetTextColor(color2);

}

void setPadCoordinates(TPaveStats* p1, double x1, double x2, double y1, double y2, Color_t color){

	p1->SetX1NDC(x1);
	p1->SetX2NDC(x2);
	p1->SetY1NDC(y1);
	p1->SetY2NDC(y2);
		
	p1->SetLineColor(color);
	p1->SetTextColor(color);
	
}



void DrawDecayTimesPtCut(){

	//funcao de inicializacao
	init();
	
	//Auxiliar functions
	TPaveStats* p1;
	TPaveStats* p2;
	
	//Open files
	TFile *file_1 = new TFile("../results/pt0_En100TeV.root");
	TFile *file_2 = new TFile("../results/pt200_En100TeV.root");
	TFile *file_3 = new TFile("../results/pt300_En100TeV.root");
	TFile *file_4 = new TFile("../results/pt500_En100TeV.root");

	//Graphics
	TH1D* decay_distance_max_1 = file_1->Get("decay_distance_en");
	TH1D* decay_distance_min_1 = file_1->Get("decay_distance_pt");
	TH1D* distance_max_1 = file_1->Get("total_distance_en");
	TH1D* distance_min_1 = file_1->Get("total_distance_pt");
	TH1D* decay_distance_max_2 = file_2->Get("decay_distance_en");
	TH1D* decay_distance_min_2 = file_2->Get("decay_distance_pt");
	TH1D* distance_max_2 = file_2->Get("total_distance_en");
	TH1D* distance_min_2 = file_2->Get("total_distance_pt");
	TH1D* decay_distance_max_3 = file_3->Get("decay_distance_en");
	TH1D* decay_distance_min_3 = file_3->Get("decay_distance_pt");
	TH1D* distance_max_3 = file_3->Get("total_distance_en");
	TH1D* distance_min_3 = file_3->Get("total_distance_pt");
	TH1D* decay_distance_max_4 = file_4->Get("decay_distance_en");
	TH1D* decay_distance_min_4 = file_4->Get("decay_distance_pt");
	TH1D* distance_max_4 = file_4->Get("total_distance_en");
	TH1D* distance_min_4 = file_4->Get("total_distance_pt");
	
	
	//Personalizar
	decay_distance_min_1->Rebin(4);
	decay_distance_max_1->Rebin(5);
	distance_min_1->Rebin(5);
	distance_max_1->Rebin(5);
	decay_distance_min_2->Rebin(5);
	decay_distance_max_2->Rebin(5);
	distance_min_2->Rebin(5);
	distance_max_2->Rebin(5);
	decay_distance_min_3->Rebin(4);
	decay_distance_max_3->Rebin(5);
	distance_min_3->Rebin(5);
	distance_max_3->Rebin(8);
	decay_distance_min_4->Rebin(5);
	decay_distance_max_4->Rebin(8);
	distance_min_4->Rebin(8);
	distance_max_4->Rebin(8);

      decay_distance_min_1->Scale(1./decay_distance_min_1->GetBinWidth(1));
      decay_distance_max_1->Scale(1./decay_distance_max_1->GetBinWidth(1));
      distance_min_1->Scale(1./distance_min_1->GetBinWidth(1));
      distance_max_1->Scale(1./distance_max_1->GetBinWidth(1));
      decay_distance_min_2->Scale(1./decay_distance_min_2->GetBinWidth(1));
      decay_distance_max_2->Scale(1./decay_distance_max_2->GetBinWidth(1));
      distance_min_2->Scale(1./distance_min_2->GetBinWidth(1));
      distance_max_2->Scale(1./distance_max_2->GetBinWidth(1));
      decay_distance_min_3->Scale(1./decay_distance_min_3->GetBinWidth(1));
      decay_distance_max_3->Scale(1./decay_distance_max_3->GetBinWidth(1));
      distance_min_3->Scale(1./distance_min_3->GetBinWidth(1));
      distance_max_3->Scale(1./distance_max_3->GetBinWidth(1));
      decay_distance_min_4->Scale(1./decay_distance_min_4->GetBinWidth(1));
      decay_distance_max_4->Scale(1./decay_distance_max_4->GetBinWidth(1));
      distance_min_4->Scale(1./distance_min_4->GetBinWidth(1));
      distance_max_4->Scale(1./distance_max_4->GetBinWidth(1));

	decay_distance_max_1->GetXaxis()->SetTitle("#tau (fm)");
	decay_distance_max_1->GetYaxis()->SetTitle("dN/d#tau");
	//decay_distance_max_1->SetAxisRange(0, 5, "X");
	decay_distance_min_1->GetXaxis()->SetTitle("#tau (fm)");
	decay_distance_min_1->GetYaxis()->SetTitle("dN/d#tau");
      //decay_distance_min_1->SetAxisRange(0, 4, "X");
	distance_max_1->GetXaxis()->SetTitle("#tau (fm)");
	distance_max_1->GetYaxis()->SetTitle("dN/d#tau");
	//distance_max_1->SetAxisRange(0, 7, "X");
	distance_min_1->GetXaxis()->SetTitle("#tau (fm)");
	distance_min_1->GetYaxis()->SetTitle("dN/d#tau");
      //distance_min_1->SetAxisRange(0, 5, "X");
	
	decay_distance_max_1->SetTitle("Maximum Decay Distance (boost with Energy)");
	decay_distance_min_1->SetTitle("Minimum Decay Distance (boost with pT)");
	distance_max_1->SetTitle("Max Decay Distance + coherence time");
	distance_min_1->SetTitle("Min Decay Distance + coherence time");
	
	decay_distance_min_1->SetLineColor(kRed-3);
	distance_min_1->SetLineColor(kRed-3);
	decay_distance_max_1->SetLineColor(kRed-3);
	distance_max_1->SetLineColor(kRed-3);
	decay_distance_min_2->SetLineColor(kAzure+7);
	//decay_distance_min_2->SetFillColor(kAzure+7);
	//decay_distance_min_2->SetFillStyle(3350);
	distance_min_2->SetLineColor(kAzure+7);
	decay_distance_max_2->SetLineColor(kAzure+7);
	distance_max_2->SetLineColor(kAzure+7);
	decay_distance_min_3->SetLineColor(kGreen+3);
	//decay_distance_min_3->SetFillColor(kGreen+3);
	//decay_distance_min_3->SetFillStyle(3944);
	distance_min_3->SetLineColor(kGreen+3);
	decay_distance_max_3->SetLineColor(kGreen+3);
	distance_max_3->SetLineColor(kGreen+3);
	decay_distance_min_4->SetLineColor(kViolet-4);
	//decay_distance_min_4->SetFillColor(kViolet-4);
	//decay_distance_min_4->SetFillStyle(3344);
	distance_min_4->SetLineColor(kViolet-4);
	decay_distance_max_4->SetLineColor(kViolet-4);
	distance_max_4->SetLineColor(kViolet-4);

      //TLegend
      TLegend* leg = new TLegend(0.5, 0.5, 0.85, 0.85);
      leg->SetHeader("En = 100 TeV (FHC)");
      leg->AddEntry(decay_distance_min_1, "PtMin(W) = 0 GeV", "l");
      leg->AddEntry(decay_distance_min_2, "PtMin(W) = 200 GeV", "l");
      leg->AddEntry(decay_distance_min_3, "PtMin(W) = 300 GeV", "l");
      leg->AddEntry(decay_distance_min_4, "PtMin(W) = 500 GeV", "l");
      leg->SetFillColor(kWhite);

	//Canvas
	TCanvas* cdec = new TCanvas("show");
	cdec->Divide(2,2);
	cdec->cd(1);
      gPad->SetLogy();
	decay_distance_min_1->Draw();
	decay_distance_min_2->Draw("SAME");
	decay_distance_min_3->Draw("SAME");
	decay_distance_min_4->Draw("SAME");
      leg->Draw();
	cdec->cd(2);
      gPad->SetLogy();
	distance_min_1->Draw();
	distance_min_2->Draw("SAME");
	distance_min_3->Draw("SAME");
	distance_min_4->Draw("SAME");
      cdec->cd(3);
      gPad->SetLogy();
	decay_distance_max_1->Draw();
	decay_distance_max_2->Draw("SAME");
	decay_distance_max_3->Draw("SAME");
	decay_distance_max_4->Draw("SAME");
      cdec->cd(4);
      gPad->SetLogy();
	distance_max_1->Draw();
	distance_max_2->Draw("SAME");
	distance_max_3->Draw("SAME");
	distance_max_4->Draw("SAME");
	
	cout << "Done All!!" << endl;
	
}
