
#include <citro2d.h>



//defines


#define CWHITE                 C2D_Color32(255, 255, 255, 255)
#define CBLACK_BG              C2D_Color32(48, 48, 48, 255)
#define CBLUE      C2D_Color32(37, 79, 174, 255)
#define CSTATUS_BAR_DARK       C2D_Color32(38, 50, 56, 255)
#define CMENU_BAR_LIGHT        C2D_Color32(51, 103, 214, 255)
#define CMENU_BAR_DARK         C2D_Color32(55, 71, 79, 255)
#define CBLACK                 C2D_Color32(0, 0, 0, 255)
#define CSELECTOR_COLOUR_LIGHT C2D_Color32(241, 241, 241, 255)
#define CSELECTOR_COLOUR_DARK  C2D_Color32(76, 76, 76, 255)
#define CTITLE_COLOUR          C2D_Color32(30, 136, 229, 255)
#define CTITLE_COLOUR_DARK     C2D_Color32(0, 150, 136, 255)
#define CTEXT_MIN_COLOUR_LIGHT C2D_Color32(32, 32, 32, 255)
#define CTEXT_MIN_COLOUR_DARK  C2D_Color32(185, 185, 185, 255)
#define CBAR_COLOUR            C2D_Color32(200, 200, 200, 255)

extern C3D_RenderTarget *RENDER_TOP, *RENDER_BOTTOM;
extern C2D_TextBuf c2d_static_buf, c2d_dynamic_buf, c2d_size_buf;
extern C2D_Font font;
typedef u32 Colour;

bool Draw_Rect(float x, float y, float w, float h, Colour colour);


void Draw_GetTextSize(float size, float *width, float *height, const char *text);
void Draw_Text(float x, float y, float size, Colour colour, const char *text);