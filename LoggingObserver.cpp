#include "LoggingObserver.h"
#include <iostream>
#include <string>
using namespace std;

//method in Observer 
Observer::Observer()
{
  cout << "Welcome to Observer class  " << endl;
}
Observer::~Observer()
{
    cout << "The object is destroy..." << endl;
}
Observer::Observer(int len) {
   cout << "Normal constructor allocating ptr (Observer)" << endl;
   
   // allocate memory for the pointer;
   ptr = new int;
   *ptr = len;
}
Observer::Observer(const Observer &obj) {
   cout << "Copy constructor allocating ptr. (observer)" << endl;
   ptr = new int;
   *ptr = *obj.ptr; // copy the value
}
 
//method in Subject 
Subject::Subject(){
  cout << "Welcome to Subject class  " << endl;
}


Subject::~Subject()
{
    cout << "The object is destroy..." << endl;
}
Subject::Subject(int len) {
   cout << "Normal constructor allocating ptr (Subject)" << endl;
   
   // allocate memory for the pointer;
   ptr = new int;
   *ptr = len;
}
Subject::Subject(const Subject &obj) {
   cout << "Copy constructor allocating ptr. (SUbject)" << endl;
   ptr = new int;
   *ptr = *obj.ptr; // copy the value
}

//method in ILoggable 
ILoggable::ILoggable(){
  cout << "Welcome to ILoggable class  " << endl;
}


ILoggable::~ILoggable()
{
    cout << "The object is destroy..." << endl;
}
ILoggable::ILoggable(int len) {
   cout << "Normal constructor allocating ptr (ILoggable)" << endl;
   
   // allocate memory for the pointer;
   ptr = new int;
   *ptr = len;
}
ILoggable::ILoggable(const ILoggable &obj) {
   cout << "Copy constructor allocating ptr. (ILoggable)" << endl;
   ptr = new int;
   *ptr = *obj.ptr; // copy the value
}

void ILoggable::stringToLog(){
  cout <<"string"<<endl;
}
void ILoggable::update(){
  //stringToLog(string c, string r);
 
}


