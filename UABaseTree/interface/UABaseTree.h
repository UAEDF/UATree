#ifndef __UABASETREE_H__
#define __UABASETREE_H__


// system include files
#include <string>
#include <vector>
#include <iostream>

// ROOT
#include "TFile.h"
#include "TTree.h"


// CMSSW Include files (Minimal)
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Point 3D
#include "DataFormats/Math/interface/Point3D.h"

// Trigger
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

// Track
#include "DataFormats/TrackReco/interface/Track.h"


// ChPartTree Analysis class decleration

#include "UATree/UADataFormat/src/MyPart.h"

#include "UATree/UADataFormat/src/MyEvtId.h"
#include "UATree/UADataFormat/src/MyL1Trig.h"
#include "UATree/UADataFormat/src/MyL1TrigOld.h"
#include "UATree/UADataFormat/src/MyHLTrig.h"

#include "UATree/UADataFormat/src/MyGenKin.h"
#include "UATree/UADataFormat/src/MyGenMet.h"
#include "UATree/UADataFormat/src/MyGenPart.h"
#include "UATree/UADataFormat/src/MySimVertex.h"
#include "UATree/UADataFormat/src/MyPUSumInfo.h"

#include "UATree/UADataFormat/src/MyBeamSpot.h"
#include "UATree/UADataFormat/src/MyVertex.h"
#include "UATree/UADataFormat/src/MyTracks.h"

#include "UATree/UADataFormat/src/MyFwdGap.h"

// MIT code
#include "UATree/UADataFormat/src/MyMITEvtSel.h"

#include "UATree/UADataFormat/src/MyCaloJet.h"
#include "UATree/UADataFormat/src/MyPFJet.h"

using namespace std;
using namespace edm;
using namespace reco;

typedef ParameterSet PSet;

//
// class decleration
//



class UABaseTree : public EDAnalyzer {
   public:
      explicit UABaseTree(const ParameterSet&);
      ~UABaseTree();


   private:
      virtual void beginJob() ;
      virtual void beginRun(Run const &, EventSetup const&) ;
      virtual void analyze(const Event&, const EventSetup&);
      virtual void endJob() ;
      
      

      // --------------------   Getters   --------------------
      virtual void GetAll(          const Event& , const EventSetup& );
      
      virtual void GetBeamSpot(     const Event& , const string& , MyBeamSpot& );
      virtual void GetAllBeamSpots( const Event& );
      virtual void GetEvtId(        const Event& );
      virtual void GetFwdGap(       const Event& );
      
      virtual void GetGenKin(       const Event& );
      virtual void GetGenMet(       const Event& );
      virtual void GetGenPart(      const Event& , const EventSetup& ); 
      virtual void GetPUSumInfo(    const Event& );
      
      virtual void GetHLTrig(       const Event& , const EventSetup& );
      virtual void GetL1Trig(       const Event& , const EventSetup& );
      virtual void GetL1TrigOld(    const Event& );
      
      virtual void GetMITEvtSel(    const Event& );
      
      virtual void GetRecoTracks(   const Event& , const string , vector<MyTracks>& );
      virtual void GetAllTracks(    const Event& );
      virtual void FillTrack(       const Track& , MyTracks& );
      virtual void GetRecoVertex(   const Event& , const string , vector<MyVertex>& ); 
      virtual void GetAllVertices(  const Event& ); 
      
      virtual void GetRecoCaloJets( const Event& , const EventSetup& , const PSet& , vector<MyCaloJet>& );
      virtual void GetAllCaloJets(  const Event& , const EventSetup& );
      
      virtual void GetRecoPFJets(   const Event& , const EventSetup& , const PSet& , vector<MyPFJet>& );
      virtual void GetAllPFJets(    const Event& , const EventSetup& );
      
      // --------------------   Get All Parameters   --------------------
      virtual void GetParameters( const ParameterSet& );
     

      // --------------------   Init All Branches   --------------------
      virtual void Init();
      
      
      // --------------------   Other Functions   --------------------
      bool hasFired(const std::string& , const TriggerNames& trigNames, const TriggerResults& ) const;
      Bool_t GetLooseCaloJetId(const MyCaloJet& , const string& );
      Bool_t GetTightCaloJetId(const MyCaloJet& , const string& );
      Bool_t GetLoosePFJetId(  const MyPFJet&   , const string& );
      Bool_t GetTightPFJetId(  const MyPFJet&   , const string& );



      // ------------------------------------------------------------------------------------------------------------------------
      
      
      
      
      // --------------------   Vars From Config File   --------------------
      
      vector<InputTag> beamspots_ ;
      Bool_t           storeEvtId_;
      InputTag         calotower_ ;
      Bool_t           storeFwdGap_;
      InputTag         hepmc_ ;
      InputTag         genmet_ ;
      InputTag         genpart_ ;
      Bool_t           storeGenKin_;
      Bool_t           storeGenMet_;
      Bool_t           storeGenPart_;
      InputTag         pusuminfo_;
      Bool_t           storePUSumInfo_;
      vector<string>   hlt_paths_;
      Bool_t           storeL1Trig_;
      Bool_t           storeL1TrigOld_;
      Bool_t           storeMITEvtSel_;
      vector<InputTag> tracks_ ;
      vector<InputTag> vertices_ ;
      vector<PSet>     vcalojets_;
      vector<PSet>     vpfjets_;
      
      //for fwdGap
      double energyThresholdHB_ ;
      double energyThresholdHE_ ;
      double energyThresholdHF_ ;
      double energyThresholdEB_ ;
      double energyThresholdEE_ ;
      
      //for genPart
      Bool_t saveMothersAndDaughters_;
      Bool_t onlyStableGenPart_;
      Bool_t onlyChargedGenPart_;
      
      //for PFJets
      Bool_t storeTracksInPFJets_;
      
      //for jet ID
      PSet ParaSetLooseCaloJetID_;
      PSet ParaSetTightCaloJetID_;
      PSet ParaSetLoosePFJetID_;
      PSet ParaSetTightPFJetID_;
      
      
      string outputfilename_ ;





      // ------------------------------------------------------------------------------------------------------------------------
      
      
      
      

      // --------------------   Tree Content   --------------------
     
      map<string,MyBeamSpot>        allBeamSpots;
      MyEvtId                       evtId;
      MyFwdGap                      fwdGap;
      
      MyGenKin                      genKin;
      MyGenMet                      genMet;
      vector<MyGenPart>             genPart;
      MySimVertex                   simVertex;
      MyPUSumInfo                   pusuminfo;      

      MyL1Trig                      L1Trig;
      MyL1TrigOld                   L1TrigOld; 
      MyHLTrig                      HLTrig;
      
      MyMITEvtSel                   MITEvtSel;
      
      map<string,vector<MyTracks> > allTracks;
      map<string,vector<MyVertex> > allVertices;


      map<string,vector<MyCaloJet> > allCaloJets;
      map<string,vector<MyPFJet> >   allPFJets;



      // ------------------------------------------------------------------------------------------------------------------------
      
      
      
      

      // --------------------   Vertex Id   --------------------
      Int_t vtxid;
      vector<math::XYZPoint> vtxid_xyz;


      // map<int,string> HLT_map;


      // --------------------   Needed For HLT   --------------------
      bool isValidHltConfig_;
      HLTConfigProvider hltConfig;
      
      
      // --------------------   File & Tree   --------------------
      
      TFile*   fout;
      TTree*   tree;



};

#endif

