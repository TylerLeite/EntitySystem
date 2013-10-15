/// Meant to be more of an interface than a parent class...
#ifndef component_hpp
#define component_hpp

//stl
#include <string>
using std::string;

class component{
  /// ...however, having all components able to be upcast to a common base class makes organization much easier
    public:
      //Constructor
        component();
      //Member function
        virtual string getName() = 0; //returns the component's internal name
      //Data member
        unsigned parentEntity;
    private:
      //Unused
        component(const component& pComponent);
        component& operator=(const component& rhsComponent);
};

#endif //component_hpp
