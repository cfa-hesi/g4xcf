// -----------------------------------------------------------------------------
//  PrimaryGeneration.h
//
//  Class for the definition of the primary generation action.
//   * Author: Everybody is an author!
//   * Creation date: 14 May 2023
// -----------------------------------------------------------------------------

#ifndef PRIMARY_GENERATION_H
#define PRIMARY_GENERATION_H

// GEANT4 includes
#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4String.hh"

// C++ includes
#include <random>

class G4ParticleDefinition;
class G4GenericMessenger;

class PrimaryGeneration : public G4VUserPrimaryGeneratorAction
{

  public:

    PrimaryGeneration();
    virtual ~PrimaryGeneration();
    virtual void GeneratePrimaries(G4Event*);

  protected:

    // GEANT4 dictionary of particles
    G4ParticleTable* particle_table_;

  private:

    G4GenericMessenger* msg_; // Messenger for configuration parameters
    G4String Particle_Type_;
    //double Particle_Energy_;

    bool decay_at_time_zero_;
    bool isotropic_;
    bool override_vertex_position_;
    double vertex_x_;
    double vertex_y_;
    double vertex_z_;

    G4GeneralParticleSource * particle_gun_;

    double detector_inner_radius_;
    double detector_outer_radius_;
    double detector_length_z_;

    // G4Box* detector_solid_vol_;
    G4Tubs* detector_solid_vol_;

    std::default_random_engine generator_;
    std::normal_distribution< double > distribution_;

};

#endif
