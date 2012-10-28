#ifndef __IFILE_H__
#define __IFILE_H__

class IFile {

public:

	IFile(): FileName("") , Buffer(new CFileBufferForZip() ) , Size( 0 ) , PozInFile( 0 ) {}

	virtual 		~IFile() = 0 ;

	int				NextInt();
	float			NextFloat();
	char			NextChar();
	void			FRead( void* ,int );
	void			ResetPozFile();
	bool			Eof();

	void*			GetBuffer();
	int				GetSize();
    int             GetPozInFile();
    void            SetPozFile(int poz);
    std::string     GetFileName();

	virtual void	Save( std::string ); // File allready have a name. the parameter will send the path to the position where should be save
	virtual void	SaveWithPathAndName( std::string , std::string );

protected:

    std::string             FileName;
	//void*                 Buffer;
    CFileBufferForZip::Ref  Buffer;
    
	int                     Size;
	int                     PozInFile; // you have to be carefull about the type of Buffer

};


#endif
