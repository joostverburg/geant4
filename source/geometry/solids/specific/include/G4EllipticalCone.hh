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
// $Id: G4EllipticalCone.hh,v 1.5 2005/11/09 15:04:28 gcosmo Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
//
// --------------------------------------------------------------------
// GEANT 4 class header file
//
// G4EllipticalCone
//
// Class description:
//
// G4EllipticalCone is a full cone with elliptical base which can be cut in Z.
//
// Member Data:
//
//      xSemiAxis       semi-axis, x
//      ySemiAxis       semi-axis, y
//      zheight         height, z
//      zTopCut         upper cut plane level, z 
//
// The height in Z corresponds to where the elliptical cone hits the 
// Z-axis if it had no Z cut. Also the cone is centered at zero having a
// base at zTopCut and another at -zTopCut. The semi-major axes at the Z=0
// plane are given by xSemiAxis*zheight and ySemiAxis*zheight so that the
// curved surface of our cone satisfies the equation: 
//
// ***************************************************************************
// *                                                                         *
// *           (x/xSemiAxis)^2 + (y/ySemiAxis)^2 = (zheight - z)^2           * 
// *                                                                         *
// ***************************************************************************
//
// Author:
//   Dionysios Anninos, 8.9.2005
//
// --------------------------------------------------------------------
#ifndef G4EllipticalCone_HH
#define G4EllipticalCone_HH

#include "G4VSolid.hh"

class G4EllipticalCone : public G4VSolid
{
  public:  // with description
   
    G4EllipticalCone(const G4String& pName,
                           G4double  pxSemiAxis,
                           G4double  pySemiAxis,
                           G4double  zMax,
                           G4double  pzTopCut);

    virtual ~G4EllipticalCone();

    // Access functions
    //
    inline G4double GetSemiAxisMax () const;
    inline G4double GetZTopCut() const;
    inline void SetSemiAxis (G4double x, G4double y, G4double z);
    inline void SetZCut (G4double newzTopCut);
    inline G4double GetCubicVolume(); 

    // Solid standard methods
    //
    G4bool CalculateExtent(const EAxis pAxis,
                           const G4VoxelLimits& pVoxelLimit,
                           const G4AffineTransform& pTransform,
                                 G4double& pmin, G4double& pmax) const;

    EInside Inside(const G4ThreeVector& p) const;

    G4ThreeVector SurfaceNormal( const G4ThreeVector& p) const;

    G4double DistanceToIn(const G4ThreeVector& p,
                          const G4ThreeVector& v) const;

    G4double DistanceToIn(const G4ThreeVector& p) const;

    G4double DistanceToOut(const G4ThreeVector& p,
                           const G4ThreeVector& v,
                           const G4bool calcNorm=G4bool(false),
                                 G4bool *validNorm=0,
                                 G4ThreeVector *n=0) const;

    G4double DistanceToOut(const G4ThreeVector& p) const;

    G4GeometryType GetEntityType() const;
  
    G4ThreeVector GetPointOnSurface() const;

    std::ostream& StreamInfo(std::ostream& os) const;

    // Visualisation functions
    //
    G4Polyhedron* GetPolyhedron () const;
    void DescribeYourselfTo(G4VGraphicsScene& scene) const;
    G4VisExtent   GetExtent() const;
    G4Polyhedron* CreatePolyhedron() const;
    G4NURBS*      CreateNURBS() const;
       
  public:  // without description

    G4EllipticalCone(__void__&);
      // Fake default constructor for usage restricted to direct object
      // persistency for clients requiring preallocation of memory for
      // persistifiable objects.

  protected:  // without description
 
    G4ThreeVectorList* CreateRotatedVertices(const G4AffineTransform& pT,
                                                   G4int& noPV) const;

    mutable G4Polyhedron* fpPolyhedron;

  private:

    G4double fCubicVolume;
    G4double xSemiAxis, ySemiAxis, zheight,
             semiAxisMax, zTopCut;
};

#include "G4EllipticalCone.icc"

#endif
