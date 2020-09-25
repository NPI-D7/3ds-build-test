
#include "common.hpp"
#include <3ds.h>

Result makeDirs(const char * path);
Result openFile(Handle* fileHandle, const char * path, bool write);
Result deleteFile(const char * path);
Result removeDir(const char * path);
Result removeDirRecursive(const char * path);
