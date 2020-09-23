/*
*   This file is part of Universal-Updater
*   Copyright (C) 2019-2020 Universal-Team
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

#include "common.hpp"
#include "msg.hpp"
#include "colors.hpp"
#include "ptmu_x.h"
#include "utils.hpp"


extern C2D_SpriteSheet sprites;



void Msg::DisplayMsg(std::string text) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	C2D_TargetClear(Bottom, BLACK);
	GFX::DrawTop();
	GFX::DrawBetteryTop();
	Gui::DrawString(0, 2, 0.8f, WHITE, timeStr());
	Gui::DrawStringCentered(0, 0, 0.8f, WHITE, "D7-Menu", 400);
	Gui::DrawString(10, 40, 0.8f, WHITE, text, 380);
	GFX::DrawBottom();
	Gui::DrawSprite(sprites, sprites_ulogo_idx, -10, 20, 0.65, 0.65);
	C3D_FrameEnd(0);
}

