//-- Description: Function to retrieve Generated Met
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"


// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"


bool GenMetDebug = false;

void UABaseTree::GetGenMet(const edm::Event& iEvent )
{

  genMet.Reset();

  // Gen Met: From GenMETCollection
  Handle<GenMETCollection> genmet;
  iEvent.getByLabel(genmet_ , genmet);
  //iEvent.getByLabel("genMetTrue" , genmet);

  genMet.SetPxPyPzE( genmet->front().px() ,  genmet->front().py() , genmet->front().pz() , genmet->front().energy() );
  
  if(GenMetDebug) genMet.Print();
}
