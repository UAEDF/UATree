// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"


UABaseTree::UABaseTree(const edm::ParameterSet& iConfig){
  //Getting all standard parameters
  this->GetParameters(iConfig);
   
  isValidHltConfig_ = false;
}


UABaseTree::~UABaseTree(){
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}


// ------------ method called to for each event  ------------
void
UABaseTree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  this->GetAll(iEvent , iSetup);
  tree->Fill(); 
}


// ------------ method called once each job just before starting event loop  ------------
void UABaseTree::beginJob(){
  this->Init();
}


//-- method called to for each run
void UABaseTree::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup){
  bool changed = true;
  isValidHltConfig_ = hltConfig.init(iRun,iSetup,"HLT",changed);
}



// ------------ method called once each job just after ending the event loop  ------------
void UABaseTree::endJob(){
   fout->Write() ;
   fout->Close() ;
}

//define this as a plug-in
DEFINE_FWK_MODULE(UABaseTree);
