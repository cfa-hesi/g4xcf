// -----------------------------------------------------------------------------
//  DetectorConstruction.h
//
//  Class for the definition of the detector geometry and materials.
//   * Author: Everybody is an author!
//   * Creation date: 15 May 2023
// -----------------------------------------------------------------------------

#ifndef DETECTOR_CONSTRUCTION_H
#define DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4Tubs.hh"

class G4Material;


class DetectorConstruction: public G4VUserDetectorConstruction
{

    public:

        DetectorConstruction();
        virtual ~DetectorConstruction();

    private:

        virtual G4VPhysicalVolume* Construct();
        virtual void ConstructSDandField();

        // G4Material*  world_material;
        // G4Material*  target_material;

        // G4Tubs*            solid_world;     // pointer to the solid envelope
        // G4LogicalVolume*   logic_world;     // pointer to the logical envelope
        // G4VPhysicalVolume* physical_world;  // pointer to the physical envelope

        // G4Tubs*            solid_target;    // pointer to the solid Target
        // G4LogicalVolume*   logic_target;    // pointer to the logical Target
        // G4VPhysicalVolume* physical_target; // pointer to the physical Target

        // // G4UserLimits* step_limit;           // pointer to user step limits

        // // G4double max_step;                  // max step size
        // G4double target_radius;             // radius of target
        // G4double target_length;             // length of target

};

#endif
