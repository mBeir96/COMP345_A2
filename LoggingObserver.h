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
	Observer(const Observer& obj);
	friend std::istream& operator>>(std::istream& in, const Observer& o);
	friend std::ostream& operator<<(std::ostream& out, const Observer& o);
	virtual void Update(ILoggable* s, string l) = 0;

};
class Subject {
public:
	Subject();
	~Subject();
	friend std::istream& operator>>(std::istream& in, const Subject& s);
	friend std::ostream& operator<<(std::ostream& out, const Subject& s);
	Subject(const Subject& obj);
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify(ILoggable* s, string l);

private:
	list<Observer*>* _observers;

};

class ILoggable {
public:
	ILoggable();
	~ILoggable();
	ILoggable(const ILoggable& obj);
	friend std::istream& operator>>(std::istream& in, const ILoggable& i);
	friend std::ostream& operator<<(std::ostream& out, const ILoggable& i);
	virtual void stringToLog(string l) = 0;

};

class LogObserver : public Observer
{
public:
	LogObserver();
	LogObserver(Subject* s);
	LogObserver(const LogObserver& old);
	~LogObserver();
	friend std::istream& operator>>(std::istream& in, const LogObserver& l);
	friend std::ostream& operator<<(std::ostream& out, const LogObserver& l);
	void Update(ILoggable* s, string l);
	void stringToLog(ILoggable* s, string l);
private:

	Subject* _subject;
};
