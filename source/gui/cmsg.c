#include "cmsg.h"

CMSG_DrawMSG(float x, float y, float size, Color, const char *text)
{
    C2D_Text c2d_text;
	C2D_TextFontParse(&c2d_text, font, c2d_dynamic_buf, text);
	C2D_TextOptimize(&c2d_text);
	C2D_DrawText(&c2d_text, C2D_WithColor, x, y, 0.5f, size, size, Color);


}
