#pragma once
#ifdef __has_include
    #if !__has_include(<imgui.h>)
        #error "Couldn't find imgui.h in the header include path, please add it to the path!"
    #endif // !<imgui.h>
#endif
#include <imgui.h>
#include <functional>
#include "UImGuiString.hpp"
#include "Common.h"

// To shorten things somewhat
#define UIMGUI_TEXT_COLOUR getDefaultTextColour()

#define UIMGUI_TEXT_UTILS_DATA (*getData())

namespace UImGui
{
    struct MLS_PUBLIC_API TextUtilsData
    {
        ImFont* bold;
        ImFont* italic;
        ImFont* boldItalic;
        ImFont* monospace;
        ImFont* smallFont;

        std::function<void(const char*)> defaultLinkClickEvent = [](const char*) -> void {};
    };

    class MLS_PUBLIC_API TextUtils
    {
    public:
        typedef UImGui_TextUtils_WidgetState WidgetState;

        struct Colour
        {
        public:
            Colour() noexcept = default;
            Colour(const UImGui_TextUtils_Colour& col) noexcept : data(col) {};
            Colour(const UImGui_TextUtils_Colour&& col) noexcept : data(col) {};
            Colour(ImVec4 col) noexcept : data(*reinterpret_cast<UImGui_TextUtils_Colour*>(&col)) {};
            Colour(ImU32 col) noexcept;

            operator UImGui_TextUtils_Colour() const noexcept;
            operator ImU32() const noexcept;
            operator ImVec4() const noexcept;
        private:
            mutable UImGui_TextUtils_Colour data{};
        };

        static Colour getDefaultTextColour() noexcept;

        static void initTextUtilsData(TextUtilsData* data) noexcept;
        static TextUtilsData* getTextUtilsData() noexcept;

        // Renders bold text
        static void Bold(const char* fmt, ...) noexcept;
        static void BoldV(const char* fmt, va_list list) noexcept;

        // Renders bold text with word wrapping
        static void BoldWrapped(const char* fmt, ...) noexcept;
        static void BoldWrappedV(const char* fmt, va_list list) noexcept;

        // Renders bold text
        static void Italic(const char* fmt, ...) noexcept;
        static void ItalicV(const char* fmt, va_list list) noexcept;

        // Renders bold text with word wrapping
        static void ItalicWrapped(const char* fmt, ...) noexcept;
        static void ItalicWrappedV(const char* fmt, va_list list) noexcept;

        // Renders bold text
        static void BoldItalic(const char* fmt, ...) noexcept;
        static void BoldItalicV(const char* fmt, va_list list) noexcept;

        // Renders bold text with word wrapping
        static void BoldItalicWrapped(const char* fmt, ...) noexcept;
        static void BoldItalicWrappedV(const char* fmt, va_list list) noexcept;

        // Renders monospace text
        static void Monospace(const char* fmt, ...) noexcept;
        static void MonospaceV(const char* fmt, va_list list) noexcept;

        // Renders monospace text with word wrapping
        static void MonospaceWrapped(const char* fmt, ...) noexcept;
        static void MonospaceWrappedV(const char* fmt, va_list list) noexcept;

        // Renders small text
        static void Small(const char* fmt, ...) noexcept;
        static void SmallV(const char* fmt, va_list list) noexcept;

        // Renders small text with word wrapping
        static void SmallWrapped(const char* fmt, ...) noexcept;
        static void SmallWrappedV(const char* fmt, va_list list) noexcept;

        /**
         * @brief Renders superscript and subscript characters in 1 function. This is because it's hard to render both
         * due to coordinate shifts, which is needed if we want to e.g. render mathematical syntax for
         * combinations, which looks like this:
         *  n
         * C
         *  k
         * Setting either text blocks as an empty string will not render it.
         * @param subscriptBegin Pointer to the first element of the subscript text array
         * @param subscriptEnd Pointer to the last element of the subscript text array
         * @param superscriptBegin Pointer to the first element of the superscript text array
         * @param superscriptEnd Pointer to the last element of the superscript text array
         */
        static void SubSuperscript(const char* subscriptBegin, const char* subscriptEnd,
                                   const char* superscriptBegin, const char* superscriptEnd) noexcept;

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
        // C++ TString variant of the normal SubSuperscript function
        static void SubSuperscript(const TString& subscript, const TString& superscript) noexcept;
#endif
        /**
         * @brief Renders ruby text, small text on top of a word. Commonly used for Furigana, a way of annotating
         * Japanese Kanji. Looks like this:
         * かん　じ
         *  漢　 字
         * Where the Hiragana above the kanji is rendered with the small font.
         * @param textBegin - Pointer to the start of the main text string, 漢字 in our example
         * @param textEnd - Pointer to the end of the main text string, 漢字 in our example
         * @param annotationBegin - Pointer to the start of the main annotation text string, かんじ in our example
         * @param annotationEnd - Pointer to the end of the main annotation text string, かんじ in our example
         * @param bWrapAnnotation - Whether to apply word wrapping to the annotation text, かんじ in our example
         * @param bWrapText - Whether to apply word wrapping to the main text, 漢字 in our example
         */
        static void Ruby(const char* textBegin, const char* textEnd,
                         const char* annotationBegin, const char* annotationEnd,
                         bool bWrapAnnotation = true, bool bWrapText = false) noexcept;

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
        // C++ TString version of the normal Ruby function
        static void Ruby(const TString& text, const TString& annotation,
                         bool bWrapAnnotation = true, bool bWrapText = false) noexcept;
#endif

        /**
         * @brief Underlines the element above
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_TEXT_COLOUR macro
         */
        static void Underline(Colour colour = UIMGUI_TEXT_COLOUR) noexcept;

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
        static WidgetState Underline(const char* fmt, const Colour colour = UIMGUI_TEXT_COLOUR, Args... args) noexcept
        {
            ImGui::Text(fmt, (args)...);
            const auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
            const auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
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
        static WidgetState UnderlineWrapped(const char* text, const char* end, Colour colour = UIMGUI_TEXT_COLOUR) noexcept;

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
        // TString wrapper on top of UnderlineWrapped
        static WidgetState UnderlineWrapped(const TString& text, Colour colour = UIMGUI_TEXT_COLOUR) noexcept;
#endif

        /**
         * @brief Cross out the element above
         * @param colour - Colour of the line, defaults to the current text colour, represented by the
         * UIMGUI_TEXT_COLOUR macro
         */
        static void Strikethrough(Colour colour = UIMGUI_TEXT_COLOUR) noexcept;

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
        static WidgetState Strikethrough(const char* fmt, const Colour colour = UIMGUI_TEXT_COLOUR, Args... args) noexcept
        {
            ImGui::Text(fmt, (args)...);
            const auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
            const auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
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
        static WidgetState StrikethroughWrapped(const char* text, const char* end, Colour colour = UIMGUI_TEXT_COLOUR) noexcept;

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
        // TString wrapper on top of StrikethroughWrapped
        static WidgetState StrikethroughWrapped(const TString& text, Colour colour = UIMGUI_TEXT_COLOUR) noexcept;
#endif


        /**
         * @brief Renders a link without text wrapping
         * @param text - The text for the link
         * @param colour - The colour of the link, defaults to UIMGUI_LINK_TEXT_UNVISITED
         * @param clicked - A callback to be called if the link is clicked, defaults to TextUtilsData::defaultLinkClickEvent
         */
        static void Link(const char* text, Colour colour = UIMGUI_LINK_TEXT_UNVISITED,
                         const std::function<void(const char* link)>& clicked = (*getData())->defaultLinkClickEvent) noexcept;

        /**
         * @brief Renders a link with text wrapping
         * @param text - The text for the link
         * @param end - The end position of the text
         * @param colour - The colour of the link, defaults to UIMGUI_LINK_TEXT_UNVISITED
         * @param clicked - A callback to be called if the link is clicked, defaults to TextUtilsData::defaultLinkClickEvent
         */
        static void LinkWrapped(const char* text, const char* end, Colour colour = UIMGUI_LINK_TEXT_UNVISITED,
                                const std::function<void(const char* link)>& clicked = (*getData())->defaultLinkClickEvent) noexcept;

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
        // TString wrapper on top of LinkWrapped
        static void LinkWrapped(const TString& text, Colour colour = UIMGUI_LINK_TEXT_UNVISITED,
                                const std::function<void(const char* link)>& clicked = (*getData())->defaultLinkClickEvent) noexcept;
#endif

        /**
         * @brief Highlight the element above
         * @param colour - Colour of the highlight, defaults to the default highlight text colour, represented by the
         * UIMGUI_HIGHLIGHT_TEXT_COLOUR macro
         */
        static void Highlight(Colour colour = UIMGUI_HIGHLIGHT_TEXT_COLOUR) noexcept;

        /**
         * @brief Abstraction on top of ImGui::Text for highlighted text. Renders highlighted text without word wrapping
         * @tparam Args - A templated variadic list of elements to be formatted by the format string
         * @param fmt - The format string
         * @param colour - Colour of the highlight, defaults to the default highlight text colour, represented by the
         * UIMGUI_HIGHLIGHT_TEXT_COLOUR macro
         * @param args - Variadic arguments passed to ImGui::Text
         * @return State of the text, represented using the WidgetState bitmask
         */
        template<typename ...Args>
        static WidgetState Highlight(const char* fmt, const Colour colour = UIMGUI_HIGHLIGHT_TEXT_COLOUR, Args... args) noexcept
        {
            ImGui::Text(fmt, (args)...);
            const auto bHovered = ImGui::IsItemHovered() ? UIMGUI_TEXT_UTILS_WIDGET_STATE_HOVERED : 0;
            const auto bClicked = ImGui::IsMouseClicked(ImGuiMouseButton_Left) ? UIMGUI_TEXT_UTILS_WIDGET_STATE_CLICKED : 0;
            Highlight(colour);

            return static_cast<WidgetState>(bHovered | bClicked);
        }

        /**
         * @brief Renders highlighted text with word wrapping
         * @param text - The text pointer
         * @param end - Text pointer to the end of the text
         * @param colour - Colour of the highlight, defaults to the default highlight text colour, represented by the
         * UIMGUI_HIGHLIGHT_TEXT_COLOUR macro
         * @return State of the text, represented using the WidgetState bitmask
         */
        static WidgetState HighlightWrapped(const char* text, const char* end, Colour colour = UIMGUI_HIGHLIGHT_TEXT_COLOUR) noexcept;

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
        // TString wrapper on top of HighlightWrapped
        static WidgetState HighlightWrapped(const TString& text, Colour colour = UIMGUI_HIGHLIGHT_TEXT_COLOUR) noexcept;
#endif

        /**
         * @brief Renders a single blockquote rectangle
         * @param colour - Colour of the blockquote, defaults to the default blockquote colour, represented by the
         * UIMGUI_BLOCKQUOTE_TEXT_COLOUR macro
         */
        static void Blockquote(Colour colour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR) noexcept;

        /**
         * @brief Abstraction on top of ImGui::Text for blockquotes. Renders text without word wrapping
         * @tparam Args - A templated variadic list of elements to be formatted by the format string
         * @param fmt - The format string
         * @param colour - Colour of the blockquote, defaults to the default blockquote colour, represented by the
         * UIMGUI_BLOCKQUOTE_TEXT_COLOUR macro
         * @param args - Variadic arguments passed to ImGui::Text
         */
        template<typename ...Args>
        static void Blockquote(const char* fmt, const Colour colour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR, Args... args) noexcept
        {
            Blockquote(colour);
            ImGui::SameLine();
            ImGui::Text(fmt, (args)...);
        }

        /**
         * @brief Renders text in blockquote with word wrapping
         * @param text - The text pointer
         * @param end - Text pointer to the end of the text
         * @param colour - Colour of the blockquote, defaults to the default blockquote colour, represented by the
         * UIMGUI_BLOCKQUOTE_TEXT_COLOUR macro
         */
        static void BlockquoteWrapped(const char* text, const char* end, Colour colour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR) noexcept;

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
        // TString wrapper on top of HighlightWrapped
        static void BlockquoteWrapped(const TString& text, Colour colour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR) noexcept;
#endif

        /**
         * @brief Renders text code as a markdown code block
         * @param begin - Pointer to the beginning of the string
         * @param end - Pointer to the end of the string
         * @param bWrapText - Whether to enable word wrapping
         * @param backgroundColour - The background colour of the code block, defaults to UIMGUI_BLOCKQUOTE_TEXT_COLOUR
         */
        static void CodeBlock(const char* begin, const char* end, bool bWrapText,
                                Colour backgroundColour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR) noexcept;

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
        // C++ TString abstraction on top of the normal CodeBlock function
        static void CodeBlock(const TString& text, bool bWrapText,
                                Colour backgroundColour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR) noexcept;
#endif


        /**
         * @brief Renders inline code
         * @param begin - Pointer to the beginning of the string
         * @param end - Pointer to the end of the string
         * @param backgroundColour - The background colour of the code block, defaults to UIMGUI_BLOCKQUOTE_TEXT_COLOUR
         */
        static void CodeInline(const char* begin, const char* end, Colour backgroundColour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR) noexcept;

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
        // C++ TString abstraction on top of the normal CodeInline function
        static void CodeInline(const TString& text, Colour backgroundColour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR) noexcept;
#endif

        /**
         * @brief Renders inline code with word wrapping
         * @param begin - Pointer to the beginning of the string
         * @param end - Pointer to the end of the string
         * @param backgroundColour - The background colour of the code block, defaults to UIMGUI_BLOCKQUOTE_TEXT_COLOUR
         */
        static void CodeInlineWrapped(const char* begin, const char* end, Colour backgroundColour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR) noexcept;

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
        // C++ TString abstraction on top of the normal CodeInlineWrapped function
        static void CodeInlineWrapped(const TString& text, Colour backgroundColour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR) noexcept;
#endif

        // dear imgui's ImGui::ShowDemoWindow equivalent. While the only argument is a void*, treat it as a boolean
        static void ShowDemoWindow(void* bOpen = nullptr) noexcept;
    private:
        static void customFontGenericText(const char* fmt, ImFont* font, va_list args) noexcept;
        static void customFontGenericTextWrapped(const char* fmt, ImFont* font, va_list args) noexcept;

        static bool isPartOfWord(char character) noexcept;
        static TextUtilsData** getData() noexcept;

        static WidgetState renderWrappedTextGeneric(const char* text, const char* end, Colour colour,
                                                    const std::function<void(Colour)>& after,
                                                    const std::function<void(Colour)>& before,
                                                    const std::function<void(UImGui::TextUtilsData* data, const char* s, const char* e, Colour backgroundColour)>& render =
                                                            [](UImGui::TextUtilsData* data, const char* s, const char* e, Colour) -> void {
                                                                ImGui::TextUnformatted(s, e);
                                                            }) noexcept;
    };
}