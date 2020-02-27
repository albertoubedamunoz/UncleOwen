// NIF 48724775B ÚBEDA MUÑOZ, ALBERTO
#include <iostream>
#include <stdexcept>
#include "Android.h"

using namespace std;

// ---------------- android -------------------------
const int NUMDROIDMODELS=25;

typedef struct {

  string modelName;
  int    hoursMaintenance;

} AndroidData;

const AndroidData ANDROIDDATA[NUMDROIDMODELS] = 
  {
    "x-75", 8,
    "fx-7", 10,
    "JK9", 15,
    "XAR-25", 5,
    "HC-2", 12,
    "Xj 23 v7.5", 10,
    "c3p0-2", 20,
    "r2d2", 15,
    "f9-x d27", 10,
    "-v65 +23", 11,
    "@prog2ua", 13,
    "#h45ht4g", 18,
    "fx-9", 10,
    "x-7", 12,
    "JK10", 7,
    "GHR tdi9", 10,
    "fx-8", 20,
    "fx-75", 5,
    "JK9-75", 14,
    "HC-3.7", 12,
    "xw-a87", 17,
    "tiDef 8", 25,
    "fx-5", 10,
    "fx-3", 8,
    "fx-4", 9
 };
 //--------------------------------------------------

int Android::nextSerialNumber=100;

Android::Android() {

  model="";
  speed=-1;
}

Android::Android(string model, int speed) {

  bool findAndroid=false;

  for(int i=0; i<NUMDROIDMODELS && !findAndroid ; i++) {
    if(model==ANDROIDDATA[i].modelName) {
      findAndroid=true;
    }  
  }
  if(findAndroid) {
    if(speed>0) {
      this -> model=model;
      this -> speed=speed;
      serialNumber=nextSerialNumber;
      nextSerialNumber++;
      status=ST_IDLE;
      hoursWorked=0;
    }
    else {
      throw invalid_argument("wrong speed");
    }   
  }
  else {
    throw invalid_argument("wrong android model");
  }
}

bool Android::isIdle() const {

  bool isIdle=false;
  
  if(status==ST_IDLE) {
    isIdle=true;
  }

  return isIdle;
}

void Android::oneMoreHour() {

  hoursWorked++;
}

bool Android::isMaintenanceTime() const {

  bool isMaintenanceTime=false;
  bool findAndroid=false;

  for(int i=0; i<NUMDROIDMODELS && !findAndroid ; i++) {
    if(model==ANDROIDDATA[i].modelName) {
      findAndroid=true;
      if(hoursWorked>=ANDROIDDATA[i].hoursMaintenance) {
        isMaintenanceTime=true;
      }
    }
  }   

  return isMaintenanceTime;
}

ostream& operator<<(ostream &os,const Android& a) {

  os << "[" << a.model;
  os << " sn=" << a.serialNumber;
  os << " s=" << a.speed;
  os << " hw=" << a.hoursWorked;
  os << " st=" << a.status;
  os << "]";  

  return os;
}