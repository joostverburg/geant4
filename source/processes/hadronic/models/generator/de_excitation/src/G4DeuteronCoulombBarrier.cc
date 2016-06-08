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
// $Id: G4DeuteronCoulombBarrier.cc,v 1.2.2.1 2001/06/28 19:13:12 gunter Exp $
// GEANT4 tag $Name:  $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (Dec 1999)


#include "G4DeuteronCoulombBarrier.hh"

G4DeuteronCoulombBarrier::G4DeuteronCoulombBarrier(const G4DeuteronCoulombBarrier & right)
{
    G4Exception("G4DeuteronCoulombBarrier::copy_constructor meant to not be accessable.");
}


const G4DeuteronCoulombBarrier & G4DeuteronCoulombBarrier::operator=(const G4DeuteronCoulombBarrier & right)
{
    G4Exception("G4DeuteronCoulombBarrier::operator= meant to not be accessable.");
    return *this;
}

G4bool G4DeuteronCoulombBarrier::operator==(const G4DeuteronCoulombBarrier & right) const 
{
    return false;
}

G4bool G4DeuteronCoulombBarrier::operator!=(const G4DeuteronCoulombBarrier & right) const 
{
    return true;
}


G4double G4DeuteronCoulombBarrier::BarrierPenetrationFactor(const G4double aZ) const
{
    // Data comes from 
    // Dostrovsky, Fraenkel and Friedlander
    // Physical Review, vol 116, num. 3 1959
    // 
    // const G4int size = 5;
    // const G4double Zlist[size] = {10.0, 20.0, 30.0, 50.0, 70.0};
    // const G4double Kprot[size] = {0.42, 0.58, 0.68, 0.77, 0.80};
    // 
    // K for deuteron is K for protons + 0.06
    G4double K = 1.0;
    if (aZ>=70.0) {
	K = 0.80;
    } else {
	K = (((0.2357e-5*aZ) - 0.42679e-3)*aZ + 0.27035e-1)*aZ + 0.19025;
    }
    return K+0.06;
}