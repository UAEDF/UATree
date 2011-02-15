// Description: Function to retrieve the Parameters from the python file

// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"

bool ParametersDebug = false;


void UABaseTree::GetParameters(const edm::ParameterSet& iConfig){

   beamspots_      = iConfig.getUntrackedParameter<vector<InputTag> >("beamspots",vector<InputTag>());
   storeEvtId_     = iConfig.getUntrackedParameter<bool>("storeEvtId",false);
   calotower_      = iConfig.getUntrackedParameter<InputTag>("calotower",InputTag(""));
   hepmc_          = iConfig.getUntrackedParameter<InputTag>("hepmc",InputTag(""));
   genmet_         = iConfig.getUntrackedParameter<InputTag>("genmet",InputTag(""));
   genpart_        = iConfig.getUntrackedParameter<InputTag>("genpart",InputTag(""));
   pusuminfo_      = iConfig.getUntrackedParameter<InputTag>("pusuminfo",InputTag(""));
   hlt_paths_      = iConfig.getUntrackedParameter<vector<string> >("hlt_paths",vector<string>());
   storeL1Trig_    = iConfig.getUntrackedParameter<bool>("storeL1Trig",false);
   storeL1TrigOld_ = iConfig.getUntrackedParameter<bool>("storeL1TrigOld",false);
   storeMITEvtSel_ = iConfig.getUntrackedParameter<bool>("storeMITEvtSel",false);
   tracks_         = iConfig.getUntrackedParameter<vector<InputTag> >("tracks",vector<InputTag>());
   vertices_       = iConfig.getUntrackedParameter<vector<InputTag> >("vertices",vector<InputTag>());
   vcalojets_      = iConfig.getUntrackedParameter<vector<PSet> >("vcalojets",vector<PSet>());
   
   
   //Specific for fwdGap
   energyThresholdHB_ = iConfig.getUntrackedParameter<double>("EnergyThresholdHB",0) ;
   energyThresholdHE_ = iConfig.getUntrackedParameter<double>("EnergyThresholdHE",0) ;
   energyThresholdHF_ = iConfig.getUntrackedParameter<double>("EnergyThresholdHF",0) ;
   energyThresholdEB_ = iConfig.getUntrackedParameter<double>("EnergyThresholdEB",0) ;
   energyThresholdEE_ = iConfig.getUntrackedParameter<double>("EnergyThresholdEE",0) ;

   //Specific for genPart
   saveMothersAndDaughters_    = iConfig.getUntrackedParameter<bool>("saveMothersAndDaughters",false);
   onlyStableGenPart_          = iConfig.getUntrackedParameter<bool>("onlyStableGenPart",false);
   onlyChargedGenPart_         = iConfig.getUntrackedParameter<bool>("onlyChargedGenPart_",false);
   
   //Specific for PFJets
   storeTracksInPFJets_        = iConfig.getUntrackedParameter<bool>("storeTracksInPFJets",false);


   // Get output filename
   outputfilename_ = iConfig.getUntrackedParameter<string>("outputfilename","");

}
