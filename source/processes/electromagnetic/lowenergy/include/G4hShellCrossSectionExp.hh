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
// -------------------------------------------------------------------
//
// GEANT4 Class file
//
//
// File name:  G4hShellCrossSectionExp   
//
// Author:     Simona Saliceti (simona.saliceti@ge.infn.it)
// 
// History:
// -----------
// From 23 Oct 2001 A. Mantero G4hShellCrossSection
// 30/03/2004 Simona Saliceti 1st implementation
// -------------------------------------------------------------------
// Class Description: 
// Empiric Model for shell cross sections in proton ionisation
// Based on Fitted empirical Reference Cross Sections for K-Shell Ionization 
// by Protons by H.Paul and J.Sacher, At. Data Nucl. Data Tables 42 (1989) 105

// -------------------------------------------------------------------
// $Id: G4hShellCrossSectionExp.hh,v 1.2 2004/11/26 08:50:47 pia Exp $
// GEANT4 tag $Name: geant4-08-00 $

#ifndef G4HSHELLCROSSSECTIONEXP_HH
#define G4HSHELLCROSSSECTIONEXP_HH 1

#include "globals.hh"
#include "G4VhShellCrossSection.hh" 
#include "G4hShellCrossSectionExpData.hh"

class G4hShellCrossSectionExp : public G4VhShellCrossSection
{
public:

  G4hShellCrossSectionExp();

  virtual ~G4hShellCrossSectionExp();

  virtual std::vector<G4double> GetCrossSection(G4int Z,
						G4double incidentEnergy,
						G4double mass,
						G4double deltaEnergy,
						G4bool testFlag = false) const;
 
  void SetTotalCS(G4double);
 
protected:

  virtual std::vector<G4double> Probabilities(G4int Z,
					      G4double incidentEnergy,
					      G4double mass,
					      G4double deltaEnergy) const;


private:

  G4double GetCrossSectionExp(G4int Z,
			      G4double incidentEnergy) const;

  // Hide copy constructor and assignment operator 
  G4hShellCrossSectionExp(const G4hShellCrossSectionExp&);
  G4hShellCrossSectionExp & operator = (const G4hShellCrossSectionExp &right);
  G4hShellCrossSectionExpData* kShellData;

  G4double atomTotalCrossSection;
};

#endif
