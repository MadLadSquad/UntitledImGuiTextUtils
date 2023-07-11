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
