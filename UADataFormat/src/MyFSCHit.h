#ifndef __MyFSCHit_H__
#define __MyFSCHit_H__

#include "TObject.h"

class MyFSCHit : public TObject {
  
 public :
   MyFSCHit();
  ~MyFSCHit();
  
  void Reset();
  void Print();
 
  Int_t section;
  Double_t energy;
  Double_t time;
  Int_t side; 

 private:
  ClassDef (MyFSCHit,1)
};

#endif
