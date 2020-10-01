#include <string.h>

#include "audio.h"
#include "fs.h"

#include "3dsaudiolib.h"

#include "mp3.h"


bool playing = true;
Audio_Metadata metadata = {0};
static Audio_Metadata empty = {0};

enum Audio_FileType {
	FILE_TYPE_NONE = 0,
	
	FILE_TYPE_MP3 = 2,

};

static enum Audio_FileType file_type = FILE_TYPE_NONE;

static u32 Audio_GetSampleRate(void) {
	u32 sample_rate = 0;

	switch(file_type) {
	

		case FILE_TYPE_MP3:
			sample_rate = MP3_GetSampleRate();
			break;

	

	


		default:
			break;
	}

	return sample_rate;
}

static u8 Audio_GetChannels(void) {
	u8 channels = 0;

	switch(file_type) {
	

		case FILE_TYPE_MP3:
			channels = MP3_GetChannels();
			break;

	



		default:
			break;
	}

	return channels;
}

void Audio_Callback(void *userdata, void *stream, int length) {
	switch(file_type) {
		
		case FILE_TYPE_MP3:
			MP3_Decode(stream, length / (Audio_GetChannels() * sizeof(s16)), userdata);
			break;


		default:
			break;
	}
}

static const char *Audio_GetFileExt(const char *filename) {
	const char *dot = strrchr(filename, '.');
	
	if (!dot || dot == filename)
		return "";
	
	return dot + 1;
}

void Audio_Init(const char *path) {
	playing = true;

	
	else if (!strncasecmp(Audio_GetFileExt(path), "mp3", 3))
		file_type = FILE_TYPE_MP3;
	

	u32 samples = 0;

	switch(file_type) {
	

		case FILE_TYPE_MP3:
			MP3_Init(path);
			samples = 4096;
			break;

	
		default:
			break;
	}

	_3dsAudioInit(Audio_GetChannels(), Audio_GetSampleRate(), samples);
	_3dsAudioCreateThread();
}

bool Audio_IsPaused(void) {
	return ndspChnIsPaused(0);
}

void Audio_Pause(void) {
	ndspChnSetPaused(0, !(ndspChnIsPaused(0)));
}

void Audio_Stop(void) {
	playing = !playing;
}

u64 Audio_GetPosition(void) {
	u64 position = -1;

	switch(file_type) {
	

		case FILE_TYPE_MP3:
			position = MP3_GetPosition();
			break;


		default:
			break;
	}

	return position;
}

u64 Audio_GetLength(void) {
	u64 length = 0;

	switch(file_type) {
		
		case FILE_TYPE_MP3:
			length = MP3_GetLength();
			break;



		default:
			break;
	}

	return length;
}

u64 Audio_GetPositionSeconds(void) {
	return (Audio_GetPosition()/Audio_GetSampleRate());
}

u64 Audio_GetLengthSeconds(void) {
	return (Audio_GetLength()/Audio_GetSampleRate());
}

void Audio_Term(void) {
	switch(file_type) {
		

		case FILE_TYPE_MP3:
			MP3_Term();
			break;

	
		default:
			break;
	}

	playing = true;

	// Clear metadata struct
	metadata = empty;
	_3dsAudioExitThread();
	_3dsAudioEnd();
}
