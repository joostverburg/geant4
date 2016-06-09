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
// $Id: G4OpenGLXmVWidgetObject.cc,v 1.4 2001/07/11 10:08:58 gunter Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
//Virtual base class for all Motif widgets.

#ifdef G4VIS_BUILD_OPENGLXM_DRIVER

#include "G4OpenGLXmVWidgetObject.hh"

G4OpenGLXmVWidgetObject::G4OpenGLXmVWidgetObject ()
{}

G4OpenGLXmVWidgetObject::~G4OpenGLXmVWidgetObject ()
{}

G4OpenGLXmViewer* G4OpenGLXmVWidgetObject::GetView ()
{
  return pView;
}

void G4OpenGLXmVWidgetObject::ProcesspView () 
{
  cmap = pView->cmap;
  depth = pView->vi->depth;
  visual = pView->vi->visual;
  borcol = pView->borcol;
  bgnd = pView->bgnd;
  top = pView->toplevel;
}

#endif
