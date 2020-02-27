// NIF 48724775B ÚBEDA MUÑOZ, ALBERTO
#ifndef FARM_H_
#define FARM_H_

#include <iostream>
#include <string>
#include <vector>
#include "Field.h"
#include "Util.h"

class Farm {

  friend ostream& operator<<(ostream &os,const Farm& f);

  protected:
    string name;
    unsigned int numAndroids;
    static const int MAXANDROIDS=30;
    void distributeAndroids();
    void collect();
    vector<Android> androids;
    vector<Field> fields;

  public:
	  Farm(string name);
    string getName() const { return name; }
    unsigned int numFields() const;
    unsigned int getNumAndroids() const { return numAndroids; }
    void createField(string fieldName="");
    void createAndroid(int speed=-1, string model="");
    void processProducts(string products);
    void startWorkingHour(int &hour);
	
};

#endif