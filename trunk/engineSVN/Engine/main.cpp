
#include <iostream>

#include <vector>

#include <sstream>

#include "engine.h"

class Test : public referenceCounting{
public:
    int a;
};

typedef SmartPtr<Test> TestPtr ;

void ff( TestPtr a) {
    
}

void ff( Test aa) {
    
}


/**************************************************/

// EVENT TESTING
class Zambet;
class Incruntare;
class Ana : public TemplateObserver<Zambet> , public TemplateObserver<Incruntare> ,
            public virtual referenceCounting , public virtual Mutex {
public:
    typedef SmartPtr<Ana> Ptr;
    virtual void Event( Zambet * ev ) {
        printf("mouse event\n");
    }
    
    virtual void Event( Incruntare * ev ) {
        printf("tasta Event\n");
    }
};

class Horea : public Mutex , public referenceCounting , public CThrowEvents {
public:
    typedef SmartPtr<Horea> Ptr;
};

class Zambet : public IEvent {
    
};

class Incruntare : public IEvent {
    
};

/**************************************************/

int main(int argc, const char * argv[])
{

    //int t = 8;
    //int &tt = 5;
    //const int & ttt = 6;
    
    /*
    TestPtr cla( new Test() );
    
    TestPtr cla2 (cla ) ;

    TestPtr cla4 = new Test();
    
    TestPtr& cla3 = cla2;
    
    cla->a = 4;

    ff( cla );
    
    ff( new Test() );
    
    ff( TestPtr( new Test()) );
     */

    //ManagerBUFFERS()->Add("Anca");
    //SourceBufferSPtr a = ManagerBUFFERS()->Search("Anca");
    //std::cout<<a->Name;
    //ManagerBUFFERS()->Delete("Anca");
    
    //ManagerSOURCES()
    
    //typedef SingletonThreadSafe<ManagerSources> aa;
    
    //( SmartPtr<ManagerSources>() = ManagerSOURCES() )->Delete("Alba");
    //aa bb( ManagerSOURCES() );
    
    //ManagerSources * ppp = ManagerSOURCES();
    
    //static_cast<aa>( aa( ppp ) );
   // aa bb( ManagerSOURCES() );
    //aa()->Search("ANA");
    
    //GetManagerBuffersThreadSafe()->Search("Anca");
    
    //SmartPtr<ManagerSources>() = ManagerSOURCES();
    
    
    
    
    // test zip
   /* ZipInstance zip("Test1.zip");
    printf("%s", zip.GetName().c_str());
    for (; !zip.EOZip(); zip.GoToNextFile())
    {
        zip.OpenCurrentFile();
        CFile *bla = (CFile*)zip.ReadCurrentFile();
        zip.GetCurrentFileInfo().print();
        bla->Save("");
        zip.CloseCurrentFile();
    }
    */
    
    printf("\n ENGINE OK ! \n");
    
    /***********************************************/
    
    // EVENTS TESTING (random testing)
    Ana::Ptr ana( new Ana() );
    
    Horea::Ptr horea( new Horea() );
    
    dynamic_cast<TemplateObserver<Zambet> *>(*ana)->RegisterTo(*horea);
    dynamic_cast<TemplateObserver<Incruntare>* >(*ana)->RegisterTo(*horea);
    
    horea->addEvent(new Zambet() );
    
    horea->Dispatch();
    
    // TO COMPLETE
    
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

    return 0;
}

