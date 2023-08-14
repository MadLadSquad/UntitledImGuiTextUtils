#include "UImGuiTextUtils.hpp"

UImGui::TextUtilsData** UImGui::TextUtils::getData() noexcept
{
    static TextUtilsData* data;
    return &data;
}

void UImGui::TextUtils::initTextUtilsData(UImGui::TextUtilsData* data) noexcept
{
    *getData() = data;
}

void UImGui::TextUtils::ShowDemoWindow(void* bOpen) noexcept
{
    ImGui::Begin("UntitledImGuiTextUtils Demo Window", (bool*)bOpen);

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
        SubSuperscript("3", "6");
        ImGui::SameLine();
        ImGui::Text("= 20");

        ImGui::PopStyleVar(2);

        ImGui::SeparatorText("Ruby text");
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });

        Ruby("Kanji", "han4zi4");
        ImGui::PopStyleVar(2);

        ImGui::SeparatorText("* Note");
        ImGui::Text("All widgets here were rendered with");
        CodeInline("ImGuiStyleVar_WindowPadding");
        ImGui::SameLine();
        ImGui::Text("and");
        ImGui::SameLine();
        CodeInline("ImGuiStyleVar_ItemSpacing");
        ImGui::SameLine();
        ImGui::Text("set to");
        ImGui::SameLine();
        CodeInline("{ 0.0f, 0.0f }");
    }

    if (ImGui::CollapsingHeader("Rich text"))
    {
        static ImVec4 underlineColour = ImGui::GetStyle().Colors[ImGuiCol_Text];
        static ImVec4 strikethroughColour = ImGui::GetStyle().Colors[ImGuiCol_Text];
        static ImVec4 linkColour = ImGui::ColorConvertU32ToFloat4(UIMGUI_LINK_TEXT_UNVISITED);
        static ImVec4 highlightColour = ImGui::ColorConvertU32ToFloat4(UIMGUI_HIGHLIGHT_TEXT_COLOUR);

        ImGui::SeparatorText("Underlined text");
        ImGui::ColorEdit4("Underline colour", (float*)&underlineColour);

        ImGui::TextWrapped("Normal text with underlining after it's rendered");
        Underline(underlineColour);
        Underline("Underline wrapper with formatting: %d", underlineColour, i);
        UnderlineWrapped("Underline with text wrapping. The quick brown fox jumps over the lazy dog. "
                         "The quick brown fox jumps over the lazy dog.", underlineColour);

        ImGui::SeparatorText("Strikethrough");
        ImGui::ColorEdit4("Strikethrough colour", (float*)&strikethroughColour);

        ImGui::TextWrapped("Normal text with strikethrough after it's rendered");
        Strikethrough(strikethroughColour);
        Strikethrough("Strikethrough wrapper with formatting: %d", strikethroughColour, i);
        StrikethroughWrapped("Strikethrough with text wrapping. The quick brown fox jumps over the lazy dog. "
                             "The quick brown fox jumps over the lazy dog.", strikethroughColour);

        ImGui::SeparatorText("Links");
        ImGui::ColorEdit4("Link colour", (float*)&linkColour);

        Link("Link", linkColour);
        LinkWrapped("Link with text wrapping. The quick brown fox jumps over the lazy dog. "
                             "The quick brown fox jumps over the lazy dog.", linkColour);

        ImGui::SeparatorText("Highlight");
        ImGui::ColorEdit4("Highlight colour", (float*)&highlightColour);

        ImGui::TextWrapped("Normal text with highlight after it's rendered");
        Highlight(highlightColour);
        Highlight("Highlight wrapper with formatting: %d", highlightColour, i);
        HighlightWrapped("Highlight with text wrapping. The quick brown fox jumps over the lazy dog. "
                             "The quick brown fox jumps over the lazy dog.", highlightColour);
    }

    if (ImGui::CollapsingHeader("Code"))
    {
        static ImVec4 backgroundColour = ImGui::ColorConvertU32ToFloat4(UIMGUI_BLOCKQUOTE_TEXT_COLOUR);
        ImGui::ColorEdit4("Code background colour", (float*)&backgroundColour);

        ImGui::SeparatorText("Code blocks");
        static bool bWrapCodeBlock = false;
        ImGui::Checkbox("Code block text wrapping", &bWrapCodeBlock);
        CodeBlock(R"(#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
)", bWrapCodeBlock, backgroundColour);

        ImGui::SeparatorText("Inline code");
        CodeInline("This can be in the middle of a sentence");
        CodeInlineWrapped("This is inline code with wrapping. The quick brown fox jumps over the lazy dog."
                          "The quick brown fox jumps over the lazy dog.");
    }

    if (ImGui::CollapsingHeader("Blockquotes"))
    {
        static ImVec4 backgroundColour = ImGui::ColorConvertU32ToFloat4(UIMGUI_BLOCKQUOTE_TEXT_COLOUR);
        ImGui::ColorEdit4("Blockquote colour", (float*)&backgroundColour);

        ImGui::Text("Independent blockquote rect: ");
        ImGui::SameLine();
        Blockquote(backgroundColour);

        Blockquote("Blockquote with formatting: %d", backgroundColour, i);

        BlockquoteWrapped("Blockquote with wrapping. The quick brown fox jumps over the lazy dog. "
                          "The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog",
                          backgroundColour);

    }

    ImGui::End();
}