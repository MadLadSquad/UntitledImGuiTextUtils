#include "UImGuiTextUtils.hpp"

UImGui::TextUtilsData** UImGui::TextUtils::getData() noexcept
{
    static TextUtilsData* data;
    return &data;
}

UImGui::TextUtils::Colour UImGui::TextUtils::getDefaultTextColour() noexcept
{
    return ImGui::GetColorU32(ImGui::GetStyle().Colors[ImGuiCol_Text]);
}

void UImGui::TextUtils::initTextUtilsData(TextUtilsData* data) noexcept
{
    *getData() = data;
}

UImGui::TextUtilsData* UImGui::TextUtils::getTextUtilsData() noexcept
{
    return *getData();
}

void UImGui::TextUtils::ShowDemoWindow(void* bOpen) noexcept
{
    ImGui::Begin("UntitledImGuiTextUtils Demo Window", static_cast<bool*>(bOpen));

    ImGui::TextWrapped("Welcome to the UntitledImGuiTextUtils demo. This window showcases all widgets.");

    static int i = 0;

    ImGui::SliderInt("Modify integer", &i, 0, 200);
    if (ImGui::CollapsingHeader("Text Rendering"))
    {
        ImGui::SeparatorText("Rendering using additional fonts");
        ImGui::SliderInt("Modify integer", &i, 0, 200);

        Bold("This is bold text, it has formatting: %d.", i);
        Italic("This is italic text, it has formatting: %d.", i);
        BoldItalic("This is bold italic text, it has formatting: %d.", i);
        Monospace("This is monospaced text, it has formatting: %d.", i);
        Small("This is small text, it has formatting: %d.", i);


        ImGui::SeparatorText("Versions with text wrapping");

        BoldWrapped("This is bold text, it has formatting: %d. The quick brown fox jumps over the lazy dog. "
                    "The quick brown fox jumps over the lazy dog", i);
        ItalicWrapped("This is italic text, it has formatting: %d. The quick brown fox jumps over the lazy dog. "
                      "The quick brown fox jumps over the lazy dog", i);
        BoldItalicWrapped("This is bold italic text, it has formatting: %d. The quick brown fox jumps over the "
                          "lazy dog. The quick brown fox jumps over the lazy dog", i);
        MonospaceWrapped("This is monospaced text, it has formatting: %d. The quick brown fox jumps over the lazy"
                         " dog. The quick brown fox jumps over the lazy dog", i);
        SmallWrapped("This is small text, it has formatting: %d. The quick brown fox jumps over the lazy dog. "
                     "The quick brown fox jumps over the lazy dog", i);
    }

    if (ImGui::CollapsingHeader("Annotations"))
    {

        ImGui::SeparatorText("Subscript and superscript");

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });

        ImGui::Text("C");
        ImGui::SameLine();
        SubSuperscript("3", nullptr, "6", nullptr);
        ImGui::SameLine();
        ImGui::Text("= 20");

        ImGui::PopStyleVar(2);

        ImGui::SeparatorText("Ruby text");
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });

        Ruby("Kanji", nullptr, "han4zi4", nullptr);
        ImGui::PopStyleVar(2);

        ImGui::SeparatorText("* Note");
        ImGui::Text("All widgets here were rendered with");
        CodeInline("ImGuiStyleVar_WindowPadding", nullptr);
        ImGui::SameLine();
        ImGui::Text("and");
        ImGui::SameLine();
        CodeInline("ImGuiStyleVar_ItemSpacing", nullptr);
        ImGui::SameLine();
        ImGui::Text("set to");
        ImGui::SameLine();
        CodeInline("{ 0.0f, 0.0f }", nullptr);
    }

    if (ImGui::CollapsingHeader("Rich text"))
    {
        static auto underlineColour =       ImGui::GetColorU32(ImGui::GetStyle().Colors[ImGuiCol_Text]);
        static auto strikethroughColour =   ImGui::GetColorU32(ImGui::GetStyle().Colors[ImGuiCol_Text]);
        static auto linkColour =            ImGui::GetColorU32(ImGui::ColorConvertU32ToFloat4(UIMGUI_LINK_TEXT_UNVISITED));
        static auto highlightColour =       ImGui::GetColorU32(ImGui::ColorConvertU32ToFloat4(UIMGUI_HIGHLIGHT_TEXT_COLOUR));

        ImGui::SeparatorText("Underlined text");
        ImGui::ColorEdit4("Underline colour", reinterpret_cast<float*>(&underlineColour));

        ImGui::TextWrapped("Normal text with underlining after it's rendered");
        Underline(underlineColour);
        Underline("Underline wrapper with formatting: %d", underlineColour, i);
        UnderlineWrapped("Underline with text wrapping. The quick brown fox jumps over the lazy dog. "
                         "The quick brown fox jumps over the lazy dog.", nullptr, underlineColour);

        ImGui::SeparatorText("Strikethrough");
        ImGui::ColorEdit4("Strikethrough colour", reinterpret_cast<float*>(&strikethroughColour));

        ImGui::TextWrapped("Normal text with strikethrough after it's rendered");
        Strikethrough(strikethroughColour);
        Strikethrough("Strikethrough wrapper with formatting: %d", strikethroughColour, i);
        StrikethroughWrapped("Strikethrough with text wrapping. The quick brown fox jumps over the lazy dog. "
                             "The quick brown fox jumps over the lazy dog.", nullptr, strikethroughColour);

        ImGui::SeparatorText("Links");
        ImGui::ColorEdit4("Link colour", reinterpret_cast<float*>(&linkColour));

        Link("Link", linkColour);
        LinkWrapped("Link with text wrapping. The quick brown fox jumps over the lazy dog. "
                             "The quick brown fox jumps over the lazy dog.", nullptr, linkColour);

        ImGui::SeparatorText("Highlight");
        ImGui::ColorEdit4("Highlight colour", reinterpret_cast<float*>(&highlightColour));

        ImGui::TextWrapped("Normal text with highlight after it's rendered");
        Highlight(highlightColour);
        Highlight("Highlight wrapper with formatting: %d", highlightColour, i);
        HighlightWrapped("Highlight with text wrapping. The quick brown fox jumps over the lazy dog. "
                             "The quick brown fox jumps over the lazy dog.", nullptr, highlightColour);
    }

    if (ImGui::CollapsingHeader("Code"))
    {
        static auto backgroundColour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR;
        ImGui::ColorEdit4("Code background colour", reinterpret_cast<float*>(&backgroundColour));

        ImGui::SeparatorText("Code blocks");
        static bool bWrapCodeBlock = false;
        ImGui::Checkbox("Code block text wrapping", &bWrapCodeBlock);
        CodeBlock(R"(#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
)", nullptr, bWrapCodeBlock, backgroundColour);

        ImGui::SeparatorText("Inline code");
        CodeInline("This can be in the middle of a sentence", nullptr);
        CodeInlineWrapped("This is inline code with wrapping. The quick brown fox jumps over the lazy dog."
                          "The quick brown fox jumps over the lazy dog.", nullptr);
    }

    if (ImGui::CollapsingHeader("Blockquotes"))
    {
        static auto backgroundColour = UIMGUI_BLOCKQUOTE_TEXT_COLOUR;
        ImGui::ColorEdit4("Blockquote colour", reinterpret_cast<float*>(&backgroundColour));

        ImGui::Text("Independent blockquote rect: ");
        ImGui::SameLine();
        Blockquote(backgroundColour);

        Blockquote("Blockquote with formatting: %d", backgroundColour, i);

        BlockquoteWrapped("Blockquote with wrapping. The quick brown fox jumps over the lazy dog. "
                          "The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog",
                    nullptr,backgroundColour);

    }

    ImGui::End();
}
