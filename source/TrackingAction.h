// -----------------------------------------------------------------------------
//  TrackingAction.h
//
//  Definition of tracking action.
//   * Author: Everybody is an author!
//   * Creation date: 15 May 2023
// -----------------------------------------------------------------------------

#ifndef TRACKING_ACTION_H
#define TRACKING_ACTION_H 1

#include "G4UserTrackingAction.hh"

class TrackingAction : public G4UserTrackingAction
{
    public:
        TrackingAction();
        ~TrackingAction();

        void PreUserTrackingAction(const G4Track*);
        void PostUserTrackingAction(const G4Track*);
};

#endif
