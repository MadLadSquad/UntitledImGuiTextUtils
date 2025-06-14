// This is for typeface related features such as:
// - Bold, Italic, bold + italic
// - Monospace
// - Ruby, superscript, subscript
// TODO: Remove version num checks on January 1st
#include "UImGuiTextUtils.hpp"

#if IMGUI_VERSION_NUM > 19197
    #define LEGACY_SIZE(x) ImGui::GetFontSize()
#else
    #define LEGACY_SIZE(x) UIMGUI_TEXT_UTILS_DATA->x->FontSize
#endif

#define CUSTOM_FONT_BOILERPLATE(x, y) va_list args;             \
va_start(args, x);                                              \
customFontGenericText(fmt, UIMGUI_TEXT_UTILS_DATA->y, args);    \
va_end(args)


#define CUSTOM_FONT_BOILERPLATE_WRAPPED(x, y) va_list args;         \
va_start(args, x);                                                  \
customFontGenericTextWrapped(fmt, UIMGUI_TEXT_UTILS_DATA->y, args); \
va_end(args)

void UImGui::TextUtils::Bold(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, bold);
}

void UImGui::TextUtils::BoldV(const char* fmt, va_list list) noexcept
{
    customFontGenericText(fmt, UIMGUI_TEXT_UTILS_DATA->bold, list);
}

void UImGui::TextUtils::BoldWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, bold);
}

void UImGui::TextUtils::BoldWrappedV(const char* fmt, va_list list) noexcept
{
    customFontGenericTextWrapped(fmt, UIMGUI_TEXT_UTILS_DATA->bold, list);
}

void UImGui::TextUtils::Italic(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, italic);
}

void UImGui::TextUtils::ItalicV(const char* fmt, va_list list) noexcept
{
    customFontGenericText(fmt, UIMGUI_TEXT_UTILS_DATA->italic, list);
}

void UImGui::TextUtils::ItalicWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, italic);
}

void UImGui::TextUtils::ItalicWrappedV(const char* fmt, va_list list) noexcept
{
    customFontGenericTextWrapped(fmt, UIMGUI_TEXT_UTILS_DATA->italic, list);
}

void UImGui::TextUtils::BoldItalic(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, boldItalic);
}

void UImGui::TextUtils::BoldItalicV(const char* fmt, va_list list) noexcept
{
    customFontGenericText(fmt, UIMGUI_TEXT_UTILS_DATA->boldItalic, list);
}

void UImGui::TextUtils::BoldItalicWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, boldItalic);
}

void UImGui::TextUtils::BoldItalicWrappedV(const char* fmt, va_list list) noexcept
{
    customFontGenericTextWrapped(fmt, UIMGUI_TEXT_UTILS_DATA->boldItalic, list);
}

void UImGui::TextUtils::Monospace(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, monospace);
}

void UImGui::TextUtils::MonospaceV(const char* fmt, va_list list) noexcept
{
    customFontGenericText(fmt, UIMGUI_TEXT_UTILS_DATA->monospace, list);
}

void UImGui::TextUtils::MonospaceWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, monospace);
}

void UImGui::TextUtils::MonospaceWrappedV(const char* fmt, va_list list) noexcept
{
    customFontGenericTextWrapped(fmt, UIMGUI_TEXT_UTILS_DATA->monospace, list);
}

void UImGui::TextUtils::Small(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, smallFont);
}

void UImGui::TextUtils::SmallV(const char* fmt, va_list list) noexcept
{
    customFontGenericText(fmt, UIMGUI_TEXT_UTILS_DATA->smallFont, list);
}

void UImGui::TextUtils::SmallWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, smallFont);
}

void UImGui::TextUtils::SmallWrappedV(const char* fmt, va_list list) noexcept
{
    customFontGenericTextWrapped(fmt, UIMGUI_TEXT_UTILS_DATA->smallFont, list);
}

void UImGui::TextUtils::customFontGenericText(const char* fmt, ImFont* font, va_list args) noexcept
{
    ImGui::PushFont(font);
    ImGui::TextV(fmt, args);
    ImGui::PopFont();
}

void UImGui::TextUtils::customFontGenericTextWrapped(const char* fmt, ImFont* font, va_list args) noexcept
{
    ImGui::PushFont(font);
    ImGui::TextWrappedV(fmt, args);
    ImGui::PopFont();
}

void UImGui::TextUtils::Ruby(const char* textBegin, const char* textEnd, const char* annotationBegin, const char* annotationEnd, const bool bWrapAnnotation, const bool bWrapText) noexcept
{
    static float width = 0.0f;

    ImGui::BeginGroup();
    const auto offset = (LEGACY_SIZE(smallFont) / 2);

    ImGui::PushID(textBegin, textEnd);
    // Render
    {
        auto min = ImGui::GetCursorScreenPos();
        min.y -= offset;

        const auto textSize = UIMGUI_TEXT_UTILS_DATA->smallFont->CalcTextSizeA(LEGACY_SIZE(smallFont), FLT_MAX, width, annotationBegin, annotationEnd);

        const ImVec2 max = { min.x + textSize.x, min.y + textSize.y };
        const ImVec2 size = {max.x - min.x, max.y - min.y };
        ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->smallFont, LEGACY_SIZE(smallFont), min,
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            annotationBegin, annotationEnd, width);
        // Render an invisible button, which will act as our element
        ImGui::InvisibleButton("##rubyannotation", size);
    }
    {
        auto min = ImGui::GetItemRectMin();
        min.y += offset;

        const auto textSize = ImGui::CalcTextSize(textBegin, textEnd, false, bWrapText ? ImGui::GetContentRegionAvail().x : -1.0f);
        width = bWrapAnnotation ? std::min(textSize.x, ImGui::GetContentRegionAvail().x) : -1.0f;

        const ImVec2 max = { min.x + textSize.x, min.y + textSize.y };
        const ImVec2 size = {max.x - min.x, max.y - min.y };
        ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(),
#if IMGUI_VERSION_NUM > 19197
                                            ImGui::GetFontSize(),
#else
                                            ImGui::GetFont()->FontSize,
#endif
                                            min,
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            textBegin, textEnd, width);
        // Render an invisible button, which will act as our element
        ImGui::InvisibleButton("##ruby", size);
    }
    ImGui::PopID();
    ImGui::EndGroup();
}

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
void UImGui::TextUtils::Ruby(const TString& text, const TString& annotation, const bool bWrapAnnotation, const bool bWrapText) noexcept
{
    Ruby(text.c_str(), text.c_str() + text.size(), annotation.c_str(), annotation.c_str() + annotation.size(), bWrapAnnotation, bWrapText);
}


void UImGui::TextUtils::SubSuperscript(const TString& subscript, const TString& superscript) noexcept
{
    SubSuperscript(subscript.c_str(), subscript.c_str() + subscript.size(),
                   superscript.c_str(), superscript.c_str() + superscript.size());
}
#endif

void UImGui::TextUtils::SubSuperscript(const char* subscriptBegin, const char* subscriptEnd,
                                       const char* superscriptBegin, const char* superscriptEnd) noexcept
{
    const auto offset = (LEGACY_SIZE(smallFont) / 2);
    const auto superscriptTextSize = UIMGUI_TEXT_UTILS_DATA->smallFont->CalcTextSizeA(LEGACY_SIZE(smallFont), FLT_MAX,
                                                                            -1.0f, superscriptBegin, superscriptEnd);
    const auto subscriptTextSize = UIMGUI_TEXT_UTILS_DATA->smallFont->CalcTextSizeA(LEGACY_SIZE(smallFont), FLT_MAX,
                                                                            -1.0f, subscriptBegin, subscriptEnd);
    ImVec2 min = ImGui::GetCursorScreenPos();
    min.y -= offset;
    ImGui::PushID(subscriptBegin, subscriptEnd);
    ImGui::PushID(superscriptBegin, superscriptEnd);
    {

        const ImVec2 max = { min.x + superscriptTextSize.x, min.y + superscriptTextSize.y + ImGui::GetStyle().FramePadding.y - offset };
        const ImVec2 size = { max.x - min.x, max.y - min.y };
        ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->smallFont, LEGACY_SIZE(smallFont), min,
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            superscriptBegin, superscriptEnd, -1.0f);

        ImGui::InvisibleButton("##superscript", size);
    }
    ImGui::SameLine();
    {
        const ImVec2 max = { min.x + subscriptTextSize.x, min.y + subscriptTextSize.y + ImGui::GetStyle().FramePadding.y - offset };
        const ImVec2 size = { max.x - min.x, max.y - min.y };

        ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->smallFont, LEGACY_SIZE(smallFont), { min.x, max.y },
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            subscriptBegin, subscriptEnd, -1.0f);

        ImGui::InvisibleButton("##subscript", size);
    }
    ImGui::PopID();
    ImGui::PopID();
}
