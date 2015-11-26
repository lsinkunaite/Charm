#ifndef __CINT__
#include "RooGlobalFun.h"
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

void D_mass_fit()
{
// Create variables to load from the ntuple.
RooRealVar D0_M("D0_M","D0_M",1850,1860);
RooArgSet ntupleVarSet(D0_M);

TFile* file = new TFile("/nfs/lhcb/malexander01/charm/4pi/data/full-run-I/full_2011_data.root");
TTree* tree = file->Get("Dst2010ToD0TopipipipipiTuple/DecayTree;1");
RooDataSet data("ntuple_of_D_candidates","ntuple of D candidates",tree,ntupleVarSet);
}


