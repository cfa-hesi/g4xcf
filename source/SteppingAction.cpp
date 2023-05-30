// -----------------------------------------------------------------------------
//  SteppingAction.cpp
//
//  Definition of stepping action.
//   * Author: Everybody is an author!
//   * Creation date: 15 May 2023
// -----------------------------------------------------------------------------

#include "SteppingAction.h"


#include "AnalysisManager.h"
#include "G4VProcess.hh"


SteppingAction::SteppingAction(): G4UserSteppingAction()
{
}


SteppingAction::~SteppingAction()
{
}


void SteppingAction::UserSteppingAction(const G4Step* step)
{
    AnalysisManager * analysis_manager = AnalysisManager::Instance();

    analysis_manager->AddProcess(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
}
