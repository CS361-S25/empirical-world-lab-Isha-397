#pragma once
#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism {
    private:
        emp::Random* random_ptr;
        int species_id;
        double energy;
    
    public:
        Organism(emp::Random* r_ptr, int species=0)
          : random_ptr(r_ptr), species_id(species), energy(0.0) { }
    
        Organism(const Organism& other)
          : random_ptr(other.random_ptr), species_id(other.species_id), energy(other.energy) { }
    
        void Process(double resources) {
            energy += resources;  //  absorb energy!\
        }
    
        emp::Ptr<Organism> CheckReproduction() {
            if (energy >= 200.0) { 
                energy -= 100.0;    // split energy
                return emp::NewPtr<Organism>(random_ptr, species_id);
            }
            return nullptr;
        }
    
        int GetSpecies() const { return species_id; }
    };
    

// Prey class
    class Prey : public Organism {
    public:
        Prey(emp::Random* random_ptr)
          : Organism(random_ptr, 0) { }
    
        Prey(const Prey& other)
          : Organism(other) { }
    
        emp::Ptr<Organism> Clone() const  {
            return new Prey(*this);
        }
    };
    
    // Predator class
    class Predator : public Organism {
    public:
        Predator(emp::Random* random_ptr)
          : Organism(random_ptr, 1) { }
    
        Predator(const Predator& other)
          : Organism(other) { }
    
        emp::Ptr<Organism> Clone() const  {
            return new Predator(*this);
        }
    };
#endif

