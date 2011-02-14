// Description: Function to retrieve all the classes

// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"

bool AllDebug = false;


void UABaseTree::GetAll(const edm::Event& iEvent , const edm::EventSetup& iSetup){

  // General Info

                                    GetAllBeamSpots(iEvent);
  if(storeEvtId_)                   GetEvtId(iEvent);
  if(calotower_.label().size() > 0) GetFwdGap(iEvent); 

  if(hepmc_.label().size() > 0)     GetGenKin (iEvent);
  if(genpart_.label().size() > 0 &&
     genmet_ .label().size() > 0 )  GetGenMet (iEvent);
  if(genpart_.label().size() > 0)   GetGenPart(iEvent,iSetup);

  if(hlt_paths_.size() > 0)         GetHLTrig(iEvent,iSetup);
  if(storeL1Trig_)		    GetL1Trig(iEvent,iSetup);
  if(storeL1TrigOld_)		    GetL1TrigOld(iEvent);
  
 
  GetMITEvtSel(iEvent);


  // Reset vtx id and vector
  vtxid = 0;
  vtxid_xyz.clear();

  GetAllVertices(iEvent); // Needs to be before tracks !!
  GetAllTracks(iEvent); 
}

