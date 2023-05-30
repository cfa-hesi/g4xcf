// -----------------------------------------------------------------------------
//  PrimaryGeneration.cpp
//
//  Class for the definition of the primary generation action.
//   * Author: Everybody is an author!
//   * Creation date: 15 May 2023
// -----------------------------------------------------------------------------

#include "PrimaryGeneration.h"

// Q-Pix includes
#include "MCTruthManager.h"
#include "GeneratorParticle.h"

// GEANT4 includes
#include "G4PhysicalConstants.hh"
#include "G4LogicalVolumeStore.hh"

#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4Event.hh"

#include "G4Electron.hh"
#include "G4MuonPlus.hh"
#include "G4Proton.hh"

#include "G4GenericMessenger.hh"
#include "Randomize.hh"

// ROOT includes
#include "Math/SVector.h"
#include "Math/SMatrix.h"
#include "TF1.h"

// C++ includes
#include <chrono>
#include <math.h>
#include <stdlib.h>

PrimaryGeneration::PrimaryGeneration()
  : G4VUserPrimaryGeneratorAction(),
    decay_at_time_zero_(false),
    isotropic_(false),
    override_vertex_position_(false),
    vertex_x_(2.3/2),
    vertex_y_(6.0/2),
    vertex_z_(3.6/2),
    particle_gun_(0)
{
  msg_ = new G4GenericMessenger(this, "/Inputs/", "Control commands of the ion primary generator.");
  msg_->DeclareProperty("Particle_Type", Particle_Type_,  "which particle?");
  msg_->DeclareProperty("decay_at_time_zero", decay_at_time_zero_,
                        "Set to true to make unstable isotopes decay at t=0.");
  msg_->DeclareProperty("isotropic", isotropic_, "isotropic");
  msg_->DeclareProperty("override_vertex_position",
                        override_vertex_position_,
                        "override vertex position");
  msg_->DeclareProperty("vertex_x", vertex_x_, "vertex x").SetUnit("mm");
  msg_->DeclareProperty("vertex_y", vertex_y_, "vertex y").SetUnit("mm");
  msg_->DeclareProperty("vertex_z", vertex_z_, "vertex z").SetUnit("mm");

  particle_gun_ = new G4GeneralParticleSource();

  // get dictionary of particles
  particle_table_ = G4ParticleTable::GetParticleTable();

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  // std::default_random_engine generator(seed);
  generator_ = std::default_random_engine(seed);
  distribution_ = std::normal_distribution< double >(0, 1);
}


PrimaryGeneration::~PrimaryGeneration()
{
  delete msg_;
  delete particle_gun_;
}


void PrimaryGeneration::GeneratePrimaries(G4Event* event)
{
  // get MC truth manager
  MCTruthManager * mc_truth_manager = MCTruthManager::Instance();

  // get detector dimensions
  if (!detector_solid_vol_)
  {
    G4LogicalVolume* detector_logic_vol
      = G4LogicalVolumeStore::GetInstance()->GetVolume("detector.logical");
    if (detector_logic_vol) detector_solid_vol_ = dynamic_cast<G4Tubs*>(detector_logic_vol->GetSolid());
  }
  if (detector_solid_vol_)
  {
    detector_inner_radius_ = detector_solid_vol_->GetInnerRadius() * 2.;
    detector_outer_radius_ = detector_solid_vol_->GetOuterRadius() * 2.;
    detector_length_z_ = detector_solid_vol_->GetZHalfLength() * 2.;
  }

  if (true)
  {
    particle_gun_->GeneratePrimaryVertex(event);

    // get generated particle
    G4ParticleDefinition * const particle_definition = particle_gun_->GetParticleDefinition();

    int const pdg_code = particle_definition->GetPDGEncoding();
    double const charge = particle_definition->GetPDGCharge();
    double const mass = particle_definition->GetPDGMass() * CLHEP::MeV;

    // if the particle is a nucleus
    if (pdg_code > 1000000000)
    {
      if (decay_at_time_zero_ && !(particle_definition->GetPDGStable()))
      {
          // make unstable isotopes decay at t=0
          particle_definition->SetPDGLifeTime(1.*CLHEP::ps);
      }
    } // if the particle is a nucleus

    G4ThreeVector const & position = particle_gun_->GetParticlePosition();
    G4ThreeVector const & direction = particle_gun_->GetParticleMomentumDirection();

    double const x = position.x() / CLHEP::cm;
    double const y = position.y() / CLHEP::cm;
    double const z = position.z() / CLHEP::cm;
    double const t = particle_gun_->GetParticleTime();  // ns

    double const dx = direction.x();
    double const dy = direction.y();
    double const dz = direction.z();

    double const kinetic_energy = particle_gun_->GetParticleEnergy() * CLHEP::MeV;
    double const energy = kinetic_energy + mass;

    double const momentum = std::sqrt(energy*energy - mass*mass);

    double const px = momentum * dx;
    double const py = momentum * dy;
    double const pz = momentum * dz;

    // create generator particle
    GeneratorParticle * particle = new GeneratorParticle();
    particle->SetPDGCode (pdg_code);
    particle->SetMass    (mass    );
    particle->SetCharge  (charge  );
    particle->SetX       (x       );
    particle->SetY       (y       );
    particle->SetZ       (z       );
    particle->SetT       (t       );
    particle->SetPx      (px      );
    particle->SetPy      (py      );
    particle->SetPz      (pz      );
    particle->SetEnergy  (energy  );

    // add to MC truth manager
    mc_truth_manager->AddInitialGeneratorParticle(particle);
    mc_truth_manager->AddFinalGeneratorParticle(particle);
  }

}

