#   For all possibilities that are not here (like some of the input collections),
#   please look at all parameters retrieved in src/GetParameters.cc
#   All the parameters have anyway a default value !

import FWCore.ParameterSet.Config as cms

from UABaseTree_forward_cfi import *

# Monte Carlo specific configuration
uabasetree.filterEvents                  = cms.untracked.bool(False) #all MC events are stored.
uabasetree.storeGenKin                   = cms.untracked.bool(True) 
uabasetree.storeGenPart                  = cms.untracked.bool(True)
uabasetree.saveMothersAndDaughters       = cms.untracked.bool(False) #saves the 2 mothers & 2 daughters for each genPart. USeless if not all genParts are stored (ie if 1 of the 3 switch below is on
uabasetree.saveGenPartsInDifferentColls  = cms.untracked.bool(False) #saves status=3 in genPart, and status=1 Electrons, Muons and Neutrinos in genElec, genMu, genNu
uabasetree.onlyStableGenPart             = cms.untracked.bool(True) #saves only status=1 in genPart
uabasetree.onlyChargedGenPart            = cms.untracked.bool(True) #saves only charged particles in genPart
uabasetree.storePUSumInfo                = cms.untracked.bool(True) 
uabasetree.hlt_paths = cms.untracked.vstring()

# Tracking --------------------------------------------------------------
if not doMBTracking:
    uabasetree.tracks   = cms.untracked.VInputTag("generalTracks")

# Jet Collections -------------------------------------------------------------------
if storeJets:
    # stores tracks used to construct the PFJet in the PFJet.vtrack member. Only if the RefTracks are present. 
    uabasetree.storeTracksInPFJets  = cms.untracked.bool(False)
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

# Basic jets:
uabasetree.basicjets = cms.untracked.VInputTag()
#uabasetree.basicjets.insert(0,"ueSisCone5ChgGenJet500")
#uabasetree.basicjets.insert(0,"ueAk5ChgGenJet500")

# Track jets
uabasetree.trackjets = cms.untracked.VInputTag()

# MET Collections --------------------------------------------------------------------
if storeMET:					     
    uabasetree.mets.insert(0,"genMetTrue")
