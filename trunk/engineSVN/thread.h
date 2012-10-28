
#ifndef Engine_thread_h
#define Engine_thread_h

#include <string>
#include <map>

#include "ForwardDeclaration.h"

#include <pthread.h>

// acesta clasa trebuie sa fie mostenita

#define DEBUG_MSG(str1, str2) \
                char str[100]; \
                sprintf(str, "%s %s\n", str1, str2); \
                printf("%s", str); 

class Mutex {
    
private:

    // trebuie sa adaug si variabile conditionale !
    pthread_mutex_t _mutex;
    pthread_mutexattr_t Attr;
    
protected:
    
    Mutex();
    
public:
    
    ~Mutex();
    
    void Lock();
    
    void Unlock();
    
};

typedef enum _threadState {
    
    ThreadStop    = 0,
    ThreadPlay    = 1,
    ThreadPause   = 2,
    
} threadState;

typedef enum _priorityState {
    
    // aici pot sa mai fie adaugate state-uri suplimentare
    
    LOW     = 23 ,
    NORMAL  = 31 ,
    HIGH    = 39 
    
} priorityState;

class Thread : public referenceCounting, public Mutex {
    
    friend class ThreadManager;
    
    void Init();
    
protected:
    
    // starea curenta
    threadState         state;
    
    // prioritatea
    priorityState       priority;
    
    // thread id
    pthread_t           thread;
    
    std::string         Name;
    
    bool                wasCreated;
    
    float               thread_dt;
    
    struct sched_param  param;
    
        
    Thread( std::string name , float dt );
    
    virtual void main();
    
    virtual void Clean();
    
    static void* Select(void* obj) {
        
        reinterpret_cast<Thread*>(obj)->main();
        
        return NULL;
        
    }
    
    //daca functia de pe thread si-a terminat treaba poate sa isi schimbe starea EX. in ThreadStop
    virtual void Loop(float dt) = 0;
    
    virtual ~Thread();
    
public:
    
    void Play ();
    void Pause();
    void Stop ();
    
    std::string getName() {
        return Name;
    }
    
    typedef SmartPtr<Thread> Ptr;
};

/***********************************************/
 
 class ThreadExample : public  Thread {
     
 public:
     ThreadExample( std::string Name , float dt ) : Thread( Name , dt )  {}
 
     virtual void Loop( float dt ) {
         DEBUG_MSG("Running thread", getName().c_str())         
     }
     ~ThreadExample() {
         DEBUG_MSG("Destroyed thread ", getName().c_str()) 
     }
     
};
 
 
 /*********************************************/

#define GetThreads() ThreadManager::GetInstance()

class ThreadManager {
    
    friend class Thread; // the user doesn't need to add resources, they are self added from Thread class
    
protected:
    
    ThreadManager() {};
    ThreadManager(const ThreadManager& cpy) {}
    void operator=(ThreadManager &cpy) {}
    
    std::map<std::string, Thread::Ptr > Threads;
    
    static ThreadManager* Instance;
    
    void Add(Thread::Ptr thread);
    
public:
    
    void Del(std::string NameThread);
    
    
    Thread::Ptr operator[](std::string NameThread);

    static ThreadManager* GetInstance();
    
};




#endif
