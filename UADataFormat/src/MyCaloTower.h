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
    
  private:

  ClassDef (MyCaloTower,1)
};

#endif
