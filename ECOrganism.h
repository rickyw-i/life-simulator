//
//  ECOrganism.h
//  
//

#ifndef ECOrganism_h
#define ECOrganism_h

#include <string>
#include <vector>
using namespace std;
// ********************************************************
// Generic organism

class ECOrganism
{
public:
    // your code here
    ECOrganism(){}
    virtual ~ECOrganism(){}
    
    ECOrganism(string name) : name(name), vitality(100){}
    ECOrganism(string name, string type) : name(name),type(type), vitality(100){}
    // work and consume energy
    
    virtual void Work(double hour, int type)=0;
    // eat and gain energy
    virtual void Eat(double hour)=0;
    // is sleeping at this hour?
    //virtual bool IsSleeping(double hour) const = 0;
    
    //virtual void DoSomething(ECOrganism &rhs);

    string GetName(){
        return name;
    }
    vector< vector<double> > events; // hour type subtype
     
    float vitality;
    string type;
    string name;
protected:
  // your code

private:
  // your code
    
   
};


#endif /* ECOrganism_h */
