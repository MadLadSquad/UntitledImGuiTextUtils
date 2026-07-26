// This is for typeface related features such as:
// - Bold, Italic, bold + italic
// - Monospace
// - Ruby, superscript, subscript
#include "UImGuiTextUtils.hpp"

// All font calculations for this file are in the small font so small font calculations are already done here.
//
// Because dear imgui's new font API is not font-specific we're calculating the font using the pushed font size / 2.
// The font size is the height, and we're after that here too. For small fonts we want to cover half the size of the
// normal glyphs + the frame padding Y space. This is because normal glyphs have some padding already applied and also
// because we're using FramePadding.y - (the small font's size / 2) = FramePadding.y - ((FontSize / 2 + FramePadding.y) / 2)
// which gives us a nice offset that places us between the half of the font size and the half of the frame padding
#define SMALL_FONT_SIZE(x) ((ImGui::GetFontSize() / 2) + ImGui::GetStyle().FramePadding.y)

#define CUSTOM_FONT_BOILERPLATE(x, y) va_list args;             \
va_start(args, x);                                              \
customFontGenericText(fmt, UIMGUI_TEXT_UTILS_DATA->y, args);    \
va_end(args)


#define CUSTOM_FONT_BOILERPLATE_WRAPPED(x, y) va_list args;         \
va_start(args, x);                                                  \
customFontGenericTextWrapped(fmt, UIMGUI_TEXT_UTILS_DATA->y, args); \
va_end(args)

// Checks whether a text range renders no glyphs at all. Following dear imgui's convention, a null end pointer
// means that the string is null-terminated. Needed because dear imgui asserts on 0-sized InvisibleButtons, which
// every manually laid out widget in this file uses to advance the cursor
static bool isTextRangeEmpty(const char* begin, const char* end) noexcept
{
    if (begin == nullptr)
        return true;
    return end != nullptr ? begin >= end : *begin == '\0';
}

void UImGui::TextUtils::Bold(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, bold);
}

void UImGui::TextUtils::BoldV(const char* fmt, va_list list) noexcept
{
    customFontGenericText(fmt, UIMGUI_TEXT_UTILS_DATA->bold, list);
}

void UImGui::TextUtils::BoldWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, bold);
}

void UImGui::TextUtils::BoldWrappedV(const char* fmt, va_list list) noexcept
{
    customFontGenericTextWrapped(fmt, UIMGUI_TEXT_UTILS_DATA->bold, list);
}

void UImGui::TextUtils::Italic(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, italic);
}

void UImGui::TextUtils::ItalicV(const char* fmt, va_list list) noexcept
{
    customFontGenericText(fmt, UIMGUI_TEXT_UTILS_DATA->italic, list);
}

void UImGui::TextUtils::ItalicWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, italic);
}

void UImGui::TextUtils::ItalicWrappedV(const char* fmt, va_list list) noexcept
{
    customFontGenericTextWrapped(fmt, UIMGUI_TEXT_UTILS_DATA->italic, list);
}

void UImGui::TextUtils::BoldItalic(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, boldItalic);
}

void UImGui::TextUtils::BoldItalicV(const char* fmt, va_list list) noexcept
{
    customFontGenericText(fmt, UIMGUI_TEXT_UTILS_DATA->boldItalic, list);
}

void UImGui::TextUtils::BoldItalicWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, boldItalic);
}

void UImGui::TextUtils::BoldItalicWrappedV(const char* fmt, va_list list) noexcept
{
    customFontGenericTextWrapped(fmt, UIMGUI_TEXT_UTILS_DATA->boldItalic, list);
}

void UImGui::TextUtils::Monospace(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, monospace);
}

void UImGui::TextUtils::MonospaceV(const char* fmt, va_list list) noexcept
{
    customFontGenericText(fmt, UIMGUI_TEXT_UTILS_DATA->monospace, list);
}

void UImGui::TextUtils::MonospaceWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, monospace);
}

void UImGui::TextUtils::MonospaceWrappedV(const char* fmt, va_list list) noexcept
{
    customFontGenericTextWrapped(fmt, UIMGUI_TEXT_UTILS_DATA->monospace, list);
}

void UImGui::TextUtils::Small(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE(fmt, smallFont);
}

void UImGui::TextUtils::SmallV(const char* fmt, va_list list) noexcept
{
    customFontGenericText(fmt, UIMGUI_TEXT_UTILS_DATA->smallFont, list);
}

void UImGui::TextUtils::SmallWrapped(const char* fmt, ...) noexcept
{
    CUSTOM_FONT_BOILERPLATE_WRAPPED(fmt, smallFont);
}

void UImGui::TextUtils::SmallWrappedV(const char* fmt, va_list list) noexcept
{
    customFontGenericTextWrapped(fmt, UIMGUI_TEXT_UTILS_DATA->smallFont, list);
}

// The small font is the only typeface rendered at a size we compute ourselves. Every other one keeps the size dear
// imgui already has pushed, which its font API spells as 0.0f
static float customFontSize(const ImFont* font) noexcept
{
    return font == UImGui::TextUtils::getTextUtilsData()->smallFont ? SMALL_FONT_SIZE(smallFont) : 0.0f;
}

void UImGui::TextUtils::customFontGenericText(const char* fmt, ImFont* font, va_list args) noexcept
{
    ImGui::PushFont(font, customFontSize(font));
    ImGui::TextV(fmt, args);
    ImGui::PopFont();
}

void UImGui::TextUtils::customFontGenericTextWrapped(const char* fmt, ImFont* font, va_list args) noexcept
{
    ImGui::PushFont(font, customFontSize(font));
    ImGui::TextWrappedV(fmt, args);
    ImGui::PopFont();
}

void UImGui::TextUtils::Ruby(const char* textBegin, const char* textEnd, const char* annotationBegin, const char* annotationEnd, const bool bWrapAnnotation, const bool bWrapText) noexcept
{
    const bool bHasAnnotation = !isTextRangeEmpty(annotationBegin, annotationEnd);
    const bool bHasText = !isTextRangeEmpty(textBegin, textEnd);

    // Nothing to render, bail out before opening a group we'd never put an item into
    if (!bHasAnnotation && !bHasText)
        return;

    ImGui::BeginGroup();
    const auto offset = (SMALL_FONT_SIZE(smallFont) / 2);
    const float widthAvail = ImGui::GetContentRegionAvail().x;

    // The annotation is rendered first but has to wrap to the width of the main text sitting below it, so the main
    // text is measured up front. This used to travel between the 2 blocks through a static, which lagged a frame
    // behind and got overwritten by every other Ruby widget rendered in the same frame
    const float textWrapWidth = bWrapText ? widthAvail : -1.0f;
    const auto textSize = bHasText ? ImGui::CalcTextSize(textBegin, textEnd, false, textWrapWidth) : ImVec2{ 0.0f, 0.0f };

    // With no main text underneath it there's no width to match, so the annotation wraps to the space we have
    float annotationWidth = -1.0f;
    if (bWrapAnnotation)
        annotationWidth = bHasText ? std::min(textSize.x, widthAvail) : widthAvail;

    // At least one of the 2 ranges is non-empty by this point, so hash the ID out of whichever one we actually
    // have. An empty pointer pair would make dear imgui hash starting from a null address
    if (bHasText)
        ImGui::PushID(textBegin, textEnd);
    else
        ImGui::PushID(annotationBegin, annotationEnd);
    // Render
    if (bHasAnnotation)
    {
        auto min = ImGui::GetCursorScreenPos();
        min.y -= offset;

        const auto annotationSize = UIMGUI_TEXT_UTILS_DATA->smallFont->CalcTextSizeA(SMALL_FONT_SIZE(smallFont), FLT_MAX, annotationWidth, annotationBegin, annotationEnd);

        ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->smallFont, SMALL_FONT_SIZE(smallFont), min,
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            annotationBegin, annotationEnd, annotationWidth);
        // Render an invisible button, which will act as our element
        ImGui::InvisibleButton("##rubyannotation", annotationSize);
    }
    if (bHasText)
    {
        // Without an annotation there's no item above us to align to, so start at the cursor instead
        auto min = ImGui::GetCursorScreenPos();
        if (bHasAnnotation)
        {
            min = ImGui::GetItemRectMin();
            min.y += offset;
        }

        ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(),
#if IMGUI_VERSION_NUM > 19197
                                            ImGui::GetFontSize(),
#else
                                            ImGui::GetFont()->FontSize,
#endif
                                            min,
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            textBegin, textEnd, textWrapWidth);
        // Render an invisible button, which will act as our element
        ImGui::InvisibleButton("##ruby", textSize);
    }
    ImGui::PopID();
    ImGui::EndGroup();
}

#ifndef UIMGUI_TEXT_UTILS_DISABLE_STRING
void UImGui::TextUtils::Ruby(const TString& text, const TString& annotation, const bool bWrapAnnotation, const bool bWrapText) noexcept
{
    Ruby(text.c_str(), text.c_str() + text.size(), annotation.c_str(), annotation.c_str() + annotation.size(), bWrapAnnotation, bWrapText);
}


void UImGui::TextUtils::SubSuperscript(const TString& subscript, const TString& superscript) noexcept
{
    SubSuperscript(subscript.c_str(), subscript.c_str() + subscript.size(),
                   superscript.c_str(), superscript.c_str() + superscript.size());
}
#endif

void UImGui::TextUtils::SubSuperscript(const char* subscriptBegin, const char* subscriptEnd,
                                       const char* superscriptBegin, const char* superscriptEnd) noexcept
{
    const bool bHasSubscript = !isTextRangeEmpty(subscriptBegin, subscriptEnd);
    const bool bHasSuperscript = !isTextRangeEmpty(superscriptBegin, superscriptEnd);

    // Setting either text block to an empty string doesn't render it, so with both empty there's nothing to do
    if (!bHasSubscript && !bHasSuperscript)
        return;

    const auto offset = (SMALL_FONT_SIZE(smallFont) / 2);
    ImVec2 min = ImGui::GetCursorScreenPos();
    min.y -= offset;
    // Only hash IDs out of the ranges we actually have. An empty pointer pair would make dear imgui hash starting
    // from a null address
    if (bHasSubscript)
        ImGui::PushID(subscriptBegin, subscriptEnd);
    if (bHasSuperscript)
        ImGui::PushID(superscriptBegin, superscriptEnd);
    if (bHasSuperscript)
    {
        const auto superscriptTextSize = UIMGUI_TEXT_UTILS_DATA->smallFont->CalcTextSizeA(SMALL_FONT_SIZE(smallFont), FLT_MAX,
                                                                                -1.0f, superscriptBegin, superscriptEnd);

        const ImVec2 max = { min.x + superscriptTextSize.x, min.y + superscriptTextSize.y + ImGui::GetStyle().FramePadding.y - offset };
        const ImVec2 size = { max.x - min.x, max.y - min.y };
        ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->smallFont, SMALL_FONT_SIZE(smallFont), min,
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            superscriptBegin, superscriptEnd, -1.0f);

        ImGui::InvisibleButton("##superscript", size);
    }
    if (bHasSubscript)
    {
        // Only join the subscript to the superscript if the latter was actually rendered
        if (bHasSuperscript)
            ImGui::SameLine();

        const auto subscriptTextSize = UIMGUI_TEXT_UTILS_DATA->smallFont->CalcTextSizeA(SMALL_FONT_SIZE(smallFont), FLT_MAX,
                                                                                -1.0f, subscriptBegin, subscriptEnd);

        const ImVec2 max = { min.x + subscriptTextSize.x, min.y + subscriptTextSize.y + ImGui::GetStyle().FramePadding.y - offset };
        const ImVec2 size = { max.x - min.x, max.y - min.y };

        ImGui::GetWindowDrawList()->AddText(UIMGUI_TEXT_UTILS_DATA->smallFont, SMALL_FONT_SIZE(smallFont), { min.x, max.y },
                                            ImGui::ColorConvertFloat4ToU32(ImGui::GetStyle().Colors[ImGuiCol_Text]),
                                            subscriptBegin, subscriptEnd, -1.0f);

        ImGui::InvisibleButton("##subscript", size);
    }
    if (bHasSuperscript)
        ImGui::PopID();
    if (bHasSubscript)
        ImGui::PopID();
}
