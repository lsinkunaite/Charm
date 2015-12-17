#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

// ROOT
#include "TH1D.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TTree.h"

// RooFit
#include "RooPlot.h"
#include "RooGaussian.h"
#include "RooDataHist.h"
#include "RooRealVar.h"
#include "RooDataSet.h"

using namespace RooFit;
using namespace std;

void mass_fit()
{
TFile *file = new TFile("/nfs/lhcb/malexander01/charm/4pi/data/full-run-I/full_2011_data.root");
TTree *tree = (TTree*) file->Get("Dst2010ToD0TopipipipipiTuple/DecayTree;1");
tree->SetBranchStatus("*", 0) ;
tree->SetBranchStatus("D0_M", 1) ;
tree->SetBranchStatus("D0_L0HadronDecision_TOS", 1);
tree->SetBranchStatus("lab0_L0Global_TIS", 1);
tree->SetBranchStatus("D0_Hlt1TrackAllL0Decision_TOS", 1);
tree->SetBranchStatus("lab0_Hlt2CharmHadD02HHHHDecision_TOS", 1);
tree->SetBranchStatus("piplus_P", 1);
tree->SetBranchStatus("piplus_PT",1);

//RooRealVar D0_M("D0_M","D0_M",1780,1950);
RooRealVar D0_M("D0_M","D0_M",1805,1925);
RooRealVar D0_L0HadronDecision_TOS("D0_L0HadronDecision_TOS","D0_L0HadronDecision_TOS",0,2);
RooRealVar lab0_L0Global_TIS("lab0_L0Global_TIS","lab0_L0Global_TIS",0,2);
RooRealVar lab0_Hlt2CharmHadD02HHHHDecision_TOS("lab0_Hlt2CharmHadD02HHHHDecision_TOS","lab0_Hlt2CharmHadD02HHHHDecision_TOS",0,2);
RooRealVar D0_Hlt1TrackAllL0Decision_TOS("D0_Hlt1TrackAllL0Decision_TOS","D0_Hlt1TrackAllL0Decision_TOS",0,2);
RooRealVar piplus_P("piplus_P","piplus_P",0,20e6);
RooRealVar piplus_PT("piplus_PT","piplus_PT",0,540e3);

// --Constructors--
// const char* name,const char* title,const RooArgSet &vars,const char* wgtVarName = 0 (for an empty ds)
// const char* name,const char* title,TTree* intree,const RooArgSet& vars,const char* selExpr = 0,const char* wgtVarName = 0 (obtained from tree) 

//RooDataSet data("data","data",tree,RooArgSet(D0_M,lab0_Hlt2CharmHadD02HHHHDecision_TOS));
RooDataSet data("data","data",RooArgSet(D0_M,D0_L0HadronDecision_TOS,lab0_L0Global_TIS,lab0_Hlt2CharmHadD02HHHHDecision_TOS,D0_Hlt1TrackAllL0Decision_TOS,piplus_P,piplus_PT),Import(*tree),Cut("(D0_L0HadronDecision_TOS||lab0_L0Global_TIS)&&lab0_Hlt2CharmHadD02HHHHDecision_TOS&&D0_Hlt1TrackAllL0Decision_TOS&&(piplus_P>3000)&&(piplus_PT>350)"));
//RooDataSet data = data.reduce("lab0_Hlt2CharmHadD02HHHHDecision_TOS && D0_Hlt1TrackAllL0Decision_TOS && (lab0_L0Global_TIS || D0_L0HadronDecision_TOS) && piplus_P > 3000 && piplus_PT > 350");

// Gaussian signal PDF
RooRealVar sigmean("sigmean","D^{0} mass",1865,1805,1925);
RooRealVar sigwidth("sigwidth","D^{0} width",2.5,0.,10.);
RooGaussian signal("signal","Signal PDF",D0_M,sigmean,sigwidth);

/*
// Linear background PDF
RooRealVar a_coeff("a_coeff","a_coeff",.5,0.,1.);
RooRealVar b_coeff("b_coeff","b_coeff",45000.,40000.,50000.);
RooPolynomial bkg("bkg","bkg",D0_M,RooArgSet(a_coeff,b_coeff));
*/

// Expo bakcground
RooRealVar expo("expo", "expo shape parameter", 0., -10., 10.); 
RooExponential bkg("bkg", "bkg", D0_M, expo); 

RooRealVar bkgfrac("bkgfrac","bkgfrac",.9,0.,1.);
RooAddPdf model("model", "Sg+Bkg",RooArgList(signal,bkg),bkgfrac);

model.fitTo(data);
//model.fitTo(data, Extended(),NumCPU(6)); 

TCanvas c;
RooPlot* frame = D0_M.frame();
data.plotOn(frame);
model.plotOn(frame);
frame->Draw();
c.SaveAs("D0_mass_fit_all_cuts.eps");
}
