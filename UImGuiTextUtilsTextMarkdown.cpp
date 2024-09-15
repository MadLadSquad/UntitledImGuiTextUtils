// This is for text markdown features such as:
// - Underlined text
// - Strikethrough text
// - Highlight text
#include "UImGuiTextUtils.hpp"

void UImGui::TextUtils::Underline(const Colour colour) noexcept
{
    auto min = ImGui::GetItemRectMin();
    const auto max = ImGui::GetItemRectMax();

    min.y = max.y;

    ImGui::GetWindowDrawList()->AddLine(min, max, colour, 1.0f);
}

UImGui::TextUtils::WidgetState UImGui::TextUtils::UnderlineWrapped(const char* text, const char* end, const Colour colour) noexcept
{
    return renderWrappedTextGeneric(text, end, colour, [](const Colour col) -> void { Underline(col); }, [](Colour) -> void {});
}

bool UImGui::TextUtils::isPartOfWord(const char character) noexcept
{
    return character != ' ' && character != '.' && character != ',' && character != '!' && character != '?' &&
           character != '\'' && character != '\"' && character != '`';
}

void UImGui::TextUtils::Link(const char* text, const Colour colour, const std::function<void(const char* link)>& clicked) noexcept
{
    ImGui::PushStyleColor(ImGuiCol_Text, colour);
    const auto state = Underline(text, colour, "");
    if (state & UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED)
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        if (state & UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED)
            clicked(text);
    }

    ImGui::PopStyleColor();
}

void UImGui::TextUtils::LinkWrapped(const char* text, const char* end, const Colour colour, const std::function<void(const char* link)>& clicked) noexcept
{
    ImGui::PushStyleColor(ImGuiCol_Text, colour);
    const auto state = UnderlineWrapped(text, end, colour);
    if (state & UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED)
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        if (state & UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED)
            clicked(text);
    }
    ImGui::PopStyleColor();
}

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
UImGui::TextUtils::WidgetState UImGui::TextUtils::UnderlineWrapped(const TString& text, const Colour colour) noexcept
{
    return UnderlineWrapped(text.c_str(), text.c_str() + text.size(), colour);
}

void UImGui::TextUtils::LinkWrapped(const TString& text, const Colour colour, const std::function<void(const char*)>& clicked) noexcept
{
    return LinkWrapped(text.c_str(), text.c_str() + text.size(), colour, clicked);
}
#endif

void UImGui::TextUtils::Strikethrough(const Colour colour) noexcept
{
    ImVec2 min = ImGui::GetItemRectMin();
    ImVec2 max = ImGui::GetItemRectMax();

    // Do this casting to round up automatically
    max.y -= static_cast<float>(static_cast<int>((max.y - min.y) / 2));
    min.y = max.y;

    ImGui::GetWindowDrawList()->AddLine(min, max, colour, 0.25f);
}

UImGui::TextUtils::WidgetState UImGui::TextUtils::StrikethroughWrapped(const char* text, const char* end, const Colour colour) noexcept
{

    return renderWrappedTextGeneric(text, end, colour, [](const Colour col) -> void { Strikethrough(col); }, [](Colour) -> void {});
}

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
UImGui::TextUtils::WidgetState UImGui::TextUtils::StrikethroughWrapped(const TString& text, const Colour colour) noexcept
{
    return StrikethroughWrapped(text.c_str(), text.c_str() + text.size(), colour);
}
#endif

void UImGui::TextUtils::Highlight(const Colour colour) noexcept
{
    ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), colour);
}

UImGui::TextUtils::WidgetState UImGui::TextUtils::HighlightWrapped(const char* text, const char* end, const Colour colour) noexcept
{
    return renderWrappedTextGeneric(text, end, colour, [](const Colour col) -> void { Highlight(col); }, [](Colour) -> void {});
}

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
UImGui::TextUtils::WidgetState UImGui::TextUtils::HighlightWrapped(const TString& text, const Colour colour) noexcept
{
    return HighlightWrapped(text.c_str(), text.c_str() + text.size(), colour);
}
#endif

void UImGui::TextUtils::Blockquote(const Colour colour) noexcept
{
    // Get the font size
    const float scale = ImGui::GetFontSize();

    // Calculate rect size and coordinates
    const auto min = ImGui::GetCursorScreenPos();
    const auto max = ImVec2(min.x +
                                        static_cast<float>(static_cast<int>(scale / 4)) +
                                        static_cast<float>(static_cast<int>(scale / 6)),
                            min.y + scale + static_cast<float>(static_cast<int>(scale / 2)));
    const auto size = ImVec2(max.x - min.x, max.y - min.y);

    // Add rectangle with min, max and the colour
    ImGui::GetWindowDrawList()->AddRectFilled(min, max, colour);

    // Render an invisible button, which will act as our element
    ImGui::InvisibleButton("##bq", size);
}

void UImGui::TextUtils::BlockquoteWrapped(const char* text, const char* end, const Colour colour) noexcept
{
    renderWrappedTextGeneric(text, end, colour, [](Colour) -> void {}, [](const Colour col) -> void {
        Blockquote(col);
        ImGui::SameLine();
    });
}

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
void UImGui::TextUtils::BlockquoteWrapped(const TString& text, const Colour colour) noexcept
{
    BlockquoteWrapped(text.c_str(), text.c_str() + text.size(), colour);
}
#endif

void UImGui::TextUtils::CodeBlock(const char* begin, const char* end, const bool bWrapText, const Colour backgroundColour) noexcept
{
    const float wrapWidth = bWrapText ? ImGui::GetContentRegionAvail().x : -1.0f;

    // Get the font size
    const auto textSize = UIMGUI_TEXT_UTILS_DATA->monospace->CalcTextSizeA(UIMGUI_TEXT_UTILS_DATA->monospace->FontSize, FLT_MAX, wrapWidth, begin, end);

    // Calculate rect size and coordinates
    const auto min = ImGui::GetCursorScreenPos();
    const ImVec2 max = { min.x + textSize.x, min.y + textSize.y + ImGui::GetStyle().FramePadding.y };
    const ImVec2 size = {max.x - min.x, max.y - min.y };

    // Add rectangle with min, max and the colour
    ImGui::GetWindowDrawList()->AddRectFilled(min, max, backgroundColour);
    ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->monospace, UIMGUI_TEXT_UTILS_DATA->monospace->FontSize,min,
                                        ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                        begin, end, wrapWidth);

    // Render an invisible button, which will act as our element
    ImGui::InvisibleButton("##code", size);
}

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
void UImGui::TextUtils::CodeBlock(const TString& text, const bool bWrapText, const Colour backgroundColour) noexcept
{
    CodeBlock(text.c_str(), text.c_str() + text.size(), bWrapText, backgroundColour);
}
#endif

void UImGui::TextUtils::CodeInlineWrapped(const char* begin, const char* end, const Colour backgroundColour) noexcept
{
    renderWrappedTextGeneric(begin, end, backgroundColour,
                             [](Colour) -> void {}, [](Colour) -> void {}, [](TextUtilsData const* data, const char* s, const char* e, const Colour colour) -> void
    {
        // Get the font size
        const auto textSize = data->monospace->CalcTextSizeA(data->monospace->FontSize, FLT_MAX, -1.0f, s, e);

        // Calculate rect size and coordinates
        const auto min = ImGui::GetCursorScreenPos();
        const ImVec2 max = { min.x + textSize.x, min.y + textSize.y + ImGui::GetStyle().FramePadding.y };
        const ImVec2 size = {max.x - min.x, max.y - min.y };

        // Add rectangle with min, max and the colour
        ImGui::GetWindowDrawList()->AddRectFilled(min, max, colour);
        ImGui::GetWindowDrawList()->AddText(data->monospace, data->monospace->FontSize,min,
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            s, e, -1.0f);

        // Render an invisible button, which will act as our element
        ImGui::InvisibleButton("##code", size);
    });
}

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
void UImGui::TextUtils::CodeInlineWrapped(const TString& text, const Colour backgroundColour) noexcept
{
    CodeInlineWrapped(text.c_str(), text.c_str() + text.size(), backgroundColour);
}
#endif

void UImGui::TextUtils::CodeInline(const char* begin, const char* end, const Colour backgroundColour) noexcept
{
    // Get the font size
    const auto textSize = UIMGUI_TEXT_UTILS_DATA->monospace->CalcTextSizeA(UIMGUI_TEXT_UTILS_DATA->monospace->FontSize, FLT_MAX, -1.0f, begin, end);

    // Calculate rect size and coordinates
    const auto min = ImGui::GetCursorScreenPos();
    const ImVec2 max = { min.x + textSize.x, min.y + textSize.y + ImGui::GetStyle().FramePadding.y };
    const ImVec2 size = {max.x - min.x, max.y - min.y };

    // Add rectangle with min, max and the colour
    ImGui::GetWindowDrawList()->AddRectFilled(min, max, backgroundColour);
    ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->monospace, UIMGUI_TEXT_UTILS_DATA->monospace->FontSize,min,
                                        ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                        begin, end, -1.0f);

    // Render an invisible button, which will act as our element
    ImGui::InvisibleButton("##code", size);
}

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
void UImGui::TextUtils::CodeInline(const TString& text, const Colour backgroundColour) noexcept
{
    CodeInline(text.c_str(), text.c_str() + text.size(), backgroundColour);
}
#endif

UImGui::TextUtils::WidgetState UImGui::TextUtils::renderWrappedTextGeneric(const char* text, const char* end, const Colour colour,
                                                                           const std::function<void(Colour)>& after,
                                                                           const std::function<void(Colour)>& before,
                                                                           const std::function<void(TextUtilsData*,
                                                                                                    const char*, const char*,
                                                                                                    Colour)>& render) noexcept
{
    const float scale = ImGui::GetIO().FontGlobalScale;
    float widthAvail = ImGui::GetContentRegionAvail().x;
    const char* endLine = text;

    if (widthAvail > 0.0f)
        endLine = ImGui::GetFont()->CalcWordWrapPositionA(scale, text, end, widthAvail);
    if (endLine > text && endLine < end)
    {
        if (isPartOfWord(*endLine))
        {
            // Get maximum line width like this because dear imgui rc 1.90.9+ deprecated these
            const float nextLineWidth = (ImGui::GetContentRegionAvail() + ImGui::GetCursorScreenPos()).x;
            const char* nextLineEnd = ImGui::GetFont()->CalcWordWrapPositionA(scale, text, end, nextLineWidth);
            if (nextLineEnd == end || (nextLineEnd <= end && !isPartOfWord(*nextLineEnd)))
                endLine = text;
        }
    }

    ImGui::PushTextWrapPos(-1.0f);
    before(colour);
    render(*getData(), text, endLine, colour);

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
        render(*getData(), text, endLine, colour);

        bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
        bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;

        after(colour);

        result = static_cast<WidgetState>(result | bHovered | bClicked);

        ImGui::PopTextWrapPos();
    }
    return result;
}
