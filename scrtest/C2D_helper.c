#include <assert.h>
#include <stdarg.h>

#include "common.hpp"
#include "C2D_helper.h"
#include "fs.h"

void Draw_Text(float x, float y, float size, Colour colour, const char *text) {
	C2D_Text c2d_text;
	C2D_TextFontParse(&c2d_text, font, c2d_dynamic_buf, text);
	C2D_TextOptimize(&c2d_text);
	C2D_DrawText(&c2d_text, C2D_WithColor, x, y, 0.5f, size, size, colour);
}

void Draw_GetTextSize(float size, float *width, float *height, const char *text) {
	C2D_Text c2d_text;
	C2D_TextFontParse(&c2d_text, font, c2d_size_buf, text);
	C2D_TextGetDimensions(&c2d_text, size, size, width, height);
}

bool Draw_Rect(float x, float y, float w, float h, Colour colour) {
	return C2D_DrawRectSolid(x, y, 0.5f, w, h, colour);
}

