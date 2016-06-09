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
// $Id: G4MaterialTable.hh,v 1.5 2003/06/16 16:56:21 gunter Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
// 
// ------------------------------------------------------------
//	GEANT 4 class header file 
//
//      ----------------  G4MaterialTable  ----------------
// History:
// First implementation: Torre Wenaus, November 1995
// ------------------------------------------------------------
 
#ifndef G4MATERIALTABLE_HH
#define G4MATERIALTABLE_HH

class G4Material;

typedef std::vector<G4Material*> G4MaterialTable;

#endif
