#include "MyBaseJet.h"
#include <iostream>

using namespace std;

ClassImp(MyBaseJet)

MyBaseJet::MyBaseJet(){}

MyBaseJet::~MyBaseJet(){}

void MyBaseJet::Print(){
  (*((MyPart*) this)).Print();
  
  cout<<"correction - uncertainty: "<<endl;
  cout<<"jec: "<<this->jec<<endl;
  cout<<"jec_unc: "<<this->jec_unc<<endl;

}

void MyBaseJet::Reset(){
  (*((MyPart*) this)).Reset();
  
  jec     = 0;
  jec_unc = 0;
  
}
