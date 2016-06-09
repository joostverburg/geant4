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
// $Id: G4VTrajectoryPoint.hh,v 1.12 2005/11/24 12:47:36 allison Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
//
//---------------------------------------------------------------
//
// G4VTrajectoryPoint.hh
//
// class description:
//   This class is the abstract base class which represents the point
//   which consists of a trajectory.
//   It includes information of a the point.
//
// ---------------------------------------------------------------

#ifndef G4VTrajectoryPoint_h
#define G4VTrajectoryPoint_h 1

#include "globals.hh"
#include <vector>
#include <map>
#include "G4ThreeVector.hh"

class G4AttDef;
class G4AttValue;

class G4VTrajectoryPoint
{
 public: // with description

 // Constructor/Destructor
   G4VTrajectoryPoint();
   virtual ~G4VTrajectoryPoint();

 // Operators
   G4bool operator==(const G4VTrajectoryPoint& right) const;

 // Get/Set functions
   virtual const G4ThreeVector GetPosition() const = 0;

 // Get method for a vector of auxiliary points
   virtual const std::vector<G4ThreeVector>* GetAuxiliaryPoints() const
   { return 0; }
   // If implemented by a derived class, returns a pointer to a list
   // of auxiliary points, e.g., intermediate points used during the
   // calculation of the step that can be used for drawing a smoother
   // trajectory.  The user must test the validity of this pointer.

 // Get method for HEPRep style attribute definitions
   virtual const std::map<G4String,G4AttDef>* GetAttDefs() const
   { return 0; }
   // If implemented by a derived class, returns a pointer to a map of
   // attribute definitions for the attribute values below.  The user
   // must test the validity of this pointer.  See G4Trajectory for an
   // example of a concrete implementation of this method.

 // Get method for HEPRep style attribute values
   virtual std::vector<G4AttValue>* CreateAttValues() const
   { return 0; }
   // If implemented by a derived class, returns a pointer to a list
   // of attribute values suitable, e.g., for picking.  Each must
   // refer to an attribute definition in the above map; its name is
   // the key.  The user must test the validity of this pointer (it
   // must be non-zero and conform to the G4AttDefs, which may be
   // checked with G4AttCheck) and delete the list after use.  See
   // G4Trajectory for an example of a concrete implementation of this
   // method and G4VTrajectory::ShowTrajectory for an example of its
   // use.

};

#endif

