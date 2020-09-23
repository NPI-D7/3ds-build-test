#include "download.h"

#include "cybertrust.h"
#include "digicert.h"

Result setupContext(httpcContext * context, const char * url, u32 * size)
{
	Result ret = 0;
	u32 statuscode = 0;
	
	ret = httpcOpenContext(context, HTTPC_METHOD_GET, url, 1);
	if (ret != 0) {
		printf("Error in:\nhttpcOpenContext\n");
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcAddRequestHeaderField(context, "User-Agent", "MultiUpdater");
	if (ret != 0) {
		printf("Error in:\nhttpcAddRequestHeaderField\n");
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcAddRequestHeaderField(context, "Connection", "Keep-Alive");
	if (ret != 0) {
		printf("Error in:\nhttpcAddRequestHeaderField\n");
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcAddTrustedRootCA(context, cybertrust_cer, cybertrust_cer_len);
	if (ret != 0) {
		printf("Error in:\nhttpcAddRequestHeaderField\n");
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcAddTrustedRootCA(context, digicert_cer, digicert_cer_len);
	if (ret != 0) {
		printf("Error in:\nhttpcAddRequestHeaderField\n");
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcBeginRequest(context);
	if (ret != 0) {
		printf("Error in:\nhttpcBeginRequest\n");
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcGetResponseStatusCode(context, &statuscode);
	if (ret != 0) {
		printf("Error in:\nhttpcGetResponseStatusCode\n");
		httpcCloseContext(context);
		return ret;
	}
	
	if ((statuscode >= 301 && statuscode <= 303) || (statuscode >= 307 && statuscode <= 308)) {
		char * newurl = malloc(0x1000); // One 4K page for new URL
		if (newurl == NULL) {
			httpcCloseContext(context);
			return DL_ERROR_ALLOC;
		}
		
		ret = httpcGetResponseHeader(context, "Location", newurl, 0x1000);
		if (ret != 0) {
			printf("Error in:\nhttpcGetResponseHeader\n");
			httpcCloseContext(context);
			free(newurl);
			return ret;
		}
		
		httpcCloseContext(context); // Close this context before we try the next
		
		ret = setupContext(context, newurl, size);
		free(newurl);
		return ret;
	}
	
	if (statuscode != 200) {
		printf("Error: HTTP status code is not 200 OK.\nStatus code: %lu\n", statuscode);
		httpcCloseContext(context);
		return DL_ERROR_STATUSCODE;
	}
	
	ret = httpcGetDownloadSizeState(context, NULL, size);
	if (ret != 0) {
		printf("Error in:\nhttpcGetDownloadSizeState\n");
		httpcCloseContext(context);
		return ret;
	}
	
	return 0;
}

Result downloadToFile(const char * url, const char * filepath)
{
	if (url == NULL) {
		printf("Download cannot start, the URL is blank.\n");
		return DL_ERROR_CONFIG;
	}
	
	printf("Downloading file from:\n%s\nto:\n%s\n", url, filepath);
	
	httpcContext context;
	Result ret = 0;
	u32 contentsize = 0, readsize = 0;
	
	ret = setupContext(&context, url, &contentsize);
	if (ret != 0) return ret;
	
	printf("Downloading %lu bytes...\n", contentsize);
	
	FILE * fh = fopen(filepath, "wb");
	if (fh == NULL) {
		printf("Error: couldn't open file to write.\n");
		return DL_ERROR_WRITEFILE;
	}
	
	u8 * buf = malloc(0x1000);
	if (buf == NULL) {
		httpcCloseContext(&context);
		return DL_ERROR_ALLOC;
	}
	
	u64 startTime = osGetTime();
	do {
		ret = httpcDownloadData(&context, buf, 0x1000, &readsize);
		fwrite(buf, 1, readsize, fh);
	} while (ret == (Result)HTTPC_RESULTCODE_DOWNLOADPENDING);
	printf("Download took %llu milliseconds.\n", osGetTime()-startTime);
	
	free(buf);
	fclose(fh);
	httpcCloseContext(&context);
	
	if (ret != 0) {
		printf("Error in:\nhttpcDownloadData\n");
		return ret;
	}
	
	return 0;
}

Result downloadLatestRelease(const char * filepath)
{
	httpcContext context;
	Result ret = 0;
	u32 contentsize = 0, readsize = 0;
	
	ret = setupContext(&context, API_URL, &contentsize);
	if (ret != 0) return ret;
	
	char * buf = malloc(contentsize+1);
	if (buf == NULL) {
		httpcCloseContext(&context);
		return DL_ERROR_ALLOC;
	}
	buf[contentsize] = 0; //nullbyte to end it as a proper C style string
	
	do {
		ret = httpcDownloadData(&context, (u8 *)buf, contentsize, &readsize);
	} while (ret == (Result)HTTPC_RESULTCODE_DOWNLOADPENDING);
	
	httpcCloseContext(&context);
	if (ret != 0) {
		printf("Error in:\nhttpcDownloadData\n");
		free(buf);
		return ret;
	}
	
	char * asseturl = NULL;
	
	char * tagstring = "\"browser_download_url\":\"";
	char * endstring = "\"}";

	char *tagstart, *tagend;

	if ((tagstart = strstr(buf, tagstring)) != NULL) {
		if ((tagend = strstr(tagstart, endstring)) != NULL) {
			tagstart += strlen(tagstring);
			int len = tagend-tagstart;
			asseturl = calloc(len+1, sizeof(char));
			strncpy(asseturl, tagstart, len);
		}
	}
	
	ret = downloadToFile(asseturl, filepath);
	free(asseturl);
	free(buf);
	
	return ret;
}
