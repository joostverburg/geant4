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
// $Id: G4OpenGLImmediateSceneHandler.hh,v 1.8 2005/09/05 11:02:38 allison Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
// 
// Andrew Walkden  10th February 1997
// G4OpenGLImmediateSceneHandler - no Display lists.

#ifdef G4VIS_BUILD_OPENGL_DRIVER

#ifndef G4OPENGLIMMEDIATESCENEHANDLER_HH
#define G4OPENGLIMMEDIATESCENEHANDLER_HH

#include "G4VSceneHandler.hh"
#include "G4OpenGLViewer.hh"
#include "G4OpenGLImmediateViewer.hh"
#include "globals.hh"
#include "G4RotationMatrix.hh"
#include "G4OpenGLSceneHandler.hh"

class G4OpenGLImmediate;

class G4OpenGLImmediateSceneHandler: public G4OpenGLSceneHandler {

public:
  G4OpenGLImmediateSceneHandler (G4VGraphicsSystem& system, const G4String& name);
  virtual ~G4OpenGLImmediateSceneHandler ();
  void BeginPrimitives (const G4Transform3D& objectTransformation);
  void EndPrimitives ();
  void BeginModeling ();
  void EndModeling ();
  void ClearTransientStore ();

private:
  void RequestPrimitives (const G4VSolid& solid);
  static G4int    fSceneIdCount;  // static counter for OpenGLImmediate scenes.
};

#endif

#endif
