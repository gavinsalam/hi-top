/*
 *  Boost.cpp
 *  
 *
 *  Created by Liliana Apolinário on 18/12/14.
 *  Copyright 2014 Liliana Apolinario. All rights reserved.
 *
 */

/* 
 Check decay distance of boosted top --> b + W with W --> q qbar
 To check the effects of the medium, a coherence time of the qqbar antenna is also added 
 */


#include <cstdlib> // for exit function
#include <math.h>
#include <complex>
#include <string.h>
#include <sstream>
#include <iostream>

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"

#include "Pythia.h"

using namespace std;
using namespace Pythia8;

#define _USE_MATH_DEFINES
const double mine_pi = 4.0*atan(1.0);
const double gev = 1/0.2; //fm^{-1}

//MAIN FUNCTION
int main(int argc, char* argv[]) {

      // ******************** INPUT/OUTPUT *********************//
      string output;
      double ptmin = 200;

      cout << "Output filename?";
      cin >> output;
      cout << output << endl;
      cout << "Pt min of W boson?";
      cin >> ptmin;
      cout << ptmin << endl;

	
	// ********************* VARIABLES *********************** //
	Pythia pythia; //generator

	//Read from external file
	pythia.readFile(argv[1]);
	int nEvent = pythia.mode("Main:numberOfEvents");

	//Files
	TFile* outfile = new TFile(output.c_str(), "RECREATE");

	//Variables
	double const qhat = 4.*pow(gev, 2); //qhat = 4 GeV^2 fm^{-1}
	double const tau_top = 1/(2.*gev), tau_w = 1/(2.085*gev);

	int id_top = 6, id_wboson = 24, id_bottom = 5;
	int i_daughter1 = 0, i_daughter2 = 0;
	int i_top = 0, i_wboson = 0;
	double boost_top_en = 0., boost_top_pt = 0., boost_w_en = 0., boost_w_pt = 0.;
	double theta_qqbar = 0., coh_time = 0.;

	//Histograms
	TH1D* hist_boost_en_top = new TH1D("boost_en_top", "boost_top", 300, 0, 30);
	TH1D* hist_boost_pt_top = new TH1D("boost_pt_top", "boost_top", 300, 0, 30);
	TH1D* hist_boost_en_w = new TH1D("boost_en_w", "boost_w", 300, 0, 30);
	TH1D* hist_boost_pt_w = new TH1D("boost_pt_w", "boost_w", 300, 0, 30);

	TH1D* decay_distance_en = new TH1D("decay_distance_en", "decay_distance", 800, 0, 10);
	TH1D* decay_distance_pt = new TH1D("decay_distance_pt", "decay_distance", 800, 0, 10);
	TH1D* total_distance_en = new TH1D("total_distance_en", "total_distance", 800, 0, 10);
	TH1D* total_distance_pt = new TH1D("total_distance_pt", "total_distance", 800, 0, 10);
	TH1D decay_time("decay_time", "decay_time", 150, 0, 10);	
	TH1D decay_pos("decay_position", "decay_position", 150, 0, 10);	
	TH1D prod_time("prod_time", "prod_time", 150, 0, 10);	
	TH1D prod_pos("prod_position", "prod_position", 150, 0, 10);	

	
	// *************** RUN **************//
	pythia.init();

	//Generate events: event loop
	for (int iEvent = 0; iEvent < nEvent; iEvent++){
	//for (int iEvent = 0; iEvent < 10; iEvent++){

		pythia.next();

		//Just to be safe: if the generated particles are a ttbar
		//Entry 0 is the system, entries 1 and 2 are the beam, entries 3 and 4 are the consituents of the beam that scattered. Therefore, the reaction products start on 5 and 6
		if ( (pythia.event[5].id() == id_top && pythia.event[6].id() == -id_top) || (pythia.event[5].id() == -id_top && pythia.event[6].id() == id_top) ){
			
			//Put decay times (and distance) into the histogram of both t and tbar
			decay_time.Fill(pythia.event[5].tDec());
			decay_time.Fill(pythia.event[6].tDec());
			decay_pos.Fill(sqrt( pow(pythia.event[5].xDec(), 2) + pow(pythia.event[5].yDec(), 2) + pow(pythia.event[5].zDec(), 2) ));
			decay_pos.Fill(sqrt( pow(pythia.event[6].xDec(), 2) + pow(pythia.event[6].yDec(), 2) + pow(pythia.event[6].zDec(), 2) ));

			//select top
			if (pythia.event[5].id() == id_top) i_top = 5;
			else i_top = 6;

			//gamma = E/m, gammaT = mT/m
			boost_top_en = pythia.event[i_top].e()/pythia.event[i_top].m();
			boost_top_pt = pythia.event[i_top].mT()/pythia.event[i_top].m();

			i_daughter1 = i_top;
			i_daughter2 = i_top;

			//Retrieve daughters of t	
			while (i_daughter1 == i_daughter2){
				i_daughter1 = pythia.event[i_daughter1].daughter1();
				i_daughter2 = pythia.event[i_daughter2].daughter2();
			}

			//At this point, top decayed
			//If t --> W+ + b or t--> b + W+
			if ( (pythia.event[i_daughter1].id() == id_wboson && pythia.event[i_daughter2].id() == id_bottom && pythia.event[i_daughter1].pT() > ptmin) || ( pythia.event[i_daughter1].id() == id_bottom && pythia.event[i_daughter2].id() == id_wboson && pythia.event[i_daughter2].pT() > ptmin) ){

				//select wboson
				if (pythia.event[i_daughter1].id() == id_wboson) i_wboson = i_daughter1;
				else i_wboson = i_daughter2;

				boost_w_en = pythia.event[i_wboson].e()/pythia.event[i_wboson].m();
				boost_w_pt = pythia.event[i_wboson].pT()/pythia.event[i_wboson].m();

				//Put production time (and distances) into the histogram
				prod_time.Fill(pythia.event[i_wboson].tProd());
				prod_pos.Fill( sqrt( pow( pythia.event[i_wboson].xProd(), 2) + pow( pythia.event[i_wboson].yProd(), 2) + pow( pythia.event[i_wboson].zProd(), 2) ) );

				//Retrieve daughters of w+
				i_daughter1 = i_wboson;
				i_daughter2 = i_wboson;
				while (i_daughter1 == i_daughter2){
					i_daughter1 = pythia.event[i_daughter1].daughter1();
					i_daughter2 = pythia.event[i_daughter2].daughter2();
				}

				//Determine if the w+ decayed to qqbar or some e.m. channel (lepton + neutrino)
				if (abs(pythia.event[i_daughter1].id()) <= 8 && abs(pythia.event[i_daughter2].id()) <= 8 ){ 

					//theta = acos ( (p1.p2)/(|p1||p2|) )
					theta_qqbar = acos( (pythia.event[i_daughter1].px()*pythia.event[i_daughter2].px() + pythia.event[i_daughter1].py()*pythia.event[i_daughter2].py() + pythia.event[i_daughter1].pz()*pythia.event[i_daughter2].pz())/(sqrt(pow(pythia.event[i_daughter1].px(),2) + pow(pythia.event[i_daughter1].py(),2) + pow(pythia.event[i_daughter1].pz(),2) )*sqrt(pow(pythia.event[i_daughter2].px(),2) + pow(pythia.event[i_daughter2].py(),2) + pow(pythia.event[i_daughter2].pz(),2))) );
					//theta_qqbar = theta_qqbar - acos(1 - 2.*pow(pythia.event[i_wboson].m(),2)/pow(pythia.event[i_wboson].e(),2) );
					//theta_qqbar = 2*pythia.event[i_wboson].m()/pythia.event[i_wboson].pT();

					//cout << "theta = " << theta_qqbar << endl;
					coh_time = pow(12./(4*qhat*pow(theta_qqbar,2)), 1./3.);

					//Fill histograms
					hist_boost_en_w->Fill(boost_w_en);
					hist_boost_pt_w->Fill(boost_w_pt);
					hist_boost_en_top->Fill(boost_top_en);
					hist_boost_pt_top->Fill(boost_top_pt);
					decay_distance_en->Fill(tau_top*boost_top_en + tau_w*boost_w_en);
					decay_distance_pt->Fill(tau_top*boost_top_pt + tau_w*boost_w_pt);
					total_distance_en->Fill(tau_top*boost_top_en + tau_w*boost_w_en + coh_time);
					total_distance_pt->Fill(tau_top*boost_top_pt + tau_w*boost_w_pt + coh_time);

				}

			}

		}
	}

	//pythia.stat();
	outfile->cd();
	hist_boost_en_top->Write();
	hist_boost_pt_top->Write();
	hist_boost_en_w->Write();
	hist_boost_pt_w->Write();
	decay_distance_en->Write();
	decay_distance_pt->Write();
	total_distance_en->Write();
	total_distance_pt->Write();
	prod_time.Write();
	prod_pos.Write();
	decay_time.Write();
	decay_pos.Write();
	outfile->Close();

	cout << "DONE ALL" << endl;
	
	return 0;

}
