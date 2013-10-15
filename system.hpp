/// Meant to be more of an interface than a parent class
#ifndef system_hpp
#define system_hpp

//stl
#include <string>
using std::string;
//components
#include "component.hpp" // Superfluous
#include "entityManager.hpp"

class system{
    public:
      //constructor
        system(entityManager* pEntityManager);
      //member functions
        virtual string getName() = 0;                                           // Return the system's internal name
        virtual void   processOneGameTick(const unsigned long& pDeltaTime) = 0; // Used when the system is "fps-advertant"
        virtual void   processOneGameTick()                                = 0; // Used when the system is "fps-pococurante"
      //pointer
        entityManager* mEntityManager; // The manager that the system gets component data from
    private:
        system();
        system(const system& pSystem);
        system& operator=(const system& rhsSystem);
};

#endif //system_hpp
