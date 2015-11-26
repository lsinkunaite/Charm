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
//TFile *file = new TFile("/nfs/lhcb/malexander01/charm/4pi/data/full-run-I/full_2011_data.root");
TFile *file = new TFile("/nfs/lhcb/malexander01/charm/baryon-lifetimes-2015/data/run-II-data/turbo_2015_data.root");
//TTree *tree = (TTree*) file->Get("Dst2010ToD0TopipipipipiTuple/DecayTree;1");
TTree *tree = (TTree*) file->Get("Lambda_cToKppiTuple/DecayTree;1");

//RooRealVar D0_M("D0_M","D0_M",1780,1950);
RooRealVar D0_M("Lambda_cplus_M","Lambda_cplus_M",2216,2356);

// --Constructors--
// const char* name,const char* title,const RooArgSet &vars,const char* wgtVarName = 0 (for an empty ds)
// const char* name,const char* title,TTree* intree,const RooArgSet& vars,const char* selExpr = 0,const char* wgtVarName = 0 (obtained from tree) 

//RooDataSet data("data","data",D0_M); // empty dataset to check whether fit works
RooDataSet data("data","data",tree,RooArgSet(D0_M)); // stops here***********************************************

// Gaussian signal PDF
//RooRealVar sigmean("sigmean","D^{0} mass",1865,1805,1925);
RooRealVar sigmean("sigmean","D^{0} mass",2250,2216,2356);
RooRealVar sigwidth("sigwidth","D^{0} width",10.,0.5,50.);
RooGaussian signal("signal","Signal PDF",D0_M,sigmean,sigwidth);

/*
// Linear background PDF
RooRealVar a_coeff("a_coeff","a_coeff",.5,0.,1.);
RooRealVar b_coeff("b_coeff","b_coeff",45000.,40000.,50000.);
RooPolynomial bkg("bkg","bkg",D0_M,RooArgSet(a_coeff,b_coeff));
*/

// Expo bakcground
RooRealVar expo("expo", "expo shape parameter", -0.1, -5., 0.); 
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
c.SaveAs("gediminas_data.pdf");
}
