// This is for text markdown features such as:
// - Underlined text
// - Strikethrough text
// - Highlight text
#include "UImGuiTextUtils.hpp"
#include <iostream>

void UImGui::TextUtils::Underline(ImColor colour) noexcept
{
    ImVec2 min = ImGui::GetItemRectMin();
    ImVec2 max = ImGui::GetItemRectMax();

    min.y = max.y;

    ImGui::GetWindowDrawList()->AddLine(min, max, colour, 1.0f);
}

UImGui::TextUtils::WidgetState UImGui::TextUtils::UnderlineWrapped(const char* text, const char* end, ImColor colour) noexcept
{
    return renderWrappedTextGeneric(text, end, colour, [](ImColor color) -> void { Underline(color); });
}

bool UImGui::TextUtils::isPartOfWord(char character) noexcept
{
    return character != ' ' && character != '.' && character != ',' && character != '!' && character != '?' &&
           character != '\'' && character != '\"' && character != '`';
}

void UImGui::TextUtils::Link(const char* text, ImColor colour, const std::function<void(const char* link)>& clicked) noexcept
{
    ImGui::PushStyleColor(ImGuiCol_Text, colour.Value);
    auto state = Underline(text, colour, "");
    if (state & UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED)
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        if (state & UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED)
            clicked(text);
    }

    ImGui::PopStyleColor();
}

void UImGui::TextUtils::LinkWrapped(const char* text, const char* end, ImColor colour, const std::function<void(const char* link)>& clicked) noexcept
{
    ImGui::PushStyleColor(ImGuiCol_Text, colour.Value);
    auto state = UnderlineWrapped(text, end, colour);
    if (state & UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED)
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        if (state & UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED)
            clicked(text);
    }
    ImGui::PopStyleColor();
}

UImGui::TextUtils::WidgetState UImGui::TextUtils::UnderlineWrapped(const std::string& text, ImColor colour) noexcept
{
    return UnderlineWrapped(text.c_str(), text.c_str() + text.size(), colour);
}

void UImGui::TextUtils::LinkWrapped(const std::string& text, ImColor colour, const std::function<void(const char*)>& clicked) noexcept
{
    return LinkWrapped(text.c_str(), text.c_str() + text.size(), colour, clicked);
}

void UImGui::TextUtils::Strikethrough(ImColor colour) noexcept
{
    ImVec2 min = ImGui::GetItemRectMin();
    ImVec2 max = ImGui::GetItemRectMax();

    // Do this casting to round up automatically
    max.y -= (float)(int)((max.y - min.y) / 2);
    min.y = max.y;

    ImGui::GetWindowDrawList()->AddLine(min, max, colour, 0.25f);
}

UImGui::TextUtils::WidgetState UImGui::TextUtils::StrikethroughWrapped(const char* text, const char* end, ImColor colour) noexcept
{

    return renderWrappedTextGeneric(text, end, colour, [](ImColor color) -> void { Strikethrough(color); });
}

UImGui::TextUtils::WidgetState UImGui::TextUtils::StrikethroughWrapped(const std::string& text, ImColor colour) noexcept
{
    return StrikethroughWrapped(text.c_str(), text.c_str() + text.size(), colour);
}

void UImGui::TextUtils::Highlight(ImColor colour) noexcept
{
    ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), colour);
}

UImGui::TextUtils::WidgetState UImGui::TextUtils::HighlightWrapped(const char* text, const char* end, ImColor colour) noexcept 
{
    return renderWrappedTextGeneric(text, end, colour, [](ImColor color) -> void { Highlight(color); });
}

UImGui::TextUtils::WidgetState UImGui::TextUtils::HighlightWrapped(const std::string& text, ImColor colour) noexcept
{
    return HighlightWrapped(text.c_str(), text.c_str() + text.size(), colour);
}

void UImGui::TextUtils::Blockquote(ImColor colour) noexcept
{
    float scale = ImGui::GetFontSize();

    ImVec2 max;
    max.x = ImGui::GetCursorScreenPos().x + ((float)(int)(scale / 4) + (float)(int)(scale / 6));
    max.y = ImGui::GetCursorScreenPos().y - (scale + (float)(int)(scale / 2));

    ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetCursorScreenPos(), max, colour);
}

UImGui::TextUtils::WidgetState UImGui::TextUtils::BlockquoteWrapped(const char* text, const char* end, ImColor colour) noexcept
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
    Blockquote(colour);
    ImGui::TextUnformatted(text, endLine);
    auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
    auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
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

        Blockquote(colour);
        ImGui::TextUnformatted(text, endLine);
        bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
        bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;

        result = static_cast<WidgetState>(result | bHovered | bClicked);

        ImGui::PopTextWrapPos();
    }
    return result;
}

UImGui::TextUtils::WidgetState UImGui::TextUtils::BlockquoteWrapped(const std::string& text, ImColor colour) noexcept
{
    return BlockquoteWrapped(text.c_str(), text.c_str() + text.size(), colour);
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