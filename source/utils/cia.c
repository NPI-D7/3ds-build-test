#include "cia.h"

Result deletePrevious(u64 titleid, FS_MediaType media)
{
	Result ret = 0;
	
	u32 titles_amount = 0;
	ret = AM_GetTitleCount(media, &titles_amount);
	if (R_FAILED(ret)) {
		printf("Error in:\nAM_GetTitleCount\n");
		return ret;
	}
	
	u32 read_titles = 0;
	u64 * titleIDs = malloc(titles_amount * sizeof(u64));
	ret = AM_GetTitleList(&read_titles, media, titles_amount, titleIDs);
	if (R_FAILED(ret)) {
		free(titleIDs);
		printf("Error in:\nAM_GetTitleList\n");
		return ret;
	}
	
	for (u32 i = 0; i < read_titles; i++) {
		if (titleIDs[i] == titleid) {
			ret = AM_DeleteAppTitle(media, titleid);
			break;
		}
	}
	
	free(titleIDs);
	if (R_FAILED(ret)) {
		printf("Error in:\nAM_DeleteAppTitle\n");
		return ret;
	}
	
	return 0;
}

Result installCia(const char * ciaPath)
{
	u64 size = 0;
	u32 bytes;
	Handle ciaHandle;
	Handle fileHandle;
	AM_TitleEntry info;
	Result ret = 0;
	
	FS_MediaType media = MEDIATYPE_SD;
	
	ret = openFile(&fileHandle, ciaPath, false);
	if (R_FAILED(ret)) {
		printf("Error in:\nopenFile\n");
		return ret;
	}
	
	ret = AM_GetCiaFileInfo(media, &info, fileHandle);
	if (R_FAILED(ret)) {
		printf("Error in:\nAM_GetCiaFileInfo\n");
		return ret;
	}
	
	ret = deletePrevious(info.titleID, media);
	if (R_FAILED(ret))
		return ret;
	
	ret = FSFILE_GetSize(fileHandle, &size);
	if (R_FAILED(ret)) {
		printf("Error in:\nFSFILE_GetSize\n");
		return ret;
	}
	ret = AM_StartCiaInstall(media, &ciaHandle);
	if (R_FAILED(ret)) {
		printf("Error in:\nAM_StartCiaInstall\n");
		return ret;
	}
	
	u32 toRead = 0x1000;
	u8 * cia_buffer = malloc(toRead);
	for (u64 startSize = size; size != 0; size -= toRead) {
		if (size < toRead) toRead = size;
		FSFILE_Read(fileHandle, &bytes, startSize-size, cia_buffer, toRead);
		FSFILE_Write(ciaHandle, &bytes, startSize-size, cia_buffer, toRead, 0);
	}
	free(cia_buffer);
	
	ret = AM_FinishCiaInstall(ciaHandle);
	if (R_FAILED(ret)) {
		printf("Error in:\nAM_FinishCiaInstall\n");
		return ret;
	}
	ret = FSFILE_Close(fileHandle);
	if (R_FAILED(ret)) {
		printf("Error in:\nFSFILE_Close\n");
		return ret;
	}
	
	return 0;
}
