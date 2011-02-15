// Description: Function to retrieve Generated Kinematic et al.

// DataFormats
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"


// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"


bool PUSumInfoDebug = false ;

void UABaseTree::GetPUSumInfo(const edm::Event& iEvent)
{

   pusuminfo.Reset();
   
   edm::Handle<PileupSummaryInfo> puInfoH;
   try {
     iEvent.getByLabel(pusuminfo_,puInfoH);
     pusuminfo.nPU = puInfoH->getPU_NumInteractions();
     cout << "nPU = " << puInfoH->getPU_NumInteractions() << " " << pusuminfo.nPU << endl;
     for(int i=0; i<puInfoH->getPU_NumInteractions(); i++){
       pusuminfo.zposition.push_back(puInfoH->getPU_zpositions()[i]);
       pusuminfo.sumpT_lowpT.push_back(puInfoH->getPU_sumpT_lowpT()[i]);
       pusuminfo.sumpT_highpT.push_back(puInfoH->getPU_sumpT_highpT()[i]);
       pusuminfo.ntrks_lowpT.push_back(puInfoH->getPU_ntrks_lowpT()[i]);
       pusuminfo.ntrks_highpT.push_back(puInfoH->getPU_ntrks_highpT()[i]);
     } 
 
   }
   catch (...){
     cout << "[UABaseTree::GetPUSumInfo] Was not able to retrieve PU Summary" << endl;
   }
   
   if(PUSumInfoDebug) pusuminfo.Print();
}

