#ifndef _CMSG_H
#define _CMSG_H


#include <3ds.h>
#include <citro2d.h>


typedef u32 Colour;
extern C2D_Font font;
extern C2D_TextBuf c2d_static_buf, c2d_dynamic_buf, c2d_size_buf;



void DrawMSG(float x, float y, float size, Colour color, const char *text);







#endif