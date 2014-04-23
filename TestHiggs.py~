import FWCore.ParameterSet.Config as cms
 
# Disclaimer :
#
# This set of Pythia configuration cards has been copied 
# and pasted from 
#   RecoTracker/RoadSearchCloudMaker/test/sim_pythia.cfg
# prepared by Oliver Gutsche (FNAL)
#
# the only change is MSTP(128)=2 - this option takes decay 
# products out of doc section; decay products point at parents
# in the main section (Julia Yarba, FNAL).
generator = cms.EDFilter("Pythia6GeneratorFilter",
    # to printout HepMC::GenEvent record (HepMC::GenEvent::print())
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    maxEventsToPrint = cms.untracked.int32(0),
    # to printout pythia event record (call pylist)
    pythiaPylistVerbosity = cms.untracked.int32(0),
    comEnergy = cms.double(8000.0),
    PythiaParameters = cms.PSet(
        pythiaHZZmumumumu = cms.vstring('MSTJ(22)=4    ! Require both long-lived exotics to decay inside the CMS volume',
         'PARJ(73)=7000. ! radius (mm) of CMS cylinder',
         'PARJ(74)=9000. ! half (mm) length of CMS cylinder',
         'MSEL=0',
         'MSUB(152)=1',
         'MWID(35)=2 ! Let me set H0 properties'
         'PMAS(35,1)=125.0 ! This probably has no effect ...',
         'PMAS(35,2)=1.'),
        parameterSets = cms.vstring('pythiaHZZmumumumu')
	PYUPDAParameters = cms.vstring('PYUPDAFILE =  Configuration/Generator/data/higgs_pythia6.pyupda'
	"PYUPDApostPYINIT"
	)
    )
)
