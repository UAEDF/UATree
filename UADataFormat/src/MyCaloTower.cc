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


  cout << "caloId : " << this->caloId << endl;
  cout << "zside : " << this->zside << endl;
}

void MyCaloTower::Reset(){
  MyPart::Reset();
  
  emEnergy  = 0;
  hadEnergy = 0;

  caloId = X;
  zside= 0;
}
