#include "LoggingObserver.h"
#include <iostream>
#include <string>
using namespace std;

//method in Observer 
Observer::Observer()
{
    
}
Observer::~Observer()
{
   
}

Observer::Observer(const Observer& obj) {
    
}

std::ostream& operator<<(std::ostream& out, const Observer& o)
{
    return out;
}

std::istream& operator>>(std::istream& in, Observer& o)
{
    return in;
}


//method in Subject 
Subject::Subject() {
    _observers = new list<Observer*>;
}
std::ostream& operator<<(std::ostream& out, const Subject& s)
{
    out << s._observers;
    return out;
}

std::istream& operator>>(std::istream& in, Subject& t)
{
    return in;
}

Subject::~Subject()
{
    delete _observers;
    _observers = NULL;
}

Subject::Subject(const Subject& obj)
{
    _observers = obj._observers;
}
void Subject::Attach(Observer* o) {
    _observers->push_back(o);
};
void Subject::Detach(Observer* o) {
    _observers->remove(o);
};
void Subject::Notify(ILoggable* s, string l) {
   
    _observers->back()->Update(s, l);
};


//method in ILoggable 
ILoggable::ILoggable() {
    
}


ILoggable::~ILoggable()
{
    
}

ILoggable::ILoggable(const ILoggable& obj) {
   
    
}
std::ostream& operator<<(std::ostream& out, const ILoggable& i)
{
    return out;
}

std::istream& operator>>(std::istream& in, ILoggable& i)
{
    return in;
}
//LogObserver Class
LogObserver::LogObserver()
{

}

LogObserver::LogObserver(const LogObserver& old)
{
    _subject = old._subject;
}

LogObserver::~LogObserver()
{
    _subject->Detach(this);
}

LogObserver::LogObserver(Subject* s)
{
    _subject = s;
    _subject->Attach(this);

}

std::ostream& operator<<(std::ostream& out, const LogObserver& l)
{
    l._subject;
    return out;
}

std::istream& operator>>(std::istream& in, LogObserver& l)
{
    return in;
}

void LogObserver::Update(ILoggable* s, string l)
{
    stringToLog(s, l);
}

void LogObserver::stringToLog(ILoggable* s, string l)
{
    s->stringToLog(l);
}


