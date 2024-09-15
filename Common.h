#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

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

    enum [[maybe_unused]] UImGui_TextUtils_WidgetState
    {
        UIMGUI_TEXT_UTILS_WIDGET_STATE_NONE = 0,
        UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED = 1 << 0,
        UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED = 1 << 1,
        UIMGUI_TEXT_UTILS_WIDGET_STATE_ALL = UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED | UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED,
    };

    typedef uint32_t UImGui_TextUtils_Colour;

    // The default colour for links that have not been visited
    #define UIMGUI_LINK_TEXT_UNVISITED IM_COL32(0, 0, 238, 255)

    // The default colour for links that have been visited
    #define UIMGUI_LINK_TEXT_VISITED IM_COL32(85, 26, 139, 255)

    // The default highlight text colour, yellow with ~25% opacity
    #define UIMGUI_HIGHLIGHT_TEXT_COLOUR IM_COL32(255, 255, 0, 64)

    // The default colour for blockquote rectangle, gray
    #define UIMGUI_BLOCKQUOTE_TEXT_COLOUR IM_COL32(69, 71, 90, 255)

#ifdef __cplusplus
}
#endif