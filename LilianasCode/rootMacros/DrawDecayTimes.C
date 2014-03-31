/*
 *  Draw3SubjetsObs.C
 *  
 *
 *  Created by Liliana Apolinário on 16/12/14.
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
	gStyle->SetOptStat(10001111);
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



void DrawDecayTimes(){

	//funcao de inicializacao
	init();
	
	//Auxiliar functions
	TPaveStats* p1;
	TPaveStats* p2;
	
	//Open files
	TFile *file_1 = new TFile("../results/pt500_En5TeV.root");
	string name = "", aux = "_ptW500_En5TeV";

	//Graphics
	TH1D* boost_top_max = file_1->Get("boost_en_top"); 
	TH1D* boost_top_min = file_1->Get("boost_pt_top");
	TH1D* boost_w_max = file_1->Get("boost_en_w");
	TH1D* boost_w_min = file_1->Get("boost_pt_w");
	
	TH1D* decay_distance_max = file_1->Get("decay_distance_en");
	TH1D* decay_distance_min = file_1->Get("decay_distance_pt");
	
	TH1D* distance_max = file_1->Get("total_distance_en");
	TH1D* distance_min = file_1->Get("total_distance_pt");
	
	
	//Personalizar
	boost_top_min->Rebin(2);
	boost_top_max->Rebin(2);
	boost_w_min->Rebin(2);
	boost_w_max->Rebin(2);
	decay_distance_min->Rebin(5);
	decay_distance_max->Rebin(5);
	distance_min->Rebin(5);
	distance_max->Rebin(5);

	boost_top_max->GetXaxis()->SetTitle("");
	boost_top_max->GetYaxis()->SetTitle("# events");
	boost_top_min->GetXaxis()->SetTitle("");
	boost_top_min->GetYaxis()->SetTitle("# events");
	boost_w_max->GetXaxis()->SetTitle("fm");
	boost_w_max->GetYaxis()->SetTitle("# events");
	boost_w_min->GetXaxis()->SetTitle("");
	boost_w_min->GetYaxis()->SetTitle("# events");
	decay_distance_max->GetXaxis()->SetTitle("fm");
	decay_distance_max->GetYaxis()->SetTitle("# events");
	decay_distance_min->GetXaxis()->SetTitle("fm");
	decay_distance_min->GetYaxis()->SetTitle("# events");
	distance_max->GetXaxis()->SetTitle("fm");
	distance_max->GetYaxis()->SetTitle("# events");
	distance_min->GetXaxis()->SetTitle("fm");
	distance_min->GetYaxis()->SetTitle("# events");
	
	boost_top_max->SetTitle("Boost Top");
	boost_top_min->SetTitle("Boost Top");
	boost_w_max->SetTitle("Boost W");
	boost_w_min->SetTitle("Boost W");
	decay_distance_max->SetTitle("Distance Top + W");
	decay_distance_min->SetTitle("Distance Top + W");
	distance_max->SetTitle("Distance Top + W + tcoh");
	distance_min->SetTitle("Distance Top + W + tcoh");
	
	boost_top_min->SetLineColor(kRed);
	boost_w_min->SetLineColor(kRed);
	decay_distance_min->SetLineColor(kRed);
	distance_min->SetLineColor(kRed);

	//Canvas
	TCanvas* cdec = new TCanvas("show");
	cdec->Divide(2,2);
	cdec->cd(1);
	boost_top_min->Draw();
	boost_top_max->Draw("SAMES");
	cdec->cd(2);
	boost_w_min->Draw();
	boost_w_max->Draw("SAMES");
	cdec->cd(3);
	decay_distance_min->Draw();
	decay_distance_max->Draw("SAMES");
	cdec->cd(4);
	distance_min->Draw();
	distance_max->Draw("SAMES");
	cdec->Modified();
	cdec->Update();
	
	p1 = (TPaveStats*)boost_top_min->GetListOfFunctions()->FindObject("stats");
	p2 = (TPaveStats*)boost_top_max->GetListOfFunctions()->FindObject("stats");
	movePadsY(p1,p2,kRed,kBlue);
	cdec->cd(1);
	boost_top_min->Draw();
	boost_top_max->Draw("SAMES");

	p1 = (TPaveStats*)boost_w_min->GetListOfFunctions()->FindObject("stats");
	p2 = (TPaveStats*)boost_w_max->GetListOfFunctions()->FindObject("stats");
	movePadsY(p1,p2,kRed,kBlue);
	cdec->cd(2);
	boost_w_min->Draw();
	boost_w_max->Draw("SAMES");

	p1 = (TPaveStats*)decay_distance_min->GetListOfFunctions()->FindObject("stats");
	p2 = (TPaveStats*)decay_distance_max->GetListOfFunctions()->FindObject("stats");
	movePadsY(p1,p2,kRed,kBlue);
	cdec->cd(3);
	decay_distance_min->Draw();
	decay_distance_max->Draw("SAMES");

	p1 = (TPaveStats*)distance_min->GetListOfFunctions()->FindObject("stats");
	p2 = (TPaveStats*)distance_max->GetListOfFunctions()->FindObject("stats");
	movePadsY(p1,p2,kRed,kBlue);
	cdec->cd(4);
	distance_min->Draw();
	distance_max->Draw("SAMES");
	
	name = "../Images/Decay" + aux + ".eps";
	//cdec->SaveAs(name.c_str());

	cout << "Done All!!" << endl;
	
}
