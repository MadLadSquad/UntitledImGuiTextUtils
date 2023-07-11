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

UImGui::TextUtils::WidgetState UImGui::TextUtils::renderWrappedTextGeneric(const char* text, const char* end, ImColor colour, const std::function<void(ImColor)>& f) noexcept
{
    float scale = ImGui::GetIO().FontGlobalScale;
    float widthAvail = ImGui::GetContentRegionAvail().x;
    const char* endLine = text;

    if (widthAvail > 0.0f)
        endLine = ImGui::GetFont()->CalcWordWrapPositionA(scale, text, end, widthAvail);
    if (endLine > text && endLine < end)
    {
        if (isPartOfWord(*endLine))
        {
            float nextLineWidth = ImGui::GetContentRegionMax().x;
            const char* nextLineEnd = ImGui::GetFont()->CalcWordWrapPositionA(scale, text, end, nextLineWidth);
            if (nextLineEnd == end || (nextLineEnd <= end && !isPartOfWord(*nextLineEnd)))
                endLine = text;
        }
    }

    ImGui::PushTextWrapPos(-1.0f);
    ImGui::TextUnformatted(text, endLine);
    auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
    auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;

    f(colour);
    ImGui::PopTextWrapPos();

    widthAvail = ImGui::GetContentRegionAvail().x;
    auto result = static_cast<WidgetState>(bHovered | bClicked);
    while (endLine < end)
    {
        text = endLine;
        if (*text == ' ')
            ++text;
        endLine = ImGui::GetFont()->CalcWordWrapPositionA(scale, text, end, widthAvail);
        if (text == endLine)
            endLine++;
        ImGui::PushTextWrapPos(-1.0f);
        ImGui::TextUnformatted(text, endLine);
        bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
        bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
        f(colour);

        result = static_cast<WidgetState>(result | bHovered | bClicked);

        ImGui::PopTextWrapPos();
    }
    return result;
}
