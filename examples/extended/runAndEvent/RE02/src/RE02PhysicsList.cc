//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
// $Id: RE02PhysicsList.cc,v 1.1 2005/11/24 01:44:18 asaim Exp $
// --------------------------------------------------------------
//
// 28-Jan-04 Add QGSP_BERT and QGSP_BIC for hadronic lists. T. Koi
// 22-Nov-04 Comment out QGSP_BERT and QGSP_BIC
//           Output Notificaiton message             
//           All Particles are created in GeneralPhysics 

#include "RE02PhysicsList.hh"

#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4ios.hh"
#include <iomanip>

#include "RE02GeneralPhysics.hh"
#include "RE02EMPhysics.hh"
#include "RE02MuonPhysics.hh"
#include "RE02HadronPhysics.hh"
#include "RE02IonPhysics.hh"

//#include "HadronPhysicsQGSP_BERT.hh"
//#include "HadronPhysicsQGSP_BIC.hh"

RE02PhysicsList::RE02PhysicsList():  G4VModularPhysicsList()
{

  G4cout << "You are using the RE02PhysicsList" << G4endl;
  G4cout << "This PhysicsList originally comes from "<<G4endl;
  G4cout << "example/extended/analysis/A01, and is modified "<<G4endl;
  G4cout << "in Hadron Physics in order to involve Binary Cascade" << G4endl;
  G4cout << "at low energy region and inelastic process for generic ions. "<<G4endl;
  G4cout << "Full set of particles (barions bosons and mesons) will be created and" << G4endl;
  G4cout << "Standard EM Physics and Low & High Energy parameterized models will be applied." << G4endl;
  G4cout << "RE02PhysicsList is optimized for robustness" << G4endl;
  G4cout << "and not for any particular usage." << G4endl;
  G4cout << "For the hadronic physics, educated guesses of physics list are prepared for various use cases." << G4endl;
  G4cout << "When you will start REAL calculations for your own interest," << G4endl;
  G4cout << "please consider the usage of hadronic_lists instead of RE02PhysicsLists." << G4endl;
  G4cout << "More information can also be found from the Geant4 HyperNews." << G4endl;
  G4cout << "http://geant4-hn.slac.stanford.edu:5090/Geant4-HyperNews/index" << G4endl;
  G4cout << "" << G4endl;

  // default cut value  (1.0mm)
  defaultCutValue = 1.0*mm;
  SetVerboseLevel(1);

  // General Physics ( Create ALL Particle and apply Decay )
  RegisterPhysics( new RE02GeneralPhysics("general") );

  // EM Physics ( Apply related Processes to gamma and e-/+)
  RegisterPhysics( new RE02EMPhysics("standard EM"));

  // Muon Physics ( Apply related processes to mu and tau
  RegisterPhysics(  new RE02MuonPhysics("muon"));

   // Hadron Physics ( Apply related processes to hadrons )
   RegisterPhysics(  new RE02HadronPhysics("hadron"));
// We do not use hadronic lists since v7.
  //RegisterPhysics(  new HadronPhysicsQGSP_BERT("hadron"));
  //RegisterPhysics(  new HadronPhysicsQGSP_BIC("hadron"));

  // Ion Physics ( Apply related processes to ions )
  RegisterPhysics( new RE02IonPhysics("ion"));

}

RE02PhysicsList::~RE02PhysicsList()
{
}

void RE02PhysicsList::SetCuts()
{
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets
  //   the default cut value for all particle types
  SetCutsWithDefault();
}



