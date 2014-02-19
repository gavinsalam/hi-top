
/// simple program to get a quick estimate of cross sections and a
/// handful of basic distributions from MC run and flat/HepMC/UW
/// files, etc.
///
#include "AnalysisFramework.hh"
#include "boost/foreach.hpp"
#define foreach BOOST_FOREACH


using namespace std;
using namespace fastjet;

double log10(double x) {return log(x)/log(10.0);}

/// Example class derived from AnalysisFramework that will help in evaluation of
/// some basic cross sections. 
class XSctAnalysis : public AnalysisFramework {
public:
  XSctAnalysis(CmdLine & cmdline) : AnalysisFramework(cmdline) {}
  void user_startup() {
    // extra user parameters
    param["missing.ptmin"] = 30.0;
    param["jet.ptmin"] = 20.0;
    param["jet.rapmax"] = 5.0;

    if (cmdline.present("-R")) jet_def = JetDefinition(antikt_algorithm, cmdline.value<double>("-R"));

    DefaultHist::set_defaults(0.0, 4.4, cmdline.value("-hist.binwidth",0.2));
  }

  void analyse_event() {
    // cout << "Cross section pointer: " 
    // 	 << driver->generator->gen_event()->cross_section()  << " "
    // 	 << driver->generator->gen_event()->weights().size()
    // 	 << endl;

    double evwgt = driver->generator->hadron_level().weight();
    xsections["total cross section"] += evwgt;

    averages["event multipliticity"] += evwgt * driver->generator->hadron_level().particles().size();

    // do a little bit of analysis
    anl->new_event(driver->generator->hadron_level());
    if (anl->emus.size() > 0) xsections["total e/mu cross section"] += evwgt;
    if (anl->missing.perp() > param["missing.ptmin"]) 
      xsections["total missing-pt cross section"] += evwgt;

    hists["log10-missing-pt"].add_entry(log10(anl->missing.perp()), evwgt);
    if (anl->emus.size() > 0) hists["log10-emu1-pt"].add_entry(log10(anl->emus[0].perp()), evwgt);
    
    if (abs(anl->jets[0].rap() - anl->jets[1].rap()) < 0.5) xsections["dy.jj<0.5"] += evwgt;
    
    vector<PseudoJet> cut_jets;
    for (unsigned i = 0; i < anl->jets.size(); i++) {
      if (abs(anl->jets[i].rap()) < param["jet.rapmax"] &&
          anl->jets[i].perp() > param["jet.ptmin"]) cut_jets.push_back(anl->jets[i]);
      if (i < 2) {
	hists["jet.mass"].set_lims_add_entry(0,300,5, anl->jets[i].m(), evwgt);
      }
    }
    if (cut_jets.size() > 0) hists["log10-jet1-pt"].add_entry(log10(cut_jets[0].perp()), evwgt);

    

    // now get ht sum
    double ht = 0;
    int njets = 0, nbjets=0;
    double jet_ptmin = param["jet.ptmin"];
    for (unsigned i = 0; i < cut_jets.size(); i++) {
      hists["incljet-pt"].set_lims_add_entry(10,1000,5.0,cut_jets[i].perp(),evwgt);
      ht += cut_jets[i].perp();
      njets++;
      if (anl->btagger.has_bs_weight(cut_jets[i]) > 0.99) nbjets++;
    }
    hists["njets"].set_lims_add_entry(-0.5, 12.5, 1.0, double(njets), evwgt);
    hists["nbjets"].set_lims_add_entry(-0.5, 12.5, 1.0, double(nbjets), evwgt);

    for (unsigned i = 0; i < anl->emus.size(); i++) ht += anl->emus[i].perp();
    // no pt cut on the missing pt included
    ht += anl->missing.perp(); 
    hists["log10-ht"].add_entry(log10(ht), evwgt);


    if (rootstr.get()) anl->cs->print_jets_for_root(anl->jets, *rootstr);
  }
};

//----------------------------------------------------------------------
int main (int argc, char ** argv) {
  
  CmdLine cmdline(argc,argv);
  XSctAnalysis analysis(cmdline);
  analysis.run();
}
