
#include <iostream>

#include <vector>

#include <sstream>

#include "engine.h"



/**************************************************/

// EVENT TESTING

class Zambet : public IEvent {
    
};

class Incruntare : public IEvent {
    
};

class Anca :    public TemplateObserver<Zambet> , public TemplateObserver<Incruntare> ,
                public virtual referenceCounting , public virtual Mutex {
public:
    
    virtual void Event( Zambet * ev ) {
        printf("mouse event\n");
    }
    
    virtual void Event( Incruntare * ev ) {
        printf("tasta Event\n");
    }
                
    typedef SmartPtr<Anca> Ptr;
};

class Horea : public Mutex , public referenceCounting , public CThrowEvents {
public:
    typedef SmartPtr<Horea> Ptr;
};



/**************************************************/

int main(int argc, const char * argv[])
{


    
    printf("\n ENGINE OK ! \n");
    
    /***********************************************/
    
    // EVENTS TESTING (random testing)
    Anca::Ptr anca( new Anca() );
    
    Horea::Ptr horea( new Horea() );
    
    dynamic_cast<TemplateObserver<Zambet> *>(*anca)->RegisterTo(*horea);
    dynamic_cast<TemplateObserver<Incruntare>* >(*anca)->RegisterTo(*horea);
    
    horea->addEvent(new Zambet() );
    
    horea->Dispatch();
    
    
    /***********************************************/
    // create threads
    std::vector<ThreadExample*> threadList;
    for (int i=1; i<=5; i++) {
        std::ostringstream ostr;
        ostr<<i;
        std::string indexToString = ostr.str();
        
        std::string strName("Thread");
        
        threadList.push_back(new ThreadExample(strName.append(indexToString), 100));
    }
    
    // run all threads
    for (std::vector<ThreadExample*>::iterator it = threadList.begin(); it != threadList.end(); it++ ) {
        (*it)->Play();
    }
    
    // pause all threads
    for (std::vector<ThreadExample*>::iterator it = threadList.begin(); it != threadList.end(); it++ ) {
        (*it)->Pause();
        usleep(600);
    }
    
    // stop all threads
    for (std::vector<ThreadExample*>::iterator it = threadList.begin(); it != threadList.end(); it++ ) {
        (*it)->Stop();
    }
    
    /*
    ZipInstance zip("sylphis3d-svn-rev11.zip");
    
    printf("%s",zip.GetName().c_str() );
    
    for(zip.GoToFirstFile() ; !zip.EOZip() ; zip.GoToNextFile() ) {
        zip.OpenCurrentFile();
        //zip.GetCurrentFileInfo().print();
        CFile* ff = (CFile*) zip.ReadCurrentFile();
        ff->Save("");
        delete ff;
        zip.CloseCurrentFile();
    }
    */
     
    return 0;
}

