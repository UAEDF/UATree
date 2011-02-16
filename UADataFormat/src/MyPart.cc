#include "MyPart.h"
#include <iostream>
using namespace std;

ClassImp(MyPart)

MyPart::MyPart(){
  this->Reset();
}

MyPart::~MyPart(){}


void MyPart::Reset(){
  v      = TLorentzVector(0,0,0,0);
  charge = 0;
}

void MyPart::Print(){
  cout << "px     : " << this->v.Px() << endl;
  cout << "py     : " << this->v.Py() << endl;
  cout << "pz     : " << this->v.Pz() << endl;
  cout << "E      : " << this->v.E()  << endl;
  cout << "charge : " << this->charge << endl;
}

TLorentzVector MyPart::vmpi()
{
  Double_t mpion = 139.57018;
  TLorentzVector vm;
  vm.SetPtEtaPhiM( this->v.Pt() , this->v.Eta() , this->v.Phi() , mpion );
  return vm;
}

Bool_t MyPart::operator<( const MyPart& part ){
  return this->v.Pt() < part.v.Pt();
}
 
//bool operator== ( const MyPart* genpart){
//  return (*this).pt == genpart.pt;
//} 
