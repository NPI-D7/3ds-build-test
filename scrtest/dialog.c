#include <stdio.h>

#include "common.hpp"

#include "C2D_helper.h"
#include "textures.h"


static void Dialog_DisplayBoxAndMsg(const char *title, const char *msg_1, const char *msg_2, float msg_1_width, float msg_2_width) {


   
    Draw_Text(((320 - (dialog.subtex->width)) / 2) + 6, ((240 - (dialog.subtex->height)) / 2) + 6 - 3, 0.42f, 
       CBLUE, title);

    if (msg_1 && msg_2) {
        Draw_Text(((320 - (msg_1_width)) / 2), ((240 - (dialog.subtex->height)) / 2) + 34 - 3, 0.42f, 
            CBLUE, msg_1);

        Draw_Text(((320 - (msg_2_width)) / 2), ((240 - (dialog.subtex->height)) / 2) + 50 - 4, 0.42f, 
            CBLUE, msg_2);
    }
    else if (msg_1 && !msg_2)
        Draw_Text(((320 - (msg_1_width)) / 2), ((240 - (dialog.subtex->height)) / 2) + 40 - 3, 0.42f, 
            CBLUE, msg_1);
}

void Dialog_DisplayMessage(const char *title, const char *msg_1, const char *msg_2) {
    float text_width1 = 0.0f, text_width2 = 0.0f, confirm_width = 0.0f, confirm_height = 0.0f;
    
    if (msg_1)
        Draw_GetTextSize(0.42f, &text_width1, NULL, msg_1);
        
    if (msg_2)
        Draw_GetTextSize(0.42f, &text_width2, NULL, msg_2);
    
    Dialog_DisplayBoxAndMsg(title, msg_1, msg_2, text_width1, text_width2, with_bg);

    Draw_GetTextSize(0.42f, &confirm_width, &confirm_height, "OK");

    Draw_Rect((288 - confirm_width) - 5, (159 - confirm_height) - 5, confirm_width + 10, confirm_height + 10, 
        CBLUE);
    Draw_Text(288 - confirm_width, (159 - confirm_height) - 3, 0.42f, CWHITE, "OK");

  
}