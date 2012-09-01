//-- Description: Function to retrieve FSC rec. hit information

//-- Castor RecHit
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalRecHit/interface/ZDCRecHit.h"

#include "UATree/UABaseTree/interface/UABaseTree.h"

bool FSCInfoDebug = false;

void UABaseTree::GetFSCInfo(const edm::Event& event) {

   fscInfo.Reset();
   fscHits.clear();

   // Get the ZDC rechits collection from the event
   edm::Handle<ZDCRecHitCollection> recoZDChits;
   event.getByLabel(fscrechits_, recoZDChits);

   if( !recoZDChits.isValid() ) return;

   const ZDCRecHitCollection* zdchits = recoZDChits.product();
   ZDCRecHitCollection::const_iterator zdchit;

   MyFSCHit myfschit;
   int nFSChitCand = 0;
   double FSCsumHADminus = 0.;
   double FSCsumEMminus = 0.;
   double FSCsumHADplus = 0.;
   double FSCsumEMplus = 0.;
   for ( zdchit = zdchits->begin(); zdchit != zdchits->end(); ++zdchit )
   {
      HcalZDCDetId id(zdchit->id());
      int side      = (zdchit->id()).zside();
      int section   = (zdchit->id()).section();
      double energy = zdchit->energy();
      double time = zdchit->time();

      if((section == 1) && (side == 1))  FSCsumEMplus   += energy;
      if((section == 1) && (side == -1)) FSCsumEMminus  += energy;
      if((section == 2) && (side == 1))  FSCsumHADplus  += energy;
      if((section == 2) && (side == -1)) FSCsumHADminus += energy;
      ++nFSChitCand;

      if(storeFSCHits_){
         myfschit.Reset();
	 myfschit.side = side;
	 myfschit.section = section;
	 myfschit.energy = energy;
	 myfschit.time = time;
	 fscHits.push_back(myfschit);
	 if (FSCInfoDebug) fscHits.back().Print();   
      }
   }

   fscInfo.nHits = nFSChitCand;
   fscInfo.sumEnergyEMPlus = FSCsumEMplus;
   fscInfo.sumEnergyEMMinus = FSCsumEMminus;
   fscInfo.sumEnergyHADPlus = FSCsumHADplus;
   fscInfo.sumEnergyHADMinus = FSCsumHADminus;
   if (FSCInfoDebug) fscInfo.Print();   
}
