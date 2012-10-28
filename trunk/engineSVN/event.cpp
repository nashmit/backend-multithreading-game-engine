
#include "engine.h"

ManagerEvents* ManagerEvents::Instance = NULL;

void CThrowEvents::addEvent(IEvent* event) {
    
   Events.push_back( event );
    
}

void CThrowEvents::Dispatch() {
    
    for( int i = 0 ; i < Events.size() ; i++ )
        for( int j = 0 ; j < Observers.size() ; j++ ){
            Observers[j]->FireEvent( Events[i] );
        }
    
    while ( !Events.empty() ) {
        delete Events[0];
        Events.pop_front();
    }
}

void CThrowEvents::Register(const IObserver::Ptr & cpy) {
    Observers.push_back(cpy);
}

CThrowEvents::~CThrowEvents() {
    while ( !Events.empty() ) {
        delete Events[0];
        Events.pop_front();
    }
}

void IObserver::FireEvent( IEvent*  event) {};

IObserver::~IObserver() {};
    
    

bool ManagerEvents::EventTimeOut(IEvent* event)
{
    // TO DO
    return true;
}

void ManagerEvents::Dispatch() {
    
    for( int i = 0 ; i < Events.size() ; i++ )
        
        // TO DO -> check if the event is not timed out, call function EventTimeOut();
        
        for( int j = 0 ; j < Observers.size() ; j++ ){
            Observers[j]->FireEvent( Events[i] );
        }
    
    while ( !Events.empty() ) {
        delete Events[0];
        Events.pop_front();
    }
}
