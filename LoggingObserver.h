#pragma once

#include <iostream>
#include <string>

class Observer  {
  public:
	Observer();
  ~Observer();
  Observer(int len);
  Observer(const Observer &obj);
  
  private:
	 int *ptr;
};
class Subject{
  public:
  Subject();
  ~Subject();
  Subject(int len);
  Subject(const Subject &obj);
  private:
  int *ptr;
};
class ILoggable{
  public:
  ILoggable();
  ~ILoggable();
  ILoggable(int len);
  ILoggable(const ILoggable &obj);
  virtual stringToLog() = 0;
  update();
  private:
  int *ptr;
};