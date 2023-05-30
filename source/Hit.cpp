// -----------------------------------------------------------------------------
//  Hit.cpp
//
//  Definition of hit.
//   * Author: Everybody is an author!
//   * Creation date: 15 May 2023
// -----------------------------------------------------------------------------

#include "Hit.h"


G4ThreadLocal G4Allocator<Hit>* HitAllocator=0;


Hit::Hit():
  G4VHit()
{
}


Hit::~Hit()
{
}


Hit::Hit(const Hit& right): G4VHit()
{
  edep_ = right.edep_;
  xyz_  = right.xyz_;
}


const Hit& Hit::operator=(const Hit& right)
{
  edep_ = right.edep_;
  xyz_  = right.xyz_;

  return *this;
}


G4bool Hit::operator==(const Hit& right) const
{
return ( this == &right ) ? true : false;
}


void Hit::Draw()
{
}


void Hit::Print()
{
}
