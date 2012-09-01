#include "MyFSCHit.h"
#include <iostream>

using namespace std;

ClassImp(MyFSCHit)

MyFSCHit::MyFSCHit(){
  this->Reset();
}

MyFSCHit::~MyFSCHit(){}

void MyFSCHit::Reset() {
  section = -1;
  energy = -1.;
  time = -1.;
  side = 0; 
}

void MyFSCHit::Print() {
  cout << "side: " << this->side << endl;
  cout << "section: " << this->section << endl;
  cout << "energy: " << this->energy << endl;
  cout << "time: " << this->time << endl;
}
