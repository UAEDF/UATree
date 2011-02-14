#ifndef __MyTracks_H__
#define __MyTracks_H__

#include <vector>
#include "TObject.h"
#include "MyPart.h"

class MyTracks : public MyPart {

  public :
    MyTracks();
    virtual ~MyTracks();

    void Print();
    void Reset();

    Bool_t   quality[5];
    Int_t    trackAlgo;
    Int_t    nhit , nvalidhit , npixhit;
    Double_t chi2n;
    Double_t dz  , d0 ;
    Double_t edz , ed0 , ept ; 
    Double_t vx, vy, vz ;

    std::vector<Int_t>     vtxid;
    std::vector<Double_t>  vtxdxy  ;
    std::vector<Double_t>  vtxdz   ;

  private:

  ClassDef (MyTracks,1)
};

#endif

