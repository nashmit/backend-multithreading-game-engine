#ifndef __ZIPINSTANCE_H__
#define __ZIPINSTANCE_H__

#include "unzip.h"
#include "IFile.h"

class ZipInstance {

public:

	static int			EndOfZipConstant();
	bool				EOZip();

						ZipInstance();
	explicit			ZipInstance(std::string);
						~ZipInstance();
						ZipInstance(const ZipInstance& cpy );
    
    //ZipInstance         operator=(ZipInstance& cpy);

	void				Open(std::string);
	void				OpenWithPassword(std::string,std::string);

	void				GoToFirstFile();
	int					GoToNextFile();
	bool				FindAndSetCurrentFile(std::string ,int CaseSensitiv = 1 );

	void				OpenCurrentFile();
	void				OpenCurrentFileWithPassword(std::string);
	void				CloseCurrentFile();
	FileInfoFromZip 	GetCurrentFileInfo();

	// single thread reading file
	IFile*				ReadCurrentFile();
    
    // multithreading reading file
    void                ReadFileWithThreads(std::string NameFile, IFile * outFile );

    std::string         GetName();


	void				Close();//every file from the zip must be close with: "CloseCurrentFile()" before use a close on entire zip file

protected:

    CFile               ZipFile;
	unzFile 			mZipInstance;
	bool				_EOZip;
	static const int	_EndOfZipConstant;
    std::string         path; // name of the zip file
    
    unzFile             OpenNewContext();
};

#endif
