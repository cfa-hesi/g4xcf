## ---------------------------------------------------------
##  g4xcf | source/CMakeLists.txt
##
##  CMake build script.
##   * Author: Everyone is an author!
##   * Creation date: 15 May 2023
## ---------------------------------------------------------

include_directories(${CMAKE_SOURCE_DIR}/source)

SET(SRC   AnalysisManager.cpp
          GeneratorParticle.cpp
          MCTruthManager.cpp
          MCParticle.cpp
          DetectorConstruction.cpp
          PrimaryGeneration.cpp
          RunAction.cpp
          EventAction.cpp
          SteppingAction.cpp
          TrackingAction.cpp
          SensitiveDetector.cpp
          Hit.cpp)

add_library(${CMAKE_PROJECT_NAME} SHARED ${SRC} dictionary.cxx)

# link to the filesystem library on linux
if (UNIX AND NOT APPLE)
  target_link_libraries(${CMAKE_PROJECT_NAME} stdc++fs)
endif ()

# link to GEANT4 and ROOT libraries
target_link_libraries(${CMAKE_PROJECT_NAME} ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

# generate ROOT dictionary
ROOT_GENERATE_DICTIONARY(dictionary AnalysisManager.h LINKDEF LinkDef.h)

