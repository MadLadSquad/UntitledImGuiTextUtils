#pragma once
#include <imgui.h>
#include <functional>
#include <string>

// To shorten things somewhat
#define UIMGUI_TEXT_COLOUR ImGui::GetStyle().Colors[ImGuiCol_Text]

// The default colour for links that have not been visited
#define UIMGUI_LINK_TEXT_UNVISITED IM_COL32(0, 0, 238, 255)

// The default colour for links that have been visited
#define UIMGUI_LINK_TEXT_VISITED IM_COL32(85, 26, 139, 255)

// The default highlight text colour, yellow with ~25% opacity
#define UIMGUI_HIGHLIGHT_TEXT_COLOUR IM_COL32(255, 255, 0, 64)

// The default colour for blockquote rectangle, gray
#define UIMGUI_BLOCKQUOTE_TEXT_COLOUR IM_COL32(69, 71, 90, 255)

namespace UImGui
{
    struct IMGUI_API TextUtilsData
    {
        ImFont* bold;
        ImFont* italic;
        ImFont* boldItalic;
        ImFont* monospace;
        ImFont* small;

        std::function<void(const char*)> defaultLinkClickEvent = [](const char*) -> void {};
    };

    class IMGUI_API TextUtils
    {
    public:
        enum [[maybe_unused]] WidgetState
        {
            UIMGUI_TEXT_UTILS_WIDGET_STATE_NONE = 0,
            UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED = 1 << 0,
            UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED = 1 << 1,
            UIMGUI_TEXT_UTILS_WIDGET_STATE_ALL = UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED | UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED,
        };

        static void initTextUtilsData(TextUtilsData* data) noexcept;

        // Renders bold text
        static void Bold(const char* fmt, ...) noexcept;

        // Renders bold text with word wrapping
        static void BoldWrapped(const char* fmt, ...) noexcept;

        // Renders bold text
        static void Italic(const char* fmt, ...) noexcept;

        // Renders bold text with word wrapping
        static void ItalicWrapped(const char* fmt, ...) noexcept;

        // Renders bold text
        static void BoldItalic(const char* fmt, ...) noexcept;

        // Renders bold text with word wrapping
        static void BoldItalicWrapped(const char* fmt, ...) noexcept;

        // Renders monospace text
        static void Monospace(const char* fmt, ...) noexcept;

        // Renders monospace text with word wrapping
        static void MonospaceWrapped(const char* fmt, ...) noexcept;

        // Renders small text
        static void Small(const char* fmt, ...) noexcept;

        // Renders small text with word wrapping
        static void SmallWrapped(const char* fmt, ...) noexcept;

        /**
         * @brief Renders subscript text, small text starting from the lower right corner
         * @param begin Pointer to the first element of the text array
         * @param end Pointer to the last element of the text array
         * @param bWrap Whether to enable word wrapping
         * @param verticalAlignmentDivide A magic number which the vertical position of the element is divided by to
         * achieve vertical text alignment of the text. Default is 1.5, but can be changed if needed.
         */
        static void Subscript(const char* begin, const char* end, bool bWrap, float verticalAlignmentDivide = 1.5f) noexcept;

        // C++ std::string variant of the normal subscript function
        static void Subscript(const std::string& str, bool bWrap, float verticalAlignmentDivide = 1.5f) noexcept;

        /**
         * @brief Renders superscript text, small text starting from the lower right corner
         * @param begin Pointer to the first element of the text array
         * @param end Pointer to the last element of the text array
         * @param bWrap Whether to enable word wrapping
         * @param verticalAlignmentDivide A magic number which the vertical position of the element is divided by to
         * achieve vertical text alignment of the text. Default is 1.5, but can be changed if needed.
         */
        static void Superscript(const char* begin, const char* end, bool bWrap, float verticalAlignmentDivide = 4.0f) noexcept;

        // C++ std::string variant of the normal superscript function
        static void Superscript(const std::string& str, bool bWrap, float verticalAlignmentDivide = 4.0f) noexcept;

        /**
         * @brief Underlines the element above
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_TEXT_COLOUR macro
         */
        static void Underline(ImColor colour = UIMGUI_TEXT_COLOUR) noexcept;

        /**
         * @brief Abstraction on top of ImGui::Text for underlined text. Renders underlined text without word wrapping
         * @tparam Args - A templated variadic list of elements to be formatted by the format string
         * @param fmt - The format string
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_TEXT_COLOUR macro
         * @param args - Variadic arguments passed to ImGui::Text
         * @return State of the text, represented using the WidgetState bitmask
         */
        template<typename ...Args>
        static WidgetState Underline(const char* fmt, ImColor colour = UIMGUI_TEXT_COLOUR, Args... args) noexcept
        {
            ImGui::Text(fmt, (args)...);
            auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
            auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
            Underline(colour);

            return static_cast<WidgetState>(bHovered | bClicked);
        }

        /**
         * @brief Renders underlined text with word wrapping
         * @param text - The text pointer
         * @param end - Text pointer to the end of the text
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_TEXT_COLOUR macro
         * @return State of the text, represented using the WidgetState bitmask
         */
        static WidgetState UnderlineWrapped(const char* text, const char* end, ImColor colour = UIMGUI_TEXT_COLOUR) noexcept;

        // std::string wrapper on top of UnderlineWrapped
        static WidgetState UnderlineWrapped(const std::string& text, ImColor colour = UIMGUI_TEXT_COLOUR) noexcept;

        /**
         * @brief Cross out the element above
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_TEXT_COLOUR macro
         */
        static void Strikethrough(ImColor colour = UIMGUI_TEXT_COLOUR) noexcept;

        /**
         * @brief Abstraction on top of ImGui::Text for strikethrough text. Renders strikethrough text without word wrapping
         * @tparam Args - A templated variadic list of elements to be formatted by the format string
         * @param fmt - The format string
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_TEXT_COLOUR macro
         * @param args - Variadic arguments passed to ImGui::Text
         * @return State of the text, represented using the WidgetState bitmask
         */
        template<typename ...Args>
        static WidgetState Strikethrough(const char* fmt, ImColor colour = UIMGUI_TEXT_COLOUR, Args... args) noexcept
        {
            ImGui::Text(fmt, (args)...);
            auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
            auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
            Strikethrough(colour);

            return static_cast<WidgetState>(bHovered | bClicked);
        }

        /**
         * @brief Renders strikethrough text with word wrapping
         * @param text - The text pointer
         * @param end - Text pointer to the end of the text
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_TEXT_COLOUR macro
         * @return State of the text, represented using the WidgetState bitmask
         */
        static WidgetState StrikethroughWrapped(const char* text, const char* end, ImColor colour = UIMGUI_TEXT_COLOUR) noexcept;

        // std::string wrapper on top of StrikethroughWrapped
        static WidgetState StrikethroughWrapped(const std::string& text, ImColor colour = UIMGUI_TEXT_COLOUR) noexcept;


        /**
         * @brief Renders a link without text wrapping
         * @param text - The text for the link
         * @param colour - The colour of the link, defaults to UIMGUI_LINK_TEXT_UNVISITED
         * @param clicked - A callback to be called if the link is clicked, defaults to TextUtilsData::defaultLinkClickEvent
         */
        static void Link(const char* text, ImColor colour = UIMGUI_LINK_TEXT_UNVISITED,
                         const std::function<void(const char* link)>& clicked = (*getData())->defaultLinkClickEvent) noexcept;

        /**
         * @brief Renders a link with text wrapping
         * @param text - The text for the link
         * @param end - The end position of the text
         * @param colour - The colour of the link, defaults to UIMGUI_LINK_TEXT_UNVISITED
         * @param clicked - A callback to be called if the link is clicked, defaults to TextUtilsData::defaultLinkClickEvent
         */
        static void LinkWrapped(const char* text, const char* end, ImColor colour = UIMGUI_LINK_TEXT_UNVISITED,
                                const std::function<void(const char* link)>& clicked = (*getData())->defaultLinkClickEvent) noexcept;

        // std::string wrapper on top of LinkWrapped
        static void LinkWrapped(const std::string& text, ImColor colour = UIMGUI_LINK_TEXT_UNVISITED,
                                const std::function<void(const char* link)>& clicked = (*getData())->defaultLinkClickEvent) noexcept;

        /**
         * @brief Highlight the element above
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_HIGHLIGHT_TEXT_COLOUR macro
         */
        static void Highlight(ImColor colour = UIMGUI_HIGHLIGHT_TEXT_COLOUR) noexcept;

        /**
         * @brief Abstraction on top of ImGui::Text for highlighted text. Renders highlighted text without word wrapping
         * @tparam Args - A templated variadic list of elements to be formatted by the format string
         * @param fmt - The format string
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_HIGHLIGHT_TEXT_COLOUR macro
         * @param args - Variadic arguments passed to ImGui::Text
         * @return State of the text, represented using the WidgetState bitmask
         */
        template<typename ...Args>
        static WidgetState Highlight(const char* fmt, ImColor colour = UIMGUI_HIGHLIGHT_TEXT_COLOUR, Args... args) noexcept
        {
            ImGui::Text(fmt, (args)...);
            auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
            auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
            Highlight(colour);

            return static_cast<WidgetState>(bHovered | bClicked);
        }

        /**
         * @brief Renders highlighted text with word wrapping
         * @param text - The text pointer
         * @param end - Text pointer to the end of the text
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_HIGHLIGHT_TEXT_COLOUR macro
         * @return State of the text, represented using the WidgetState bitmask
         */
        static WidgetState HighlightWrapped(const char* text, const char* end, ImColor colour = UIMGUI_HIGHLIGHT_TEXT_COLOUR) noexcept;

        // std::string wrapper on top of HighlightWrapped
        static WidgetState HighlightWrapped(const std::string& text, ImColor colour = UIMGUI_HIGHLIGHT_TEXT_COLOUR) noexcept;

        /**
         * @brief Renders a single blockquote rectangle
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_HIGHLIGHT_TEXT_COLOUR macro
         */
        static void Blockquote(ImColor colour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR) noexcept;

        /**
         * @brief Abstraction on top of ImGui::Text for blockquotes. Renders text without word wrapping
         * @tparam Args - A templated variadic list of elements to be formatted by the format string
         * @param fmt - The format string
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_HIGHLIGHT_TEXT_COLOUR macro
         * @param args - Variadic arguments passed to ImGui::Text
         * @return State of the text, represented using the WidgetState bitmask
         */
        template<typename ...Args>
        static WidgetState Blockquote(const char* fmt, ImColor colour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR, Args... args) noexcept
        {
            Blockquote(colour);
            ImGui::SameLine();
            ImGui::Text(fmt, (args)...);
            auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
            auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;

            return static_cast<WidgetState>(bHovered | bClicked);
        }

        /**
         * @brief Renders text in blockquote with word wrapping
         * @param text - The text pointer
         * @param end - Text pointer to the end of the text
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_HIGHLIGHT_TEXT_COLOUR macro
         * @return State of the text, represented using the WidgetState bitmask
         */
        static WidgetState BlockquoteWrapped(const char* text, const char* end, ImColor colour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR) noexcept;

        // std::string wrapper on top of HighlightWrapped
        static WidgetState BlockquoteWrapped(const std::string& text, ImColor colour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR) noexcept;

        /**
         * @brief Renders text in the form of a markdown keyboard shortcut
         * @tparam Args - A templated variadic list of elements to be formatted by the format string
         * @param fmt - The format string
         * @param colour - Background colour, defaults to the current text colour, represented by the
         * UIMGUI_HIGHLIGHT_TEXT_COLOUR macro
         * @param args - Variadic arguments passed to ImGui::Text
         * @return State of the text, represented using the WidgetState bitmask
         */
        template<typename ...Args>
        static WidgetState Keyboard(const char* fmt, ImColor colour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR, Args... args) noexcept
        {
            ImGui::Text(fmt, (args)...);
            ImGui::AlignTextToFramePadding();
            auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
            auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;


            ImGui::GetForegroundDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), colour, 1.0f);

            return static_cast<WidgetState>(bHovered | bClicked);
        }
    private:
        static void customFontGenericText(const char* fmt, ImFont* font, va_list args) noexcept;
        static void customFontGenericTextWrapped(const char* fmt, ImFont* font, va_list args) noexcept;

        static bool isPartOfWord(char character) noexcept;
        static TextUtilsData** getData() noexcept;

        static WidgetState renderWrappedTextGeneric(const char* text, const char* end, ImColor colour, const std::function<void(ImColor colour)>& f) noexcept;
    };
}