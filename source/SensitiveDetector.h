// -----------------------------------------------------------------------------
//  SensitiveDetector.h
//
//  TODO: Class description
//   * Author: Everybody is an author!
//   * Creation date: 15 May 2023
// -----------------------------------------------------------------------------

#ifndef SENSITIVE_DETECTOR_H
#define SENSITIVE_DETECTOR_H

#include <G4VSensitiveDetector.hh>
#include "Hit.h"
#include <G4GenericMessenger.hh>

#include <vector>

class G4GenericMessenger;

class SensitiveDetector: public G4VSensitiveDetector
{
public:
  SensitiveDetector(const G4String&, const G4String&);
  virtual ~SensitiveDetector();

  // virtual void   Initialize(G4HCofThisEvent*);
  virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  // virtual void   EndOfEvent(G4HCofThisEvent*);

private:
  // TrackingHitsCollection* hc_;
  G4GenericMessenger* msg_; // Messenger for configuration parameters
  double Event_Cutoff_;
};
#endif
