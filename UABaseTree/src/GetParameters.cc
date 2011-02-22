// Description: Function to retrieve the Parameters from the python file

// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"

bool ParametersDebug = false;


void UABaseTree::GetParameters(const edm::ParameterSet& iConfig){

   beamspots_      = iConfig.getUntrackedParameter<vector<InputTag> >("beamspots",vector<InputTag>());
   storeEvtId_     = iConfig.getUntrackedParameter<bool>("storeEvtId",false);
   calotower_      = iConfig.getUntrackedParameter<InputTag>("calotower",InputTag("towerMaker"));
   storeFwdGap_    = iConfig.getUntrackedParameter<bool>("storeFwdGap",false);
   hepmc_          = iConfig.getUntrackedParameter<InputTag>("hepmc",InputTag("generator::HLT"));
   genmet_         = iConfig.getUntrackedParameter<InputTag>("genmet",InputTag("genMetTrue"));
   genpart_        = iConfig.getUntrackedParameter<InputTag>("genpart",InputTag("genParticles"));
   storeGenKin_    = iConfig.getUntrackedParameter<bool>("storeGenKin",false);
   storeGenMet_    = iConfig.getUntrackedParameter<bool>("storeGenMet",false);
   storeGenPart_   = iConfig.getUntrackedParameter<bool>("storeGenPart",false);
   pusuminfo_      = iConfig.getUntrackedParameter<InputTag>("pusuminfo",InputTag("addPileupInfo"));
   storePUSumInfo_ = iConfig.getUntrackedParameter<bool>("storePUSumInfo",false);
   hlt_paths_      = iConfig.getUntrackedParameter<vector<string> >("hlt_paths",vector<string>());
   storeL1Trig_    = iConfig.getUntrackedParameter<bool>("storeL1Trig",false);
   storeL1TrigOld_ = iConfig.getUntrackedParameter<bool>("storeL1TrigOld",false);
   storeMITEvtSel_ = iConfig.getUntrackedParameter<bool>("storeMITEvtSel",false);
   tracks_         = iConfig.getUntrackedParameter<vector<InputTag> >("tracks",vector<InputTag>());
   vertices_       = iConfig.getUntrackedParameter<vector<InputTag> >("vertices",vector<InputTag>());
   vcalojets_      = iConfig.getUntrackedParameter<vector<PSet> >("vcalojets",vector<PSet>());
   vpfjets_        = iConfig.getUntrackedParameter<vector<PSet> >("vpfjets",vector<PSet>());
   genjets_        = iConfig.getUntrackedParameter<vector<InputTag> >("genjets",vector<InputTag>());
   
   castorrechits_  = iConfig.getUntrackedParameter<InputTag>("castorrechits",InputTag());
   basicjets_      = iConfig.getUntrackedParameter<InputTag>("basicjets",InputTag());
   castorjetid_    = iConfig.getUntrackedParameter<InputTag>("castorjetid",InputTag());
   castordigis_    = iConfig.getUntrackedParameter<InputTag>("castordigis",InputTag());
   
   electrons_      = iConfig.getUntrackedParameter<vector<InputTag> >("electrons",vector<InputTag>());
   muons_          = iConfig.getUntrackedParameter<vector<InputTag> >("muons",vector<InputTag>());
   
   
   //Specific for fwdGap
   energyThresholdHB_ = iConfig.getUntrackedParameter<double>("EnergyThresholdHB",1.5) ;
   energyThresholdHE_ = iConfig.getUntrackedParameter<double>("EnergyThresholdHE",2.0) ;
   energyThresholdHF_ = iConfig.getUntrackedParameter<double>("EnergyThresholdHF",4.0) ;
   energyThresholdEB_ = iConfig.getUntrackedParameter<double>("EnergyThresholdEB",1.5) ;
   energyThresholdEE_ = iConfig.getUntrackedParameter<double>("EnergyThresholdEE",2.5) ;

   //Specific for genPart
   saveMothersAndDaughters_    = iConfig.getUntrackedParameter<bool>("saveMothersAndDaughters",false);
   onlyStableGenPart_          = iConfig.getUntrackedParameter<bool>("onlyStableGenPart",false);
   onlyChargedGenPart_         = iConfig.getUntrackedParameter<bool>("onlyChargedGenPart_",false);
   enableGenMetFromGenPart_    = iConfig.getUntrackedParameter<bool>("enableGenMetFromGenPart",storeGenMet_);
   
   //Specific for PFJets
   storeTracksInPFJets_        = iConfig.getUntrackedParameter<bool>("storeTracksInPFJets",false);


   //Specific to DiJets
   jetPtCut_  = iConfig.getUntrackedParameter<double>("jetPtCut"   , 8.0);
   jetEtaCut_ = iConfig.getUntrackedParameter<double>("jetEtaCut" , 2.5);


   // Get output filename
   outputfilename_ = iConfig.getUntrackedParameter<string>("outputfilename","");

}
