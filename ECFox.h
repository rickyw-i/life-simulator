//
//  ECFox.h
//  
//

#ifndef ECFox_h
#define ECFox_h
#include "ECOrganism.h"
#include "string"

// Spider
class ECFox :virtual public ECOrganism
{
public:
    ECFox(){}
    ~ECFox(){}
    ECFox(string name): ECOrganism(name, "fox"),eat_limit(8), sleep_start(7), sleep_end(14){}
    
    ECFox(string name, ECOrganism *rhs) : ECFox(name){
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
        if (vitality <=0)
            return;
        if (hour >= sleep_start && hour <= sleep_end)
            return ;
        if(type ==0)
        {
            run();
        }
        else{
            DoSomething(target);
        }
         
    }

  // work and consume energy
    virtual void run()
    {
        vitality -= 10;
    }
    
    virtual void DoSomething(ECOrganism *target)
    {
        if (target == NULL)
            return ;
        if(target->vitality == 0)
            return;
        vitality -= 40;
        if (target->type == "mouse")
            target->vitality = 0;
    };
     
private:
    int eat_limit;
    float sleep_start;
    float sleep_end;
    ECOrganism *target;
    
};

#endif /* ECFox_h */
