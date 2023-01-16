//
//  ECLifeSimulator.h
//  
//
//  Created by Yufeng Wu on 10/12/22.
//

#ifndef ECLifeSimulator_h
#define ECLifeSimulator_h

#include "ECOrganism.h"
#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;
// ********************************************************
// Life simulator

class ECLifeSimulator
{
public:
    ECLifeSimulator(){}
    ~ECLifeSimulator(){}
    
    // Initialize the simulation. Clear out all previous inputs (including the organisms)
    void Initialize()
    {
        listOrganism.clear();
    }
    
    // Add an organism to simulate. Note: don't free its memory inside simulator
    // return its position in the list of organisms (to be used in future reference)
    int AddOrganism(ECOrganism *ptr)
    {
        listOrganism.push_back(ptr);
        return listOrganism.size()-1;
    }
    
    // Schedule a daily event for an organism, at certain time of day (hours), type of event (0: eat, 1: work), subtype of the event (for work, the kind of work)
    void AddDailyEvent( double hours, int indexOrganism, int type, int subtype )
    {
        vector<double> temp;
        temp.push_back(hours);
        temp.push_back(type);
        temp.push_back(subtype);
        listOrganism[indexOrganism]->events.push_back(temp);
        
    };
    
    // Run simulation from some time (hours) until there is no living organisms or run out of time (as specified in timeLimt, which is in the unit of hours)
    //Return the total elapsed time from start to end of the simulation (in hours).
    double Simulate(double hoursStart, double timeLimit)
    {
        if (listOrganism.size() == 0)
            return 0;
        double time = hoursStart;
        double res= 0;
        int index = -1;
        vector< vector<double> > *schedule = new vector< vector<double> >;
        
        
        //add all the events to daily schedule
        for (auto x : listOrganism)
        {
            index += 1; //the index of the animal
            //loop to run all the events this animal have and add to schedule
            for (auto i = 0; i < (x->events).size(); i++ )
            {
                //if this animal have no event to do then break
                if ((x->events).size() == 0)
                    break;
                //event = ith element of the animal's event
                vector<double> *event = new vector<double> ;
                *event = (x->events).at(i);
                event->push_back(index);
                schedule->push_back(*event);
                delete event;
            }
        }
        
        //sort schedule by time and index
        *schedule = schedule_sort(*schedule);
        
        
        for (auto x: *schedule)
        {
            cout<< x[0]<<"  ";
            cout<< x[1]<<"  ";
            cout<< x[2]<<"  ";
            cout<< x[3]<<endl;
        }
        
        //run the schedule
        res = run_schedule(*schedule, res, time , timeLimit, index);
        delete schedule;
        return res;
        
    }
    
    bool all_dead(vector<ECOrganism *> rhs)
    {
        for (auto x: rhs)
        {
            if (x->vitality >0)
                return false;
        }
        return true;
    }
    // Collect info on simulation
    // Get the alive organisms and return their names in the passed-in set
    void GetAliveOrganisms(std::set<std::string> &setAlives) const
    {
        for( auto x: listOrganism)
        {
            if( x->vitality > 0)
            {
                setAlives.insert(x->name);
            }
                
        }
    }
    
    // Get the vitality of a specific organism (as named)
    double GetVitalityFor(const std::string &orgName) const
    {
        for (auto x : listOrganism)
        {
            if (x->name == orgName)
                return x->vitality;
        }
        return 0;
    }
    
private:
    // your code here...
    vector<ECOrganism *> listOrganism;
    
    
    
    
    vector< vector<double> > schedule_sort(vector< vector<double> > schedule)
    {
        vector<double> temp;
        int n = schedule.size();
        for (auto i = 0; i < n - 1; i++)
        {
            for (auto j = 0; j < n - i - 1; j++)
            {
                if (schedule.at(j)[0] == schedule.at(j+1)[0] && schedule.at(j)[3] > schedule.at(j+1)[3])
                {
                    temp = schedule.at(j);
                    schedule.at(j) = schedule.at(j+1);
                    schedule.at(j+1) = temp;
                }
                else if (schedule.at(j)[0] > schedule.at(j+1)[0])
                {
                    temp = schedule.at(j);
                    schedule.at(j) = schedule.at(j+1);
                    schedule.at(j+1) = temp;
                }
            }
        }
        return schedule;
    }
    
    
    
    
    double run_schedule(vector< vector<double> > schedule, double res, double time , double timeLimit, int index)
    {
        for (auto i = 0; i< schedule.size(); i++)
        {
            if (time == (schedule.at(i)).at(0))
            {
                break;
            }
            else if (time < (schedule.at(i)).at(0))
            {
                res += (schedule.at(i)).at(0) - time;
                time = (schedule.at(i)).at(0);
                break;
            }
            else if (i == schedule.size()-1 && (time != (schedule.at(i)).at(0)))
            {
                res += 24 - time;
                time = 0;
            }
        }
        cout<< "res ="<<0<<endl;
        cout<< "timelimit ="<<timeLimit<<endl;
        if (schedule.size()==0)
        {
            return 0;
        }
        else
        {
            while (res <= timeLimit)
            {
                for (auto i = 0; i< schedule.size(); i++)
                {
                    if (time == schedule[i][0])
                    {
                        cout<< "time = "<<time<<"     res ="<<res<<endl;
                        index  =schedule[i][3];
                        
                        
                        
                        if (schedule[i][1] == 0)
                        {
                            
                            listOrganism[index]->Eat(schedule[i][0]);
                            if (all_dead(listOrganism))
                                return res;
                            
                            //move time to next on schedule
                            if (i < schedule.size()-1)
                            {
                                res += schedule[i+1][0] - time;
                                time = schedule[i+1][0];
                                if (res > timeLimit)
                                    return timeLimit;
                            }
                            else
                            {
                                res += 24 - time +schedule[0][0];
                                time = schedule[0][0];
                                if (res > timeLimit)
                                    return timeLimit;
                            }
                            
                        }
                        else
                        {
                            listOrganism[index]->Work(schedule[i][0], schedule[i][2]);
                            if (all_dead(listOrganism))
                                return res;
                            //move time to next on schedule
                            if (i < schedule.size()-1)
                            {
                                res += schedule[i+1][0] - time;
                                time = schedule[i+1][0];
                                if (res > timeLimit)
                                    return timeLimit;
                            }
                            else
                            {
                                res += 24 - time +schedule[0][0];
                                time = schedule[0][0];
                                if (res > timeLimit)
                                    return timeLimit;
                            }
                        }
                        
                        for (auto i = 0; i< listOrganism.size(); i++)
                            cout<<listOrganism[i]->type<< " " << listOrganism[i]->name<<" = "<<listOrganism[i]->vitality<<endl;
                    }
                    
                }
                
            }
        }
        if (res >= timeLimit)
            return timeLimit;
        
        return res;
    }
    
};

#endif /* ECLifeSimulator_h */
