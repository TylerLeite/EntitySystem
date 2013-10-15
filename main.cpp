///How to use the framework!

//stl
#include <iostream>
using std::cout;
///include all components and systems
//components
#include "component.hpp"     //superfluous, included in entityManager.hpp and all components
#include "entityManager.hpp" //superfluous, included in all system.hpp and all systems
//systems
#include "system.hpp"

/** Example Component **/
class cmpExample : public component{
    public:
      //constructors
        cmpExample(const int& pFoo, const int& pBar, const int& pIsFooBar) :
            foo(pFoo), bar(pBar), isFooBar(pIsFooBar)
        {}
      //member function
        string getName(){return "example";} //returns the component's internal name: "example"
      //data members
        double foo, bar;
        bool isFooBar;
    private:
        cmpExample();
        cmpExample(const cmpExample& pSize);
        cmpExample& operator=(const cmpExample& rhsSize);
};

/** Example System **/
class sysExample : public system{
    public:
      //constructor
        sysExample(entityManager* pEntityManager) :
            system(pEntityManager)
        {};
      //member functions
        virtual string getName(){return "example";} //returns the system's internal name: "example"
      //don't put all the code in processOneGameTick
        double helperFunc(const double& pFoo, const double& pBar){return pFoo/pBar;} 
        void processOneGameTick(){ //this system doesn't need to know the fps
          //create a list of entities that the system is concerned with
            list<unsigned> entitiesToAffect = mEntityManager->getAllEntitiesWithComponent("example");
        /*
          //for systems with more than one dependency, use of the following method is recommended:
            list<string> dependencies;
            dependencies.push_back("example");
            dependencies.push_back("spam");
            dependencies.push_back("foo");
            dependencies.push_back("bar");
            
            list<unsigned> entitiesToAffect = mEntityManager->getAllEntitiesWithComponents(dependencies);
        //*/
            
          //iterate through the list, applying your mighty logic to each entity
            list<unsigned>::iterator listIt = entitiesToAffect.begin();
            for (; listIt != entitiesToAffect.end(); listIt++){
                cmpExample* Example = ((cmpExample*)(mEntityManager->getComponent(*listIt, "example"))); //convenience pointer
                
              //if you want to actually modify these values, simply make them pointers
              // e.g. int* Foo = &(Example->foo);
                double Foo = Example->foo;
                double Bar = Example->bar;
            
            //do whatever logic the system is meant to here
                double Result = helperFunc(Foo, Bar);
                
                if (Result < 1.0d && Result > -1.0d){
                    Example->isFooBar = true;
                    cout << *listIt << " is a FooBar: "     << Result << "\n";
                } else {
                    Example->isFooBar = false;
                    cout << *listIt << " is NOT a FooBar: " << Result << "\n";
                }
            }
        }; 
    private:
      //if you ever need to call any of these, you are doing something wrong
        sysExample();
        sysExample(const sysExample& pSysRender);
        sysExample& operator=(const sysExample& rhsSysRender);
        void processOneGameTick(const unsigned long& pDeltaTime){return;}
};

/* Main */
int main(int argc, char** argv){
  //declare a entity manager
    entityManager EntityManager;
    
  //declare your systems, in this case only one
    sysExample ExampleSystem(&EntityManager);
    
  //make some entities
  ///first entity
    unsigned FirstEntity = EntityManager.createEntity();
  ///first entity's example component
    cmpExample* FirstEntityExampleCmp = new cmpExample(10.0d, 15.0d, true);
    EntityManager.addComponent(FirstEntity, FirstEntityExampleCmp);
    
  ///second entity
    unsigned SecondEntity = EntityManager.createEntity();
  ///second entity's example component
    cmpExample* SecondEntityExampleCmp = new cmpExample(20.0d, 5.0d, false);
    EntityManager.addComponent(SecondEntity, SecondEntityExampleCmp);
    
  //call systems' processOneGameTick() in whatever order you deem fit
    ExampleSystem.processOneGameTick();
    
    return 0;
}
