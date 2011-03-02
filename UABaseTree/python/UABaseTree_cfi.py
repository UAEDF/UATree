import FWCore.ParameterSet.Config as cms

# General switches --------------------------------------------------------------------

isMonteCarlo = True
doDAvertex   = True
doMBTracking = False
useMITFilter = False
storeJets    = False
storeMET     = False
storeCastor  = False 
keepCMSData  = True 

# Event Reconstruction (need to be updated) ----------------------------------------

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
                                     'HLT_MinBiasPixel_SingleTrack' )
)

# Monte-Carlo -----------------------------------------------------------------------

if isMonteCarlo:
  uabasetree.storeGenKin    = cms.untracked.bool(False) 
  uabasetree.storeGenMet    = cms.untracked.bool(True) 
  uabasetree.storeGenPart   = cms.untracked.bool(False) 
  uabasetree.saveMothersAndDaughters = cms.untracked.bool(False) ;
  uabasetree.onlyStableGenPart       = cms.untracked.bool(False) ;
  uabasetree.onlyChargedGenPart      = cms.untracked.bool(False) ;
  uabasetree.storePUSumInfo = cms.untracked.bool(False) 

# Minimumbias Tracking --------------------------------------------------------------

if doMBTracking:
  uabasetree.tracks   = cms.untracked.VInputTag("generalTracks","allTracks","generalPlusMinBiasTracks")
  uabasetree.vertices = cms.untracked.VInputTag("offlinePrimaryVertices","pixel3Vertices","generalVertices","allVertices","mergedVertices","offlinePrimaryVerticesWithMBTracks")
else:
  uabasetree.tracks   = cms.untracked.VInputTag("generalTracks")
  uabasetree.vertices = cms.untracked.VInputTag("offlinePrimaryVertices")

# DA Vertex -------------------------------------------------------------------------

if doDAvertex:
   uabasetree.vertices.insert(0,'offlinePrimaryVerticesDA')

# Beam Scrapping filter -------------------------------------------------------------

if useMITFilter:
  uabasetree.storeMITEvtSel = cms.untracked.bool(True)

# Jet Collections -------------------------------------------------------------------

if storeJets:
#  if isMonteCarlo:
    uabasetree.vpfjets   = cms.untracked.VPSet(cms.PSet( jetcoll    = cms.untracked.InputTag("ak5PFJets"),
                                                        corrections = cms.untracked.vstring('ak5PFL2L3','ak5PFL1Offset','ak5PFL1Fastjet','ak5PFL1L2L3','ak5PFL1FastL2L3'),
							#dijetcoll   = cms.untracked.string('ak5PFL2L3')
                                                       )  
				              )
    uabasetree.vcalojets = cms.untracked.VPSet(cms.PSet( jetcoll    = cms.untracked.InputTag("ak5CaloJets"),
	 						corrections = cms.untracked.vstring('ak5CaloL2L3'),
							calojetid   = cms.untracked.InputTag('ak5JetID'),
							#dijetcoll   = cms.untracked.string('ak5CaloL2L3')
						       )
					      )
#  else:
#    uabasetree.vpfjets   = cms.untracked.VPSet(cms.PSet( jetcoll    = cms.untracked.InputTag("ak5PFJets"),
#                                                        corrections = cms.untracked.vstring('ak5PFL2L3Residual','ak5PFL1Offset','ak5PFL1Fastjet','ak5PFL1L2L3Residual','ak5PFL1FastL2L3Residual'),
#                                                        #dijetcoll   = cms.untracked.string('ak5PFL2L3Residual')
#                                                       )
#                                              )
#    uabasetree.vcalojets = cms.untracked.VPSet(cms.PSet( jetcoll    = cms.untracked.InputTag("ak5CaloJets"),
#                                                        corrections = cms.untracked.vstring('ak5CaloL2L3Residual'),
#                                                        calojetid   = cms.untracked.InputTag('ak5JetID'),
#                                                        #dijetcoll   = cms.untracked.string('ak5CaloL2L3Residual')
#                                                       )
#                                              )


# MET Collections --------------------------------------------------------------------

if storeMET:					     
  if isMonteCarlo:
    uabasetree.mets = cms.untracked.VInputTag("genMetTrue" , "met" , "pfMet" , "tcMet")
  else:
    uabasetree.mets = cms.untracked.VInputTag("met" , "pfMet" , "tcMet")

# CASTOR -----------------------------------------------------------------------------
					     
if storeCastor:
   uabasetree.castorrechits = cms.untracked.InputTag('castorreco')
   uabasetree.basicjets     = cms.untracked.InputTag('ak7BasicJets')
   uabasetree.castorjetid   = cms.untracked.InputTag('ak7CastorJetID')
   #uabasetree.castordigis   = cms.untracked.InputTag('castorDigis')


