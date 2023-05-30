## ---------------------------------------------------------
##  app/CMakeLists.txt
##
##  CMake build script.
##   * Author: Everyone is an author!
##   * Creation date: 15 May 2023
## ---------------------------------------------------------


add_executable(main main.cpp)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/source)
target_link_libraries(main ${CMAKE_PROJECT_NAME} ${Geant4_LIBRARIES})

install(TARGETS main RUNTIME DESTINATION bin)
