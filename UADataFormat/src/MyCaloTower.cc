#include "MyCaloTower.h"
#include <iostream>

ClassImp(MyCaloTower)

MyCaloTower::MyCaloTower(){
  this->Reset();
}

MyCaloTower::~MyCaloTower(){}

void MyCaloTower::Print(){
  MyPart::Print();
  
  cout << "emEnergy  : " << emEnergy  << endl;
  cout << "hadEnergy : " << hadEnergy << endl;

}

void MyCaloTower::Reset(){
  MyPart::Reset();
  
  emEnergy  = 0;
  hadEnergy = 0;
}
