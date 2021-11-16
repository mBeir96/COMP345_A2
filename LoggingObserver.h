#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;

class ILoggable;

class Observer
{
public:
	Observer();
	~Observer();
	Observer(int len);
	Observer(const Observer& obj);
	virtual void Update(ILoggable* s, string l) = 0;
private:
	int* ptr;
};
class Subject {
public:
	Subject();
	~Subject();
	Subject(int len);
	Subject(const Subject& obj);
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify(ILoggable* s, string l);

private:
	list<Observer*>* _observers;
	int* ptr;
};

class ILoggable {
public:
	ILoggable();
	~ILoggable();
	ILoggable(int len);
	ILoggable(const ILoggable& obj);
	virtual void stringToLog(string l) = 0;

private:
	int* ptr;

};

class LogObserver : public Observer
{
public:
	LogObserver();
	LogObserver(Subject* s);
	LogObserver(const LogObserver& old);
	void Update(ILoggable* s, string l);
	void stringToLog(ILoggable* s, string l);
private:

	Subject* _subject;
};
