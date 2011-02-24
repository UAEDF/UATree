#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"


template <class T,class U>
void UABaseTree::FillJetCorrections(const EventSetup& iSetup , const vector<T>& raw , const vector<string>& corrections_ , vector<U>& JetVector ){

  //start looping over corrections
  const JetCorrector* Jetcorrector = NULL;
  for(unsigned int corr=0 ; corr < corrections_.size() ; ++corr){

    try{  
      Jetcorrector = JetCorrector::getJetCorrector(corrections_[corr],iSetup);
    
      //Filling corrected collection
      Int_t i = 0;
      for (typename vector<T>::const_iterator jet = raw.begin(); jet != raw.end(); ++jet , ++i){
        //-- correction 
        T corrected_jet = *jet;                              //-- copy orignial jet
        Double_t jec = Jetcorrector->correction(jet->p4());  //-- calculate correction 
        corrected_jet.scaleEnergy(jec);                      //-- apply correction
        JetVector[i].mapjet[corrections_[corr]].jec = jec;

        //-- uncertainty (function of the CORRECTED jet)
        //PFJetCorUnc->setJetEta(corrected_jet.eta());
        //PFJetCorUnc->setJetPt(corrected_jet.pt());
        //JetVector[i].mapjet[list_[corr]].jec_unc = PFJetCorUnc->getUncertainty(true);
        JetVector[i].mapjet[corrections_[corr]].SetPxPyPzE(corrected_jet.px() , corrected_jet.py() , corrected_jet.pz() , corrected_jet.energy() );
      }
    }
    catch(...){
      cout << "Please provide an ESSource for coll " << corrections_[corr] << endl;
    }
  }
    
}
