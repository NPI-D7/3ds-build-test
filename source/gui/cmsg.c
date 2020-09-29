#include <citro2d.h>

#include "common.hpp"

#include <assert.h>
#include <stdarg.h>

#include "cmsg.h"

void DrawMSG(float x, float y, float size, u32 Colour, const char *text, C2D_Font fnt)
{
    C2D_Text c2d_text;

	if (fnt != nullptr) {
		C2D_TextFontParse(&c2d_text, fnt, TextBuf, text);
	} else {
		C2D_TextFontParse(&c2d_text, Font, TextBuf, text);
	}

	C2D_TextOptimize(&c2d_text);

		
	

}
