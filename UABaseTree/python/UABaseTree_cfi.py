import FWCore.ParameterSet.Config as cms

isMonteCarlo = True
doMBTracking = True
useMITFilter = True
storeJets    = True
storeCastor  = False 

# Event Reconstruction (need to be updated)
uabasetree = cms.EDAnalyzer('UABaseTree',
  outputfilename = cms.untracked.string("test.root"),
  storeEvtId = cms.untracked.bool(True),
  storeFwdGap = cms.untracked.bool(False),
  storeL1Trig = cms.untracked.bool(False),
  storeL1TrigOld = cms.untracked.bool(False),
  hlt_paths = cms.untracked.vstring('HLT_L1_BscMinBiasOR_BptxPlusORMinus',
                                     'HLT_PixelTracks_Multiplicity40' ,
                                     'HLT_PixelTracks_Multiplicity70' ,
                                     'HLT_PixelTracks_Multiplicity85' ,
                                     'HLT_MinBiasPixel_SingleTrack' ),

  
)

if isMonteCarlo:
   uabasetree.storeGenKin    = cms.untracked.bool(False) 
   uabasetree.storeGenMet    = cms.untracked.bool(False) 
   uabasetree.storeGenPart   = cms.untracked.bool(False) 
   uabasetree.storePUSumInfo = cms.untracked.bool(False) 
   uabasetree.saveMothersAndDaughters = cms.untracked.bool(False) ;
   uabasetree.onlyStableGenPart       = cms.untracked.bool(False) ;
   uabasetree.onlyChargedGenPart      = cms.untracked.bool(False) ;

if doMBTracking:
  uabasetree.tracks   = cms.untracked.VInputTag("generalTracks","allTracks","generalPlusMinBiasTracks")
  uabasetree.vertices = cms.untracked.VInputTag("offlinePrimaryVertices","pixel3Vertices","generalVertices","allVertices","mergedVertices","offlinePrimaryVerticesWithMBTracks")

if useMITFilter:
   uabasetree.storeMITEvtSel = cms.untracked.bool(False)


if storeJets:
   uabasetree.vpfjets   = cms.untracked.VPSet(cms.PSet( jetcoll     = cms.untracked.InputTag("ak5PFJets"),
                                                        corrections = cms.untracked.vstring('ak5PFL2L3'),
							dijetcoll   = cms.untracked.string('ak5PFL2L3')
						      )
				             )
   uabasetree.vcalojets = cms.untracked.VPSet(cms.PSet( jetcoll     = cms.untracked.InputTag("ak5CaloJets"),
							corrections = cms.untracked.vstring('ak5CaloL2L3'),
							calojetid   = cms.untracked.InputTag('ak5JetID'),
							dijetcoll   = cms.untracked.string('ak5CaloL2L3')
						     )
					    )
					     
					     
if storeCastor:
   uabasetree.castorrechits = cms.untracked.InputTag('castorreco')
   uabasetree.basicjets     = cms.untracked.InputTag('ak7BasicJets')
   uabasetree.castorjetid   = cms.untracked.InputTag('ak7CastorJetID')
   uabasetree.castordigis   = cms.untracked.InputTag('castorDigis')


