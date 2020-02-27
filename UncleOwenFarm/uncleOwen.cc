// NIF 48724775B ÚBEDA MUÑOZ, ALBERTO
#include <iostream>
#include <climits>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cstring>

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



enum Status {
  ST_WORKING, 
  ST_IDLE, 
  ST_MAINTENANCE0,
  ST_MAINTENANCE1 
};

typedef struct {

   string model;
   int speed;
   int serialNumber;
   Status status;
   int hoursWorked;
   
} Android;

// ---------------- field -------------------------

typedef struct {

   string name;
   int products;
   int hoursLeft;
   
   vector<Android> androids;
} Field;

// ---------------- farm --------------------------

const int DAILY_WORKING_HOURS=10;

typedef struct {

  string name;
  vector<Field> fields;
  vector<Android> androids;

} Farm;

// ---------------- error -------------------------
enum Error {
  ERR_NO_FIELDS, 
  ERR_UNKNOWN_OPTION,
  ERR_WRONG_MODEL,
  ERR_WRONG_FIELD,
  ERR_WRONG_SPEED, 
  ERR_WRONG_PRODUCTS,
  ERR_NAME,
  ERR_OPEN_FILE,
  ERR_ARGS
};

void error(Error n)
{
  switch (n) {
   
    case ERR_NO_FIELDS:
      cout << "Error, there are no fields in the farm" << endl;
      break;
      
    case ERR_UNKNOWN_OPTION:
      cout << "Error, unknown option" << endl;
      break;

    case ERR_WRONG_MODEL:
      cout << "Error, wrong android model name" << endl;
      break;

    case ERR_WRONG_FIELD:
      cout << "Error, wrong field name" << endl;
      break;

    case ERR_WRONG_SPEED:
      cout << "Error, wrong speed" << endl;
      break;

    case ERR_WRONG_PRODUCTS:
      cout << "Error, wrong number of products" << endl;
      break;

    case ERR_NAME:
      cout << "Error, field name repeated" << endl;
      break;

    case ERR_OPEN_FILE:
      cout << "Error, can't open file" << endl;
      break;
    
    case ERR_ARGS:
      cout << "Error, wrong arguments" << endl
           << "Usage: uncleOwen [-f fieldName] [-a androidsFile] [-p productsFile]" << endl;
      break;
  }
}

//---------------------------------------------------------------
const string HEADER1="---- start ----";
const string HEADER2="---- distribution ----";
const string HEADER3="---- end ----";
const string HOUR="Hour: ";
const string SEPARATOR="===============================================";
//---------------------------------------------------------------



void printAndroid(const Android &a) {

     cout << "[" << a.model;
     cout << " sn=" << a.serialNumber;
     cout << " s=" << a.speed;
     cout << " hw=" << a.hoursWorked;
     cout << " st=" << a.status;
     cout << "]";  
}

void printField(const Field &f) {

     cout << "{Field: " << f.name;
     cout << "(" << f.products << " " << f.hoursLeft << ")" << endl;
     for(unsigned int i=0; i<f.androids.size(); i++) {
       cout << "  ";     
       printAndroid(f.androids[i]);
       cout << endl;
     } 
     cout << "}";
}

void printFarm(const Farm &f) {

     cout << "Farm: " << f.name << endl;
     for(unsigned int i=0; i<f.fields.size(); i++) {
       printField(f.fields[i]);
       cout << endl;
     } 
     for(unsigned int j=0; j<f.androids.size(); j++) {
         printAndroid(f.androids[j]); 
         cout << endl;
     }   
}

bool checkFields(Farm &farm, string fieldName, int &numberOfField) {

     bool checkFields=false;

     for(unsigned int i=0; i<farm.fields.size() && !checkFields; i++) {
       if(fieldName==farm.fields[i].name) {
         checkFields=true;  
         numberOfField=i;  
       }    
     }  

     return checkFields;
}

// creates a new field in the farm with the name provided by the user
void createField(Farm &farm) {

     Field newField;
     int numberOfField;

     cout << "Enter field name: ";
     getline(cin, newField.name);
     if(farm.fields.size()==0) {
       newField.products=0;
       newField.hoursLeft=DAILY_WORKING_HOURS;
       farm.fields.push_back(newField);
     }
     else {
       if(checkFields(farm, newField.name, numberOfField)) {
         error(ERR_NAME);
       }
       else {  
         newField.products=0;
         newField.hoursLeft=DAILY_WORKING_HOURS;
         farm.fields.push_back(newField);
      }
    } 
}

// Creates a new android asking the data to the user given nextSerialNumber, and
// adds the android to the farm
void createAndroid(Farm &farm, int &nextSerialNumber) {

     Android newAndroid;
     bool addAndroid=false;

     cout << "Enter android speed: ";
     cin >> newAndroid.speed;
     if(newAndroid.speed<=0) {
       error(ERR_WRONG_SPEED);
     }
     else {
       cout << "Enter android model: ";
       cin.get();
       getline(cin, newAndroid.model);

       for(int i=0; i<NUMDROIDMODELS && !addAndroid ; i++) {
         if(newAndroid.model==ANDROIDDATA[i].modelName) {
           newAndroid.serialNumber=nextSerialNumber;
           nextSerialNumber++;
           newAndroid.status=ST_IDLE;
           newAndroid.hoursWorked=0;
           farm.androids.push_back(newAndroid);
           addAndroid=true;
         }
         else {
           if(i==NUMDROIDMODELS-1) {
             error(ERR_WRONG_MODEL);
           }
         }
       }
     }
}


void distributeAndroids(Farm &f) {

     unsigned int numberOfAndFarm=f.androids.size();

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
     }
}

vector<Android> collectField(Field &f) {

     int recoletedProducts=0;
     bool findAndroid=false;
     vector<Android> androids;

     for(unsigned int i=0; i<f.androids.size(); i++) {
       recoletedProducts+=(f.androids[i].speed);
       f.androids[i].hoursWorked++;
       findAndroid=false;
       for(int j=0; j<NUMDROIDMODELS && !findAndroid ; j++) {
         if(f.androids[i].model==ANDROIDDATA[j].modelName) {
           findAndroid=true;
           if(f.androids[i].hoursWorked>=ANDROIDDATA[j].hoursMaintenance) {
             f.androids[i].status=ST_MAINTENANCE0;
             androids.push_back(f.androids[i]);
           }
         }
       }   
     } 
     if(recoletedProducts>=f.products) {
       f.products=0;
     }
     else {
       f.products-=recoletedProducts;
     }
     f.hoursLeft--;
     if(f.products==0 || f.hoursLeft==0) {
       f.hoursLeft=DAILY_WORKING_HOURS;
       for(unsigned int k=0; k<f.androids.size(); k++) {
         if(f.androids[k].status==ST_WORKING) {
           f.androids[k].status=ST_IDLE;
           androids.push_back(f.androids[k]);
        }
       }  
     }

     return androids;
}

void collectFarm(Farm &farm,int &hour) {

     vector<Android> androids;

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
     }
}


void processProducts(Farm &f,string products) {

     string field, nOfproducts;
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
     }  
}

void startWorkingHour(Farm &f,int &hour) {
     
     string products;

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
     collectFarm(f, hour);
}


//--------------------------------------------------------

const int MAXNAME=10;

typedef struct {
  char model[MAXNAME];
   int speed;
   int serialNumber;
   Status status;
   int hoursWorked;
} AndroidBin;

typedef struct {
  char name[MAXNAME];
  unsigned int products;
  int hoursLeft;
  unsigned int numAndroids;
} FieldBin;

typedef struct {
  char name[MAXNAME];
  int nextSerialNumber;
  int hour;
  unsigned int numFields;
} FarmBin;


// asks for the filename, then opens the file and writes farm data. If the
// file can't be opened returns false, otherwise returns true
bool writeFarmData(const Farm &farm,int nextSerialNumber,int hour) {

     bool correct=true;
     string fileName;
     char fileB[100];
     FarmBin farmBin;

     cout << "Enter filename: ";
     getline(cin, fileName);
     strcpy(fileB, fileName.c_str());
     ofstream fbe(fileB, ios::binary);
     if(fbe.is_open()) {
       strcpy(farmBin.name, farm.name.c_str());
       farmBin.nextSerialNumber=nextSerialNumber;
       farmBin.hour=hour;
       farmBin.numFields=farm.fields.size();
       fbe.write((const char *)&farmBin, sizeof(farmBin));
       for(unsigned int i=0; i<farm.fields.size(); i++) {

         FieldBin fieldBin;

         strcpy(fieldBin.name, farm.fields[i].name.c_str());
         fieldBin.products=farm.fields[i].products;
         fieldBin.hoursLeft=farm.fields[i].hoursLeft;
         fieldBin.numAndroids=farm.fields[i].androids.size();
         fbe.write((const char *)&fieldBin, sizeof(fieldBin));
         for(unsigned int j=0; j<farm.fields[i].androids.size(); j++) {
         
           AndroidBin androidBin;

           strcpy(androidBin.model, farm.fields[i].androids[j].model.c_str());
           androidBin.speed=farm.fields[i].androids[j].speed;
           androidBin.serialNumber=farm.fields[i].androids[j].serialNumber;
           androidBin.status=farm.fields[i].androids[j].status;
           androidBin.hoursWorked=farm.fields[i].androids[j].hoursWorked;
           fbe.write((const char *)&androidBin, sizeof(androidBin));
         } 
       }
       for(unsigned int k=0; k<farm.androids.size(); k++) {
         
         AndroidBin androidBin;

         strcpy(androidBin.model, farm.androids[k].model.c_str());
         androidBin.speed=farm.androids[k].speed;
         androidBin.serialNumber=farm.androids[k].serialNumber;
         androidBin.status=farm.androids[k].status;
         androidBin.hoursWorked=farm.androids[k].hoursWorked;
         fbe.write((const char *)&androidBin, sizeof(androidBin));
       } 
     }
     else {
       error(ERR_OPEN_FILE);
       correct=false;
     }

     fbe.close();

     return correct;
}

// asks for the filename, then opens the file and reads farm data. If the
// file can't be opened returns false, otherwise returns true
bool readFarmData(Farm &farm, int &nextSerialNumber,int &hour) {

     bool correct=true;
     string fileName;
     char fileB[100];

     cout << "Enter filename: ";
     getline(cin, fileName);
     strcpy(fileB, fileName.c_str());
     ifstream fbl(fileB, ios::binary); 
     if(fbl.is_open()) {

       farm.fields.clear();
       farm.androids.clear();

       FarmBin farmBinNuevo;
       FieldBin fieldBinNuevo;
       AndroidBin androidBinNuevo;

       fbl.read((char *)&farmBinNuevo, sizeof(farmBinNuevo));
       farm.name=farmBinNuevo.name;
       nextSerialNumber=farmBinNuevo.nextSerialNumber;
       hour=farmBinNuevo.hour;
       for(unsigned int j=0; j<farmBinNuevo.numFields; j++) {

         fbl.read((char *)&fieldBinNuevo, sizeof(fieldBinNuevo));

         Field fieldNuevo;

         fieldNuevo.name=fieldBinNuevo.name;
         fieldNuevo.products=fieldBinNuevo.products;
         fieldNuevo.hoursLeft=fieldBinNuevo.hoursLeft;
         for(unsigned int i=0; i<fieldBinNuevo.numAndroids; i++) {

           fbl.read((char *)&androidBinNuevo, sizeof(androidBinNuevo)); 

           Android androidNuevo;

           androidNuevo.model=androidBinNuevo.model;
           androidNuevo.speed=androidBinNuevo.speed;
           androidNuevo.serialNumber=androidBinNuevo.serialNumber;
           androidNuevo.status=androidBinNuevo.status;
           androidNuevo.hoursWorked=androidBinNuevo.hoursWorked;
           fieldNuevo.androids.push_back(androidNuevo);
         }
         farm.fields.push_back(fieldNuevo);    
       } 
       while(fbl.read((char *)&androidBinNuevo, sizeof(androidBinNuevo))) {

           Android androidNuevo;

           androidNuevo.model=androidBinNuevo.model;
           androidNuevo.speed=androidBinNuevo.speed;
           androidNuevo.serialNumber=androidBinNuevo.serialNumber;
           androidNuevo.status=androidBinNuevo.status;
           androidNuevo.hoursWorked=androidBinNuevo.hoursWorked;
           farm.androids.push_back(androidNuevo);
         }
     }
     else {
       error(ERR_OPEN_FILE);
       correct=false;
     } 

     fbl.close();

     return correct;
}

// asks for the filename, then opens the file and reads android data. If the
// file can't be opened returns false, otherwise returns true
bool importAndroids(Farm &farm,int &nextSerialNumber) {

     bool correct=false;

     return correct;
}

// asks for the filename, then opens the file and reads product data. If the
// file can't be opened returns false, otherwise returns true
bool importProducts(Farm &farm) {

     bool correct=false;

     return correct;
}

//------------------------------------------------------
void menu(int hour)
{
  cout << "-----========== Farm manager ==========-----" << endl
       << "1- List farm info" << endl
       << "2- Add field" << endl
       << "3- Add android" << endl
       << "4- Start working hour (" << hour << ")" << endl
       << "5- Write farm data" << endl
       << "6- Read farm data" << endl
       << "7- Import androids" << endl
       << "8- Import products" << endl
       << "q- Quit" << endl
       << "Option: " ;
}

bool processArguments(int argc,char *argv[],Farm &farm,int &nextSerialNumber) {
  return true;
}


int main(int argc,char *argv[])
{
   Farm farm;
   farm.name = "west farm";
   char option;
   int nextSerialNumber = 100;
   int hour=1;

   if (processArguments(argc,argv,farm,nextSerialNumber))
     do {
        menu(hour);
        cin >> option; cin.get();
        
        switch (option) {
          case '1': printFarm(farm);
            break;
          case '2': createField(farm);
            break;
          case '3': createAndroid(farm, nextSerialNumber);
            break;
          case '4': startWorkingHour(farm, hour);
            break;
          case '5': writeFarmData(farm, nextSerialNumber, hour);
            break;
          case '6': readFarmData(farm, nextSerialNumber, hour);
            break;
          case '7': importAndroids(farm, nextSerialNumber);
            break;
          case '8': importProducts(farm);
            break;
          case 'q':
            break;
          default: error(ERR_UNKNOWN_OPTION);
            break;
        }
     } while (option != 'q');
     
   return 0;
}
