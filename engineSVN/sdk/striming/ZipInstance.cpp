#include "streaming.h"


const int ZipInstance::_EndOfZipConstant = UNZ_END_OF_LIST_OF_FILE;

int ZipInstance::EndOfZipConstant() {
	return _EndOfZipConstant;
}

bool ZipInstance::EOZip() {
	return _EOZip;
}


ZipInstance::ZipInstance()
: _EOZip( false ) , path("") {
}

 
ZipInstance::ZipInstance( std::string  _path )
: _EOZip( false ) , path( _path ) {

	Open( _path ) ;

}

ZipInstance::~ZipInstance() {
}

#pragma  message("Trebuie sa implementezi cum trebuie metodele astea !")
ZipInstance::ZipInstance(const ZipInstance& cpy ) { // this is not good ! please repair as soon as possible !!!!
	// this is also necesary for making multithreding possible on loading assets !!!

	_EOZip			= cpy._EOZip;
	mZipInstance	= cpy.mZipInstance; // this is not good programming... mZipInstance contain a pointer to a structure and that structure contain one pointer to a state that represent the curent file to be open and read
	path			= cpy.path;
}

/*
ZipInstance ZipInstance::operator=(ZipInstance& cpy) {
    // this is not good ! please repair as soon as possible !!!!
	// this is also necesary for making multithreding possible on loading assets !!!
    
	_EOZip			= cpy._EOZip;
	mZipInstance	= cpy.mZipInstance; // this is not good programming... mZipInstance contain a pointer to a structure and that structure contain one pointer to a state that represent the curent file to be open and read
	path			= cpy.path;
    
    return *this;
    
}
*/

voidpf  fopen_file_func( voidpf opaque , const char* filename , int mode) {
    return opaque;
}

uLong  fread_file_func ( voidpf opaque , voidpf stream , void* buf , uLong size) {
    CFile *str = (CFile*)stream;
    str->FRead(buf, size);
    return size; // ar trebui totusi sa verific daca a reusit sa citeasca atatea char-uri
}

uLong  fwrite_file_func ( voidpf opaque , voidpf stream , const void* buf , uLong size) {
}

long  ftell_file_func ( voidpf opaque , voidpf stream) {
    CFile *str = (CFile*)stream;
    return str->GetPozInFile();
}

long  fseek_file_func ( voidpf opaque , voidpf stream , uLong offset , int origin) {
    CFile *str = (CFile*)stream;
    
    switch (origin)
    {
        case ZLIB_FILEFUNC_SEEK_CUR :
            str->SetPozFile( str->GetPozInFile() + offset );
            break;
        case ZLIB_FILEFUNC_SEEK_END :
            str->SetPozFile( str->GetSize() + offset );
            break;
        case ZLIB_FILEFUNC_SEEK_SET :
            str->SetPozFile( offset );
            break;
        default: return -1;
    }
    return 0;
}

int  fclose_file_func ( voidpf opaque , voidpf stream) {}

int  ferror_file_func ( voidpf opaque , voidpf stream) {}

zlib_filefunc_def *pzlib_filefunc_def;

void ZipInstance::Open(std::string path) {

    /*ZipFile = */
    CFile a(path);
    ZipFile = a;
    //CFile(path);
    
	//mZipInstance = unzOpen( path.c_str() );
    
    pzlib_filefunc_def = (zlib_filefunc_def*)malloc( sizeof(zlib_filefunc_def) );
    
    pzlib_filefunc_def->opaque = &ZipFile;
    pzlib_filefunc_def->zread_file = fread_file_func;
    pzlib_filefunc_def->zwrite_file = NULL;
    pzlib_filefunc_def->ztell_file = ftell_file_func;
    pzlib_filefunc_def->zseek_file = fseek_file_func;
    pzlib_filefunc_def->zclose_file = fclose_file_func;
    pzlib_filefunc_def->zerror_file = ferror_file_func;
    pzlib_filefunc_def->zopen_file = fopen_file_func;
    pzlib_filefunc_def->zerror_file = ferror_file_func;
    
    
    mZipInstance = unzOpen2( path.c_str() , pzlib_filefunc_def );

	assert( mZipInstance != NULL );

}

unzFile ZipInstance::OpenNewContext() {
    return unzOpen2( path.c_str() , pzlib_filefunc_def  );
}

void ZipInstance::OpenWithPassword( std::string path , std::string password ) {

}

void ZipInstance::GoToFirstFile() {

	assert( unzGoToFirstFile( mZipInstance ) == UNZ_OK );
}

int ZipInstance::GoToNextFile() {

	int status = unzGoToNextFile( mZipInstance );

	assert( status	== UNZ_OK || status == UNZ_END_OF_LIST_OF_FILE );

	_EOZip = ( status == UNZ_END_OF_LIST_OF_FILE );

	return status;

}

bool ZipInstance::FindAndSetCurrentFile(std::string file ,int CaseSensitiv) {

	int status = unzLocateFile( mZipInstance , file.c_str() , CaseSensitiv );

	assert( status	== UNZ_OK || status == UNZ_END_OF_LIST_OF_FILE );

	_EOZip = ( status == UNZ_END_OF_LIST_OF_FILE );

	return EOZip();
}


void ZipInstance::OpenCurrentFile() {

	assert( unzOpenCurrentFile( mZipInstance ) == UNZ_OK );

}

void ZipInstance::OpenCurrentFileWithPassword(std::string password) {

	unzOpenCurrentFilePassword( mZipInstance , password.c_str() );

}

void ZipInstance::CloseCurrentFile() {

	unzCloseCurrentFile( mZipInstance );

}

FileInfoFromZip ZipInstance::GetCurrentFileInfo() {

	return	FileInfoFromZip( mZipInstance );

}


#pragma message("paralelizare")
// asta trebuie paralelizata!
IFile* ZipInstance::ReadCurrentFile() {

	FileInfoFromZip FileInfo( mZipInstance );
	IFile *File = new CFile( FileInfo );

	unzReadCurrentFile( mZipInstance , File->GetBuffer() , File->GetSize() );
	return File;
}

void ZipInstance::ReadFileWithThreads(std::string NameFile, IFile * outFile ) {
    
    unzFile Context = OpenNewContext();
    
    int status = unzLocateFile( Context , NameFile.c_str() , 1 );
    
	assert( status	== UNZ_OK || status == UNZ_END_OF_LIST_OF_FILE );
    
    FileInfoFromZip FileInfo( Context );
    
    outFile = new CFile( FileInfo );
    
    unzReadCurrentFile( Context , outFile->GetBuffer() , outFile->GetSize() );
    
    unzClose( Context );
    
}

std::string ZipInstance::GetName() {
	return path;
}

void ZipInstance::Close() { // every file from the zip must be close before use a close on entire zip file.

	// maybe I shoud iterate the entire zip file and close manualy every file that is ovep... just a safe situation !!!
	unzClose( mZipInstance );

}
