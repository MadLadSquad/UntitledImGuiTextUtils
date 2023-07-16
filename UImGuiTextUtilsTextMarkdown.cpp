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
    return renderWrappedTextGeneric(text, end, colour, [](ImColor color) -> void { Underline(color); }, [](ImColor) -> void {});
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

    return renderWrappedTextGeneric(text, end, colour, [](ImColor color) -> void { Strikethrough(color); }, [](ImColor) -> void {});
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
    return renderWrappedTextGeneric(text, end, colour, [](ImColor color) -> void { Highlight(color); }, [](ImColor) -> void {});
}

UImGui::TextUtils::WidgetState UImGui::TextUtils::HighlightWrapped(const std::string& text, ImColor colour) noexcept
{
    return HighlightWrapped(text.c_str(), text.c_str() + text.size(), colour);
}

void UImGui::TextUtils::Blockquote(ImColor colour) noexcept
{
    // Get the font size
    float scale = ImGui::GetFontSize();

    // Calculate rect size and coordinates
    ImVec2 min = ImGui::GetCursorScreenPos();
    ImVec2 max = ImVec2(min.x + (float)(int)(scale / 4) + (float)(int)(scale / 6), min.y + scale + (float)(int)(scale / 2));
    ImVec2 size = ImVec2(max.x - min.x, max.y - min.y);

    // Add rectangle with min, max and the colour
    ImGui::GetWindowDrawList()->AddRectFilled(min, max, colour);

    // Render an invisible button, which will act as our element
    ImGui::InvisibleButton("##bq", size);
}

void UImGui::TextUtils::BlockquoteWrapped(const char* text, const char* end, ImColor colour) noexcept
{
    renderWrappedTextGeneric(text, end, colour, [](ImColor) -> void {}, [](ImColor col) -> void {
        Blockquote(col);
        ImGui::SameLine();
    });
}

void UImGui::TextUtils::BlockquoteWrapped(const std::string& text, ImColor colour) noexcept
{
    BlockquoteWrapped(text.c_str(), text.c_str() + text.size(), colour);
}

void UImGui::TextUtils::CodeBlock(const char* begin, const char* end, bool bWrapText, ImColor backgroundColour) noexcept
{
    float wrapWidth = bWrapText ? ImGui::GetContentRegionAvail().x : -1.0f;

    // Get the font size
    auto textSize = UIMGUI_TEXT_UTILS_DATA->monospace->CalcTextSizeA(UIMGUI_TEXT_UTILS_DATA->monospace->FontSize, FLT_MAX, wrapWidth, begin, end);

    // Calculate rect size and coordinates
    ImVec2 min = ImGui::GetCursorScreenPos();
    ImVec2 max = { min.x + textSize.x, min.y + textSize.y + ImGui::GetStyle().FramePadding.y };
    ImVec2 size = {max.x - min.x, max.y - min.y };

    // Add rectangle with min, max and the colour
    ImGui::GetWindowDrawList()->AddRectFilled(min, max, backgroundColour);
    ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->monospace, UIMGUI_TEXT_UTILS_DATA->monospace->FontSize,min,
                                        ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                        begin, end, wrapWidth);

    // Render an invisible button, which will act as our element
    ImGui::InvisibleButton("##code", size);
}

void UImGui::TextUtils::CodeBlock(const std::string& text, bool bWrapText, ImColor backgroundColour) noexcept
{
    CodeBlock(text.c_str(), text.c_str() + text.size(), bWrapText, backgroundColour);
}

void UImGui::TextUtils::CodeInlineWrapped(const char* begin, const char* end, ImColor backgroundColour) noexcept
{
    auto f = [](UImGui::TextUtilsData* data, const char* s, const char* e, ImColor backgroundColour) -> void {
        // Get the font size
        auto textSize = data->monospace->CalcTextSizeA(data->monospace->FontSize, FLT_MAX, -1.0f, s, e);

        // Calculate rect size and coordinates
        ImVec2 min = ImGui::GetCursorScreenPos();
        ImVec2 max = { min.x + textSize.x, min.y + textSize.y + ImGui::GetStyle().FramePadding.y };
        ImVec2 size = {max.x - min.x, max.y - min.y };

        // Add rectangle with min, max and the colour
        ImGui::GetWindowDrawList()->AddRectFilled(min, max, backgroundColour);
        ImGui::GetWindowDrawList()->AddText(data->monospace, data->monospace->FontSize,min,
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            s, e, -1.0f);

        // Render an invisible button, which will act as our element
        ImGui::InvisibleButton("##code", size);
    };

    float scale = ImGui::GetIO().FontGlobalScale;
    float widthAvail = ImGui::GetContentRegionAvail().x;
    const char* endLine = begin;

    if (widthAvail > 0.0f)
        endLine = ImGui::GetFont()->CalcWordWrapPositionA(scale, begin, end, widthAvail);
    if (endLine > begin && endLine < end)
    {
        if (isPartOfWord(*endLine))
        {
            float nextLineWidth = ImGui::GetContentRegionMax().x;
            const char* nextLineEnd = ImGui::GetFont()->CalcWordWrapPositionA(scale, begin, end, nextLineWidth);
            if (nextLineEnd == end || (nextLineEnd <= end && !isPartOfWord(*nextLineEnd)))
                endLine = begin;
        }
    }

    ImGui::PushTextWrapPos(-1.0f);
    f(UIMGUI_TEXT_UTILS_DATA, begin, endLine, backgroundColour);

    ImGui::PopTextWrapPos();

    widthAvail = ImGui::GetContentRegionAvail().x;
    while (endLine < end)
    {
        begin = endLine;
        if (*begin == ' ')
            ++begin;
        endLine = ImGui::GetFont()->CalcWordWrapPositionA(scale, begin, end, widthAvail);
        if (begin == endLine)
            endLine++;
        ImGui::PushTextWrapPos(-1.0f);
        f(UIMGUI_TEXT_UTILS_DATA, begin, endLine, backgroundColour);

        ImGui::PopTextWrapPos();
    }
}

void UImGui::TextUtils::CodeInlineWrapped(const std::string& text, ImColor backgroundColour) noexcept
{
    CodeInlineWrapped(text.c_str(), text.c_str() + text.size(), backgroundColour);
}

void UImGui::TextUtils::CodeInline(const char* begin, const char* end, ImColor backgroundColour) noexcept
{
    // Get the font size
    auto textSize = UIMGUI_TEXT_UTILS_DATA->monospace->CalcTextSizeA(UIMGUI_TEXT_UTILS_DATA->monospace->FontSize, FLT_MAX, -1.0f, begin, end);

    // Calculate rect size and coordinates
    ImVec2 min = ImGui::GetCursorScreenPos();
    ImVec2 max = { min.x + textSize.x, min.y + textSize.y + ImGui::GetStyle().FramePadding.y };
    ImVec2 size = {max.x - min.x, max.y - min.y };

    // Add rectangle with min, max and the colour
    ImGui::GetWindowDrawList()->AddRectFilled(min, max, backgroundColour);
    ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->monospace, UIMGUI_TEXT_UTILS_DATA->monospace->FontSize,min,
                                        ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                        begin, end, -1.0f);

    // Render an invisible button, which will act as our element
    ImGui::InvisibleButton("##code", size);
}

void UImGui::TextUtils::CodeInline(const std::string& text, ImColor backgroundColour) noexcept
{
    CodeInline(text.c_str(), text.c_str() + text.size(), backgroundColour);
}

UImGui::TextUtils::WidgetState UImGui::TextUtils::renderWrappedTextGeneric(const char* text, const char* end, ImColor colour, const std::function<void(ImColor)>& after, const std::function<void(ImColor)>& before) noexcept
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
    before(colour);
    ImGui::TextUnformatted(text, endLine);

    auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
    auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;

    after(colour);
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
        before(colour);
        ImGui::TextUnformatted(text, endLine);

        bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
        bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;

        after(colour);

        result = static_cast<WidgetState>(result | bHovered | bClicked);

        ImGui::PopTextWrapPos();
    }
    return result;
}
