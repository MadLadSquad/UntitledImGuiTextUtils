// This is for typeface related features such as:
// - Bold, Italic, bold + italic
// - Monospace
// - Ruby, superscript, subscript
#include "UImGuiTextUtils.hpp"

#define CUSTOM_FONT_BOILERPLATE(x, y) va_list args;     \
va_start(args, x);                                      \
customFontGenericText(fmt, UIMGUI_TEXT_UTILS_DATA->y, args);      \
va_end(args)


#define CUSTOM_FONT_BOILERPLATE_WRAPPED(x, y) va_list args;     \
va_start(args, x);                                              \
customFontGenericTextWrapped(fmt, UIMGUI_TEXT_UTILS_DATA->y, args);       \
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

void UImGui::TextUtils::Subscript(const char* begin, const char* end, bool bWrap, float verticalAlignmentDivide) noexcept
{
    //auto max = ImGui::GetItemRectMax();
    //// If word wrapping is enabled set width to region avail - 1 character,
    //// otherwise use the existing default argument
    //auto width = bWrap ? ImGui::GetContentRegionAvail().x - ImGui::GetFontSize() : 0.0f;
    //auto textSize = ImGui::CalcTextSize(begin, end, false, width);
//
    //ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->small, UIMGUI_TEXT_UTILS_DATA->small->FontSize,
    //                                    ImVec2(max.x, static_cast<float>(max.y - (UIMGUI_TEXT_UTILS_DATA->small->FontSize / verticalAlignmentDivide))),
    //                                    ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
    //                                    begin, end, width);
    //ImGui::SetCursorScreenPos({ max.x + textSize.x, max.y });

    float wrapWidth = bWrap ? ImGui::GetContentRegionAvail().x : -1.0f;

    // Get the font size
    auto textSize = UIMGUI_TEXT_UTILS_DATA->small->CalcTextSizeA(UIMGUI_TEXT_UTILS_DATA->small->FontSize, FLT_MAX, wrapWidth, begin, end);

    auto itemRectMax = ImGui::GetItemRectMax();

    // Calculate rect size and coordinates
    ImVec2 min = ImGui::GetItemRectMin();
    ImVec2 max = { min.x + textSize.x, min.y + itemRectMax.y };
    ImVec2 size = {max.x - min.x, max.y - min.y };

    ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->small, UIMGUI_TEXT_UTILS_DATA->small->FontSize, max,
                                        ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                        begin, end, wrapWidth);

    // Render an invisible button, which will act as our element
    ImGui::InvisibleButton("##subscript", size);
}

void UImGui::TextUtils::Superscript(const char* begin, const char* end, bool bWrap, float verticalAlignmentDivide) noexcept
{
    //auto max = ImGui::GetItemRectMax();
    //auto min = ImGui::GetItemRectMin();
//
    //// If word wrapping is enabled set width to region avail - 1 character,
    //// otherwise use the existing default argument
    //auto width = bWrap ? ImGui::GetContentRegionAvail().x - ImGui::GetFontSize() : 0.0f;
    //auto textSize = ImGui::CalcTextSize(begin, end, false, width);
//
    //ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->small, UIMGUI_TEXT_UTILS_DATA->small->FontSize,
    //                                    ImVec2(max.x, min.y - (UIMGUI_TEXT_UTILS_DATA->small->FontSize / verticalAlignmentDivide)),
    //                                    ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
    //                                    begin, end,width);
    //ImGui::SetCursorScreenPos({ max.x + textSize.x, min.y });
    float wrapWidth = bWrap ? ImGui::GetContentRegionAvail().x : -1.0f;

    // Get the font size
    auto textSize = UIMGUI_TEXT_UTILS_DATA->small->CalcTextSizeA(UIMGUI_TEXT_UTILS_DATA->small->FontSize, FLT_MAX, wrapWidth, begin, end);

    // Calculate rect size and coordinates
    ImVec2 min = ImGui::GetCursorScreenPos();
    ImVec2 max = { min.x + textSize.x, min.y + textSize.y + ImGui::GetStyle().FramePadding.y };
    ImVec2 size = {max.x - min.x, max.y - min.y };

    ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->small, UIMGUI_TEXT_UTILS_DATA->small->FontSize, { max.x, min.y },
                                        ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                        begin, end, wrapWidth);

    // Render an invisible button, which will act as our element
    ImGui::InvisibleButton("##superscript", size);
}

void UImGui::TextUtils::Subscript(const std::string& str, bool bWrap, float verticalAlignmentDivide) noexcept
{
    Subscript(str.c_str(), str.c_str() + str.size(), bWrap, verticalAlignmentDivide);
}

void UImGui::TextUtils::Superscript(const std::string& str, bool bWrap, float verticalAlignmentDivide) noexcept
{
    Superscript(str.c_str(), str.c_str() + str.size(), bWrap, verticalAlignmentDivide);
}

void UImGui::TextUtils::Ruby(const char* begin, const char* end) noexcept
{
    auto min = ImGui::GetItemRectMin();

    ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->small, UIMGUI_TEXT_UTILS_DATA->small->FontSize,
                                        ImVec2(min.x, min.y - UIMGUI_TEXT_UTILS_DATA->small->FontSize / 2),
                                        ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                        begin, end);
}

void UImGui::TextUtils::Ruby(const std::string& text) noexcept
{
    Ruby(text.c_str(), text.c_str() + text.size());
}