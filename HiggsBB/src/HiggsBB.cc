// -*- C++ -*-
//
// Package:    HiggsBB
// Class:      HiggsBB
// 
/**\class HiggsBB HiggsBB.cc test/HiggsBB/src/HiggsBB.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Christoperh Grud
//         Created:  Thu Apr 17 15:42:32 EDT 2014
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//you need the TFileService in order to make plots
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
//for reco::Candidate
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
//for the GenParticleCollection and GenParticles
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <vector>
#include <iostream>
#include <cmath>
#include "TH1D.h"
#include <fstream>
#include "TLorentzVector.h"
#include "TVector3.h"

//
// class declaration
//

class HiggsBB : public edm::EDAnalyzer {
   public:
      explicit HiggsBB(const edm::ParameterSet&);
      ~HiggsBB();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
};

edm::Service<TFileService> fs;
edm::Handle< reco::GenParticleCollection > particles;
edm::InputTag particles_;
ofstream myfile;

TH1D* howManyB;
TH1D* howManyMu;
TH1D* howManyE;
TH1D* pdgParts;
TH1D* bPt;
TH1D* bParent;
TH1D* howManyLL;




HiggsBB::HiggsBB(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
	particles_ = iConfig.getParameter<edm::InputTag>("particles");
	myfile.open("output.txt");

}


HiggsBB::~HiggsBB()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
  myfile.close();
}


//
// member functions
//

// ------------ method called for each event  ------------
void
HiggsBB::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace reco;
   using namespace std;
   iEvent.getByLabel(particles_,particles);
   int countB = 0;
   int countMu = 0;
   int countE = 0;
   int countLL = 0;
//   edm::Handle<std::vector<reco::GenParticle>> particles;
//   const std::vector<reco::GenParticle> & p = *particles;  
   // fstream myfile;
   //myfile.open ("/users/h2/grud/CMSSW_5_3_9/src/test/HiggsBB/output.txt"); 
  myfile << "************************NEW EVENT*****************************\n\n**************************************************************\n";
//   vector< TLorentzVector > p4;
//   TLorentzVector tempP4;

/*   for (unsigned int i=0; i<particles->size(); ++i){
	tempP4.SetPxPyPzE(p[i].px(),p[i].py(),p[i].pz(),p[i].energy());
	p4.push_back( tempP4 );
//	myfile << p[i].pdgId() << "      " << p[i].mother() << "     " << p4[i].Pt() << endl;	
   }
*/
int counter = 0;
for (reco::GenParticleCollection::const_iterator iParticle = particles->begin();      iParticle != particles->end(); ++iParticle){
/*	if (iParticle->status()!=3) continue;
	if (iParticle->pdgId()==21 || iParticle->pdgId()==22) continue; 
	pdgParts->Fill(iParticle->pdgId());
	if (iParticle->pdgId()==5 || iParticle->pdgId()==-5){
		countB++;
		bPt->Fill(iParticle->pt());
		std::cout << iParticle->mother()->pdgId() << std::endl;
		bParent->Fill(iParticle->mother()->pdgId());
	}
	if (iParticle->pdgId()==13 || iParticle->pdgId()==-13){
		countMu++;
	}
	if (iParticle->pdgId()==11 || iParticle->pdgId()==-11){
		countE++;
	}
	if (iParticle->pdgId()==6001112){
		countLL++;
	}*/
	counter ++;
	myfile << counter << "               "<< iParticle->mother() << "                " << iParticle->pdgId() << "               " << iParticle->px() << "               "  << iParticle->py() << "               " << iParticle->pz() << "               " << iParticle->mass() << "\n";	

     //   ofstream myfile;
	//	myfile.open ("/users/h2/grud/CMSSW_5_3_9/src/test/HiggsBB/output.txt");
	//	myfile << "************************NEW EVENT*****************************\n\n**************************************************************\n"
			
}

if (countB != 0) howManyB->Fill(countB);
if (countMu != 0) howManyMu->Fill(countMu);
if (countE != 0) howManyE->Fill(countE);
if (countLL != 0) howManyLL->Fill(countLL);

//bbBarDR = reco::deltaR(bEta, bPhi, bBarEta, bBarPhi);
//bbBarDRVsHiggsPt->Fill(iParticle->pt(),bbBarDR);
  
//myfile.close();   
   
}

// ------------ method called once each job just before starting event loop  ------------
void 
HiggsBB::beginJob()
{

howManyB = fs->make<TH1D>("howManyB","howManyB",20,0,20);
howManyMu = fs->make<TH1D>("howManyMu","howManyMu",10,0,10);
howManyE = fs->make<TH1D>("howManyE","howManyE",10,0,10);
pdgParts = fs->make<TH1D>("pdgParts","pdgParts",10000,0,10000);
bPt = fs->make<TH1D>("bPt","bPt",230,0,230);
bParent = fs->make<TH1D>("bParent","bParent",60,-10,50);
howManyLL = fs->make<TH1D>("howManyLL","howManyLL",20,0,20);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
HiggsBB::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
HiggsBB::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
HiggsBB::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
HiggsBB::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
HiggsBB::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HiggsBB::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HiggsBB);
