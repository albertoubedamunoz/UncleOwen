// NIF 48724775B ÚBEDA MUÑOZ, ALBERTO
#ifndef FIELD_H_
#define FIELD_H_

#include <iostream>
#include <string>
#include <vector>
#include "Android.h"

using namespace std;

class Field {

  friend ostream& operator<<(ostream &os,const Field& f);

  protected:
    string name;
    int products;
    int hoursLeft;
    vector<Android*> androids;
    int droidsCapacity() const;

  public:
    Field(string name);
    string getName() const { return name; }
    int getProducts() const { return products; }
    int getHoursLeft() const {return hoursLeft; }
    unsigned int numAndroids() const { return androids.size(); }
    void setProducts(int products);
    void addProducts(int products);
    bool needsDroids() const;
    void addDroid(Android *newAndroid);
    void collect();

};

#endif