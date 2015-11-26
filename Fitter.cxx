void Fitter() {

    TFile in_file("/nfs/lhcb/malexander01/charm/4pi/data/full-run-I/full_2011_data.root");
    TH1F* h=(TH1F*) in_file.GetObjectChecked("Dst2010ToD0TopipipipipiTuple/DecayTree","D0_M");
    h->DrawClone();

}
