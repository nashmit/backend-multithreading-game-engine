#include "streaming.h"


ZipManager* ZipManager::Instance = NULL;


ZipManager* ZipManager::GetInstance() {

	if( Instance == NULL )
		Instance = new ZipManager();

	return Instance;

}

ZipManager::ZipManager() {

}

void ZipManager::AddZip( std::string path ) {

	Zip[ path ] = ZipInstance( path );

}

void ZipManager::Dell( std::string ZipName ) {

	Zip.erase( Zip.find( ZipName ) );

}
