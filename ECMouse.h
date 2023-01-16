//
//  ECMouse.h
//  
//

#ifndef ECMouse_h
#define ECMouse_h


#include "ECOrganism.h"
#include "string"

// Spider
class ECMouse :virtual public ECOrganism
{
public:
    ECMouse(){}
    ~ECMouse(){}
    ECMouse(string name): ECOrganism(name, "mouse"),eat_limit(10), sleep_start(10), sleep_end(18){}
    
    ECMouse(string name, ECOrganism *rhs) : ECMouse(name){
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
        vitality -= 20;
        if (target->type == "grasshopper")
            target->vitality = 0;
    };
     
private:
    int eat_limit;
    float sleep_start;
    float sleep_end;
    ECOrganism *target;
    
};

#endif /* ECMouse_h */
