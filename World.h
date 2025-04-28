#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/base/vector.hpp"
#include "emp/math/Random.hpp"

#include "Org.h"

class OrgWorld : public emp::World<Organism> {
  protected:
      emp::Random& random;
  public:
      OrgWorld(emp::Random& random) : emp::World<Organism>(random), random(random) { }
  
      void Update() {
          emp::World<Organism>::Update();
  
          emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
  
          for (size_t i : schedule) {
              if (!IsOccupied(i)) continue;
              pop[i]->Process(100);
          }
  
          emp::vector<size_t> repro_schedule = emp::GetPermutation(random, GetSize());
  
          for (size_t i : repro_schedule) {
              if (!IsOccupied(i)) continue;
              emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
              if (offspring) {
                  DoBirth(*offspring, i);
              }
          }
      }
  
      emp::Ptr<Organism> ExtractOrganism(size_t i) {
          emp::Ptr<Organism> org = pop[i];
          pop[i] = nullptr;
          return org;
      }
  };

#endif