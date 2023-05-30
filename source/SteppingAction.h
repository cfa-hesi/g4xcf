// -----------------------------------------------------------------------------
//  SteppingAction.h
//
//  Definition of stepping action.
//   * Author: Everybody is an author!
//   * Creation date: 15 May 2023
// -----------------------------------------------------------------------------

#ifndef STEPPING_ACTION_H
#define STEPPING_ACTION_H

#include <G4UserSteppingAction.hh>


class SteppingAction: public G4UserSteppingAction
{
  public:
    SteppingAction();
    virtual ~SteppingAction();
    virtual void UserSteppingAction(const G4Step*);
};

#endif
