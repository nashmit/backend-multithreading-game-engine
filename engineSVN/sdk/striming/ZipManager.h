#ifndef __ZIPMANAGER_H__
#define __ZIPMANAGER_H__


class ZipManager {

public:
	static ZipManager* GetInstance();

	ZipInstance* operator[]( std::string ZipName ) {

		if( Zip.find( ZipName ) != Zip.end() )
			return &Zip[ ZipName ];
		else
			return NULL;

	}

	void AddZip( std::string );
	void Dell( std::string );

protected:

	ZipManager();

	static ZipManager* Instance;
	//vector<ZipInstance> Zip;
    std::map< std::string , ZipInstance > Zip;

};

#endif
