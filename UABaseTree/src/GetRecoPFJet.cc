//-- Description: Function to retrieve PF Jet information

//--DataFormats
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"

#include "DataFormats/JetReco/interface/JetID.h"
#include "DataFormats/Common/interface/ValueMap.h"

#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

#include "UATree/UABaseTree/interface/UABaseTree.h"

bool PFJetDebug = true;

void UABaseTree::GetRecoPFJets(const edm::Event& iEvent, const edm::EventSetup& iSetup, const PSet& pfjets_ , vector<MyPFJet>& JetVector){

  JetVector.clear();

  
  vector<string> list_ = pfjets_.getUntrackedParameter<vector<string> >("list",vector<string>());
  InputTag pfjetid_  = pfjets_.getUntrackedParameter<InputTag>("pfjetid",InputTag(""));
    
  Handle<PFJetCollection> raw;
  iEvent.getByLabel(list_[0],raw);
  
  //Initialize vector with number of jets
  JetVector.assign(raw->size() , MyPFJet());
    
  //filling raw collection
  Int_t i = 0;
  for (PFJetCollection::const_iterator jet = raw->begin(); jet != raw->end(); ++jet , ++i){
  
    JetVector[i].mapjet[list_[0]].v.SetPxPyPzE(jet->px() , jet->py() , jet->pz() , jet->energy() );
    
    JetVector[i].fhad_ch = jet->chargedHadronEnergyFraction();
    JetVector[i].fhad_ne = jet->neutralHadronEnergyFraction();

    JetVector[i].fem_ch = jet->chargedEmEnergyFraction();
    JetVector[i].fem_ne = jet->neutralEmEnergyFraction();

    JetVector[i].multi_ch = jet->chargedMultiplicity();
    JetVector[i].multi_ne = jet->neutralMultiplicity();

    JetVector[i].multi_ch_had = jet->chargedHadronMultiplicity();
    JetVector[i].multi_ne_had = jet->neutralHadronMultiplicity();

    JetVector[i].multi_gamma = jet->photonMultiplicity();
    JetVector[i].multi_ele = jet->electronMultiplicity();
    JetVector[i].multi_mu = jet->muonMultiplicity();


    //-- number of constituents (PFObject for PFjet, CaloTower for Calojet)
    JetVector[i].nconstituent = jet->getPFConstituents().size();
    
    
    //-- number of tracks (PFjet only)
    if(jet->getTrackRefs().isAvailable()){
      reco::TrackRefVector vtrackref = jet->getTrackRefs();
      JetVector[i].ntrack = vtrackref.size();
      if(storeTracksInPFJets_){
	JetVector[i].vtracks.assign(JetVector[i].ntrack , MyTracks());
        for(unsigned int i=0; i<vtrackref.size();i++)
          if(vtrackref.at(i).isAvailable())
	    this->FillTrack(*(vtrackref.at(i)) , JetVector[i].vtracks[i]);
      }
    }

    
    //-- jet ID
    JetVector[i].LooseJetId = GetLoosePFJetId(JetVector[i],list_[0]);
    JetVector[i].TightJetId = GetTightPFJetId(JetVector[i],list_[0]);

  }


  //start looping over corrections
  const JetCorrector* PFJetcorrector = NULL;
  for(unsigned int corr=1 ; corr < list_.size() ; ++corr){
  
    PFJetcorrector = JetCorrector::getJetCorrector(list_[corr],iSetup);
    
    //Filling corrected collection
    Int_t i = 0;
    for (PFJetCollection::const_iterator jet = raw->begin(); jet != raw->end(); ++jet , ++i){
      //-- correction 
      PFJet corrected_jet = *jet;                            //-- copy orignial jet
      Double_t jec = PFJetcorrector->correction(jet->p4());  //-- calculate correction 
      corrected_jet.scaleEnergy(jec);                          //-- apply correction
      JetVector[i].mapjet[list_[corr]].jec = jec;

      //-- uncertainty (function of the CORRECTED jet)
      //PFJetCorUnc->setJetEta(corrected_jet.eta());
      //PFJetCorUnc->setJetPt(corrected_jet.pt());
      //JetVector[i].mapjet[list_[corr]].jec_unc = PFJetCorUnc->getUncertainty(true);
      JetVector[i].mapjet[list_[corr]].v.SetPxPyPzE(corrected_jet.px() , corrected_jet.py() , corrected_jet.pz() , corrected_jet.energy() );
      
    }

    //JetCorrectionUncertainty *PFJetCorUnc(0);

    //ESHandle<JetCorrectorParametersCollection> PFJetCorParColl;
    //iSetup.get<JetCorrectionsRecord>().get(PFJetJECunc_,PFJetCorParColl);
    
    //JetCorrectorParameters const & PFJetCorPar = (*PFJetCorParColl)["Uncertainty"];
    //PFJetCorUnc = new JetCorrectionUncertainty(PFJetCorPar);

    //nPFJet = PFJetcoll->size();
  
  }
  

}


void UABaseTree::GetAllPFJets(const edm::Event& iEvent , const edm::EventSetup& iSetup){
  
  if(PFJetDebug) cout << "Number of PJet collections " << vpfjets_.size() << endl;
  vector<string> list_;
  for(vector<PSet>::iterator it = vpfjets_.begin() ; it != vpfjets_.end() ; ++it){
    list_ = it->getUntrackedParameter<vector<string> >("list",vector<string>());
    if(list_.size() > 0)
      if(list_[0] != "")
        this->GetRecoPFJets(iEvent , iSetup , *it , this->allPFJets[list_[0]] );  
  }
}


// -------------------------------------------------------------------------------------------------------------------------------------------


Bool_t UABaseTree::GetLoosePFJetId(const MyPFJet& myjet , const string& raw_coll) {

  //DON'T EXIST
  //ALWAYS RETURNS 1

  return true;
}


Bool_t UABaseTree::GetTightPFJetId(const MyPFJet& myjet , const string& raw_coll) {

  //-- parameters for the selection

  double fhad_ne_CutUp;
  double fem_ne_CutUp;

  double fhad_ch_CutLow;
  double fem_ch_CutUp;

  unsigned int nconstituent_CutLow;
  int multi_ch_CutLow;

  //-- retrieve the parameters

  fhad_ne_CutUp = ParaSetTightPFJetID_.getUntrackedParameter<double>("fhad_ne_CutUp",0);
  fem_ne_CutUp = ParaSetTightPFJetID_.getUntrackedParameter<double>("fem_ne_CutUp",0);

  fhad_ch_CutLow = ParaSetTightPFJetID_.getUntrackedParameter<double>("fhad_ch_CutLow",0);
  fem_ch_CutUp = ParaSetTightPFJetID_.getUntrackedParameter<double>("fem_ch_CutUp",0);

  nconstituent_CutLow = ParaSetTightPFJetID_.getUntrackedParameter<int>("nconstituent_CutLow",0);
  multi_ch_CutLow = ParaSetTightPFJetID_.getUntrackedParameter<int>("multi_ch_CutLow",0);

  //-- thight selection for PF jet

  Bool_t accept = false;

  //-- selection depends on f_nh, f_ne and nconstituent
  if(myjet.fhad_ne < fhad_ne_CutUp && myjet.fem_ne < fem_ne_CutUp && myjet.nconstituent > nconstituent_CutLow) {

    //-- inside tracker acceptance, selection depends on f_ce, f_ch and multi_c
    if(fabs(myjet.mapjet.find(raw_coll)->second.v.Eta()) < 2.4) {
      if(myjet.fem_ch < fem_ch_CutUp && myjet.fhad_ch > fhad_ch_CutLow && myjet.multi_ch > multi_ch_CutLow)
        accept = true;
    }

    //-- outside tracker acceptance, jet accepted without f_ce, f_ch and multi_c
    else accept = true;
  }

  return(accept);

}
