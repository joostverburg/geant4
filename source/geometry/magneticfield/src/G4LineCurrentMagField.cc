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
// $Id: G4LineCurrentMagField.cc,v 1.5 2004/12/02 09:55:20 gcosmo Exp $
// GEANT4 tag $Name: geant4-08-00 $
// -------------------------------------------------------------------

#include "G4LineCurrentMagField.hh"
#include "globals.hh"

G4LineCurrentMagField::G4LineCurrentMagField(G4double pFieldConstant)
{
   fFieldConstant = pFieldConstant ;
}
////////////////////////////////////////////////////////////////////////

G4LineCurrentMagField::~G4LineCurrentMagField()
{
}

///////////////////////////////////////////////////////////////////////////


void G4LineCurrentMagField::GetFieldValue( const G4double yTrack[7],
                                                 G4double B[3]      ) const  
{
   //   G4double fFieldConstant = 100 ;
   G4double a = 1.00*mm ;   // mm -> m 
   G4double x = a*yTrack[0], y = a*yTrack[1] ;
   G4double x2 = x*x, y2 = y*y, r2 = x2 + y2 ;
   G4double r = std::sqrt(r2+a*a) ;
   G4double Br = fFieldConstant/r;
   B[0] = -Br*y/r ;
   B[1] = Br*x/r ;
   B[2] = 0 ;
}

// -----------------------------------------------------------------
