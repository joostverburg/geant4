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
// $Id: G3toG4MakeSolid.cc,v 1.7.2.1 2001/06/28 19:08:05 gunter Exp $
// GEANT4 tag $Name:  $
//
// modified by I.Hrivnacova, V.Berejnoi 27 Sep 99 

#include "globals.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G3toG4.hh"
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"
#include "G4Para.hh"
#include "G4Hype.hh"
#include "G4EllipticalTube.hh"
#include "G3toG4MakeSolid.hh"
        
G4VSolid* G3toG4MakeSolid(const G4String& vname, const G4String& shape, 
			  const G4double* Rpar, const G4int npar, 
			  G4bool& NegVolPars, G4bool& Deferred,
			  G4bool* OKAxis){
    
  // Create the solid if no negative length parameters
  G4VSolid *solid = 0;

  NegVolPars = false;

  // if npar = 0 assume LV deferral
  Deferred = (npar == 0);
  // modified
  if (Deferred) return solid;

  for (int i=0;i<3;i++){
    OKAxis[i]=false;
  };

  if ( shape == "BOX" ) {
    G4double pX = Rpar[0]*cm;
    G4double pY = Rpar[1]*cm;
    G4double pZ = Rpar[2]*cm;

    OKAxis[0]=OKAxis[1]=OKAxis[2]=true;
    
    NegVolPars = pX<0 || pY<0 || pZ<0;
    
    if (!(NegVolPars || Deferred)) { 
      solid = new G4Box(vname, pX, pY, pZ);
    }

  } else if ( shape == "TRD1" ) {
    G4double pdx1 = Rpar[0]*cm;
    G4double pdx2 = Rpar[1]*cm;
    G4double pdy1 = Rpar[2]*cm;
    G4double pdy2 = pdy1;
    G4double pdz  = Rpar[3]*cm;

    OKAxis[1]=OKAxis[2]=true;

    NegVolPars = pdx1<0 || pdx2<0 || pdy1<0 || pdz<0;

    if (!(NegVolPars || Deferred)) {
      solid = new G4Trd(vname, pdx1, pdx2, pdy1, pdy2, pdz);
    }

  } else if ( shape == "TRD2" ) {
    G4double pdx1 = Rpar[0]*cm;
    G4double pdx2 = Rpar[1]*cm;
    G4double pdy1 = Rpar[2]*cm;
    G4double pdy2 = Rpar[3]*cm;
    G4double pdz  = Rpar[4]*cm;

    OKAxis[2]=true;

    NegVolPars = pdx1<0 || pdx2<0 || pdy1<0 || pdy2<0 || pdz<0;
 
    if (!(NegVolPars || Deferred)) {
      solid = new G4Trd(vname, pdx1, pdx2, pdy1, pdy2, pdz);
    }

  } else if ( shape == "TRAP" ) {
    G4double pDz    = Rpar[0]*cm;
    G4double pTheta = Rpar[1]*deg;
    G4double pPhi   = Rpar[2]*deg;
    G4double pDy1   = Rpar[3]*cm;
    G4double pDx1   = Rpar[4]*cm;
    G4double pDx2   = Rpar[5]*cm;
    G4double pAlp1  = Rpar[6]*deg;
    G4double pDy2   = Rpar[7]*cm;
    G4double pDx3   = Rpar[8]*cm;
    G4double pDx4   = Rpar[9]*cm;
    G4double pAlp2  = Rpar[10]*deg;

    OKAxis[2]=true;

    NegVolPars= pDz<0 || pDy1<0 || pDx1<0 || pDx2<0 || pDy2<0 || pDx3<0 || pDx4<0;

    if (!(NegVolPars || Deferred)) {
      // added for test only 
      if (!(pDz>0))  pDz  += 0.001*cm;
      if (!(pDy1>0)) pDy1 += 0.001*cm;
      if (!(pDx1>0)) pDx1 += 0.001*cm;
      if (!(pDx2>0)) pDx2 += 0.001*cm;
      if (!(pDy2>0)) pDy2 += 0.001*cm;
      if (!(pDx3>0)) pDx3 += 0.001*cm;
      if (!(pDx4>0)) pDx4 += 0.001*cm;
    
      solid = new 
	G4Trap(vname, pDz, pTheta, pPhi, pDy1, pDx1, pDx2, pAlp1, pDy2, pDx3, 
	       pDx4, pAlp2);
    }

  } else if ( shape == "TUBE" ) {
    G4double pRMin = Rpar[0]*cm;
    G4double pRMax = Rpar[1]*cm;
    G4double pDz   = Rpar[2]*cm;
    G4double pSPhi = 0.*deg;
    G4double pDPhi = 360.*deg;
    
    OKAxis[0]=OKAxis[1]=OKAxis[2]=true;

    NegVolPars = pRMin<0 || pRMax<0 || pDz<0;
    
    if (!(NegVolPars || Deferred)) {
      solid = new G4Tubs(vname, pRMin, pRMax, pDz, pSPhi, pDPhi);
    }

  } else if ( shape == "TUBS" ) {
    G4double pRMin = Rpar[0]*cm;
    G4double pRMax = Rpar[1]*cm;
    G4double pDz   = Rpar[2]*cm;
    G4double pSPhi = Rpar[3]*deg;
    G4double pDPhi = Rpar[4]*deg - pSPhi;
    if ( Rpar[4]*deg <= pSPhi ) pDPhi = pDPhi + 360.*deg;

    OKAxis[0]=OKAxis[1]=OKAxis[2]=true;

    NegVolPars = pRMin<0 || pRMax<0 || pDz<0;

    if (!(NegVolPars || Deferred)){
      solid = new G4Tubs(vname, pRMin, pRMax, pDz, pSPhi, pDPhi);
    }

  } else if ( shape == "CONE" ) {
    G4double pDz    = Rpar[0]*cm;
    G4double pRmin1 = Rpar[1]*cm;
    G4double pRmax1 = Rpar[2]*cm;
    G4double pRmin2 = Rpar[3]*cm;
    G4double pRmax2 = Rpar[4]*cm;
    G4double pSPhi = 0.*deg;
    G4double pDPhi = 360.*deg;

    OKAxis[0]=OKAxis[1]=OKAxis[2]=true;

    NegVolPars = pDz<0 || pRmin1<0 || pRmax1<0 || pRmin2<0 || pRmax2<0;

    if (!(NegVolPars || Deferred)){
      solid = new 
	G4Cons(vname, pRmin1, pRmax1, pRmin2, pRmax2, pDz, pSPhi, pDPhi);
    }

  } else if ( shape == "CONS" ) {
    G4double pDz    = Rpar[0]*cm;
    G4double pRmin1 = Rpar[1]*cm;
    G4double pRmax1 = Rpar[2]*cm;
    G4double pRmin2 = Rpar[3]*cm;
    G4double pRmax2 = Rpar[4]*cm;
    G4double pSPhi  = Rpar[5]*deg;
    G4double pDPhi  = Rpar[6]*deg - pSPhi;
    if ( Rpar[6]*deg <= pSPhi ) pDPhi = pDPhi + 360.*deg;

    OKAxis[0]=OKAxis[1]=OKAxis[2]=true;

    NegVolPars = pDz<0 || pRmin1<0 || pRmax1<0 || pRmin2<0 || pRmax2<0;

    if (!(NegVolPars || Deferred)){
      solid = new 
	G4Cons(vname, pRmin1, pRmax1, pRmin2, pRmax2, pDz, pSPhi, pDPhi);
    }

  } else if ( shape == "SPHE" ) {
    G4double pRmin  = Rpar[0]*cm;
    G4double pRmax  = Rpar[1]*cm;
    G4double pThe1  = Rpar[2]*deg;
    G4double pThe2  = Rpar[3]*deg;
    G4double pDThe  = pThe2 - pThe1;
    G4double pPhi1  = Rpar[4]*deg;
    G4double pPhi2  = Rpar[5]*deg;
    G4double pDPhi  = pPhi2 - pPhi1;

    NegVolPars = pRmin<0 || pRmax<0;

    if (!(NegVolPars || Deferred)) {
      solid = new G4Sphere(vname, pRmin, pRmax, pPhi1, pDPhi, pThe1, pDThe);
    }

  } else if ( shape == "PARA" ) {
    G4double pDx = Rpar[0]*cm;
    G4double pDy = Rpar[1]*cm;
    G4double pDz = Rpar[2]*cm;
    G4double pAlph = Rpar[3]*deg;
    G4double pThet = Rpar[4]*deg;
    G4double pPhi  = Rpar[5]*deg;

    OKAxis[0]=OKAxis[1]=OKAxis[2]=true;

    NegVolPars = pDx<0 || pDy<0 || pDz<0;

    if (!(NegVolPars || Deferred)){
      solid = new G4Para(vname, pDx, pDy, pDz, pAlph, pThet, pPhi);
    }

  } else if ( shape == "PGON" ) {
    G4int i;
    G4int npdv = int(Rpar[2]);
    G4int nz = int(Rpar[3]);
    G4double pPhi1 = Rpar[0]*deg;
    G4double dPhi  = Rpar[1]*deg;
    G4double *DzArray = new G4double[nz];
    G4double *Rmax    = new G4double[nz];
    G4double *Rmin    = new G4double[nz];

    OKAxis[0]=OKAxis[1]=OKAxis[2]=true;

    NegVolPars = 0;

    for(i=0; i<nz; i++) {
      int i4=3*i+4;
      int i5=i4+1;
      int i6=i4+2;
      DzArray[i] = Rpar[i4]*cm;
      Rmin[i] = Rpar[i5]*cm;
      Rmax[i] = Rpar[i6]*cm;
    }
    solid = new G4Polyhedra(vname, pPhi1, dPhi, npdv, nz, DzArray, Rmin, Rmax);
    delete [] DzArray;
    delete [] Rmin;
    delete [] Rmax;

  } else if ( shape == "PCON" ) {
    G4int i;
    G4double pPhi1 =  Rpar[0]*deg;
    G4double dPhi  = Rpar[1]*deg;    
    G4int nz = int(Rpar[2]);
    G4double *DzArray = new G4double[nz];
    G4double *Rmax    = new G4double[nz];
    G4double *Rmin    = new G4double[nz];

    OKAxis[0]=OKAxis[1]=OKAxis[2]=true;

    NegVolPars = 0;

    for(i=0; i<nz; i++){
      int i4=3*i+3;
      int i5=i4+1;
      int i6=i4+2;
      DzArray[i] = Rpar[i4]*cm;
      Rmin[i] = Rpar[i5]*cm;
      Rmax[i] = Rpar[i6]*cm;
    }
    solid = new G4Polycone(vname, pPhi1, dPhi, nz, DzArray, Rmin, Rmax);
    delete [] DzArray;
    delete [] Rmin;
    delete [] Rmax;

  } else if ( shape == "ELTU" ) {
    G4double dX = Rpar[0]*cm;
    G4double dY = Rpar[1]*cm;
    G4double dZ = Rpar[2]*cm;

    OKAxis[0]=OKAxis[1]=OKAxis[2]=true;
    
    NegVolPars = dX<0 || dY<0 || dZ<0;
    
    if (!(NegVolPars || Deferred)) { 
      solid = new G4EllipticalTube(vname, dX, dY, dZ);
    }

  } else if ( shape == "HYPE" ) {
    G4double pRmin = Rpar[0]*cm;
    G4double pRmax = Rpar[1]*cm;
    G4double pDz   = Rpar[2]*cm;
    G4double pThet = Rpar[3]*deg;

    NegVolPars = pRmin<0 || pRmax<0 || pDz<0;

    if (!(NegVolPars || Deferred)){
      solid = new G4Hype(vname, pRmin, pRmax, pThet, pThet, pDz);
    } else {
      G4cerr << "Negative length parameters not supported for shape " 
	     << shape << G4endl;
    }

  } else if ( shape == "GTRA" ) {
    // $$$ not implemented.
    G4cerr << "GTRA not supported" << G4endl;

  } else if ( shape == "CTUB" ) {
    // $$$ not implemented.
    G4cerr << "CTUB not supported" << G4endl;
  }
  return solid;
}









