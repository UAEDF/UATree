#ifndef __MyTrackJet_H__
#define __MyTrackJet_H__

#include "MyBaseJet.h"

class MyTrackJet : public MyBaseJet {

  public :
    MyTrackJet();
    ~MyTrackJet();

    virtual void Print();
    virtual void Reset();

    //RefById to associated vertex
    Int_t vtxId;

  private :
  
  ClassDef (MyTrackJet,1)
};

#endif


