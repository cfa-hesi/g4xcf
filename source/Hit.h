// -----------------------------------------------------------------------------
//  Hit.h
//
//  Definition of hit.
//   * Author: Everybody is an author!
//   * Creation date: 16 May 2023
// -----------------------------------------------------------------------------

#ifndef HIT_H
#define HIT_H

#include <G4VHit.hh>
#include <G4THitsCollection.hh>
#include <G4ThreeVector.hh>


class Hit: public G4VHit
{
public:
  Hit();
  Hit(const Hit&);
  virtual ~Hit();

  const Hit& operator=(const Hit&);
  G4bool operator==(const Hit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  virtual void Draw();
  virtual void Print();

  void SetEdep(G4double);
  void SetPosition(const G4ThreeVector&);

private:
  G4double edep_;
  G4ThreeVector xyz_;
};

typedef G4THitsCollection<Hit> HitsCollection;

extern G4ThreadLocal G4Allocator<Hit>* HitAllocator;

inline void* Hit::operator new(size_t)
{
  if (!HitAllocator) HitAllocator = new G4Allocator<Hit>;
  return (void*) HitAllocator->MallocSingle();
}

inline void Hit::operator delete(void* hit)
{
  HitAllocator->FreeSingle((Hit*) hit);
}

inline void Hit::SetEdep(G4double e) { edep_ = e; }

inline void Hit::SetPosition(const G4ThreeVector& p) { xyz_ = p; }

#endif
