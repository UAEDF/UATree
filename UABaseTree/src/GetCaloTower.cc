// Description: Function to retrieve CaloTowers

#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"

#include "UATree/UABaseTree/interface/UABaseTree.h"


Bool_t CaloTowerDebug = false;

void UABaseTree::GetCaloTower(const edm::Event& iEvent){

   caloTowers.clear();

   Handle<CaloTowerCollection> CaloTowers;
   try {
     iEvent.getByLabel(calotowercoll_,CaloTowers);
   }
   catch ( ... ) {
     cout << "[UABaseTree::GetCaloTower] Can't find the collection " << calotowercoll_ << endl;
   }
   
   caloTowers.assign( CaloTowers->size() , MyCaloTower() );

   Int_t i = 0;
   for (CaloTowerCollection::const_iterator iCT = CaloTowers->begin() ; iCT != CaloTowers->end() ; ++iCT , ++i) {
     
     caloTowers[i].SetPtEtaPhiE(iCT->pt() , iCT->eta() , iCT->phi() , iCT->energy() );
     caloTowers[i].emEnergy  = iCT->emEnergy();
     caloTowers[i].hadEnergy = iCT->hadEnergy();

     if(CaloTowerDebug) caloTowers[i].Print();


   } // end for CaloTowerCollection 

}
