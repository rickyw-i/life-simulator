//
//  ECSpider.h
//  
//

#ifndef ECSpider_h
#define ECSpider_h

#include "ECOrganism.h"
#include "string"

// Spider
class ECSpider :virtual public ECOrganism
{
public:
    ECSpider(){}
    ~ECSpider(){}
    ECSpider(string name): ECOrganism(name, "spider"),eat_limit(5), sleep_start(9), sleep_end(17){}
    
    ECSpider(string name, ECOrganism *rhs) : ECSpider(name){
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
            vitality += 20;
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
            Weave();
        }
        else{
            DoSomething(target);
        }
        if (vitality <0)
            vitality =0;
        
    }
    
    // work and consume energy
    virtual void Weave()
    {
        vitality -= 10;
    }
    
    virtual void DoSomething(ECOrganism *target)
    {
        if (target == NULL)
            return ;
        if(target->vitality == 0)
            return;
        vitality -= 30;
        if (target->type == "grasshopper" || target->type == "spider" || target->type == "caterpillar")
            target->vitality = 0;
    };
    
private:
    int eat_limit;
    float sleep_start;
    float sleep_end;
    ECOrganism *target;
};

#endif /* ECSpider_h */
