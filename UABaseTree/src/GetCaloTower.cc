// Description: Function to retrieve CaloTowers

#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"
#include "DataFormats/CaloTowers/interface/CaloTowerDetId.h"

#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"

#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"

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

     bool hasEB = false;
     bool hasEE = false;

     bool hasHB = false;
     bool hasHE = false;
     bool hasHF = false;
     
     //-- loop over CaloTower constituents
     for(size_t iconst = 0; iconst < iCT->constituentsSize(); iconst++){
     
       DetId detId = iCT->constituent(iconst);

       if(detId.det()==DetId::Ecal){
         EcalSubdetector ecalSubDet = (EcalSubdetector)detId.subdetId();
	 if(ecalSubDet == EcalBarrel) hasEB = true;
         else if(ecalSubDet == EcalEndcap) hasEE = true;
       }

       else if(detId.det()==DetId::Hcal){
	 HcalDetId hcalDetId(detId);
	 if(hcalDetId.subdet()==HcalBarrel) hasHB = true;
	 else if(hcalDetId.subdet()==HcalEndcap) hasHE = true;
	 else if(hcalDetId.subdet()==HcalForward) hasHF = true;
       } 

     }

     caloTowers[i].zside = iCT->zside();

     if(hasEB && !hasEE) caloTowers[i].caloId = MyCaloTower::CaloType(1);
     else if(hasEE && !hasEB) caloTowers[i].caloId = MyCaloTower::CaloType(2);
        
     if(hasHB && !hasHE) caloTowers[i].caloId = MyCaloTower::CaloType(3);
     else if(hasHE && !hasHF && !hasHB) caloTowers[i].caloId = MyCaloTower::CaloType(4);
     else if(hasHF && !hasHE) caloTowers[i].caloId = MyCaloTower::CaloType(5);
     
     if(CaloTowerDebug) caloTowers[i].Print();

   } // end for CaloTowerCollection 

}
