// Description: Function to retrieve Generated particles from HEPEVT

// system include files
#include <memory>
   
// DataFormats
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

// UABaseTree Analysis class declaration
#include "UATree/UABaseTree/interface/UABaseTree.h"

bool GenPartDebug = false ;

void UABaseTree::GetGenPart(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  // Clear GenPart List
  // (evt->GenPart).clear();
  genPart.clear();

  // Handle to access PDG data from iSetup
  ESHandle <ParticleDataTable> pdt;
  iSetup.getData( pdt );

  // Handle to access GenParticleCollection
  Handle<GenParticleCollection> genParticles;
  iEvent.getByLabel(genpart_, genParticles);
  if (!genParticles.isValid()) {
    cerr << "[UABaseTree::GetGenPart] Error: non valid GenParticleCollection " << endl;
    return;
  }

  // List for Daugther/Mother Search
  vector<const reco::Candidate *> cands;
  vector<const Candidate *>::const_iterator found = cands.begin();
  if(saveMothersAndDaughters_){
    for(GenParticleCollection::const_iterator p = genParticles->begin(); p != genParticles->end(); ++p)
      cands.push_back(&*p);
  }

  //-- position of the simulated primary vertex
  math::XYZPoint PosPVsim = (*genParticles)[2].vertex();
  simVertex.x = PosPVsim.X();
  simVertex.y = PosPVsim.Y();
  simVertex.z = PosPVsim.Z();
  if(GenPartDebug) simVertex.Print();
  
  

  // Loop on generated particle
  if ( GenPartDebug )
    cout << "GenPart # : " << genParticles->size() << endl;
  
  MyGenPart mygenpart;
  for(GenParticleCollection::const_iterator p = genParticles->begin(); p != genParticles->end(); ++p) {
    
    mygenpart.Reset();
    
    int st = p->status();

    //Filling inherited from MyPart
    mygenpart.v.SetPxPyPzE( p->px() , p->py() , p->pz() , p->energy() );
    mygenpart.charge  = p->charge();

    // Extra properties
    mygenpart.pdgId   = p->pdgId();
    //mygenpart.name    = (pdt->particle(p->pdgId()))->name(); //FIXME : crashes the code ...
    mygenpart.status  = st;

    // Mother Daughter relations
    if(saveMothersAndDaughters_){
      int nMo = p->numberOfMothers();
      int nDa = p->numberOfDaughters();

      found = find(cands.begin(), cands.end(), p->mother(0));
      if(found != cands.end()) mygenpart.mo1 = found - cands.begin() ;
 
      found = find(cands.begin(), cands.end(), p->mother(nMo-1));
      if(found != cands.end()) mygenpart.mo2 = found - cands.begin() ;

      found = find(cands.begin(), cands.end(), p->daughter(0));
      if(found != cands.end()) mygenpart.da1 = found - cands.begin() ;
 
      found = find(cands.begin(), cands.end(), p->daughter(nDa-1));
      if(found != cands.end()) mygenpart.da2 = found - cands.begin() ;
    } 

    Bool_t store = true;
    if( onlyStableGenPart_  && st!=1)                    store = false;
    if( onlyChargedGenPart_ && fabs(mygenpart.charge) < 1) store = false;
    
    if(store) genPart.push_back(mygenpart);
    
    if(GenPartDebug && store) mygenpart.Print();

  }

}
