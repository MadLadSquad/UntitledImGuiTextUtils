#pragma once
#include "../Common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    typedef void(*UImGui_TextUtils_LinkCallback)(const char*);

    MLS_PUBLIC_API void UImGui_TextUtils_Bold(const char* fmt, ...);
    MLS_PUBLIC_API void UImGui_TextUtils_BoldWrapped(const char* fmt, ...);
    MLS_PUBLIC_API void UImGui_TextUtils_BoldV(const char* fmt, va_list args);
    MLS_PUBLIC_API void UImGui_TextUtils_BoldWrappedV(const char* fmt, va_list args);

    MLS_PUBLIC_API void UImGui_TextUtils_Italic(const char* fmt, ...);
    MLS_PUBLIC_API void UImGui_TextUtils_ItalicWrapped(const char* fmt, ...);
    MLS_PUBLIC_API void UImGui_TextUtils_ItalicV(const char* fmt, va_list args);
    MLS_PUBLIC_API void UImGui_TextUtils_ItalicWrappedV(const char* fmt, va_list args);

    MLS_PUBLIC_API void UImGui_TextUtils_BoldItalic(const char* fmt, ...);
    MLS_PUBLIC_API void UImGui_TextUtils_BoldItalicWrapped(const char* fmt, ...);
    MLS_PUBLIC_API void UImGui_TextUtils_BoldItalicV(const char* fmt, va_list args);
    MLS_PUBLIC_API void UImGui_TextUtils_BoldItalicWrappedV(const char* fmt, va_list args);

    MLS_PUBLIC_API void UImGui_TextUtils_Monospace(const char* fmt, ...);
    MLS_PUBLIC_API void UImGui_TextUtils_MonospaceWrapped(const char* fmt, ...);
    MLS_PUBLIC_API void UImGui_TextUtils_MonospaceV(const char* fmt, va_list args);
    MLS_PUBLIC_API void UImGui_TextUtils_MonospaceWrappedV(const char* fmt, va_list args);

    MLS_PUBLIC_API void UImGui_TextUtils_Small(const char* fmt, ...);
    MLS_PUBLIC_API void UImGui_TextUtils_SmallWrapped(const char* fmt, ...);
    MLS_PUBLIC_API void UImGui_TextUtils_SmallV(const char* fmt, va_list args);
    MLS_PUBLIC_API void UImGui_TextUtils_SmallWrappedV(const char* fmt, va_list args);

    MLS_PUBLIC_API void UImGui_TextUtils_SubSuperscript(const char* subscriptBegin, const char* subscriptEnd,
                                                    const char* superscriptBegin, const char* superscriptEnd);

    MLS_PUBLIC_API void UImGui_TextUtils_Ruby(const char* textBegin, const char* textEnd,
                                          const char* annotationBegin, const char* annotationEnd,
                                          bool bWrapAnnotation, bool bWrapText);

    MLS_PUBLIC_API void UImGui_TextUtils_Underline(UImGui_TextUtils_Colour colour);
    MLS_PUBLIC_API UImGui_TextUtils_WidgetState UImGui_TextUtils_Underline_fmt(UImGui_TextUtils_Colour colour, const char* fmt, ...);
    MLS_PUBLIC_API UImGui_TextUtils_WidgetState UImGui_TextUtils_Underline_fmtV(UImGui_TextUtils_Colour colour, const char* fmt, va_list args);
    MLS_PUBLIC_API UImGui_TextUtils_WidgetState UImGui_TextUtils_UnderlineWrapped(const char* text, const char* end, UImGui_TextUtils_Colour colour);

    MLS_PUBLIC_API void UImGui_TextUtils_Strikethrough(UImGui_TextUtils_Colour colour);
    MLS_PUBLIC_API UImGui_TextUtils_WidgetState UImGui_TextUtils_Strikethrough_fmt(UImGui_TextUtils_Colour colour, const char* fmt, ...);
    MLS_PUBLIC_API UImGui_TextUtils_WidgetState UImGui_TextUtils_Strikethrough_fmtV(UImGui_TextUtils_Colour colour, const char* fmt, va_list args);
    MLS_PUBLIC_API UImGui_TextUtils_WidgetState UimGui_TextUtils_StrikethroughWrapped(const char* text, const char* end, UImGui_TextUtils_Colour colour);

    MLS_PUBLIC_API void UImGui_TextUtils_Link(const char* text, UImGui_TextUtils_Colour colour, UImGui_TextUtils_LinkCallback callback);
    MLS_PUBLIC_API void UImGui_TextUtils_LinkWrapped(const char* text, const char* end, UImGui_TextUtils_Colour colour, UImGui_TextUtils_LinkCallback callback);

    MLS_PUBLIC_API void UImGui_TextUtils_Highlight(UImGui_TextUtils_Colour colour);
    MLS_PUBLIC_API UImGui_TextUtils_WidgetState UImGui_TextUtils_Highlight_fmt(UImGui_TextUtils_Colour colour, const char* fmt, ...);
    MLS_PUBLIC_API UImGui_TextUtils_WidgetState UImGui_TextUtils_Highlight_fmtV(UImGui_TextUtils_Colour colour, const char* fmt, va_list args);
    MLS_PUBLIC_API UImGui_TextUtils_WidgetState UImGui_TextUtils_HighlightWrapped(const char* begin, const char* end, UImGui_TextUtils_Colour colour);

    MLS_PUBLIC_API void UImGui_TextUtils_Blockquote(UImGui_TextUtils_Colour colour);
    MLS_PUBLIC_API void UImGui_TextUtils_Blockquote_fmt(UImGui_TextUtils_Colour colour, const char* fmt, ...);
    MLS_PUBLIC_API void UImGui_TextUtils_Blockquote_fmtV(UImGui_TextUtils_Colour colour, const char* fmt, va_list args);
    MLS_PUBLIC_API void UImGui_TextUtils_BlockquoteWrapped(const char* text, const char* end, UImGui_TextUtils_Colour colour);

    MLS_PUBLIC_API void UImGui_TextUtils_CodeBlock(const char* begin, const char* end, bool bWrapText, UImGui_TextUtils_Colour colour);
    MLS_PUBLIC_API void UImGui_TextUtils_CodeInline(const char* begin, const char* end, UImGui_TextUtils_Colour colour);
    MLS_PUBLIC_API void UImGui_TextUtils_CodeInlineWrapped(const char* begin, const char* end, UImGui_TextUtils_Colour colour);

    MLS_PUBLIC_API void UImGui_TextUtils_ShowDemoWindow(void* bOpen);
#ifdef __cplusplus
}
#endif