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
//
// $Id: PhysListEmG4v52.cc,v 1.1 2005/05/09 16:11:52 maire Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PhysListEmG4v52.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

#include "G4PhotoElectricEffect52.hh"
#include "G4ComptonScattering52.hh"
#include "G4GammaConversion52.hh"
#include "G4GammaConversionToMuons.hh"

#include "G4MultipleScattering52.hh"

#include "G4eIonisation52.hh"
#include "G4eBremsstrahlung52.hh"
#include "G4eplusAnnihilation52.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysListEmG4v52::PhysListEmG4v52(const G4String& name)
   :  G4VPhysicsConstructor(name)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysListEmG4v52::~PhysListEmG4v52()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysListEmG4v52::ConstructProcess()
{
  // Add EM processes realised on base of prototype of model approach design

  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
     
    if (particleName == "gamma") {
      // gamma         
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect52);
      pmanager->AddDiscreteProcess(new G4ComptonScattering52);
      pmanager->AddDiscreteProcess(new G4GammaConversion52);
      pmanager->AddDiscreteProcess(new G4GammaConversionToMuons);      
      
    } else if (particleName == "e-") {
      //electron
      pmanager->AddProcess(new G4MultipleScattering52, -1, 1,1);
      pmanager->AddProcess(new G4eIonisation52,        -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung52,    -1,-1,3);
	    
    } else if (particleName == "e+") {
      //positron
      pmanager->AddProcess(new G4MultipleScattering52, -1, 1,1);
      pmanager->AddProcess(new G4eIonisation52,        -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung52,    -1,-1,3);
      pmanager->AddProcess(new G4eplusAnnihilation52,   0,-1,4);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
