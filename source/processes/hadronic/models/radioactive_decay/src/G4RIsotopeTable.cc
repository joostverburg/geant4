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
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// MODULE:              G4RIsotopeTable.cc
//
// Version:             0.b.4
// Date:                14/04/00
// Author:              F Lei & P R Truscott
// Organisation:        DERA UK
// Customer:            ESA/ESTEC, NOORDWIJK
// Contract:            12115/96/JG/NL Work Order No. 3
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// CHANGE HISTORY
// --------------
//
// 29 February 2000, P R Truscott, DERA UK
// 0.b.3 release.
//
// 14 April 2000, F Lei, DERA UK
// 0.b.4 release. Minor changes to 
//            1) levelTolerance = 2.0 keV
//            2) changes to verbose control
//
// 18,July 2001 F.Lei
//  tidy up the print out at run level
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
///////////////////////////////////////////////////////////////////////////////
//
#include "G4DecayTable.hh"
#include "G4ParticleTable.hh"
#include "G4IsotopeProperty.hh"
#include "G4RIsotopeTable.hh"

#include "G4HadronicException.hh"

/*
#include "G4RadioactiveDecayMode.hh"
#include "G4ITDecayChannel.hh"
#include "G4BetaMinusDecayChannel.hh"
#include "G4BetaPlusDecayChannel.hh"
#include "G4KshellECDecayChannel.hh"
#include "G4LshellECDecayChannel.hh"
#include "G4AlphaDecayChannel.hh"
*/
#include "G4ios.hh"
#include "globals.hh"
#include <iomanip>
#include <fstream>
#include <strstream>

const G4double G4RIsotopeTable::levelTolerance = 2.0*keV;

///////////////////////////////////////////////////////////////////////////////
//
G4RIsotopeTable::G4RIsotopeTable()
{
  ;
}

///////////////////////////////////////////////////////////////////////////////
//
G4RIsotopeTable::~G4RIsotopeTable()
{
  fIsotopeList.clear();
  fIsotopeNameList.clear(); 
}
///////////////////////////////////////////////////////////////////////////////
//
G4int G4RIsotopeTable::GetVerboseLevel() const
{
  return G4ParticleTable::GetParticleTable()->GetVerboseLevel();
}
///////////////////////////////////////////////////////////////////////////////
//
G4bool G4RIsotopeTable::FindIsotope(G4IsotopeProperty* )
{
  // do nothing, it is here just for the compiler
  // it is required by the base class
  return true;
}
///////////////////////////////////////////////////////////////////////////////
//
G4IsotopeProperty* G4RIsotopeTable::GetIsotope(G4int Z, G4int A, G4double E)
{
  G4String fname = GetIsotopeName(Z, A, E);  
  G4int j = -1;
  for (G4int i = 0 ; i< Entries(); i++) {
    if(fIsotopeNameList[i] == fname) j = i;}
  if (j >=0) {
    if (GetVerboseLevel()>0) {
    G4cout <<"G4RIsotopeTable::GetIsotope No. : ";
    G4cout <<j<<G4endl;   
    }
    return  GetIsotope(j);}
  // isotope property data has been loaded already and just return the pointer
  else{
    G4double meanlife = GetMeanLifeTime(Z, A, E);
    // E is pass as a refence hence on entry E is supplied by the user and it 
    // could be slightly different from the returned value which is the one 
    // defined in the database.
    // this call is to ensure the code uses a consistane E value through out.
    //
    
    G4IsotopeProperty* fProperty = new G4IsotopeProperty();   
    // Set Isotope Property
    fProperty->SetLifeTime(meanlife);
    fProperty->SetAtomicNumber(Z);
    fProperty->SetAtomicMass(A);
    // Notic that the value of E may have been changed
    fProperty->SetEnergy(E);
    // The spin is not being used in the current implementation
    fProperty->SetiSpin(0);
    // the decaytable will be loaded later in G4RadioactiveDecay when it is needed
    fProperty->SetDecayTable(0);
    
    fIsotopeList.push_back(fProperty);
    fname = GetIsotopeName(Z, A, E);
    fIsotopeNameList.push_back(fname);
    if (GetVerboseLevel()>0) {
      G4cout <<"G4RIsotopeTable::GetIsotope create: ";
      G4cout <<fname <<G4endl;  
    }
    return fProperty;

  }
}
///////////////////////////////////////////////////////////////////////////////
//
G4String G4RIsotopeTable::GetIsotopeName(G4int Z, G4int A, G4double E)  
{
  G4String name;
  char val[50];
  std::ostrstream os(val,50);
  os.setf(std::ios::fixed);
  os <<"A"<< A << "Z" << Z <<'[' << std::setprecision(1) << E/keV << ']' << '\0';
  name = val;
  if (GetVerboseLevel()>0) {
    G4cerr <<"G4RIsotopeTable::GetIsotope Name: ";
    G4cerr <<name <<G4endl;   
  }
  return name;
}
///////////////////////////////////////////////////////////////////////////////
//
G4double G4RIsotopeTable::GetMeanLifeTime (G4int Z, G4int A, G4double& aE)
{
  G4double lifetime = -1.0;
  //  G4double  levelTolerance = 1.0 * keV ;
  if ( !getenv("G4RADIOACTIVEDATA")) {
    G4cout << "Please setenv G4RADIOACTIVEDATA to point to the radioactive decay data files." << G4endl;
    throw G4HadronicException(__FILE__, __LINE__, 
			      "Please setenv G4RADIOACTIVEDATA to point to the radioactive decay data files.");
  }
  G4String dirName = getenv("G4RADIOACTIVEDATA");

  char val[100];
  std::ostrstream os(val,100);
  os <<dirName <<"/z" <<Z <<".a" <<A <<'\0';
  G4String file(val);
  std::ifstream DecaySchemeFile(file);

  if (!DecaySchemeFile )
  {
    if (GetVerboseLevel()>0) {
      G4cout <<"G4RIsotopeTable::GetMeanLife() : "
	     <<"cannot find ion radioactive decay file: " 
	     <<file <<G4endl;
      G4cout <<"The nucleus is assumed to be stable " <<G4endl;
    }
  }
  else
  {
    G4bool found(false);
    char inputChars[80]={' '};
    G4String inputLine;
    G4String recordType("");
    G4double a(0.0);
    G4double b(0.0);

    while (!found && -DecaySchemeFile.getline(inputChars, 80).eof() != EOF)
    {
      inputLine = inputChars;
      //G4String::stripType stripend(1);
      //G4String::stripType stripend =trailing;
      inputLine = inputLine.strip(1);

      if (inputChars[0] != '#' && inputLine.length() != 0)
      {
        std::istrstream tmpstream(inputLine);
 //       tmpstream = inputLine;
        tmpstream >>recordType >>a >>b;
        if (recordType == "P")
        {
          if (std::abs(a*keV-aE) < levelTolerance)
          {
            found    = true;
            lifetime = b/0.693147*s ;
	    // in the database was half-life!
	    //   aE = a*keV;
	    // pass back the correct energy
          }
        }
      }
    }
    if (!found && aE )
      {
	if (GetVerboseLevel()>0) {
	  G4cout <<"G4RIsotopeTable::GetMeanLife() : ";
	  G4cout <<"cannot find ion of required excitation E = " << aE << G4endl;
	  G4cout <<"state in radioactive data file " <<G4endl;
	  G4cout <<"The nucleus is assumed to be IT decayed with life = 1E-20 s" <<G4endl;
	  G4cout <<" -----------* THIS MAY CAUSE PROBLEM IN ITS DECAY-----------" <<G4endl; 
	  lifetime = 1.0E-20*s;
	}
      }
    if (!found && !aE )
      {
	if (GetVerboseLevel()>0) {
	  G4cout <<"G4RIsotopeTable::GetMeanLife() : ";
	  G4cout <<"cannot find ion of required excitation E = " << aE << G4endl;
	  G4cout <<"state in radioactive data file " <<G4endl;
	  G4cout <<"The nucleus is assumed to be stable" <<G4endl;
	  lifetime = -1.0;
	}
      }
    DecaySchemeFile.close();
  }
  if (GetVerboseLevel()>0) {
    G4cout <<"G4RIsotopeTable::GetMeanLifeTime: ";
    G4cout <<lifetime << " for " << GetIsotopeName(Z, A, aE) <<G4endl;   
  }
  return lifetime;
}
///////////////////////////////////////////////////////////////////////////////
//













