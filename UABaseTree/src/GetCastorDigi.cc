//-- Description: Function to retrieve castor digi information


//-- Castor Digi
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDigi/interface/CastorDataFrame.h"
#include "DataFormats/HcalDetId/interface/HcalCastorDetId.h"

#include "UATree/UABaseTree/interface/UABaseTree.h"

bool CastorDigiDebug = true;

void UABaseTree::GetCastorDigi(const edm::Event& iEvent) {
    
  castorDigis.clear();
  MyCastorDigi mycastordigi;
  
  Handle<CastorDigiCollection> digicoll;
  iEvent.getByLabel(castordigis_,digicoll);
  
  if (CastorDigiDebug) cout<<"number of Castor Digi: "<<digicoll->size()<<endl;
  
  //-- loop over the digi collection (224 digis)
  for(size_t i = 0; i < digicoll->size(); i++) { 
    
    CastorDataFrame digi = (*digicoll)[i];
    HcalCastorDetId castorid = digi.id();

    mycastordigi.mod = castorid.module();
    mycastordigi.sec = castorid.sector();
    mycastordigi.cha = 16*(castorid.module()-1) + castorid.sector();
    
    //-- loop over the 6 or 10 time slices for each digi
    for (int ts = 0; ts < digi.size(); ts++) {   
      mycastordigi.adc.push_back(digi[ts].adc());
      mycastordigi.fC.push_back(digi[ts].nominal_fC());
    }
    
    castorDigis.push_back(mycastordigi);
    
    if (CastorDigiDebug) mycastordigi.Print();   
  }
}
