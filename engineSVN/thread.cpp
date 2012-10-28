
#include "engine.h"

void Thread::Init() {
    
    if (!wasCreated) {
        int status = pthread_create( &thread , NULL , Select , this );
        
        wasCreated = true;
        
        if( status != 0 ) {
            assert(status);
            printf("probleme \n");
        }
    }
    
    //pthread_setschedparam( thread,SCHED_RR,&param );
    
    //param.sched_priority = param.sched_priority = NORMAL;
    
    //ThreadManager::GetInstance()->Add( Thread::Ptr(this) );
    
}

Mutex::Mutex(){
    // aici ar trebui mecanisme de assert!
    pthread_mutexattr_init(&Attr);
    pthread_mutexattr_settype(&Attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init( &_mutex , &Attr );
};

Mutex::~Mutex() {
    //aici ar trebui mecanisme de assert!
    pthread_mutex_destroy( &_mutex );
};

void Mutex::Lock() {
    // trebuie luat in considerare ca exista si apeluri recursive de Lock() !!
    pthread_mutex_lock( &_mutex );
}

void Mutex::Unlock() {
    // trebuie luat in considerare ca exista si apeluri recursive de Unlock() !!
    pthread_mutex_unlock( &_mutex );
}




Thread::Thread( std::string name , float dt ): state(ThreadPause) , priority(NORMAL) , Name(name) , wasCreated(false), thread_dt(dt)
{
    //Init();
    ThreadManager::GetInstance()->Add( Thread::Ptr(this) );
}

void Thread::main() {
    
    while ( state != ThreadStop ) {
        if ( state != ThreadPause )
            Loop( thread_dt );
        //sleep(2);
        usleep(100);
    }
    
    Clean();
}

void Thread::Clean() {
    //pthread_exit(NULL); //-> nu se mai dezaloca obiectele de pe stiva
    // nu se apeleaza distructorii acestora daca este folosita acesta
};

Thread::~Thread() {
    if( state != ThreadStop ) {
        assert(!"Obiectul trebuie sa fie in starea de Stop ca sa poata fi apelat distrugerea acestuia!\n");
    }
    
    //pthread_join(thread, NULL);
    printf("distrus in clasa principala \n");
}

void Thread::Play () {
    state = ThreadPlay;
    
    // create thread
    Init();
    
    //printf("ThreadPlay\n");
}

void Thread::Pause() {
    state = ThreadPause;
    
    DEBUG_MSG("Paused thread", getName().c_str())
}

void Thread::Stop () {
    state = ThreadStop;
    
    DEBUG_MSG("Stopped thread", getName().c_str())
    
    usleep( 1000 ); /*->necesar pentru a se termina un ciclu de thread Loop*/
}

ThreadManager* ThreadManager::Instance = NULL;

ThreadManager* ThreadManager::GetInstance() {
    if( Instance == NULL )
        Instance = new ThreadManager();
    return Instance;
};

void ThreadManager::Add(Thread::Ptr thread){
    
    Threads[ thread->Name ] = thread;
    
}

void ThreadManager::Del(std::string NameThread) {
    
    if( Threads.find(NameThread) == Threads.end() ) {
        assert(!"Nu exista acest thread");
    }
    else {
        // thead must be stoped before delete it from this manager
        Threads.erase( Threads.find(NameThread));
    }
}

Thread::Ptr ThreadManager::operator[](std::string NameThread) {
    
    assert( Threads.find( NameThread ) == Threads.end() );
    
    return Threads[ NameThread ];
}

