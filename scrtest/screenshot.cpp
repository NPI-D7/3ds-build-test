#include "screenshot.hpp"

#include <3ds.h>


static void Screenshot_GenerateFilename(int count, char *file_name) {
	time_t t = time(0);
	int day = localtime(&t)->tm_mday;
	int month = localtime(&t)->tm_mon + 1;
	int year = localtime(&t)->tm_year + 1900;
	
	if (!(FS_DirExists(sdmc_archive, "/3ds/NPI/screenshots/Test/")))
	FS_RecursiveMakeDir(archive, "/3ds/NPI/music/Test/");
		
	sprintf(file_name, "/3ds/NPI/screenshots/Test/Screenshot_%02d%02d%02d-%i.bmp", year, month, day, count);
}

