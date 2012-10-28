#include "streaming.h"

IFile::~IFile() {};

#pragma  message("Trebuie sa implementezi cum trebuie metodele astea !")

char	IFile::NextChar() {

	assert(PozInFile + sizeof( char ) <= GetSize() );

	return ( (char*) Buffer->Buffer )[ PozInFile++ ];
}

int		IFile::NextInt() {

	int value;

	assert( PozInFile + sizeof(int) <= GetSize() );

	memcpy( &value , (char*)Buffer->Buffer + PozInFile , sizeof(int) );
	PozInFile +=sizeof(int);

	return value;
}

float	IFile::NextFloat() {
	float value;

	assert( PozInFile + sizeof(float) <= GetSize() );

	memcpy( &value , (char*)Buffer->Buffer + PozInFile , sizeof(float) );
	PozInFile +=sizeof(float);

	return value;
}

void        IFile::ResetPozFile() { PozInFile = 0;	}
bool        IFile::Eof() { return ( (PozInFile == Size) ) ; }
void*       IFile::GetBuffer() { return Buffer->Buffer; }
int         IFile::GetPozInFile() { return PozInFile; }
void        IFile::SetPozFile(int poz) { PozInFile = poz; }
int         IFile::GetSize() { return Size; }
std::string	IFile::GetFileName() { return FileName; }

void	IFile::FRead(void* Buff , int Size) {

	assert( PozInFile + Size <= GetSize() ); //I'm not sure about assertion !!!

	memcpy( Buff , (char*)Buffer->Buffer + PozInFile , Size );
	PozInFile += Size;
}

void	IFile::Save(std::string path) {


    if( FileName[ FileName.length()-1 ] != '/' ) {
        
        FILE *Fout = fopen( ( path + FileName ).c_str() , "wb" );
        fwrite( Buffer->Buffer , sizeof( char ) , Size , Fout );
        fclose( Fout );
        
    }
	else {

        std::string command( std::string("mkdir") + std::string(" ") + path + FileName );
		command[ command.length() - 1 ] = ' ';
		printf("%s\n",command.c_str());

		system( command.c_str() );

		return;
	}


};

void IFile::SaveWithPathAndName(std::string path , std::string FileName ) {

#pragma message("asta nu e ok, uitete la functia de deasupra")
	FILE* Fout = fopen( (path + FileName).c_str() , "wb" );

	fwrite( Buffer->Buffer , sizeof( char ) , Size , Fout );

	fclose( Fout );

}
