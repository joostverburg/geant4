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
// $Id: G4SmoothTrajectory.cc,v 1.15 2005/05/03 17:48:51 allison Exp $
// GEANT4 tag $Name: geant4-08-00 $
//
//
// ---------------------------------------------------------------
//
// G4SmoothTrajectory.cc
//
// Contact:
//   Questions and comments to this code should be sent to
//     Katsuya Amako  (e-mail: Katsuya.Amako@kek.jp)
//     Makoto  Asai   (e-mail: asai@kekvax.kek.jp)
//     Takashi Sasaki (e-mail: Takashi.Sasaki@kek.jp)
//
// ---------------------------------------------------------------

#include "G4SmoothTrajectory.hh"
#include "G4SmoothTrajectoryPoint.hh"
#include "G4ParticleTable.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"

//#define G4ATTDEBUG
#ifdef G4ATTDEBUG
#include "G4AttCheck.hh"
#endif

G4Allocator<G4SmoothTrajectory> aSmoothTrajectoryAllocator;

G4SmoothTrajectory::G4SmoothTrajectory()
:  positionRecord(0), fTrackID(0), fParentID(0),
   PDGEncoding( 0 ), PDGCharge(0.0), ParticleName(""),
   initialMomentum( G4ThreeVector() )
{;}

G4SmoothTrajectory::G4SmoothTrajectory(const G4Track* aTrack)
{
   G4ParticleDefinition * fpParticleDefinition = aTrack->GetDefinition();
   ParticleName = fpParticleDefinition->GetParticleName();
   PDGCharge = fpParticleDefinition->GetPDGCharge();
   PDGEncoding = fpParticleDefinition->GetPDGEncoding();
   fTrackID = aTrack->GetTrackID();
   fParentID = aTrack->GetParentID();
   initialMomentum = aTrack->GetMomentum();
   positionRecord = new TrajectoryPointContainer();
   // Following is for the first trajectory point
   positionRecord->push_back(new G4SmoothTrajectoryPoint(aTrack->GetPosition()));

   // The first point has no auxiliary points, so set the auxiliary
   // points vector to NULL (jacek 31/10/2002)
   positionRecord->push_back(new G4SmoothTrajectoryPoint(aTrack->GetPosition(), NULL));
}

G4SmoothTrajectory::G4SmoothTrajectory(G4SmoothTrajectory & right):G4VTrajectory()
{
  ParticleName = right.ParticleName;
  PDGCharge = right.PDGCharge;
  PDGEncoding = right.PDGEncoding;
  fTrackID = right.fTrackID;
  fParentID = right.fParentID;
  initialMomentum = right.initialMomentum;
  positionRecord = new TrajectoryPointContainer();

  for(size_t i=0;i<right.positionRecord->size();i++)
  {
    G4SmoothTrajectoryPoint* rightPoint = (G4SmoothTrajectoryPoint*)((*(right.positionRecord))[i]);
    positionRecord->push_back(new G4SmoothTrajectoryPoint(*rightPoint));
  }
}

G4SmoothTrajectory::~G4SmoothTrajectory()
{
  //  positionRecord->clearAndDestroy();
  size_t i;
  for(i=0;i<positionRecord->size();i++){
    delete  (*positionRecord)[i];
  }
  positionRecord->clear();

  delete positionRecord;
}

void G4SmoothTrajectory::ShowTrajectory(std::ostream& os) const
{
  // Invoke the default implementation in G4VTrajectory...
  G4VTrajectory::ShowTrajectory(os);
  // ... or override with your own code here.
}

void G4SmoothTrajectory::DrawTrajectory(G4int i_mode) const
{
  // Invoke the default implementation in G4VTrajectory...
  G4VTrajectory::DrawTrajectory(i_mode);
  // ... or override with your own code here.
}

const std::map<G4String,G4AttDef>* G4SmoothTrajectory::GetAttDefs() const
{
  G4bool isNew;
  std::map<G4String,G4AttDef>* store
    = G4AttDefStore::GetInstance("G4SmoothTrajectory",isNew);
  if (isNew) {

    G4String ID("ID");
    (*store)[ID] = G4AttDef(ID,"Track ID","Bookkeeping","","G4int");

    G4String PID("PID");
    (*store)[PID] = G4AttDef(PID,"Parent ID","Bookkeeping","","G4int");

    G4String PN("PN");
    (*store)[PN] = G4AttDef(PN,"Particle Name","Bookkeeping","","G4String");

    G4String Ch("Ch");
    (*store)[Ch] = G4AttDef(Ch,"Charge","Physics","e+","G4double");

    G4String PDG("PDG");
    (*store)[PDG] = G4AttDef(PDG,"PDG Encoding","Bookkeeping","","G4int");

    G4String IMom("IMom");
    (*store)[IMom] = G4AttDef(IMom, "Momentum of track at start of trajectory",
			      "Physics","G4BestUnit","G4ThreeVector");

    G4String IMag("IMag");
    (*store)[IMag] = G4AttDef
      (IMag, "Magnitude of momentum of track at start of trajectory",
       "Physics","G4BestUnit","G4double");

    G4String NTP("NTP");
    (*store)[NTP] = G4AttDef(NTP,"No. of points","Bookkeeping","","G4int");

  }
  return store;
}


std::vector<G4AttValue>* G4SmoothTrajectory::CreateAttValues() const
{
  std::vector<G4AttValue>* values = new std::vector<G4AttValue>;

  values->push_back
    (G4AttValue("ID",G4UIcommand::ConvertToString(fTrackID),""));

  values->push_back
    (G4AttValue("PID",G4UIcommand::ConvertToString(fParentID),""));

  values->push_back(G4AttValue("PN",ParticleName,""));

  values->push_back
    (G4AttValue("Ch",G4UIcommand::ConvertToString(PDGCharge),""));

  values->push_back
    (G4AttValue("PDG",G4UIcommand::ConvertToString(PDGEncoding),""));

  values->push_back
    (G4AttValue("IMom",G4BestUnit(initialMomentum,"Energy"),""));

  values->push_back
    (G4AttValue("IMag",G4BestUnit(initialMomentum.mag(),"Energy"),""));

  values->push_back
    (G4AttValue("NTP",G4UIcommand::ConvertToString(GetPointEntries()),""));

#ifdef G4ATTDEBUG
   G4cout << G4AttCheck(values,GetAttDefs());
#endif

  return values;
}

void G4SmoothTrajectory::AppendStep(const G4Step* aStep)
{
  // (jacek 30/10/2002)
  positionRecord->push_back(
      new G4SmoothTrajectoryPoint(aStep->GetPostStepPoint()->GetPosition(),
				  aStep->GetPointerToVectorOfAuxiliaryPoints()));
}
  
G4ParticleDefinition* G4SmoothTrajectory::GetParticleDefinition()
{
   return (G4ParticleTable::GetParticleTable()->FindParticle(ParticleName));
}

void G4SmoothTrajectory::MergeTrajectory(G4VTrajectory* secondTrajectory)
{
  if(!secondTrajectory) return;

  G4SmoothTrajectory* seco = (G4SmoothTrajectory*)secondTrajectory;
  G4int ent = seco->GetPointEntries();
  for(G4int i=1;i<ent;i++) // initial point of the second trajectory should not be merged
  { 
    positionRecord->push_back((*(seco->positionRecord))[i]);
    //    positionRecord->push_back(seco->positionRecord->removeAt(1));
  }
  delete (*seco->positionRecord)[0];
  seco->positionRecord->clear();
}


