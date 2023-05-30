// -----------------------------------------------------------------------------
//  DetectorConstruction.cpp
//
//  Definition of detector geometry and materials.
//   * Author: Everybody is an author!
//   * Creation date: 15 May 2023
// -----------------------------------------------------------------------------

#include "DetectorConstruction.h"
#include "SensitiveDetector.h"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "G4LogicalVolumeStore.hh"


DetectorConstruction::DetectorConstruction():
    G4VUserDetectorConstruction()
    // solid_world(0), logic_world(0), physical_world(0),
    // solid_target(0), logic_target(0), physical_target(0), 
    // // step_limit(0), max_step(0.5*CLHEP::cm),
    // target_radius(0.3*CLHEP::cm),
    // target_length(4.0*0.5*CLHEP::cm)
{
    // // step_limit = new G4UserLimits(max_step);

    // world_material = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
    // target_material = G4NistManager::Instance()->FindOrBuildMaterial("G4_lAr");

    // // maxStep = 0.5*CLHEP::cm;
    // // targetRadius = 0.3*CLHEP::cm;
    // // targetLength = 4.0*0.5*CLHEP::cm;
    // // max_step = 0.5*CLHEP::cm;
    // target_radius = 100*CLHEP::cm;
    // target_length = 10.0*0.5*CLHEP::cm;
}

DetectorConstruction::~DetectorConstruction()
{
    // delete step_limit;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // WORLD /////////////////////////////////////////////////

    G4double world_radius = 15.*CLHEP::m;
    G4double world_length = 15.*CLHEP::m;
    G4Material* world_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");

    G4Tubs* world_solid_vol =
      new G4Tubs("world", 0., world_radius, world_length/2., 0., CLHEP::twopi);

    G4LogicalVolume* world_logic_vol =
      new G4LogicalVolume(world_solid_vol, world_mat, "world.logical");
    world_logic_vol->SetVisAttributes(G4VisAttributes::GetInvisible());

    G4VPhysicalVolume* world_phys_vol =
      new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),
                        world_logic_vol, "world.physical", 0, false, 0, true);

    // DETECTOR //////////////////////////////////////////////
    // resemble an APA size

    G4double detector_radius = 10.*CLHEP::cm;
    G4double detector_length = 10.*CLHEP::micrometer;
    // G4double detector_length = 2*CLHEP::cm;
    // G4Material* detector_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_lAr");
    G4Material* detector_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_Be");

    G4Tubs* detector_solid_vol =
      new G4Tubs("detector.solid", 0., detector_radius, detector_length/2., 0., CLHEP::twopi);

    G4LogicalVolume* detector_logic_vol =
      new G4LogicalVolume(detector_solid_vol, detector_mat, "detector.logical");

    // G4ThreeVector offset(detector_width/2., detector_height/2., detector_length/2.);
    G4ThreeVector offset(0, 0, detector_length/2.);

    new G4PVPlacement(0, offset,
                      detector_logic_vol, "detector.physical", world_logic_vol, false, 0, true);

    //////////////////////////////////////////////////////////

    return world_phys_vol;;

    // // WORLD /////////////////////////////////////////////////

    // G4double world_radius = 100*target_radius + CLHEP::cm;
    // G4double world_length = 100*target_length + CLHEP::cm;

    // solid_world = new G4Tubs("world", 0., world_radius, world_length, 0., CLHEP::twopi);
    // logic_world = new G4LogicalVolume(solid_world, world_material, "world", 0, 0, 0);

    // physical_world = new G4PVPlacement(
    //         0,               // no rotation
    //         G4ThreeVector(0, 0, 0), // at (0, 0, 0)
    //         logic_world,     // its logical volume
    //         "world",         // its name
    //         0,               // its mother  volume
    //         false,           // no boolean operations
    //         0);              // copy number

    // // TARGET ////////////////////////////////////////////////

    // //std::cout<<"construct: target solid"<<std::endl;
    // solid_target = new G4Tubs("target", 0., target_radius, target_length, 0., CLHEP::twopi);
    // //std::cout<<"construct: target logic"<<std::endl;
    // //logicTarget = new G4LogicalVolume(solidTarget,vacuum,"Target",0,0,0);
    // // logic_target = new G4LogicalVolume(solid_target, target_material, "target", 0, 0, 0);
    // logic_target = new G4LogicalVolume(solid_target, target_material, "detector.logical", 0, 0, 0);
    // // std::cout << "density: " << targetMaterial->GetDensity()/(CLHEP::g/CLHEP::cm3) << " g/cm^3" << std::endl;
    // //std::cout<<"construct: target physical"<<std::endl;
    // physical_target = new G4PVPlacement(
    //             0,               // no rotation
    //             // G4ThreeVector(0, 0, 1),  // at (x, y, z)
    //             G4ThreeVector(0, 0, target_length),  // at (x, y, z)
    //             logic_target,    // its logical volume
    //             // "target",        // its name
    //             "detector.logical",        // its name
    //             logic_world,     // its mother  volume
    //             false,           // no boolean operations
    //             0);              // copy number 

    // return physical_world;
}

void DetectorConstruction::ConstructSDandField()
{
    // SENSITIVE DETECTOR ////////////////////////////////////

    SensitiveDetector* tracking_sd = new SensitiveDetector("/g4xcf/tracking", "TrackingHitsCollection");
    G4SDManager::GetSDMpointer()->AddNewDetector(tracking_sd);

    G4LogicalVolume* detector_logic_vol =
      G4LogicalVolumeStore::GetInstance()->GetVolume("detector.logical");
      // G4LogicalVolumeStore::GetInstance()->GetVolume("target");

    SetSensitiveDetector(detector_logic_vol, tracking_sd);

    //////////////////////////////////////////////////////////
}
