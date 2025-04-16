#include <iostream>

#include "Org.h"
#include "emp/base/vector.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "World.h"

// This is the main function for the NATIVE version of this project.

int main(int argc, char* argv[])
{
  emp::Random random(2);
  OrgWorld world(random);

  // Organism* new_org = new Organism(&random);
  // world.Inject(*new_org);

  // std::cout <<world.size();
  Organism new_org(&random);

  world.Inject(new_org);


  std::cout << "World size: " << world.size() << std::endl;

  // Call Update 10 times
  for (int i = 0; i < 10; i++) {
    std::cout << "Update #" << i + 1 << std::endl;
    world.Update();
  }

  world.Resize(10,10);

  world.GetNumOrgs();

  return 0;

}
