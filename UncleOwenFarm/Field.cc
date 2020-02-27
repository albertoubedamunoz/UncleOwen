// NIF 48724775B ÚBEDA MUÑOZ, ALBERTO
#include <iostream>
#include <stdexcept>
#include "Field.h"

using namespace std;

// ---------------- field -------------------------
const int DAILY_WORKING_HOURS=10;
//-------------------------------------------------

Field::Field(string name) {
  
    this-> name=name;  
    products=0;
    hoursLeft=DAILY_WORKING_HOURS;
}

void Field::setProducts(int products) {

  this-> products=products;
  if(this-> products<0) {
    this-> products=0;
  }
}

void Field::addProducts(int products) {

  this-> products+=products;
  if(this-> products<0) {
    this-> products=0;
  }
}

bool Field::needsDroids() const {

  bool needsDroids=false;

  return needsDroids;
}

void Field::addDroid(Android *newAndroid) {

}

int droidsCapacity() {


  return 0;
}

void collect() {

}

ostream& operator<<(ostream &os,const Field& f) {

  os << "{Field: " << f.name;
  os << "(" << f.products << " " << f.hoursLeft << ")" << endl;
  for(unsigned int i=0; i<f.androids.size(); i++) {
    os << "  ";     
    os << f.androids[i];
    os << endl;
  } 
  os << "}";
 
  return os;
} 