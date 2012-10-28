#include "streaming.h"

FileInfoFromZip::FileInfoFromZip(unzFile _mZipInstance)
	:	extraField(0) , mZipInstance(_mZipInstance) , fileNameBufferSize(MAX_PATH) , extraFieldBufferSize(0) ,
        commentBufferSize(0)
{
	memset(FileName, 0, sizeof( FileName ) );

	int ok = unzGetCurrentFileInfo( mZipInstance,
                                   &pFileInfo,
                                   FileName,
                                   fileNameBufferSize,
                                   NULL,//extraField,
                                   extraFieldBufferSize,
                                   NULL,//szComment,
                                   commentBufferSize);
    assert(ok == UNZ_OK );
}

FileInfoFromZip::~FileInfoFromZip() {
}

void FileInfoFromZip::print() {

	printf("\n********************\n\n");
	printf("FileInfoFromZip File Name :		%s\n",FileName);

	printf("version made :					%lud\n",pFileInfo.version);
	printf("version needed :				%lud\n",pFileInfo.version_needed);
	printf("compresion method:				%lud\n",pFileInfo.compression_method);
	printf("compressed size:				%lud\n",pFileInfo.compressed_size);
	printf("uncompressed size:				%lud\n",pFileInfo.uncompressed_size);

	printf("\nMore to come !\n");
	printf("********************\n");

}
