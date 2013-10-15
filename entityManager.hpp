#ifndef entityManager_hpp
#define entityManager_hpp

//stl
#include <list>
#include <map>
#include <string>
using std::string; using std::list; using std::map; using std::pair;
// Need to know what components are, but not systems
#include "component.hpp"

class entityManager{
    public:
      // Static data members
        static unsigned nextID;
        static map<string, component*> emptyComponentMap; // Used in entity creation
    
      // Constructor
        entityManager();
      // Destructor
        virtual ~entityManager();
        
      //State functions
        void freeze();   // Set frozen to true
        void unFreeze(); // Set frozen to false
        bool isFrozen(); // Return frozen
        
      // Entity retrieval functions
        bool           hasEntity(const unsigned& pEntity);                     // Check if any of the manager's entities have id = pEntity
        list<unsigned> getAllEntities();                                       // Return the list allEntities
        list<unsigned> getAllEntitiesWithComponent (const string& pCompName);  // Return a list of all entities with component pCompName
        list<unsigned> getAllEntitiesWithComponents(list<string>& pCompNames); // Return a list of all entities with all components in pCompNames
      
      //entity management functions
        unsigned createEntity(); // Makes a new entry in allEntities and insert a blank component map into componentStores
        
        component* getComponent(const unsigned& pEntity, const string& pCompName); // Return a pointer to pEntity's component of type "pCompName"
        list<component*> getAllComponentsOnEntity(const unsigned& pEntity);        // Return a list of pointers all components on pEntity
        
        void addComponent   (const unsigned& pEntity, component* pComponent);    // Add pComponent to componentStores under pEntity
        void removeComponent(const unsigned& pEntity, component* pComponent);    // Remove pComponent from componentStores under pEntity
        void removeComponent(const unsigned& pEntity, const string& pCompName);  // Remove component named pCompName from pEntity
        bool hasComponent   (const unsigned& pEntity, const string& pCompName);  // Check if pEntity has a component of type pCompName
        bool hasComponents  (const unsigned& pEntity, list<string>& pCompNames); // Check if pEntiy has all components in the pCompNames list
        void killEntity     (const unsigned& pEntity);                           // Remove pEntity from componentStores and allEntities, freeing the dynamically allocated memory of all its components
        
      ///I'll get to these eventually
        /* 
        void saveEntity(const string& pFileName); // Write an entity's id, its components, and all its components' data to   pFileName
        void loadEntity(const string& pFileName); // Read  an entity's id, its components, and all its components' data from pFileName
        //*/
        
    protected:
      //data members
        bool frozen;
        list<unsigned> allEntities;
        map<unsigned, map<string, component*> > componentStores; //maps each entity to its components, searchable by an entity's ID and a component's internal name
};

#endif //entityManager_hpp
