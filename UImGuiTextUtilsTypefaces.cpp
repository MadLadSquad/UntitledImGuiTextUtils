// This is for typeface related features such as:
// - Bold, Italic, bold + italic
// - Monospace
// - Ruby, superscript, subscript
#include "UImGuiTextUtils.hpp"

#define CUSTOM_FONT_BOILERPLATE(x, y) va_list args; \
va_start(args, x);                                  \
customFontGenericText(fmt, &getData().y, args);     \
va_end(args)


#define CUSTOM_FONT_BOILERPLATE_WRAPPED(x, y) va_list args; \
va_start(args, x);                                          \
customFontGenericTextWrapped(fmt, &getData().y, args);      \
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