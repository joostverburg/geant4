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
// $Id: G4BREPSolidOpenPCone.cc,v 1.10 2005/11/09 15:01:25 gcosmo Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
// ----------------------------------------------------------------------
// GEANT 4 class source file
//
// G4BREPSolidOpenPCone.cc
//
// ----------------------------------------------------------------------

#include "G4BREPSolidOpenPCone.hh"
#include "G4BREPSolidPCone.hh"
#include "G4Tubs.hh"
#include "G4VGraphicsScene.hh"

G4BREPSolidOpenPCone::G4BREPSolidOpenPCone
                                  (const G4String& name,
                                   G4double start_angle,
                                   G4double opening_angle,
                                   G4int    num_z_planes, // sections,
                                   G4double z_start,                 
                                   G4double z_values[],
                                   G4double RMIN[],
                                   G4double RMAX[]
                                   )
 : G4IntersectionSolid ( name,
                         new G4BREPSolidPCone( name,
                                               start_angle, opening_angle, 
                                               num_z_planes, z_start, z_values,
                                               RMIN, RMAX
                                             ),
                         new G4Tubs( "IntersectionTubs",
                                     0., 1., 1., start_angle, opening_angle
                                   )
                       )
   //, constructorParams.z_values( 0 ), constructorParams.RMIN( 0 ), constructorParams.RMAX( 0 )
{

// compute max radius

  G4double MaxRMAX = 0;
  for ( int i = 0; i < num_z_planes; i++ ) 
    if ( RMAX[i] > MaxRMAX ) MaxRMAX = RMAX[i];
  		
  G4double length = z_values[num_z_planes-1] - z_values[0];
  
  ((G4Tubs*)fPtrSolidB)->SetOuterRadius ( MaxRMAX );
  ((G4Tubs*)fPtrSolidB)->SetZHalfLength ( length );

}

G4BREPSolidOpenPCone::G4BREPSolidOpenPCone( __void__& a )
  : G4IntersectionSolid(a)
{
}

G4BREPSolidOpenPCone::~G4BREPSolidOpenPCone()
{
}

void G4BREPSolidOpenPCone::DescribeYourselfTo (G4VGraphicsScene& scene) const
{
  scene.AddSolid ( *this );
}

// Streams solid contents to output stream.
std::ostream& G4BREPSolidOpenPCone::StreamInfo(std::ostream& os) const
{  
  G4IntersectionSolid::StreamInfo( os );

  return os;
}

