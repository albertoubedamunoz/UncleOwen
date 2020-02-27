// NIF 48724775B ÚBEDA MUÑOZ, ALBERTO
#ifndef ANDROID_H_
#define ANDROID_H_

#include <iostream>
#include <string>

using namespace std;

// ---------------- android -------------------------
enum Status {
  ST_WORKING, 
  ST_IDLE, 
  ST_MAINTENANCE0,
  ST_MAINTENANCE1 
};
//---------------------------------------------------

class Android {

  friend ostream& operator<<(ostream &os,const Android& a);

  protected:
    string model;
    int speed;
    int serialNumber;
    int hoursWorked;
    static int nextSerialNumber;
    Status status;
    bool asssigned;

  public:
    Android();
    Android(string model, int speed);
    string getModel() const { return model; }
    int getSpeed() const { return speed; }
    int getSeialNumber() const { return serialNumber; }
    int getHoursWorked() const { return hoursWorked; }
    Status getStatus() const { return status; }
    bool isAssigned() const { return asssigned;}
    void setAssigned(bool asssigned) { this-> asssigned=asssigned; }
    void setStatus(Status status) { this-> status=status; }
    void resetHoursWorked() { hoursWorked=0; }
    bool isIdle() const;
    void oneMoreHour();
    bool isMaintenanceTime() const;
    
};

#endif