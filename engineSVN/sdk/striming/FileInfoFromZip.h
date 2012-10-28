#ifndef __ZIPFILEINFO_H__
#define __ZIPFILEINFO_H__

#include "unzip.h"

class FileInfoFromZip {
public:
	FileInfoFromZip(unzFile);
	~FileInfoFromZip();

	void print();

	friend class CFile;

protected:

	unzFile mZipInstance;

	char FileName[MAX_PATH];

	unz_file_info pFileInfo;
	int fileNameBufferSize;
	void *extraField;
	uLong extraFieldBufferSize;
	char szComment[MAX_PATH];
	uLong commentBufferSize;

};

#endif
