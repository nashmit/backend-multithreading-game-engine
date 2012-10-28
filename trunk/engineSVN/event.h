
#ifndef Engine_event_h
#define Engine_event_h

#include <queue>

#include "ForwardDeclaration.h"

// IEvent-urile nu au nevoie sa fie guardate cu smart pointeri !
class IEvent /*: public referenceCounting , public Mutex */ {
public:
    virtual ~IEvent() {
        printf("Event deleted\n");
    };
    
    //typedef SmartPtr<IEvent> Ptr;
};

class IObserver : public virtual referenceCounting , public virtual Mutex {
public:
    
    virtual void RegisterTo( IThrowEvents* ) = 0;
    
    virtual void FireEvent( IEvent* );
    
    virtual ~IObserver();
    
    typedef SmartPtr< IObserver > Ptr;
    
};

// interfata pentru crearea de evenimente nu are nevoie sa fie guardata de smart pointeri !
class IThrowEvents /*: public referenceCounting , public Mutex */ {
public:
    
    virtual void Register( const IObserver::Ptr & ) = 0;
    
    virtual void Dispatch() = 0;
    
    virtual void addEvent( IEvent* ) = 0;
    
    virtual ~IThrowEvents() {};
    
    //typedef SmartPtr< IThrowEvents > Ptr;
};

class CThrowEvents : public IThrowEvents {
protected:
    
    std::deque< IEvent* > Events;
    std::vector< IObserver::Ptr > Observers;
    
public:
    
    virtual void Register(const IObserver::Ptr &);
    
    virtual void Dispatch();
    
    virtual void addEvent( IEvent* );
    
    virtual ~CThrowEvents();
    
};

template <class T>
class TemplateObserver: public IObserver {
public:
    
    void FireEvent( IEvent* event) {
        
        T* arg = dynamic_cast< T* >( event );
        if( arg != NULL )
            Event( arg );
    }
    
    void RegisterTo( IThrowEvents* Impl ) {
        Impl-> Register( dynamic_cast< TemplateObserver<T>* >( this ));
    }
    
    virtual void Event( T* ) = 0;
    
    virtual ~TemplateObserver() {};
};


/* e.g:

 class mouseEvent : public IEvent {
 
 };
 
 class tastaEvent : public IEvent {
 
 };
 
 
 class Object : public TemplateObserver<mouseEvent> , public TemplateObserver<tastaEvent> , 
                public virtual referenceCounting , public virtual Mutex {
 
 public:
    void Event( mouseEvent * ev ) {
        printf("mouse event\n");
    }
 
    void Event( tastaEvent * ev ) {
        printf("tasta Event\n");
    }
 
 };
 
 */



#define ManagerEVENTS() ManagerEvents::GetInstance()

class ManagerEvents :public virtual Mutex , public CThrowEvents {
    
protected:
    
    static ManagerEvents * Instance;
    ManagerEvents() {}
    ManagerEvents( const ManagerEvents& cpy ) {}
    ManagerEvents operator=( ManagerEvents& cpy) {return *this;}
    
public:
    
    static ManagerEvents* GetInstance() {
        
        if ( Instance == NULL )
            Instance = new ManagerEvents();
        return Instance;
        
    }
    
    bool EventTimeOut(IEvent* event);
    
    virtual void Dispatch();
    
    typedef SingletonThreadSafe<ManagerEvents> Ptr;
};

#define GetManagerEventsThreadSafe() (void)ManagerEvents::Ptr( ManagerEVENTS() )
//#define GetManagerEventsThreadSafe() static_cast<ManagerEvents::Ptr>( ManagerEVENTS() )

#endif