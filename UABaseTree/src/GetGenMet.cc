//-- Description: Function to retrieve Generated Met
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"


// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"


bool GenMetDebug = false;

void UABaseTree::GetGenMet(const edm::Event& iEvent)
{

  genMet.Reset();

  // Gen Met: From GenMETCollection
  Handle<GenMETCollection> genmet;
  iEvent.getByLabel(genmet_ , genmet);
  //iEvent.getByLabel("genMetTrue" , genmet);

  genMet.Met	= (genmet->front()).et() ; 
  genMet.MetX	= (genmet->front()).px() ; 
  genMet.MetY	= (genmet->front()).py() ; 
  genMet.MetPhi = (genmet->front()).phi() ; 



  // Gen Met: From GenPart Neutrinos ( no SUSY !!! )

  // ... Handle to access GenParticleCollection
  Handle<GenParticleCollection> genParticles;
  iEvent.getByLabel(genpart_, genParticles);
  if (!genParticles.isValid()) {
    cerr << "[UABaseTree::GetGenMet] Error: non valid GenParticleCollection " << endl;
    return;
  }
 
  double met1Px = 0 ;
  double met1Py = 0 ;
  double met1Pz = 0 ;
  double met1E  = 0 ;

  double met3Px = 0 ;
  double met3Py = 0 ;
  double met3Pz = 0 ;
  double met3E  = 0 ;

  // ... Loop on stable (final) particles
  for(GenParticleCollection::const_iterator p = genParticles->begin(); p != genParticles->end(); ++ p){
    int st  = p->status();
    int pid = p->pdgId();
    if ( st == 1 && ( abs(pid)==12 || abs(pid)==14 || abs(pid)==16 ) ){
      met1Px += p->px();
      met1Py += p->py();
      met1Pz += p->pz();
      met1E  += p->energy();
    } 
    else if ( st == 3 && ( abs(pid)==12 || abs(pid)==14 || abs(pid)==16 ) ){
      met3Px += p->px();
      met3Py += p->py();
      met3Pz += p->pz();
      met3E  += p->energy();
    }
  }

  // ... Set Missing Et 4-Vector
  genMet.MetGP1.SetPxPyPzE( met1Px , met1Py , met1Pz , met1E ) ;
  genMet.MetGP3.SetPxPyPzE( met3Px , met3Py , met3Pz , met3E ) ;

  if(GenMetDebug) genMet.Print();
}
