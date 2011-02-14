// Description: Function to retrieve Generated Kinematic et al.

// DataFormats
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"


// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"


bool GenKinDebug = false;

void UABaseTree::GetGenKin(const edm::Event& iEvent)
{
   genKin.Reset();

   // MC Process Id and PtHat for RECO
   Handle<HepMCProduct> hepMCHandle;
   iEvent.getByLabel(hepmc_, hepMCHandle ) ;
   
   const HepMC::GenEvent* GenEvt = hepMCHandle->GetEvent() ;
   genKin.MCProcId = GenEvt->signal_process_id();
   genKin.PtHat = GenEvt->event_scale();

   //-- PDF Info

   const HepMC::PdfInfo* pdfInfo = GenEvt->pdf_info();

   genKin.x1      = pdfInfo->x1();
   genKin.x2      = pdfInfo->x2();
   genKin.Q       = pdfInfo->scalePDF();
   genKin.Part1Id = pdfInfo->id1();
   genKin.Part2Id = pdfInfo->id2();
   
   //K Factor For Signal
   edm::Handle<double> KFactor;
   try {
    iEvent.getByLabel("KFactorProducer",KFactor);
    genKin.kfactor=*KFactor;
   }
   catch (...){
     cout << "[UABaseTree::GetGenKin] Was not able to retrieve k factor" << endl;
   }
   
   if(GenKinDebug) genKin.Print();
}

