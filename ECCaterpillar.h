//
//  ECCaterpillar.h
//  
//

#ifndef ECCaterpillar_h
#define ECCaterpillar_h

#include "ECOrganism.h"
#include "string"


class ECCaterpillar :virtual public ECOrganism
{
public:
    ECCaterpillar(){}
    ~ECCaterpillar(){}
    ECCaterpillar(string name): ECOrganism(name, "caterpillar"),eat_limit(5), sleep_start(9), sleep_end(17){}
    
    ECCaterpillar(string name, ECOrganism *rhs) : ECCaterpillar(name){
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
            vitality += 15;
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
        vitality -= 10;
        if (vitality < 0)
            vitality = 0;
         
    }

  // work and consume energy
    
    virtual void DoSomething(ECOrganism *target)
    {
        ;
    }
     
private:
    int eat_limit;
    float sleep_start;
    float sleep_end;
    ECOrganism *target;
    
};

#endif /* ECCaterpillar_h */
