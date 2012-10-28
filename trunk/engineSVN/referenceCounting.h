
#ifndef Engine_referenceCounting_h
#define Engine_referenceCounting_h

#include <stdio.h>

// Toate obiectele importante trebuie sa mosteneasca aceasta clasa.
// Este necesara pentru smart pointer.
// Daca lucram cu pointeri de mana trebuie sa avem grija sa incrementam / decrementam numarul de referinte de mana.


class referenceCounting  {
    
protected:
    
    int count;
    referenceCounting() : count(0) {}
    referenceCounting(const referenceCounting& cpy) {}
    void operator=(referenceCounting &cpy) {}
    
    virtual ~referenceCounting() = 0;
    
public:
    
    int GetCount();
    
    void Increase();
    
    virtual void Decrease();
};


template <class T>
class SmartPtr {
    
protected:
    
    T *pointer;
    
    class proxy {
        T* pointer;
        
    public:
        
        proxy(T* _pointer) : pointer(_pointer) {
            // LOCK();
            // nu se apeleaza cresterea numarului de referinte
            pointer->Lock();
            //pointer->Lock();
            
        }
        
        ~proxy(){
            // UNLOCK();
            // nu se decremeanteaza numarul de referinte
            pointer->Unlock();
        }
        
        T* operator->() {
            return pointer;
            
        }
    };

public:
    
    // Default parameter is needed for containers (eg. insert into a map) where we need
    // a constructor without parameters
    SmartPtr( T* cpy = NULL ): pointer(cpy) {
        
        // pentru cazul in care vrem sa creem un obict smart pointer neinitializat
        if( cpy != NULL )
            operator->().operator->()->Increase();
            //pointer->Increase();
        
    }
    
    ~SmartPtr() {
        //printf("Distructor SMARTP\n");
        
        if( pointer != NULL )
            operator->().operator->()->Decrease();
            //pointer->Decrease();
        
    }
    
    SmartPtr(const SmartPtr & cpy) {
  
        this->pointer = cpy.pointer;
        
        if( pointer != NULL )
            operator->().operator->()->Increase();
            //pointer->Increase();
        
    }
        
    //  este necesar sa nu fie referinta pentru a se putea crea obiecte on the fly
    //  altfel trebuie sa creem variabila mai intai
    //  SmartPtr<OBIECT> a;
    //  a = SmartPtr( new OBIECT ) -> asa ceva nu se poate daca avem referinta la parametrul operator=
    SmartPtr operator=(const SmartPtr & cpy) {
        
        // cazul in care ambii smart pointeri pointeaza la acelas obiect
        if( pointer == cpy.pointer )
            return *this;
        
        // pentru cazul in care cele doua obiecte contin referinte la obiecte diferite
        // trebuie sa dereferentiez pointerul din obiectul suprascris
        
        if( pointer != NULL )
            operator->().operator->()->Decrease();
            //pointer->Decrease();
        
        this->pointer = cpy.pointer;
        
        if( pointer != NULL )
            operator->().operator->()->Increase();
            //pointer->Increase();
            
        return *this;
        
    }
    
    T* operator*() {
        //assert( !"Nu recomand astfel de apeluri :D !" );
        return pointer;
    }
    
    proxy operator->() {
        
        assert( pointer != NULL );
        
        return proxy( pointer );
        
    }
};


/*
    Eg: declaring a SingletonThreadSafe variable
 
    typedef SingletonThreadSafe<ManagerSources> aa;
    aa( ManagerSources::GetInstance() ); // it doesn't work; for more details see http://stackoverflow.com/questions/12056140/definition-or-redeclaration-of-getinstance-not-allowed-inside-a-function 
    aa bb( ManagerSOURCES() ); // it works

 */

template <class T>
class SingletonThreadSafe {
    
protected:
    
    T *pointer;
    
    class proxy {
        T* pointer;
        
    public:
        
        proxy(T* _pointer) : pointer(_pointer) {
            // LOCK();
            // nu se apeleaza cresterea numarului de referinte
            
        }
        
        ~proxy(){
            // UNLOCK();
            // nu se decremeanteaza numarul de referinte
        }
        
        T* operator->() {
            return pointer;
            
        }
    };
    
public:
    
    // Default parameter is needed for containers (eg. insert into a map) where we need
    // a constructor without parameters
    SingletonThreadSafe(T* cpy = NULL): pointer(cpy) {
        
    }
    
    ~SingletonThreadSafe() {
    }
    
    SingletonThreadSafe(const SingletonThreadSafe & cpy) {
        
        this->pointer = cpy.pointer;
        
    }
    
    //  este necesar sa nu fie referinta pentru a se putea crea obiecte on the fly
    //  altfel trebuie sa creem variabila mai intai
    //  SmartPtr<OBIECT> a;
    //  a = SmartPtr( new OBIECT ) -> asa ceva nu se poate daca avem referinta la parametrul operator=
    SingletonThreadSafe operator=(const SingletonThreadSafe & cpy) {
            
            this->pointer = cpy.pointer;
            
            return *this;
        
    }
    
    T* operator*() {
        //assert( !"Nu recomand astfel de apeluri :D !" );
        return pointer;
    }
    
    proxy operator->() {
        
        assert( pointer != NULL );
        
        return proxy( pointer );
        
    }
};



template <class T>
class SmartRefCount {
    
protected:
    
    T *pointer;
    
    
public:
    
    // Default parameter is needed for containers (eg. insert into a map) where we need
    // a constructor without parameters
    SmartRefCount( T* cpy = NULL ): pointer(cpy) {
        
        // pentru cazul in care vrem sa creem un obict smart pointer neinitializat
        if( cpy != NULL )
            pointer->Increase();
        //pointer->Increase();
        
    }
    
    SmartRefCount() {
        //printf("Distructor SMARTP\n");
        
        if( pointer != NULL )
            pointer->Decrease();
        //pointer->Decrease();
        
    }
    
    SmartRefCount(const SmartRefCount & cpy) {
        
        this->pointer = cpy.pointer;
        
        if( pointer != NULL )
            pointer->Increase();
        //pointer->Increase();
        
    }
    
    //  este necesar sa nu fie referinta pentru a se putea crea obiecte on the fly
    //  altfel trebuie sa creem variabila mai intai
    //  SmartPtr<OBIECT> a;
    //  a = SmartPtr( new OBIECT ) -> asa ceva nu se poate daca avem referinta la parametrul operator=
    SmartRefCount operator=(const SmartRefCount & cpy) {
        
        // cazul in care ambii smart pointeri pointeaza la acelas obiect
        if( pointer == cpy.pointer )
            return *this;
        
        // pentru cazul in care cele doua obiecte contin referinte la obiecte diferite
        // trebuie sa dereferentiez pointerul din obiectul suprascris
        
        if( pointer != NULL )
            pointer->Decrease();
            //pointer->Decrease();
            
            this->pointer = cpy.pointer;
        
        if( pointer != NULL )
            pointer->Increase();
            //pointer->Increase();
            
            return *this;
        
    }
    
    T* operator*() {
        //assert( !"Nu recomand astfel de apeluri :D !" );
        return pointer;
    }
    
    T* operator->() {
        
        assert( pointer != NULL );
        
        return pointer;
        
    }
};




//Example !
/*
 
 SmartPtr< Clasa > Class(new  Clasa() );
 SmartPtr< Clasa > Cla = Class;
 Cla->a = 3;
 inst 2 ;
*/

#endif
