// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"

void UABaseTree::Init(){


  fout = new TFile(outputfilename_.c_str(), "RECREATE" ) ;
  tree = new TTree("evt","evt");




  // --------------------   Setting all branches   --------------------

  // BeamSpots
  for(vector<InputTag>::iterator icoll = this->beamspots_.begin() ; icoll!= this->beamspots_.end() ; ++icoll){
    //this->allBeamSpots[icoll->label()] = MyBeamSpot();
    this->tree->Branch( icoll->label().c_str() , &(this->allBeamSpots[icoll->label()]) );
  }

  // General Event Info 
  if(storeEvtId_)		     tree->Branch("evtId",&evtId);
  if(storeFwdGap_)                   tree->Branch("fwdGap",&fwdGap);
  
  //MC Info
  if(storeGenKin_)                   tree->Branch("genKin",&genKin);
  if(storeGenMet_)                   tree->Branch("genMet",&genMet);
  if(storeGenPart_)                  tree->Branch("genPart",&genPart);
  if(storeGenPart_)                  tree->Branch("simVertex",&simVertex);
  if(storePUSumInfo_)                tree->Branch("PUSumInfo",&pusuminfo); 
 
  //Triggers
  if(hlt_paths_.size() > 0)	     tree->Branch("HLTrig",&HLTrig);
  if(storeL1Trig_)		     tree->Branch("L1Trig",&L1Trig);
  if(storeL1TrigOld_)		     tree->Branch("L1TrigOld",&L1TrigOld);
  
  //MITEvtSel
  if(storeMITEvtSel_)		     tree->Branch("MITEvtSel",&MITEvtSel);

  //RecoTracks
  for(vector<InputTag>::iterator icoll = this->tracks_.begin() ; icoll!= this->tracks_.end() ; ++icoll){
    //this->allTracks[icoll->label()] = vector<MyTracks>();
    this->tree->Branch( icoll->label().c_str() , &(this->allTracks[icoll->label()]) );
  }
    
  //RecoVertices
  for(vector<InputTag>::iterator icoll = this->vertices_.begin() ; icoll!= this->vertices_.end() ; ++icoll){
    //this->allVertices[icoll->label()] = vector<MyVertex>();
    this->tree->Branch( icoll->label().c_str() , &(this->allVertices[icoll->label()]) );
  }
     
  //RecoCaloJets
  vector<string> list_;
  for(vector<PSet>::iterator icoll = this->vcalojets_.begin() ; icoll!= this->vcalojets_.end() ; ++icoll){
    list_ = icoll->getUntrackedParameter<vector<string> >("list",vector<string>());
    if(list_.size() > 0)
      if(list_[0] != "")
        this->tree->Branch( list_[0].c_str() , &(this->allCaloJets[list_[0]]) );
  }
    
}
