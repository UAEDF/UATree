#ifndef __MyCaloTower_H__
#define __MyCaloTower_H__

#include <string>
#include "MyPart.h"

using namespace std;

class MyCaloTower : public MyPart {

  public :
    MyCaloTower();
    ~MyCaloTower();

    virtual void Reset();
    virtual void Print();
    
    Double_t emEnergy;
    Double_t hadEnergy;

    enum CaloType {
      X=0,             //-- undefined
      EB=1,EE=2,       //-- ECAL 
      HB=3,HE=4,HF=5   //-- HCAL
    };

    CaloType caloId;
    
    Int_t zside;
    
  private:

  ClassDef (MyCaloTower,1)
};

#endif
