import FWCore.ParameterSet.Config as cms

#from UATree.UABaseTree.TightPFJetID_Parameters_cfi   import TightPFJetID_Parameters as   TightPFJetID_Parameters_Ref
#from UATree.UABaseTree.LooseCaloJetID_Parameters_cfi import LooseCaloJetID_Parameters as LooseCaloJetID_Parameters_Ref
#from UATree.UABaseTree.TightCaloJetID_Parameters_cfi import TightCaloJetID_Parameters as TightCaloJetID_Parameters_Ref


process = cms.Process("UABaseTree")

process.maxEvents = cms.untracked.PSet(
   input = cms.untracked.int32(3)
)

# initialize MessageLogger and output report ----------------------------------------

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.cout.placeholder = cms.untracked.bool(False)
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.options = cms.untracked.PSet(
   wantSummary = cms.untracked.bool(False)
   #SkipEvent = cms.untracked.vstring('ProductNotFound')

)

# Data source -----------------------------------------------------------------------
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('dcap://pnfs/iihe/cms/store/user/xjanssen/data/CMSSW_3_6_2/DataCopy_36x/__MinimumBias__Commissioning10-Jun14thReReco_v1__RECO/DataCopy_36x__CMSSW_3_6_2__MinimumBias__Commissioning10-Jun14thReReco_v1__RECO_1_1_xom.root'),
   #fileNames = cms.untracked.vstring('dcap:///pnfs/iihe/cms/ph/sc4/store/mc/Summer10/MinBias_7TeV-pythia8/GEN-SIM-RECODEBUG/START36_V10_SP10-v1/0002/1C57F8AA-8E74-DF11-ADCE-0017A4771024.root')
   #lumisToProcess = cms.untracked.VLuminosityBlockRange('124009:1-124009:68')

)


# configure modules via Global Tag --------------------------------------------------
# https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_36X_V12A::All'


#Geometry --------------------------------------------------------------------------
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")


#process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
#process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.EventContent.EventContent_cff')

#HLT Stuff
process.load('HLTrigger.special.hltPhysicsDeclared_cfi')
process.hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'
#process.mypath=cms.Path(process.hltPhysicsDeclared+<my_other_things_here>)


from UATree.UABaseTree.UABaseTree_cfi import *
process.load("UATree.UABaseTree.UABaseTree_cfi")
#process.add_(uabasetree)


process.path = cms.Sequence()

if not(isMonteCarlo):
   process.path = cms.Sequence(process.path * process.hltPhysicsDeclared)


#  ----------------------------   if MC   ----------------------------
if isMonteCarlo:
   process.load('UATree.UABaseTree.UABaseTree_MC_cfi')
   process.myTTRHBuilderWithoutAngle4PixelTriplets.ComputeCoarseLocalPositionFromDisk = True
   process.GlobalTag.globaltag = 'START39_V8::All'
   #process.source.fileNames = cms.untracked.vstring('dcap:///pnfs/iihe/cms/ph/sc4/store/mc/Summer10/MinBias_7TeV-pythia8/GEN-SIM-RECODEBUG/START36_V10_SP10-v1/0002/1C57F8AA-8E74-DF11-ADCE-0017A4771024.root')
   #process.source.fileNames = cms.untracked.vstring('dcap:///pnfs/iihe/cms/store/user/xjanssen/data//CMSSW_3_9_7/DataCopy_397/__GluGluToHToWWTo2L2Nu_M-160_7TeV-powheg-pythia6__Winter10-E7TeV_ProbDist_2011Flat_BX156_START39_V8-v1__GEN-SIM-RECO/DataCopy_397__CMSSW_3_9_7__GluGluToHToWWTo2L2Nu_M-160_7TeV-powheg-pythia6__Winter10-E7TeV_ProbDist_2011Flat_BX156_START39_V8-v1__GEN-SIM-RECO_1_1_RJI.root')
   process.source.fileNames = cms.untracked.vstring('file:/user/selvaggi/step2_RAW2DIGI_L1Reco_RECO_9_1_XqK.root')
   
#  ----------------------------   Filters   ----------------------------
if useMITFilter:
   process.load("MitEdm.Producers.evtSelData_cfi")
   process.load("MitEdm.Filters.FilterEvtSel_cff")
   process.load('UATree.UABaseTree.UABaseTree_tracking_cfi')
   process.path = cms.Sequence(process.path * process.redoSiHits * process.evtSelData * process.looseEvtSelFilter )
else:
   pass#process.path = cms.Sequence(process.path * process.noscraping)



#  ----------------------------   Tracking   ----------------------------
if doMBTracking:
   if not(useMITFilter):
      process.load('UATree.UABaseTree.UABaseTree_tracking_cfi')
      process.path = cms.Sequence(process.path * process.redoSiHits )
   process.pixelTertTracks.OrderedHitsFactoryPSet.maxElement = cms.uint32( 1000 )
   process.path = cms.Sequence(process.path  * process.fulltracking)

   
#  ----------------------------   Jets   ----------------------------
if storeJets:
   process.load("UATree.UABaseTree.UABaseTree_jets_cfi")


#  ----------------------------   Castor   ----------------------------
if storeCastor:
   process.castorDigis.InputLabel = 'source'
   #process.load("RecoLocalCalo.Castor.CastorCellReco_cfi")    #-- redo cell
   #process.load("RecoLocalCalo.Castor.CastorTowerReco_cfi")   #-- redo tower
   #process.load("RecoJets.JetProducers.ak7CastorJets_cfi")    #-- redo jet
   #process.load("RecoJets.JetProducers.ak7CastorJetID_cfi")   #-- redo jetid
   #process.path = cms.Sequence(process.path  * process.castorDigis*process.castorreco*process.CastorCellReco*process.CastorTowerReco*process.ak7BasicJets*process.ak7CastorJetID)
                    





#  ----------------------------   Final Path   ----------------------------
process.path = cms.Sequence(process.path * process.uabasetree)

process.p = cms.Path( process.path )
