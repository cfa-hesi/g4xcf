// -----------------------------------------------------------------------------
//  MCTruthManager.h
//
//  Class definition of the MC truth manager
//   * Author: Everybody is an author!
//   * Creation date: 15 May 2023
// -----------------------------------------------------------------------------

#ifndef MCTruthManager_h
#define MCTruthManager_h 1

// Q-Pix includes
#include "GeneratorParticle.h"
#include "MCParticle.h"

// GEANT4 includes
#include "globals.hh"

// ROOT includes
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

// C++ includes
#include <map>
#include <set>

class MCTruthManager {

    public:

        MCTruthManager();
        ~MCTruthManager();

        void EventReset();

        void SetRun(int const);
        void SetEvent(int const);

        static MCTruthManager* Instance();

        void AddInitialGeneratorParticle(GeneratorParticle *);
        void AddFinalGeneratorParticle(GeneratorParticle *);

        void AddMCParticle(MCParticle *);
        MCParticle * GetMCParticle(int const);

        inline std::vector< GeneratorParticle * > GetInitialGeneratorParticles() const { return initial_generator_particles_; }
        inline std::vector< GeneratorParticle * > GetFinalGeneratorParticles()   const { return final_generator_particles_;   }

        inline std::map< int, MCParticle * > GetMCParticleMap() const { return mc_particle_map_; }

    private:

        static MCTruthManager * instance_;

        int run_;
        int event_;

        // containers of generator particles
        std::vector< GeneratorParticle * > initial_generator_particles_;
        std::vector< GeneratorParticle * > final_generator_particles_;

        // MC particle map
        // std::map< int, MCParticle > mc_particle_map_;
        std::map< int, MCParticle * > mc_particle_map_;

};

#endif
