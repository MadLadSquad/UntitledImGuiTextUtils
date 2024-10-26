#include "CUImGuiTextUtils.h"
#include "../UImGuiTextUtils.hpp"

#define WRAP_VARIADIC_LIST(x) va_list args; \
    va_start(args, fmt); \
    x; \
    va_end(args)

#define dt_cast(x) static_cast<UImGui::TextUtilsData*>(x)

UImGui_CTextUtilsData* UImGui_TextUtilsData_allocate()
{
    return new UImGui::TextUtilsData{};
}

void UImGui_TextUtilsData_setFonts(UImGui_CTextUtilsData* data, void* bold, void* italic, void* boldItalic, void* monospace, void* smallFont)
{
    dt_cast(data)->bold         = static_cast<ImFont*>(bold);
    dt_cast(data)->italic       = static_cast<ImFont*>(italic);
    dt_cast(data)->boldItalic   = static_cast<ImFont*>(boldItalic);
    dt_cast(data)->monospace    = static_cast<ImFont*>(monospace);
    dt_cast(data)->smallFont    = static_cast<ImFont*>(smallFont);
}

void UImGui_TextUtils_initTextUtilsData(UImGui_CTextUtilsData* data)
{
    UImGui::TextUtils::initTextUtilsData(dt_cast(data));
}

void UImGui_TextUtilsData_free(UImGui_CTextUtilsData* data)
{
    delete dt_cast(data);
}

UImGui_TextUtils_Colour UImGui_TextUtils_getDefaultTextColour()
{
    return UImGui::TextUtils::getDefaultTextColour();
}

void UImGui_TextUtils_Bold(const char* fmt, ...)
{
    WRAP_VARIADIC_LIST(UImGui::TextUtils::BoldV(fmt, args));
}

void UImGui_TextUtils_BoldWrapped(const char* fmt, ...)
{
    WRAP_VARIADIC_LIST(UImGui::TextUtils::BoldWrappedV(fmt, args));
}

void UImGui_TextUtils_BoldV(const char* fmt, va_list args)
{
    UImGui::TextUtils::BoldV(fmt, args);
}

void UImGui_TextUtils_BoldWrappedV(const char* fmt, va_list args)
{
    UImGui::TextUtils::BoldWrappedV(fmt, args);
}

void UImGui_TextUtils_Italic(const char* fmt, ...)
{
    WRAP_VARIADIC_LIST(UImGui::TextUtils::ItalicV(fmt, args));
}

void UImGui_TextUtils_ItalicWrapped(const char* fmt, ...)
{
    WRAP_VARIADIC_LIST(UImGui::TextUtils::ItalicWrappedV(fmt, args));
}

void UImGui_TextUtils_ItalicV(const char* fmt, va_list args)
{
    UImGui::TextUtils::ItalicV(fmt, args);
}

void UImGui_TextUtils_ItalicWrappedV(const char* fmt, va_list args)
{
    UImGui::TextUtils::ItalicWrappedV(fmt, args);
}

void UImGui_TextUtils_BoldItalic(const char* fmt, ...)
{
    WRAP_VARIADIC_LIST(UImGui::TextUtils::BoldItalicV(fmt, args));
}

void UImGui_TextUtils_BoldItalicWrapped(const char* fmt, ...)
{
    WRAP_VARIADIC_LIST(UImGui::TextUtils::BoldItalicWrappedV(fmt, args));
}

void UImGui_TextUtils_BoldItalicV(const char* fmt, va_list args)
{
    UImGui::TextUtils::BoldItalicV(fmt, args);
}

void UImGui_TextUtils_BoldItalicWrappedV(const char* fmt, va_list args)
{
    UImGui::TextUtils::BoldItalicWrappedV(fmt, args);
}

void UImGui_TextUtils_Monospace(const char* fmt, ...)
{
    WRAP_VARIADIC_LIST(UImGui::TextUtils::MonospaceV(fmt, args));
}

void UImGui_TextUtils_MonospaceWrapped(const char* fmt, ...)
{
    WRAP_VARIADIC_LIST(UImGui::TextUtils::MonospaceWrappedV(fmt, args));
}

void UImGui_TextUtils_MonospaceV(const char* fmt, va_list args)
{
    UImGui::TextUtils::MonospaceV(fmt, args);
}

void UImGui_TextUtils_MonospaceWrappedV(const char* fmt, va_list args)
{
    UImGui::TextUtils::MonospaceWrappedV(fmt, args);
}

void UImGui_TextUtils_Small(const char* fmt, ...)
{
    WRAP_VARIADIC_LIST(UImGui::TextUtils::SmallV(fmt, args));
}

void UImGui_TextUtils_SmallWrapped(const char* fmt, ...)
{
    WRAP_VARIADIC_LIST(UImGui::TextUtils::SmallWrappedV(fmt, args));
}

void UImGui_TextUtils_Small(const char* fmt, va_list args)
{
    UImGui::TextUtils::SmallV(fmt, args);
}

void UImGui_TextUtils_SmallWrapped(const char* fmt, va_list args)
{
    UImGui::TextUtils::SmallWrappedV(fmt, args);
}

void UImGui_TextUtils_SubSuperscript(const char* subscriptBegin, const char* subscriptEnd,
                                     const char* superscriptBegin, const char* superscriptEnd)
{
    UImGui::TextUtils::SubSuperscript(subscriptBegin, subscriptEnd, superscriptBegin, superscriptEnd);
}

void UImGui_TextUtils_Ruby(const char* textBegin, const char* textEnd,
                           const char* annotationBegin, const char* annotationEnd,
                           const bool bWrapAnnotation, const bool bWrapText)
{
    UImGui::TextUtils::Ruby(textBegin, textEnd, annotationBegin, annotationEnd, bWrapAnnotation, bWrapText);
}

void UImGui_TextUtils_Underline(const UImGui_TextUtils_Colour colour)
{
    UImGui::TextUtils::Underline(colour);
}

UImGui_TextUtils_WidgetState UImGui_TextUtils_Underline_fmt(const UImGui_TextUtils_Colour colour, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ImGui::TextV(fmt, args);
    va_end(args);

    const auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
    const auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
    UImGui::TextUtils::Underline(colour);

    return static_cast<UImGui_TextUtils_WidgetState>(bHovered | bClicked);
}

UImGui_TextUtils_WidgetState UImGui_TextUtils_Underline_fmtV(const UImGui_TextUtils_Colour colour, const char* fmt, va_list args)
{
    ImGui::TextV(fmt, args);

    const auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
    const auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
    UImGui::TextUtils::Underline(colour);

    return static_cast<UImGui_TextUtils_WidgetState>(bHovered | bClicked);
}

UImGui_TextUtils_WidgetState UImGui_TextUtils_UnderlineWrapped(const char* text, const char* end, const UImGui_TextUtils_Colour colour)
{
    return UImGui::TextUtils::UnderlineWrapped(text, end, colour);
}

void UImGui_TextUtils_Strikethrough(const UImGui_TextUtils_Colour colour)
{
    UImGui::TextUtils::Strikethrough(colour);
}

UImGui_TextUtils_WidgetState UImGui_TextUtils_Strikethrough_fmt(const UImGui_TextUtils_Colour colour, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ImGui::TextV(fmt, args);
    va_end(args);

    const auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
    const auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
    UImGui::TextUtils::Strikethrough(colour);

    return static_cast<UImGui_TextUtils_WidgetState>(bHovered | bClicked);
}

UImGui_TextUtils_WidgetState UImGui_TextUtils_Strikethrough_fmtV(const UImGui_TextUtils_Colour colour, const char* fmt, va_list args)
{
    ImGui::TextV(fmt, args);

    const auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
    const auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
    UImGui::TextUtils::Strikethrough(colour);

    return static_cast<UImGui_TextUtils_WidgetState>(bHovered | bClicked);
}

UImGui_TextUtils_WidgetState UimGui_TextUtils_StrikethroughWrapped(const char* text, const char* end, const UImGui_TextUtils_Colour colour)
{
    return UImGui::TextUtils::StrikethroughWrapped(text, end, colour);
}

void UImGui_TextUtils_Link(const char* text, const UImGui_TextUtils_Colour colour, const UImGui_TextUtils_LinkCallback callback)
{
    UImGui::TextUtils::Link(text, colour, callback);
}

void UImGui_TextUtils_LinkWrapped(const char* text, const char* end, const UImGui_TextUtils_Colour colour, const UImGui_TextUtils_LinkCallback callback)
{
    UImGui::TextUtils::LinkWrapped(text, end, colour, callback);
}

void UImGui_TextUtils_Highlight(const UImGui_TextUtils_Colour colour)
{
    return UImGui::TextUtils::Highlight(colour);
}

UImGui_TextUtils_WidgetState UImGui_TextUtils_Highlight_fmt(const UImGui_TextUtils_Colour colour, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ImGui::TextV(fmt, args);
    va_end(args);

    const auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
    const auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
    UImGui::TextUtils::Highlight(colour);

    return static_cast<UImGui_TextUtils_WidgetState>(bHovered | bClicked);
}

UImGui_TextUtils_WidgetState UImGui_TextUtils_Highlight_fmtV(const UImGui_TextUtils_Colour colour, const char* fmt, va_list args)
{
    ImGui::TextV(fmt, args);

    const auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
    const auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
    UImGui::TextUtils::Highlight(colour);

    return static_cast<UImGui_TextUtils_WidgetState>(bHovered | bClicked);
}

UImGui_TextUtils_WidgetState UImGui_TextUtils_HighlightWrapped(const char* begin, const char* end, const UImGui_TextUtils_Colour colour)
{
    return UImGui::TextUtils::HighlightWrapped(begin, end, colour);
}

void UImGui_TextUtils_Blockquote(const UImGui_TextUtils_Colour colour)
{
    UImGui::TextUtils::Blockquote(colour);
}

void UImGui_TextUtils_Blockquote_fmt(const UImGui_TextUtils_Colour colour, const char* fmt, ...)
{
    UImGui::TextUtils::Blockquote(colour);
    ImGui::SameLine();

    va_list args;
    va_start(args, fmt);
    ImGui::TextV(fmt, args);
    va_end(args);
}

void UImGui_TextUtils_Blockquote_fmtV(const UImGui_TextUtils_Colour colour, const char* fmt, va_list args)
{
    UImGui::TextUtils::Blockquote(colour);
    ImGui::SameLine();
    ImGui::TextV(fmt, args);
}

void UImGui_TextUtils_BlockquoteWrapped(const char* text, const char* end, const UImGui_TextUtils_Colour colour)
{
    UImGui::TextUtils::BlockquoteWrapped(text, end, colour);
}

void UImGui_TextUtils_CodeBlock(const char* begin, const char* end, const bool bWrapText, const UImGui_TextUtils_Colour colour)
{
    UImGui::TextUtils::CodeBlock(begin, end, bWrapText, colour);
}

void UImGui_TextUtils_CodeInline(const char* begin, const char* end, const UImGui_TextUtils_Colour colour)
{
    UImGui::TextUtils::CodeInline(begin, end, colour);
}

void UImGui_TextUtils_CodeInlineWrapped(const char* begin, const char* end, const UImGui_TextUtils_Colour colour)
{
    UImGui::TextUtils::CodeInlineWrapped(begin, end, colour);
}

void UImGui_TextUtils_ShowDemoWindow(void* bOpen)
{
    UImGui::TextUtils::ShowDemoWindow(bOpen);
}
