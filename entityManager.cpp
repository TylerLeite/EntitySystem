/// Most of these implementations are fairly trivial, so commentation may be sparse
#include "entityManager.hpp"

// Static members, used in entity creation
unsigned entityManager::nextID = 0;
map<string, component*> entityManager::emptyComponentMap;

entityManager::entityManager() :
    frozen(false)
{}

entityManager::~entityManager(){
  // Iterate through allEntities and free the memory used by their components
    map<string, component*>::iterator mapIt;
    list<unsigned>::iterator listIt = allEntities.begin();
    for (; listIt != allEntities.end(); listIt++){
        mapIt = componentStores[*listIt].begin();
        for (; mapIt != componentStores[*listIt].end(); mapIt++){
            delete mapIt->second;
            mapIt->second = NULL;
        }
        
        listIt++;
    }
}

//member functions
void entityManager::freeze(){
    frozen = true;
}

void entityManager::unFreeze(){
    frozen = false;
}

bool entityManager::isFrozen(){
    return frozen;
}

bool entityManager::hasEntity(const unsigned& pEntity){
  // Check if pEntity is in the entity manager's list of all entities
    list<unsigned>::iterator listIt = allEntities.begin();
    for (; listIt != allEntities.end(); listIt++){
        if (*listIt == pEntity)
            return true;
    }
    
    return false;
}

list<unsigned> entityManager::getAllEntities(){
    return allEntities;
}

list<unsigned> entityManager::getAllEntitiesWithComponent(const string& pCompName){
    list<unsigned> entities;
    
  // Iterate through componentStores, checking if there is an entry for pCompName
    map<unsigned, map<string, component*> >::iterator mapIt = componentStores.begin();
    for (; mapIt != componentStores.end(); mapIt++){
        if (hasComponent(mapIt->first, pCompName))
            entities.push_back(mapIt->first);
    }
    
    return entities;
}

list<unsigned> entityManager::getAllEntitiesWithComponents(list<string>& pCompNames){
    list<unsigned> entities;
    
  // Iterate through componentStores, checking if there are entries for all names in pCompNames
    map<unsigned, map<string, component*> >::iterator mapIt = componentStores.begin();
    for (; mapIt != componentStores.end(); mapIt++){
        if (hasComponents(mapIt->first, pCompNames))
            entities.push_back(mapIt->first);
    }
    
    return entities;
}

unsigned entityManager::createEntity(){ 
    unsigned ID = nextID++; //simplest pseudo-uuid ever
    
  // Account for the entity in allEntities and make an entry in componentStores
    allEntities.push_back(ID);
    componentStores.insert(pair<unsigned, map<string, component*> >(ID, emptyComponentMap));
    
    return ID;
}

component* entityManager::getComponent(const unsigned& pEntity, const string& pCompName){
    if (hasComponent(pEntity, pCompName));
        return componentStores[pEntity][pCompName];
    return NULL;
}

list<component*> entityManager::getAllComponentsOnEntity(const unsigned& pEntity){
    list<component*> components;
   
  // Iterate through the componentStores[pEntity], adding all components to the output list
    map<string, component*>::iterator mapIt = componentStores[pEntity].begin();
    for (; mapIt != componentStores[pEntity].end(); mapIt++){
        components.push_back(mapIt->second);
    }
    
    return components;
}

void entityManager::addComponent(const unsigned& pEntity, component* pComponent){
    if (!hasComponent(pEntity, pComponent->getName())){
      // Insert the pComponent and its name into componetnStores at pEntity
        pair<string, component*> stringCompPair(pComponent->getName(), pComponent);
        componentStores[pEntity].insert(stringCompPair);
      // Inform the component of its new owner
        pComponent->parentEntity = pEntity;
    }
}


void entityManager::removeComponent(const unsigned& pEntity, component* pComponent){
    if (hasComponent(pEntity, pComponent->getName())){
      // Remove the componentStores entry for pComponent and free memory
        componentStores[pEntity].erase(pComponent->getName());
        delete pComponent;
        pComponent = NULL;
    }
}

void entityManager::removeComponent(const unsigned& pEntity, const string& pCompName){
  // Convenience function, just calls the other removeComponent
    if (hasComponent(pEntity, pCompName)){
        component* Component = componentStores[pEntity][pCompName];
        removeComponent(pEntity, Component);
    }
}

bool entityManager::hasComponent(const unsigned& pEntity, const string& pCompName){
    if (hasEntity(pEntity))
        return componentStores[pEntity].count(pCompName); //I'm so clever!
        
    return false;
}

bool entityManager::hasComponents(const unsigned& pEntity, list<string>& pCompNames){
    bool hasThem = true;
    
  // Iterate through pCompNames, running hasComponent on each
    list<string>::iterator listIt = pCompNames.begin();
    for (; listIt != pCompNames.end(); listIt++){
        hasThem &= componentStores[pEntity].count(*listIt);
    }
    
    return hasThem;
}

void entityManager::killEntity(const unsigned& pEntity){
  // Delete pEntity's entry in componentStores and allEntity's, free its components' memory
    if (hasEntity(pEntity)){
        map<string, component*>::iterator mapIt = componentStores[pEntity].begin();
        for (; mapIt != componentStores[pEntity].end(); mapIt++){
            delete mapIt->second;
            mapIt->second = NULL;
        }
        
        allEntities.remove(pEntity);
        componentStores.erase(pEntity);
    }
}

/*
void entityManager::saveEntity(const string& pFileName){
    return;
}

void entityManager::loadEntity(const string& pFileName){
    return;
}
//*/
