//
//  ECGrasshopper.h
//  
//

#ifndef ECGrasshopper_h
#define ECGrasshopper_h
#include "ECOrganism.h"
#include "string"


class ECGrasshopper :virtual public ECOrganism
{
public:
    ECGrasshopper(){}
    ~ECGrasshopper(){}
    ECGrasshopper(string name): ECOrganism(name, "grasshopper"),eat_limit(10), sleep_start(9), sleep_end(17){}
    
    ECGrasshopper(string name, ECOrganism *rhs) : ECGrasshopper(name){
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
            vitality += 25;
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
            hop_around();
        }
        else{
            DoSomething(target);
        }
         
    }

  // work and consume energy
    virtual void hop_around()
    {
        vitality -= 5;
    }
    
    virtual void DoSomething(ECOrganism *target)
    {
        if (target == NULL)
            return ;
        if(target->vitality == 0)
            return;
        vitality -= 40;
        if (target->type == "grasshopper" || target->type == "spider" || target->type == "caterpillar")
            target->vitality = 0;
        else if (target->type == "mouse")
        {
            target->vitality -= 5;
            if (target->vitality < 0)
                target->vitality = 0;
        }
        
    };
     
private:
    int eat_limit;
    float sleep_start;
    float sleep_end;
    ECOrganism *target;
    
};


#endif /* ECGrasshopper_h */
