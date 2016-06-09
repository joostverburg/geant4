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
// $Id: G4ThreeMat.hh,v 1.9 2003/06/16 16:52:42 gunter Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
// ----------------------------------------------------------------------
// Class G4ThreeMat
//
// Class description:
// 
// Defines the class G4ThreeMat for three by three matrices.

// Author: Alan Breakstone
// Adaptation by: J.Sulkimo, P.Urban.
// Revisions by: L.Broglia, G.Cosmo.
// ----------------------------------------------------------------------
#ifndef __THREEMAT_H
#define __THREEMAT_H

#include "G4Vector3D.hh"

class G4ThreeMat
{

public:  // with description

  G4ThreeMat();
    // Default constructor.

  G4ThreeMat( G4double a[3][3] );
    // Normal constructors with a 3 x 3 array argument.

  virtual ~G4ThreeMat();
    // Destructor.

  G4ThreeMat( const G4ThreeMat& m );
  G4ThreeMat& operator=( const G4ThreeMat& m );
    // Copy constructor and assignment operator.

  G4int operator==( const G4ThreeMat& m ) const;
    // Equality operator.

  friend std::ostream& operator<<( std::ostream& os, const G4ThreeMat& m );

  virtual const char* NameOf() const;
    // Returns the class name.

  virtual void PrintOn( std::ostream& os = G4cout ) const;
    // Printing functions (derived classes do not need to overwrite operator <<).

  G4double Determinant() const;
    // Determinant of matrix.

private:

  G4double element[3][3];
  G4Vector3D row[3], column[3];
    // The elements exist individually and are also aggregated into rows and
    // columns to use operations already written for the G4Vector3Dc class.
};

#endif
