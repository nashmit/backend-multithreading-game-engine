#include "streaming.h"


CFile::CFile() {
    // no reference counting here !
}

CFile::CFile( FileInfoFromZip Info ) {

	FileName = std::string(Info.FileName);
	Size = Info.pFileInfo.uncompressed_size;
	Buffer->Buffer = new char[Size];
    
}

CFile::CFile(std::string path) {

	FILE* fin = fopen( path.c_str() , "rb" );

	assert( fin != NULL );

	fseek( fin , 0 , SEEK_END );
	Size = ftell( fin ) ;
	Buffer->Buffer = new char [Size];
	fseek( fin , 0 , SEEK_SET);
    
    int test = fread( Buffer->Buffer , sizeof( char ) , Size , fin );

	assert ( Size == test );

	FileName = std::string( path );

	fclose( fin );
    
}

CFile::~CFile() {

	//delete[] (char*)Buffer->Buffer;
	//Buffer->Buffer = NULL;
        
}

CFile CFile::HardCopy() {
    
    CFile cpy;
    cpy.Size = Size;
    cpy.Buffer = CFileBufferForZip::Ref( new CFileBufferForZip(Size) );
    memcpy( cpy.Buffer->Buffer ,  this->Buffer->Buffer , 1);
        
    return cpy;
    
};
