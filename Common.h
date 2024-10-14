#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif
#ifdef _WIN32
    #ifdef MLS_EXPORT_LIBRARY
        #ifdef MLS_LIB_COMPILE
            #define MLS_PUBLIC_API __declspec(dllexport)
        #else
            #define MLS_PUBLIC_API __declspec(dllimport)
        #endif
    #else
        #define MLS_PUBLIC_API
    #endif
#else
    #define MLS_PUBLIC_API
#endif

    typedef struct UImGui_TextUtils_Colour
    {
        union
        {
            float coords[4];
            struct
            {
                float x;
                float y;
                float z;
                float w;
            };
        };
    } UImGui_TextUtils_Colour;

#define UIMGUI_COL32_R_SHIFT    0
#define UIMGUI_COL32_G_SHIFT    8
#define UIMGUI_COL32_B_SHIFT    16
#define UIMGUI_COL32_A_SHIFT    24
#define UIMGUI_COL32(R,G,B,A) (((UImGui_TextUtils_Colour)(A)<<UIMGUI_COL32_A_SHIFT) | ((UImGui_TextUtils_Colour)(B)<<UIMGUI_COL32_B_SHIFT) | ((UImGui_TextUtils_Colour)(G)<<UIMGUI_COL32_G_SHIFT) | ((UImGui_TextUtils_Colour)(R)<<UIMGUI_COL32_R_SHIFT))

    enum [[maybe_unused]] UImGui_TextUtils_WidgetState
    {
        UIMGUI_TEXT_UTILS_WIDGET_STATE_NONE = 0,
        UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED = 1 << 0,
        UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED = 1 << 1,
        UIMGUI_TEXT_UTILS_WIDGET_STATE_ALL = UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED | UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED,
    };


    // The default colour for links that have not been visited
    #define UIMGUI_LINK_TEXT_UNVISITED UImGui_TextUtils_Colour{ 0.0f, 0.0f, 0.94, 1.0f }

    // The default colour for links that have been visited
    #define UIMGUI_LINK_TEXT_VISITED UImGui_TextUtils_Colour{ 0.34f, 0.1f, 0.55f, 1.0f }

    // The default highlight text colour, yellow with ~25% opacity
    #define UIMGUI_HIGHLIGHT_TEXT_COLOUR UImGui_TextUtils_Colour{ 1.0f, 1.0f, 0.0f, 0.25f }

    // The default colour for blockquote rectangle, gray
    #define UIMGUI_BLOCKQUOTE_TEXT_COLOUR UImGui_TextUtils_Colour{ 0.27f, 0.28f, 0.35f, 1.0f }

#ifdef __cplusplus
}
#endif