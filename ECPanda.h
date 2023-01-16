//
//  ECPanda.hpp
//  
//

#ifndef ECPanda_h
#define ECPanda_h
#include "ECOrganism.h"
#include "string"

// Spider
class ECPanda :virtual public ECOrganism
{
public:
    ECPanda(){}
    ~ECPanda(){}
    ECPanda(string name): ECOrganism(name, "panda"),eat_limit(12), sleep_start(15), sleep_end(10){}
    
    ECPanda(string name, ECOrganism *rhs) : ECPanda(name){
        target = rhs;
    }
    
    void Eat(double hour)
    {
        if (vitality <=0)
            return;
        if (hour >= sleep_start && hour <= sleep_end)
            return ;
        
        if (eat_limit > 0 && vitality >0)
        {
            vitality += 50;
            eat_limit -= 1;
            if (vitality > 100)
                vitality = 100;
        }
        
    }
    
    virtual void Work (double hour, int type)
    {
        ;
         
    }

  // work and consume energy
    virtual void run()
    {
        vitality -= 10;
    }
    
    virtual void DoSomething(ECOrganism *target)
    {
        ;
    };
     
private:
    int eat_limit;
    float sleep_start;
    float sleep_end;
    ECOrganism *target;
    
};



#endif /* ECPanda_h */
