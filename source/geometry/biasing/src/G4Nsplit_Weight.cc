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
// $Id: G4Nsplit_Weight.cc,v 1.9 2003/06/16 16:51:06 gunter Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
// ----------------------------------------------------------------------
// GEANT 4 class source file
//
// G4Nsplit_Weight.cc
//
// ----------------------------------------------------------------------
#include "G4Nsplit_Weight.hh"

std::ostream& operator<<(std::ostream &out, 
			   const G4Nsplit_Weight &nw)
{
  out << "nw.fN = " << nw.fN << ", nw.fW = " << nw.fW;
  return out;
}
