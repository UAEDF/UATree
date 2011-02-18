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
  if(enableGenMetFromGenPart_)       tree->Branch("genMetfromGenPartst1",&genMetfromGenPartst1);
  if(enableGenMetFromGenPart_)       tree->Branch("genMetfromGenPartst3",&genMetfromGenPartst3);
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
  InputTag       jetcoll_;
  string         dijetcoll_;
  vector<string> corrections_;
  for(vector<PSet>::iterator it = vcalojets_.begin() ; it != vcalojets_.end() ; ++it){
    jetcoll_ = it->getUntrackedParameter<InputTag>("jetcoll",InputTag());
    if(jetcoll_.label().size() > 0)
      this->tree->Branch( jetcoll_.label().c_str() , &(this->allCaloJets[jetcoll_.label()]) );
    
    //DiJets from this Jetcoll
    dijetcoll_   = it->getUntrackedParameter<string>("dijetcoll","");
    corrections_ = it->getUntrackedParameter<vector<string> >("corrections",vector<string>());
    if(find(corrections_.begin() , corrections_.end() , dijetcoll_) != corrections_.end())
      this->tree->Branch( string(dijetcoll_+"DiJet").c_str() , &(this->allDiJets[string(dijetcoll_+"DiJet")]) );
    
    
  }
    
     
  //RecoPFJets
  for(vector<PSet>::iterator it = vpfjets_.begin() ; it != vpfjets_.end() ; ++it){
    jetcoll_ = it->getUntrackedParameter<InputTag>("jetcoll",InputTag());
    if(jetcoll_.label().size() > 0)
      this->tree->Branch( jetcoll_.label().c_str() , &(this->allPFJets[jetcoll_.label()]) );
     
    //DiJets from this Jetcoll
    dijetcoll_   = it->getUntrackedParameter<string>("dijetcoll","");
    corrections_ = it->getUntrackedParameter<vector<string> >("corrections",vector<string>());
    if(find(corrections_.begin() , corrections_.end() , dijetcoll_) != corrections_.end())
      this->tree->Branch( string(dijetcoll_+"DiJet").c_str() , &(this->allDiJets[dijetcoll_+"DiJet"]) );

  }
  
    
     
  //RecoGenJets
  for(vector<InputTag>::iterator it = genjets_.begin() ; it != genjets_.end() ; ++it){
      this->tree->Branch( it->label().c_str() , &(this->allGenJets[it->label()]) );
  }
  
  
  
  //Castor
  if(castorrechits_.label().size() > 0)    tree->Branch("castorRecHits",&castorRecHits);
  if(basicjets_.label().size() > 0 &&
     castorjetid_.label().size() > 0)      tree->Branch("castorJets",&castorJets);
  if(castordigis_.label().size() > 0)      tree->Branch("castorDigis",&castorDigis);
  
  
    
}
