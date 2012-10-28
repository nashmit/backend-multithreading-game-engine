#ifndef __CFILE_H__
#define __CFILE_H__

#include "FileInfoFromZip.h"

class CFile :public IFile {

protected:
    CFile();
    CFile( FileInfoFromZip );
    
public:
    
    friend class ZipInstance;

	CFile( std::string );
    
    /*
    CFile( const CFile & cpy) {
        //  soft copy for Buffer !
    }
    */
    
    /*
    CFile operator=(const CFile & cpy) {
      //  soft copy for Buffer !
    }
    */
    
    CFile HardCopy(); 
    
	virtual ~CFile() ;
};

#endif
