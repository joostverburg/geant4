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
/*
  This file only serves as a place-holder for the annotations of G4String class,
  which is a type alias in Geant4. 
  
  Only the marshaling code (MarshaledG4String.hh) generated from this file
   should be used in your code. Please make sure that this G4String.hh
   itself is NOT included in your code. Otherwise, it will override Geant4's
   valid G4String class and bad things would happen.

  vietha 2003.05.08
*/

#ifndef __G4String
#define __G4String

//MSH_BEGIN
class G4String : public std::string
{
    int dummy; /*MSH: manual
    { memcpy($$, param->c_str(), param->size());
    *($$+param->size()) = '\0'; 
    }
    { G4String* s = new G4String($$);
       memcpy(param, s, sizeof(G4String));
     }
     { int size = param->size()+1;
       while(size%8) size++;
       $SIZE = size; } */
};
//MSH_END
#endif
