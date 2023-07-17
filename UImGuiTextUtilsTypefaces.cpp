// This is for typeface related features such as:
// - Bold, Italic, bold + italic
// - Monospace
// - Ruby, superscript, subscript
#include "UImGuiTextUtils.hpp"

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

void UImGui::TextUtils::BoldWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, bold);
}

void UImGui::TextUtils::Italic(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, italic);
}

void UImGui::TextUtils::ItalicWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, italic);
}

void UImGui::TextUtils::BoldItalic(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, boldItalic);
}

void UImGui::TextUtils::BoldItalicWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, boldItalic);
}

void UImGui::TextUtils::Monospace(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, monospace);
}

void UImGui::TextUtils::MonospaceWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, monospace);
}

void UImGui::TextUtils::Small(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, small);
}

void UImGui::TextUtils::SmallWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, small);
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

void UImGui::TextUtils::Ruby(const char* textBegin, const char* textEnd, const char* annotationBegin, const char* annotationEnd, bool bWrapAnnotation, bool bWrapText) noexcept
{
    static float width = 0.0f;

    ImGui::BeginGroup();
    auto offset = (UIMGUI_TEXT_UTILS_DATA->small->FontSize / 2);

    // Render
    {
        auto min = ImGui::GetCursorScreenPos();
        min.y -= offset;

        auto textSize = UIMGUI_TEXT_UTILS_DATA->small->CalcTextSizeA(UIMGUI_TEXT_UTILS_DATA->small->FontSize, FLT_MAX, width, annotationBegin, annotationEnd);

        ImVec2 max = { min.x + textSize.x, min.y + textSize.y };
        ImVec2 size = {max.x - min.x, max.y - min.y };
        ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->small, UIMGUI_TEXT_UTILS_DATA->small->FontSize, min,
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            annotationBegin, annotationEnd, width);
        // Render an invisible button, which will act as our element
        ImGui::InvisibleButton("##rubyannotation", size);
    }
    {
        auto min = ImGui::GetItemRectMin();
        min.y += offset;

        auto textSize = ImGui::CalcTextSize(textBegin, textEnd, false, bWrapText ? ImGui::GetContentRegionAvail().x : -1.0f);
        width = bWrapAnnotation ? std::min(textSize.x, ImGui::GetContentRegionAvail().x) : -1.0f;

        ImVec2 max = { min.x + textSize.x, min.y + textSize.y };
        ImVec2 size = {max.x - min.x, max.y - min.y };
        ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFont()->FontSize, min,
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            textBegin, textEnd, width);
        // Render an invisible button, which will act as our element
        ImGui::InvisibleButton("##ruby", size);
    }
    ImGui::EndGroup();
}

void UImGui::TextUtils::Ruby(const std::string& text, const std::string& annotation, bool bWrapAnnotation, bool bWrapText) noexcept
{
    Ruby(text.c_str(), text.c_str() + text.size(), annotation.c_str(), annotation.c_str() + annotation.size(), bWrapAnnotation, bWrapText);
}

void UImGui::TextUtils::SubSuperscript(const std::string& subscript, const std::string& superscript) noexcept
{
    SubSuperscript(subscript.c_str(), subscript.c_str() + subscript.size(),
                   superscript.c_str(), superscript.c_str() + superscript.size());
}

void UImGui::TextUtils::SubSuperscript(const char* subscriptBegin, const char* subscriptEnd,
                                       const char* superscriptBegin, const char* superscriptEnd) noexcept
{
    auto offset = (UIMGUI_TEXT_UTILS_DATA->small->FontSize / 2);

    auto superscriptTextSize = UIMGUI_TEXT_UTILS_DATA->small->CalcTextSizeA(UIMGUI_TEXT_UTILS_DATA->small->FontSize, FLT_MAX,
                                                                            -1.0f, superscriptBegin, superscriptEnd);
    auto subscriptTextSize = UIMGUI_TEXT_UTILS_DATA->small->CalcTextSizeA(UIMGUI_TEXT_UTILS_DATA->small->FontSize, FLT_MAX,
                                                                            -1.0f, subscriptBegin, subscriptEnd);
    ImVec2 min = ImGui::GetCursorScreenPos();
    min.y -= offset;
    {

        ImVec2 max = { min.x + superscriptTextSize.x, min.y + superscriptTextSize.y + ImGui::GetStyle().FramePadding.y - offset };
        ImVec2 size = { max.x - min.x, max.y - min.y };
        ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->small, UIMGUI_TEXT_UTILS_DATA->small->FontSize, min,
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            superscriptBegin, superscriptEnd, -1.0f);

        ImGui::InvisibleButton("##superscript", size);
    }
    ImGui::SameLine();
    {
        ImVec2 max = { min.x + subscriptTextSize.x, min.y + subscriptTextSize.y + ImGui::GetStyle().FramePadding.y - offset };
        ImVec2 size = { max.x - min.x, max.y - min.y };
        ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->small, UIMGUI_TEXT_UTILS_DATA->small->FontSize, { min.x, max.y },
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            subscriptBegin, subscriptEnd, -1.0f);

        ImGui::InvisibleButton("##subscript", size);
    }
}
