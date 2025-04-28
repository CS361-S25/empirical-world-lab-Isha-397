#include <iostream>

#include "Org.h"
#include "emp/base/vector.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "World.h"

int main() {
  emp::Random random(5);
  OrgWorld world(random);

  world.Resize(10, 10);

  Organism* org1 = new Organism(&random, 0);
  Organism* org2 = new Organism(&random, 1);

  world.Inject(*org1);
  world.Inject(*org2);

  std::cout << "Initial number of organisms: " << world.GetNumOrgs() << std::endl;

  for (int i = 0; i < 10; i++) {
      world.Update();
      std::cout << "Update " << i << ", organisms: " << world.GetNumOrgs() << std::endl;
  }

  return 0;
}