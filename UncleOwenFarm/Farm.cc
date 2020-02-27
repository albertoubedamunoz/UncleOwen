// NIF 48724775B ÚBEDA MUÑOZ, ALBERTO
#include <iostream>
#include <stdexcept>
#include "Farm.h"

using namespace std;

Farm::Farm(string name) {

  this-> name=name;
  numAndroids=0;
}

void Farm::createField(string fieldName) {

  bool checkFields=true;

  if(fieldName=="") {
    cout << "Enter field name: ";
    getline(cin, fieldName);
  }
  for(unsigned int i=0; i<fields.size() && checkFields; i++) {
    if(fieldName==fields[i].getName()) {
      checkFields=false;  
    }    
  }
  if(checkFields) {
    Field field(fieldName);
    fields.push_back(field);
  }
  else {
    Util::error(ERR_NAME);
  }
}

void Farm::createAndroid(int speed, string model) {

  if(numAndroids>=MAXANDROIDS) {
    Util::error(ERR_MAXANDROIDS);
  }
  else {
    if(speed==-1) {
      cout << "Enter android speed: ";
      cin >> speed;
      if(speed>0) {
        cout << "Enter android model: ";
        cin.get();
        getline(cin, model);
        try {
          Android android(model, speed);
          androids.push_back(android);
        }
        catch(invalid_argument error) {
          Util::error(ERR_WRONG_MODEL);
        }
      }
      else {
        Util::error(ERR_WRONG_SPEED);
      }
    }
    else {
      try {
        Android android(model, speed);
        androids.push_back(android);
      }
      catch(invalid_argument error) {
        Util::error(ERR_WRONG_MODEL);
      }  
    }
  }
}

void Farm::processProducts(string products) {

 /* string field, nOfproducts;
     int numberOfField;
     unsigned int j=0;

     for(unsigned int i=j; i<products.size(); i=j) {
       j=i;
       field.clear();
       nOfproducts.clear();
       while(products[j]!='"' && j<products.size()) {
         j++;
       }
       if(products[j]=='"') {
         j++;
         do {
           field+=products[j];
           j++;
         }
         while(products[j]!='"' && j<products.size());
         if(!checkFields(f, field, numberOfField)) {
           error(ERR_WRONG_FIELD);
           j++;
         }
         else {
           do {
             j++;
           }
           while(products[j]!=':' && j<products.size());
           do {
             j++;
           }
           while(!isdigit(products[j]) && j<products.size());
           do {
             nOfproducts+=products[j];
             j++;
           }
           while(isdigit(products[j]) && j<products.size());
           unsigned int prodNum=atoi(nOfproducts.c_str());
           if(prodNum==0) {
             error(ERR_WRONG_PRODUCTS);
           }
           else {
             f.fields[numberOfField].products+=prodNum;
           }
         }  
       } 
     }  */
}

void Farm::distributeAndroids() {

 /* unsigned int numberOfAndFarm=f.androids.size();

     for(unsigned int l=0; l<numberOfAndFarm; l++) {

       unsigned int m=2147483647;
       int fieldMaxProd=0;
       int MaxProdField;
       int androidMaxSpeed=-1;
       int fastAndroid;
       int recoletCapacity=0;
       bool fieldsWithProd=false;
       bool workingAndroids=false;

       for(unsigned int i=0; i<f.fields.size(); i++) {
         if(f.fields[i].products>0 && f.fields[i].androids.size()<m) {
           //cout << "logrado1: "<< f.fields[i].name << "m: "<<f.fields[i].androids.size() << endl;
           if(f.fields[i].androids.size()==0) {
             recoletCapacity=0;
           }
           else {
             recoletCapacity=0;
             for(unsigned int n=0; n<f.fields[i].androids.size(); n++) {
               //cout << f.fields[i].androids[n].model << endl;
               //cout << f.fields[i].androids[n].speed << endl;
               recoletCapacity+=(f.fields[i].androids[n].speed);
               //cout << recoletCapacity << endl;
             }
           }
           if(recoletCapacity<f.fields[i].products) {
             m=f.fields[i].androids.size();
             fieldsWithProd=true;  
           }
         }
       }
       recoletCapacity=0;
       if(fieldsWithProd) {
         for(unsigned int j=0; j<f.fields.size(); j++) {
           if(f.fields[j].androids.size()==m && f.fields[j].products>fieldMaxProd) {
             for(unsigned int p=0; p<f.fields[j].androids.size(); p++) {
               recoletCapacity+=(f.fields[j].androids[p].speed);
             }
             if(recoletCapacity<f.fields[j].products) {
               fieldMaxProd=f.fields[j].products;
               MaxProdField=j;
             } 
           } 
         }
         //cout << f.fields[MaxProdField].name << endl;
         for(unsigned int k=0; k<f.androids.size(); k++) {
           if(f.androids[k].status==ST_IDLE && f.androids[k].speed>androidMaxSpeed) {
             androidMaxSpeed=f.androids[k].speed;
             fastAndroid=k;
             workingAndroids=true;
           }
         } 
         if(workingAndroids) {
           //cout << "logrado: "<< f.fields[MaxProdField].name << endl;
           f.androids[fastAndroid].status=ST_WORKING;
           f.fields[MaxProdField].androids.push_back(f.androids[fastAndroid]);
           f.androids.erase(f.androids.begin()+fastAndroid); 
         } 
       }
     } */
}

void Farm::collect() {

 /* vector<Android> androids;

     cout << SEPARATOR << endl;
     cout << HOUR << hour << endl;
     cout << HEADER1 << endl;
     printFarm(farm);
     distributeAndroids(farm);
     cout << HEADER2 << endl;
     printFarm(farm);
     for(unsigned int i=0; i<farm.fields.size(); i++) {
       if(farm.fields[i].products>0) {
         androids=collectField(farm.fields[i]);
         unsigned int numberOfAndField=androids.size();
         for(unsigned int j=0; j<numberOfAndField; j++) {
           farm.androids.push_back(androids[j]);
         } 
       }
       unsigned int numberOferaseField=farm.fields[i].androids.size(); 
       for(unsigned int k=0; k<numberOferaseField; k++) {
         if(farm.fields[i].androids[k].status!=ST_WORKING) {
           farm.fields[i].androids.erase(farm.fields[i].androids.begin()+k);
         } 
       }
     }
     hour++;
     cout << HEADER3 << endl;
     printFarm(farm);
     if(hour>DAILY_WORKING_HOURS) {
       hour=1;
       for(unsigned int l=0; l<farm.androids.size(); l++) {
         if(farm.androids[l].status==ST_MAINTENANCE1) {
           farm.androids[l].status=ST_IDLE;
           farm.androids[l].hoursWorked=0;
         }
         if(farm.androids[l].status==ST_MAINTENANCE0) {
           farm.androids[l].status=ST_MAINTENANCE1;
         }
       }
     } */
}

void Farm::startWorkingHour(int &hour) {

 /* string products;

     if(f.fields.size()>0) {
       if(hour==1) {
         cout << "Products: ";
         getline(cin, products);
         processProducts(f, products);
       } 
     }
     else {
       error(ERR_NO_FIELDS);
     }
     collectFarm(f, hour); */
}

ostream& operator<<(ostream &os,const Farm& f) {

  os << "Farm: " << f.name << endl;
  for(unsigned int i=0; i<f.fields.size(); i++) {
    os << f.fields[i];
    os << endl;
  } 
  for(unsigned int j=0; j<f.androids.size(); j++) {
    os << f.androids[j]; 
    os << endl;
  }   
 
  return os;
} 

