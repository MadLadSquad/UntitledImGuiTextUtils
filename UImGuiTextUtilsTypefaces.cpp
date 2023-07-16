// This is for typeface related features such as:
// - Bold, Italic, bold + italic
// - Monospace
// - Ruby, superscript, subscript
#include "UImGuiTextUtils.hpp"

#define CUSTOM_FONT_BOILERPLATE(x, y) va_list args;     \
va_start(args, x);                                      \
customFontGenericText(fmt, (*getData())->y, args);      \
va_end(args)


#define CUSTOM_FONT_BOILERPLATE_WRAPPED(x, y) va_list args;     \
va_start(args, x);                                              \
customFontGenericTextWrapped(fmt, (*getData())->y, args);       \
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
    auto max = ImGui::GetItemRectMax();

    ImGui::GetWindowDrawList()->AddText((*getData())->small, (*getData())->small->FontSize,
                                        ImVec2(max.x, static_cast<float>(max.y - ((*getData())->small->FontSize / verticalAlignmentDivide))),
                                        ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                        begin, end,
                                        // If word wrapping is enabled set width to region avail - 1 character,
                                        // otherwise use the existing default argument
                                        bWrap ? ImGui::GetContentRegionAvail().x - ImGui::GetFontSize() : 0.0f);
}

void UImGui::TextUtils::Superscript(const char* begin, const char* end, bool bWrap, float verticalAlignmentDivide) noexcept
{
    auto max = ImGui::GetItemRectMax();
    auto min = ImGui::GetItemRectMin();

    ImGui::GetWindowDrawList()->AddText((*getData())->small, (*getData())->small->FontSize,
                                        ImVec2(max.x, min.y - ((*getData())->small->FontSize / verticalAlignmentDivide)),
                                        ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                        begin, end,
                                        // If word wrapping is enabled set width to region avail - 1 character,
                                        // otherwise use the existing default argument
                                        bWrap ? ImGui::GetContentRegionAvail().x - ImGui::GetFontSize() : 0.0f);
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

    ImGui::GetWindowDrawList()->AddText((*getData())->small, (*getData())->small->FontSize,
                                        ImVec2(min.x, min.y - (*getData())->small->FontSize / 2),
                                        ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                        begin, end);
}

void UImGui::TextUtils::Ruby(const std::string& text) noexcept
{
    Ruby(text.c_str(), text.c_str() + text.size());
}
