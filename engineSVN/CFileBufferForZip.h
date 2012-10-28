
#ifndef Engine_CFileBufferForZip_h
#define Engine_CFileBufferForZip_h

class CFileBufferForZip : public referenceCounting {
public:
    
    CFileBufferForZip() {
        Buffer = NULL;
    };
    
    CFileBufferForZip(void* cpy) {
        Buffer = cpy;
    };
    
    CFileBufferForZip(int size) {
        
    };
    
    ~CFileBufferForZip() {
        delete [] (char*)Buffer;
        
    };
    
    void* Buffer;
    
    typedef SmartRefCount<CFileBufferForZip> Ref;
    
};



#endif
