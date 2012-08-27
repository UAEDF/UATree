#   For all possibilities that are not here (like some of the input collections),
#   please look at all parameters retrieved in src/GetParameters.cc
#   All the parameters have anyway a default value !


import FWCore.ParameterSet.Config as cms

# General switches --------------------------------------------------------------------

isMonteCarlo = True		#if running on Monte-Carlo file
doDAvertex   = False		#if you want to enable the AnnealingVertexing + stores it
doMBTracking = False		#does the low-pt tracking + merging with generalTracks + vertices + stores them. If false, store only generalTracks & offlinePrimaryVertices.
useMITFilter = False		#Not the official CMS one, but cleans better. Needed for low-pt tracking. If off, no filter is used. //the standard "noscraping" filter is used.
storeJets    = True		#stores jets. Need to choose which collections and corrections to store, and if do the Dijets.
storeMET     = True		#stores "met", "pfMet" and "tcMet". If isMonteCarlo=true , also stores "genMetTrue".
storeCastor  = False 		#stores castorrechits , castorjets
keepCMSData  = False 		#make another CMSSW root files with all the collections from the input file and those created in the path

###
storePFCands = True
storeCaloObjects = True
storeMuons = True
storeElectrons = True

# Standard Parameters For UABaseTree Process   ----------------------------------------

uabasetree = cms.EDAnalyzer('UABaseTree',
  filterEvents = cms.untracked.bool(False),		#filterEvents for data. Switched Off for MC
  storeEvtId = cms.untracked.bool(True),		
  storeFwdGap = cms.untracked.bool(False),
  storeL1Trig = cms.untracked.bool(False),
  storeL1TrigOld = cms.untracked.bool(True),		#old simple version. Deprecated.
  #hlt_paths = cms.untracked.vstring( 'HLT_DoubleMu3_v3',
  #                                   'HLT_Ele8_v2' ,
  #                                   'HLT_Jet20_v1' ,
  #                                   'HLT_Jet40_v1' ,
  #                                   'HLT_Jet60_v1' ,
  #                                   'HLT_L1DoubleForJet32_EtaOpp_v1' ,
  #                                   'HLT_L1DoubleForJet8_EtaOpp_v1' ,
  #                                   'HLT_L1DoubleMu0_v1' ,
  #                                   'HLT_L2DoubleMu0_v2' ,
  #                                   'HLT_L1SingleEG12_v1',
  #                                   "HLT_L1SingleEG5_v1",
  #                                   "HLT_L1SingleJet36_v1",
  #                                   "HLT_L1SingleMuOpen_AntiBPTX_v1",
  #                                   "HLT_L1SingleMuOpen_DT_v1",
  #                                   "HLT_L1SingleMuOpen_v1" ,
  #                                   'HLT_L1BscMinBiasORBptxPlusANDMinus_v1' ,
  #                                   'HLT_Mu0_v3' ,
  #                                   'HLT_Mu3_v3' ,
  #                                   'HLT_Mu5_v3' ,
  #                                   'HLT_Photon10_CaloIdVL_v1' ,
  #                                   'HLT_Photon15_CaloIdVL_v1' ,
  #                                   'HLT_PixelTracks_Multiplicity50_Loose' ,
  #                                   'HLT_PixelTracks_Multiplicity60_Loose' ,
  #                                   'HLT_PixelTracks_Multiplicity70_Loose' ,
  #                                   'HLT_ZeroBiasPixel_SingleTrack_v1' ,
  #                                   'HLT_ZeroBias_v1',
  #                                   'HLT_L1Tech53_MB_1_v1',
  #                                   'HLT_L1Tech53_MB_2_v1')
  #hlt_paths = cms.untracked.vstring( 'HLT_ZeroBias_v6',
  #                                   'HLT_L1Tech54_ZeroBias_v1',
  #                                   'HLT_L1Tech40_BPTXAND_1_v1',
  #                                   'HLT_L1Tech53_MB_1_v1',
  #                                   'HLT_L1Tech40_BPTXAND_2_v1',
  #                                   'HLT_L1Tech53_MB_2_v1', 
  #                                   'HLT_SingleJetC5_BHC_v1',
  #                                   'HLT_SingleJetC5_HF_v1',
  #                                   'HLT_TripleTrack02_BHC_v1',
  #                                   'LT_TripleTrack02_HF_v1',
  #                                   'HLT_L1RomanPots_OR_v1',
  #                                   'HLT_SingleForJet15_BHC_v1',
  #                                   'HLT_SingleForJet15_HF_v1' )  
  hlt_paths = cms.untracked.vstring( 'HLT_L1DoubleEG3_FwdVeto_v1',
                                     'HLT_L1DoubleMu0_v1',
                                     'HLT_L1DoubleJet20_RomanPotsOR_v1',
                                     'HLT_L1DoubleJet20part1_v1',
                                     'HLT_L1DoubleJet24_v1',
                                     'HLT_L1DoubleJet20part2_v1',
                                     'HLT_L1Tech40_BPTXAND_v1',
                                     'HLT_L1Tech53_MB_1_v1',
                                     'HLT_L1Tech_HF9OR10_v1',
                                     'HLT_T1minbias_Tech55_v1',
                                     'HLT_L1Tech53_MB_2_v1',
                                     'HLT_L1Tech53_MB_3_v1',
                                     'HLT_RomanPots_Tech52_v1',
                                     'HLT_L1Tech54_ZeroBias_v1',
                                     'HLT_ZeroBias_v7'
                                     ) 
)

# Monte-Carlo -----------------------------------------------------------------------

if isMonteCarlo:
  uabasetree.filterEvents                  = cms.untracked.bool(False) #all MC events are stored.
  uabasetree.storeGenKin                   = cms.untracked.bool(True) 
  uabasetree.storeGenPart                  = cms.untracked.bool(True)
  uabasetree.saveMothersAndDaughters       = cms.untracked.bool(False) #saves the 2 mothers & 2 daughters for each genPart. USeless if not all genParts are stored (ie if 1 of the 3 switch below is on
  uabasetree.saveGenPartsInDifferentColls  = cms.untracked.bool(False) #saves status=3 in genPart, and status=1 Electrons, Muons and Neutrinos in genElec, genMu, genNu
  uabasetree.onlyStableGenPart             = cms.untracked.bool(True) #saves only status=1 in genPart
  uabasetree.onlyChargedGenPart            = cms.untracked.bool(True) #saves only charged particles in genPart
  uabasetree.storePUSumInfo                = cms.untracked.bool(True) 
  uabasetree.hlt_paths = cms.untracked.vstring()
  #uabasetree.hlt_paths = cms.untracked.vstring(
  #                                  'HLT_ZeroBias',
  #                                  'HLT_ZeroBiasPixel_SingleTrack' ,
  #                                  'HLT_MinBiasPixel_SingleTrack' ,
  #                                  'HLT_L1_BptxXOR_BscMinBiasOR' ,
  #                                  'HLT_L1Tech_BSC_minBias_OR' ,
  #                                  'HLT_L1Tech_BSC_minBias' ,
  #                                  'HLT_L1Tech_BSC_halo' ,
  #                                  'HLT_L1Tech_BSC_halo_forPhysicsBackground' ,
  #                                  'HLT_L1Tech_BSC_HighMultiplicity' ,
  #                                  'HLT_PixelTracks_Multiplicity70',
  #                                  "HLT_PixelTracks_Multiplicity85",
  #                                  "HLT_PixelTracks_Multiplicity100" )

# Tracking --------------------------------------------------------------
if not doMBTracking:
  if not isMonteCarlo: 
      uabasetree.tracks   = cms.untracked.VInputTag("generalTracks","selectTracks")
  else:
      uabasetree.tracks   = cms.untracked.VInputTag("generalTracks")
  uabasetree.vertices = cms.untracked.VInputTag("offlinePrimaryVertices")
else:
  uabasetree.tracks   = cms.untracked.VInputTag("allTracks","generalPlusMinBiasTracks","generalTracks","selectTracks")
  uabasetree.vertices = cms.untracked.VInputTag("offlinePrimaryVertices","pixel3Vertices","generalVertices","allVertices","mergedVertices","offlinePrimaryVerticesWithMBTracks")

# DA Vertex -------------------------------------------------------------------------

if doDAvertex:
   uabasetree.vertices.insert(0,'offlinePrimaryVerticesDA')

# Beam Scrapping filter -------------------------------------------------------------

if useMITFilter:
  uabasetree.storeMITEvtSel = cms.untracked.bool(True)

# Jet Collections -------------------------------------------------------------------

# each VPSet of vpfjets or vcalojets needs to contain PSets with:
# jetcoll : not corrected collection. Can specifiy tree branch name in label using seperator # : "label#branchname:instance:process". Example : "ak5PFJets#jets". NOT NECESSARY !
# corrections : name of corrections in vector. Need to provide essource for it in python/UABaseTree_jets_cfi.py . Can specifiy corr name/key stored in Jet.mapjet using seperator # :
#               "corr#mapkey". Example : "ak5PFL1Fastjet#fastjet", but of course "ak5PFL1Fastjet" works too, the mapkey will then be the correction name, here "ak5PFL1Fastjet"
# dijetcoll : if you want to have the Dijet class done for each jetcoll. Need to provide the exact same string as the correction, #mapkey included. Example : "ak5PFL1Fastjet#fastjet"

if storeJets:
  if isMonteCarlo:
    # stores tracks used to construct the PFJet in the PFJet.vtrack member. Only if the RefTracks are present. 
    storeTracksInPFJets  = cms.untracked.bool(True)
    uabasetree.vpfjets   = cms.untracked.VPSet(
	    cms.PSet( jetcoll    = cms.untracked.InputTag("ak5PFJets"),
		      corrections = cms.untracked.vstring('ak5PFL2L3') ),
	    cms.PSet( jetcoll    = cms.untracked.InputTag("ak7PFJets"),
		      corrections = cms.untracked.vstring('ak7PFL2L3') ),
	    )
#    uabasetree.vcalojets = cms.untracked.VPSet(
#	    cms.PSet( jetcoll    = cms.untracked.InputTag("ak5CaloJets"),
#		      corrections = cms.untracked.vstring('ak5CaloL2L3') ),
#	    cms.PSet( jetcoll    = cms.untracked.InputTag("ak7CaloJets"),
#		      corrections = cms.untracked.vstring('ak7CaloL2L3') ),
#	    )
    uabasetree.genjets = cms.untracked.VInputTag("ak5GenJets","ak7GenJets")

  else:
    storeTracksInPFJets  = cms.untracked.bool(True)
    uabasetree.vpfjets   = cms.untracked.VPSet(
	    cms.PSet( jetcoll    = cms.untracked.InputTag("ak5PFJets"),
		      corrections = cms.untracked.vstring('ak5PFL2L3','ak5PFL2L3Residual') ),
	    cms.PSet( jetcoll    = cms.untracked.InputTag("ak7PFJets"),
		      corrections = cms.untracked.vstring('ak7PFL2L3','ak7PFL2L3Residual') ),
	    )
#    uabasetree.vcalojets = cms.untracked.VPSet(
#	    cms.PSet( jetcoll    = cms.untracked.InputTag("ak5CaloJets"),
#		      corrections = cms.untracked.vstring('ak5CaloL2L3','ak5CaloL2L3Residual') ),
#	    cms.PSet( jetcoll    = cms.untracked.InputTag("ak7CaloJets"),
#		      corrections = cms.untracked.vstring('ak7CaloL2L3','ak7CaloL2L3Residual') ),
#	    )
					      
# Basic jets:
if not isMonteCarlo:
    uabasetree.basicjets = cms.untracked.VInputTag("ueSisCone5TracksJet500","ueAk5TracksJet500")
else:
    pass
    #uabasetree.basicjets = cms.untracked.VInputTag("ueSisCone5TracksJet500","ueAk5TracksJet500")
    #uabasetree.basicjets.insert(0,"ueSisCone5ChgGenJet500")
    #uabasetree.basicjets.insert(0,"ueAk5ChgGenJet500")

# Track jets
if not isMonteCarlo:
    uabasetree.trackjets = cms.untracked.VInputTag("ueSisCone5TracksJet500#TrackJetSisCone","ueAk5TracksJet500#TrackJetAntiKt")

uabasetree.vtxcoll_for_trackjets = cms.untracked.string("offlinePrimaryVertices")

# MET Collections --------------------------------------------------------------------
if storeMET:					     
  uabasetree.mets = cms.untracked.VInputTag("met" , "pfMet" , "tcMet")
  if isMonteCarlo:
    uabasetree.mets.insert(0,"genMetTrue")

# CASTOR -----------------------------------------------------------------------------
if storeCastor:
   uabasetree.castorrechits = cms.untracked.InputTag('castorreco')
   uabasetree.basicjets     = cms.untracked.InputTag('ak7BasicJets')
   uabasetree.castorjetid   = cms.untracked.InputTag('ak7CastorJetID')
   #uabasetree.castordigis   = cms.untracked.InputTag('castorDigis')

# PF candidates
if storePFCands:					     
   uabasetree.pfcands = cms.untracked.VInputTag("particleFlow")

# Calo towers
if storeCaloObjects:
   uabasetree.storeCaloObjects = cms.untracked.bool(True)
   uabasetree.calotowercoll = cms.untracked.InputTag("towerMaker")

# Reco muons
if storeMuons:
   uabasetree.muons = cms.untracked.VInputTag("muons")

# Reco electrons
if storeElectrons:
   uabasetree.electrons = cms.untracked.VInputTag("gsfElectrons")
