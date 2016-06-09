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
// $Id: LHEP_BIC.hh,v 1.3 2005/12/05 18:25:06 vnivanch Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
//---------------------------------------------------------------------------
//
// ClassName: HadronPhysicsLHEP_BIC
//
// Author: 2002 J.P. Wellisch
//
// Modified:
//
//----------------------------------------------------------------------------
//
#ifndef TLHEP_BIC_h
#define TLHEP_BIC_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "CompileTimeConstraints.hh"

template<class T>
class TLHEP_BIC: public T
{
public:
  TLHEP_BIC(G4int ver = 1);
  virtual ~TLHEP_BIC();
  
public:
  // SetCuts() 
  virtual void SetCuts();

private:
  enum {ok = CompileTimeConstraints::IsA<T, G4VModularPhysicsList>::ok };
};
#include "LHEP_BIC.icc"
typedef TLHEP_BIC<G4VModularPhysicsList> LHEP_BIC;

// 2002 by J.P. Wellisch

#endif



