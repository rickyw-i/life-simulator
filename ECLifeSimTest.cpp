#include "ECLifeSimulator.h"
#include "ECSpider.h"
#include "ECGrasshopper.h"
#include "ECCaterpillar.h"
#include "ECMouse.h"
#include "ECFox.h"
#include "ECPanda.h"
#include <iostream>
using namespace std;

// test case 0: one spider, just eat; so will never die
void Test0()
{
    
    
  ECLifeSimulator sim;
  // add a spider dodo which is harmless
  ECSpider dodo("dodo");
  int indDodo = sim.AddOrganism( &dodo );
  // dodo would eat a day
  sim.AddDailyEvent(23.0, indDodo, 0, 0);
    
  double tmStart = 0.0;
  const double tmLimit = 100.0;
    
  double dur = sim.Simulate(tmStart, tmLimit);
    
    
  // it should simulate 100 hours. dodo: vitality 100
    
  cout << "Duration of simulation: " << dur << endl;
    
  cout << "dodo vitality: " << sim.GetVitalityFor("dodo") << endl;
     
}


// test case 1: one spider, more activities
void Test1()
{
  ECLifeSimulator sim;
  // add a spider dodo which is harmless
  ECSpider dodo("dodo");
  int indDodo = sim.AddOrganism( &dodo );
  // dodo would work five times a day but doesn't eat
  sim.AddDailyEvent(23.0, indDodo, 1, 0);
  sim.AddDailyEvent(23.5, indDodo, 1, 0);
    
  sim.AddDailyEvent(0.5, indDodo, 1, 0);
  sim.AddDailyEvent(21.5, indDodo, 1, 0);
  sim.AddDailyEvent(4.0, indDodo, 1, 0);
     
  double tmStart = 0.0;
    const double tmLimit = 100.0;
  // it should simulate 47.5 hours (i.e., two days, short of 0.5 hour, since ending at time 23.5
  double dur = sim.Simulate(tmStart, tmLimit);
  cout << "Duration of simulation: " << dur << endl;
    
}

// test case 2: two spiders, and one is attacking
void Test2()
{
    ECLifeSimulator sim;
    // add a spider dodo which is harmless
    ECSpider dodo("dodo");
    int indDodo = sim.AddOrganism( &dodo );
    // dodo would work twice a day but doesn't eat
    sim.AddDailyEvent(23.0, indDodo, 1, 0);
    sim.AddDailyEvent(4.0, indDodo, 1, 0);
    
    // second spider: yoyo who is attacking dodo
    ECSpider yoyo("yoyo", &dodo);
    
    int indYoyo = sim.AddOrganism( &yoyo );
    // yoyo would weave once a day, eat once and attack once
    sim.AddDailyEvent(0.0, indYoyo, 1, 0);
    sim.AddDailyEvent(1.0, indYoyo, 0, 0);
    sim.AddDailyEvent(2.0, indYoyo, 1, 1);
    
    double tmStart = 0.0;
    const double tmLimit = 50.0;
    // simulation should last 50 hours, while yoyo has vitality 90 (if my code is correct)
    double dur = sim.Simulate(tmStart, tmLimit);
    cout << "Duration of simulation: " << dur << endl;
    cout << "yoyo vitality: " << sim.GetVitalityFor("yoyo") << endl;
     
}

// test case 3: a spider, and a grasshopper (attacking the spider)
void Test3()
{
    ECLifeSimulator sim;
    // add a spider dodo which is harmless
    ECSpider dodo("dodo");
    int indDodo = sim.AddOrganism( &dodo );
    // dodo would work twice a day but doesn't eat
    sim.AddDailyEvent(23.0, indDodo, 1, 0);
    sim.AddDailyEvent(4.0, indDodo, 1, 0);
    
    // grasshopper: pupu who is attacking dodo
    ECGrasshopper pupu("pupu", &dodo);
    int indPupu = sim.AddOrganism( &pupu );
    // yoyo would hop once a day, eat once and attack once
    sim.AddDailyEvent(0.0, indPupu, 1, 0);
    sim.AddDailyEvent(1.0, indPupu, 0, 0);
    sim.AddDailyEvent(5.0, indPupu, 1, 1);
    
    double tmStart = 0.0;
    const double tmLimit = 30.0;
    // duration: 30, with pupu at 80 vitality
    double dur = sim.Simulate(tmStart, tmLimit);
    cout << "Duration of simulation: " << dur << endl;
    cout << "pupu vitality: " << sim.GetVitalityFor("pupu") << endl;
}

// test case 4: a catepillar
void Test4()
{
    ECLifeSimulator sim;
    // add a spider dodo which is harmless
    ECCaterpillar coco("coco");
    int indCoco = sim.AddOrganism( &coco );
    // dodo would work four a day and eat once
    sim.AddDailyEvent(22.0, indCoco, 1, 0);
    sim.AddDailyEvent(23.0, indCoco, 1, 0);
    sim.AddDailyEvent(0.0, indCoco, 1, 0);
    sim.AddDailyEvent(5.0, indCoco, 1, 0);
    sim.AddDailyEvent(6.0, indCoco, 0, 0);
    
    double tmStart = 0.0;
    const double tmLimit = 100.0;
    // duration = 95, coco would die at 23 hour of the 4th day
    double dur = sim.Simulate(tmStart, tmLimit);
    cout << "Duration of simulation: " << dur << endl;
}

// test case 5: a mouse and a spider
void Test5()
{
    ECLifeSimulator sim;
    //
    // add a spider dodo which is harmless
    ECSpider dodo("dodo");
    int indDodo = sim.AddOrganism( &dodo );
    // dodo would work a day
    sim.AddDailyEvent(23.0, indDodo, 1, 0);
    // mouse
    ECMouse qoqo("qoqo");
    int indQoqo = sim.AddOrganism( &qoqo );
    // dodo would work twice a day and eat once
    sim.AddDailyEvent(21.0, indQoqo, 1, 0);
    sim.AddDailyEvent(2.0, indQoqo, 1, 0);
    sim.AddDailyEvent(3.0, indQoqo, 0, 0);
    
    double tmStart = 0.0;
    const double tmLimit = 100.0;
    double dur = sim.Simulate(tmStart, tmLimit);
    // duration = 100, dodo @ vitality 60, qoqo @ vitality 100 in the end
    cout << "Duration of simulation: " << dur << endl;
    cout << "dodo vitality: " << sim.GetVitalityFor("dodo") << endl;
    cout << "qoqo vitality: " << sim.GetVitalityFor("qoqo") << endl;
}

// test case 6: a mouse and a fox that is hunting the mouse
void Test6()
{
    ECLifeSimulator sim;
    //
    ECMouse qoqo("qoqo");
    int indQoqo = sim.AddOrganism( &qoqo );
    // dodo would work twice a day and eat once
    sim.AddDailyEvent(21.0, indQoqo, 1, 0);
    sim.AddDailyEvent(2.0, indQoqo, 1, 0);
    sim.AddDailyEvent(4.0, indQoqo, 0, 0);
    
    // Fox: run twice and hunt once
    ECFox fofo("fofo", &qoqo);
    int indFofo = sim.AddOrganism( &fofo );
    sim.AddDailyEvent(2.0, indFofo, 1, 0);
    sim.AddDailyEvent(5.0, indFofo, 1, 0);
    sim.AddDailyEvent(3.0, indFofo, 1, 1);
    
    double tmStart = 0.0;
    const double tmLimit = 100.0;
    // duration = 53, fofo dies at 5 am of the 3rd day
    double dur = sim.Simulate(tmStart, tmLimit);
    cout << "Duration of simulation: " << dur << endl;
}

// test case 7: a panda
void Test7()
{
    ECLifeSimulator sim;
    //
    ECPanda popo("popo");
    int indPopo = sim.AddOrganism( &popo );
    // popo would work once a day and eat once
    sim.AddDailyEvent(11.0, indPopo, 1, 0);
    sim.AddDailyEvent(12.0, indPopo, 0, 0);
    
    double tmStart = 0.0;
    const double tmLimit = 50.0;
    // duration = 50, pop lives well with 100 vitality in the end
    double dur = sim.Simulate(tmStart, tmLimit);
    cout << "Duration of simulation: " << dur << endl;
 
}
 

int main()
{
    cout<<"start"<<endl;
  Test7();
}

