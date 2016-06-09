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
// $Id: G4OpenGLXmStyleCallbacks.cc,v 1.12 2005/10/13 17:30:08 allison Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
// 
// Andrew Walkden  16th April 1997
// G4OpenGLXmStyleCallbacks : 
//                       Several callback functions used by
//                       elements of the control panel to
//                       determine how to visualize the view.

#ifdef G4VIS_BUILD_OPENGLXM_DRIVER

#include "G4OpenGLXmViewer.hh"

#include "G4OpenGLViewerDataStore.hh"

void G4OpenGLXmViewer::drawing_style_callback (Widget w, 
					     XtPointer clientData, 
					     XtPointer) 
{
  G4long choice = (G4long)clientData;
  G4OpenGLXmViewer* pView;
  XtVaGetValues (XtParent(w),
		 XmNuserData, &pView,
		 NULL);
  G4ViewParameters::DrawingStyle style;

  switch (choice) {
    
  case 0:
    style = G4ViewParameters::wireframe;
    break;

  case 1:
    style = G4ViewParameters::hlr;
    break;

  case 2:
    style = G4ViewParameters::hsr;
    break;

  case 3:
    style = G4ViewParameters::hlhsr;
    break;

  default:
    style = G4ViewParameters::wireframe;
    G4Exception("Unrecognised case in drawing_style_callback.");
  }

  pView->fVP.SetDrawingStyle (style);
  
  pView->SetView ();
  pView->ClearView ();
  pView->DrawView ();
}

void G4OpenGLXmViewer::rep_style_callback (Widget w, 
					 XtPointer clientData, 
					 XtPointer) 
{
  G4long choice = (G4long)clientData;
  G4OpenGLXmViewer* pView;
  XtVaGetValues (XtParent(w),
		 XmNuserData, &pView,
		 NULL);
  G4ViewParameters::RepStyle style;

  switch (choice) {
    
  case 0:
    style = G4ViewParameters::polyhedron;
    break;

  case 1:
    style = G4ViewParameters::nurbs;
    break;

  default:
    style = G4ViewParameters::polyhedron;
    G4Exception("Unrecognised case in rep_style_callback.");
  }

  pView->fVP.SetRepStyle (style);

  pView->SetView ();
  pView->ClearView ();
  pView->DrawView ();
}

void G4OpenGLXmViewer::background_color_callback (Widget w, 
						XtPointer clientData, 
						XtPointer) 
{
  G4long choice = (G4long)clientData;
  G4OpenGLXmViewer* pView;
  XtVaGetValues (XtParent(w),
		 XmNuserData, &pView,
		 NULL);


  //I need to revisit the kernel if the background colour changes and
  //hidden line removal is enabled, because hlr drawing utilises the
  //background colour in its drawing...
  // (Note added by JA 13/9/2005) Background now handled in view
  // parameters.  A kernel visit is triggered on change of background.
  switch (choice) {
    
  case 0:
    ((G4ViewParameters&)pView->GetViewParameters()).
      SetBackgroundColour(G4Colour(1.,1.,1.));  // White
    break;

  case 1:
    ((G4ViewParameters&)pView->GetViewParameters()).
      SetBackgroundColour(G4Colour(0.,0.,0.));  // Black
    break;

  default:
    G4Exception("Unrecognised case in background_color_callback.");
  }

  pView->SetView ();
  pView->ClearView ();
  pView->DrawView ();
}

void G4OpenGLXmViewer::transparency_callback (Widget w, 
					    XtPointer clientData, 
					    XtPointer) 
{
  G4long choice = (G4long)clientData;
  G4OpenGLXmViewer* pView;
  XtVaGetValues (XtParent(w),
		 XmNuserData, &pView,
		 NULL);

  switch (choice) {
    
  case 0:
    pView->transparency_enabled = false;
    G4OpenGLViewerDataStore::SetTransparencyEnabled(pView, false);
    break;

  case 1:
    pView->transparency_enabled = true;
    G4OpenGLViewerDataStore::SetTransparencyEnabled(pView, true);
    break;

  default:
    G4Exception("Unrecognised case in transparency_callback.");
  }

  pView->SetNeedKernelVisit (true);
  pView->SetView ();
  pView->ClearView ();
  pView->DrawView ();
}

void G4OpenGLXmViewer::antialias_callback (Widget w, 
					 XtPointer clientData, 
					 XtPointer) 
{
  G4long choice = (G4long)clientData;
  G4OpenGLXmViewer* pView;
  XtVaGetValues (XtParent(w),
		 XmNuserData, &pView,
		 NULL);

  switch (choice) {
    
  case 0:
    pView->antialiasing_enabled = false;
    glDisable (GL_LINE_SMOOTH);
    glDisable (GL_POLYGON_SMOOTH);
    break;

  case 1:
    pView->antialiasing_enabled = true;
    glEnable (GL_LINE_SMOOTH);
    glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable (GL_POLYGON_SMOOTH);
    glHint (GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    break;

  default:
    G4Exception("Unrecognised case in antialiasing_callback.");
  }

  pView->SetView ();
  pView->ClearView ();
  pView->DrawView ();
}

void G4OpenGLXmViewer::haloing_callback (Widget w, 
				       XtPointer clientData, 
				       XtPointer) 
{
  G4long choice = (G4long)clientData;
  G4OpenGLXmViewer* pView;
  XtVaGetValues (XtParent(w),
		 XmNuserData, &pView,
		 NULL);

  switch (choice) {
    
  case 0:
    pView->haloing_enabled = false;
    break;

  case 1:
    pView->haloing_enabled = true;
    break;

  default:
    G4Exception("Unrecognised case in haloing_callback.");
  }

  pView->SetView ();
  pView->ClearView ();
  pView->DrawView ();
}

void G4OpenGLXmViewer::aux_edge_callback (Widget w, 
				       XtPointer clientData, 
				       XtPointer) 
{
  G4long choice = (G4long)clientData;
  G4OpenGLXmViewer* pView;
  XtVaGetValues (XtParent(w),
		 XmNuserData, &pView,
		 NULL);

  switch (choice) {
    
  case 0:
    pView->fVP.SetAuxEdgeVisible(false);
    break;

  case 1:
    pView->fVP.SetAuxEdgeVisible(true);
    break;

  default:
    G4Exception("Unrecognised case in aux_edge_callback.");
  }

  pView->SetNeedKernelVisit (true);
  pView->SetView ();
  pView->ClearView ();
  pView->DrawView ();
}

void G4OpenGLXmViewer::projection_callback (Widget w, 
					  XtPointer clientData, 
					  XtPointer) 
{
  G4OpenGLXmViewer* pView = (G4OpenGLXmViewer*)clientData;

  G4int choice = get_int_userData (w);

  switch (choice) {
  case 0:
    {
      pView->fVP.SetFieldHalfAngle (0.);
      break;
    }

  case 1:
    {
      if (pView->fov > 89.5 || pView->fov <= 0.0) {
	G4cout << "Field half angle should be 0 < angle <= 89.5 degrees.";
	G4cout << G4endl;
      }
      else {
	pView->fVP.SetFieldHalfAngle (pView->fov * deg);
      }
      break;
    }
  default:
    {
      G4Exception("Unrecognised choice made in projection_callback");
    }
  }

  pView->SetView ();
  pView->ClearView ();
  pView->DrawView ();
}  

#endif

