#include "MyFSCInfo.h"
#include <iostream>

using namespace std;

ClassImp(MyFSCInfo)

MyFSCInfo::MyFSCInfo(){
  this->Reset();
}

MyFSCInfo::~MyFSCInfo(){}

void MyFSCInfo::Reset() {
  nHits             = 0;
  sumEnergyEMPlus   = 0.;
  sumEnergyEMMinus  = 0.;
  sumEnergyHADPlus  = 0.;
  sumEnergyHADMinus = 0.;
}

void MyFSCInfo::Print() {
  cout << "nHits: " << this->nHits << endl;
  cout << "sumEnergyEMPlus: " << this->sumEnergyEMPlus << endl;
  cout << "sumEnergyEMMinus: " << this->sumEnergyEMMinus << endl;
  cout << "sumEnergyHADPlus: " << this->sumEnergyHADPlus << endl;
  cout << "sumEnergyHADMinus: " << this->sumEnergyHADMinus << endl;
}
