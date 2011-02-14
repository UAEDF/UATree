// Genaral Tracks and Vertex
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/src/Vertex.cc"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

// UABaseTree Analysis class decleration
#include "UATree/UABaseTree/interface/UABaseTree.h"

bool TrackDebug = false;
Double_t mpion = 139.57018;

void UABaseTree::GetRecoTracks(const edm::Event& iEvent, const string TrackCollName , vector<MyTracks>& TrackVector )
{


  TrackVector.clear(); 

  MyTracks mytrack;

  Handle<TrackCollection> tracks;
  iEvent.getByLabel(TrackCollName,tracks);

  for(TrackCollection::const_iterator tr = tracks->begin(); tr!=tracks->end(); ++tr){

    mytrack.Reset();

    mytrack.charge = tr->charge();
    mytrack.v.SetPtEtaPhiM(tr->pt(),tr->eta(),tr->phi(), mpion );  

    mytrack.nhit       =  tr->recHitsSize();
    mytrack.npixhit    =  tr->hitPattern().pixelLayersWithMeasurement() ;
    mytrack.nvalidhit  =  tr->found();
    mytrack.chi2n      =  tr->normalizedChi2();
    mytrack.dz         =  tr->dz();
    mytrack.d0         =  tr->d0();
    mytrack.edz        =  tr->dzError();
    mytrack.ed0        =  tr->d0Error();
    mytrack.ept        =  tr->ptError();

    mytrack.vx    =  tr->vertex().x();
    mytrack.vy    =  tr->vertex().y();
    mytrack.vz    =  tr->vertex().z();

    mytrack.quality[0] = tr->quality(reco::TrackBase::qualityByName("loose"));
    mytrack.quality[1] = tr->quality(reco::TrackBase::qualityByName("tight"));
    mytrack.quality[2] = tr->quality(reco::TrackBase::qualityByName("highPurity"));
    mytrack.quality[3] = tr->quality(reco::TrackBase::qualityByName("confirmed"));
    mytrack.quality[4] = tr->quality(reco::TrackBase::qualityByName("goodIterative"));

    mytrack.trackAlgo = tr->algo();

    // BeamSpot (id=0) and Vertex (id>0) Links
    mytrack.vtxid.clear();
    mytrack.vtxdxy.clear();
    mytrack.vtxdz.clear();

    for ( int i = 0 ; i != vtxid ; i++ ){
       mytrack.vtxid.push_back( i ); 
       mytrack.vtxdxy.push_back( tr->dxy( vtxid_xyz[i] ) );
       mytrack.vtxdz.push_back(  tr->dz( vtxid_xyz[i] )  );
    }


    TrackVector.push_back(mytrack);
    
    if(TrackDebug) mytrack.Print();
    
  }

}


void UABaseTree::GetAllTracks( const edm::Event& iEvent ){
  for(vector<InputTag>::iterator icoll = tracks_.begin() ; icoll!= tracks_.end() ; ++icoll)
    this->GetRecoTracks(iEvent , icoll->label() , allTracks[icoll->label()] );
}
