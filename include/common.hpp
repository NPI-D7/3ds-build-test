/*h
*   This file is part of Universal-Core-Example
*   Copyright (C) 2020 SuperSaiyajinStackie
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/





#pragma once

#include <3ds.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "file.h"
#include "screenshot.h"
#include "fs.h"
#include "utils.h"
#include "playback.h"
#include "cmsg.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef __cplusplus
}
#include <cstdio>
#include <iostream>

#include <vector>
#include <regex>
#include <curl/curl.h>

//Lol


#include "json.hpp"
#include "stringutils.hpp"

using json = nlohmann::json;



extern char * arg0;

#define APP_TITLE "Test"
#define VERSION_STRING "0.0.1"

// This is the new "screenCommon.hpp", lol.
#include "gfx.hpp"
#include "gui.hpp"
#include "screenCommon.hpp"



#define WHITE         C2D_Color32(255, 255, 255, 255)
#define WORKING_DIR	"/"
#define SCRIPTS_PATH	"sdmc:/3ds/Universal-Updater/scripts/" // The Scripts will be here.
#define MUSIC_PATH	"sdmc:/3ds/Universal-Updater/Music.wav" // Default Music File / Path.
#define SCRIPT_VERSION	4
#define STORE_PATH "sdmc:/3ds/Universal-Updater/stores/" // Default Store path.
#define ENTRIES_PER_SCREEN 3
#define ENTRIES_PER_LIST 7
#define metaFile "sdmc:/3ds/Universal-Updater/ScriptInfo.json"
#define _3DSX_PATH "sdmc:/3ds"
#define _NDS_PATH "sdmc:"
#define ARCHIVES_DEFAULT "sdmc:"


#endif
