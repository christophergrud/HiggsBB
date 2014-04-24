import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/users/h2/grud/CMSSW_5_3_9/src/test/TestHiggs_py_GEN2.root'
	#'file:/cms/skaplan/PLT/sim/CMSSW_5_3_9/src/SingleMuonPt100_PLTEta_NoSmear.root'
    )
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("thatplot.root")
)

process.demo = cms.EDAnalyzer('HiggsBB',
      particles = cms.InputTag("genParticles")
)


process.p = cms.Path(process.demo)
