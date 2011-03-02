#   For all possibilities that are not here (like some of the input collections),
#   please look at all parameters retrieved in src/GetParameters.cc
#   All the parameters have anyway a default value !


import FWCore.ParameterSet.Config as cms

# General switches --------------------------------------------------------------------

isMonteCarlo = True		#if running on Monte-Carlo file
doDAvertex   = True		#if you want to enable the AnnealingVertexing + stores it
doMBTracking = False		#does the low-pt tracking + merging with generalTracks + vertices + stores them. If false, store only generalTracks & offlinePrimaryVertices.
useMITFilter = False		#Not the official CMS one, but cleans better. Needed for low-pt tracking. If off, no filter is used. //the standard "noscraping" filter is used.
storeJets    = True		#stores jets. Need to choose which collections and corrections to store, and if do the Dijets.
storeMET     = False		#stores "met", "pfMet" and "tcMet". If isMonteCarlo=true , also stores "genMetTrue".
storeCastor  = False 		#stores castorrechits , castorjets
keepCMSData  = True 		#make another CMSSW root files with all the collections from the input file and those created in the path



# Standard Parameters For UABaseTree Process   ----------------------------------------

uabasetree = cms.EDAnalyzer('UABaseTree',
  filterEvents = cms.untracked.bool(True),		#filterEvents for data. Switched Off for MC
  storeEvtId = cms.untracked.bool(True),		
  storeFwdGap = cms.untracked.bool(False),
  storeL1Trig = cms.untracked.bool(True),
  storeL1TrigOld = cms.untracked.bool(False),		#old simple version. Deprecated.
  hlt_paths = cms.untracked.vstring('HLT_L1_BscMinBiasOR_BptxPlusORMinus',
                                     'HLT_PixelTracks_Multiplicity40' ,
                                     'HLT_PixelTracks_Multiplicity70' ,
                                     'HLT_PixelTracks_Multiplicity85' ,
                                     'HLT_MinBiasPixel_SingleTrack' )
)

# Monte-Carlo -----------------------------------------------------------------------

if isMonteCarlo:
  uabasetree.filterEvents                  = cms.untracked.bool(False) #all MC events are stored.
  uabasetree.storeGenKin                   = cms.untracked.bool(False) 
  uabasetree.storeGenPart                  = cms.untracked.bool(False) 
  uabasetree.saveMothersAndDaughters       = cms.untracked.bool(False) #saves the 2 mothers & 2 daughters for each genPart. USeless if not all genParts are stored (ie if 1 of the 3 switch below is on
  uabasetree.saveGenPartsInDifferentColls  = cms.untracked.bool(False) #saves status=3 in genPart, and status=1 Electrons, Muons and Neutrinos in genElec, genMu, genNu
  uabasetree.onlyStableGenPart             = cms.untracked.bool(False) #saves only status=1 in genPart
  uabasetree.onlyChargedGenPart            = cms.untracked.bool(False) #saves only charged particles in genPart
  uabasetree.storePUSumInfo                = cms.untracked.bool(False) 



# Tracking --------------------------------------------------------------
if not doMBTracking:
  uabasetree.tracks   = cms.untracked.VInputTag("generalTracks")
  uabasetree.vertices = cms.untracked.VInputTag("offlinePrimaryVertices")
else:
  uabasetree.tracks   = cms.untracked.VInputTag("allTracks","generalPlusMinBiasTracks")
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
#  if isMonteCarlo:
    storeTracksInPFJets  = cms.untracked.bool(True)	#stores tracks used to construct the PFJet in the PFJet.vtrack member. Only if the RefTracks are present. 

 
    uabasetree.vpfjets   = cms.untracked.VPSet(cms.PSet( jetcoll    = cms.untracked.InputTag("ak5PFJets"),  
                                                        corrections = cms.untracked.vstring('ak5PFL2L3','ak5PFL1Offset','ak5PFL1Fastjet','ak5PFL1L2L3','ak5PFL1FastL2L3'),
							#dijetcoll   = cms.untracked.string('ak5PFL2L3')    #needs to be exactly the same as the string for the correction
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
  uabasetree.mets = cms.untracked.VInputTag("met" , "pfMet" , "tcMet")

  if isMonteCarlo:
    uabasetree.mets.insert(0,"genMetTrue")



# CASTOR -----------------------------------------------------------------------------
					     
if storeCastor:
   uabasetree.castorrechits = cms.untracked.InputTag('castorreco')
   uabasetree.basicjets     = cms.untracked.InputTag('ak7BasicJets')
   uabasetree.castorjetid   = cms.untracked.InputTag('ak7CastorJetID')
   #uabasetree.castordigis   = cms.untracked.InputTag('castorDigis')


