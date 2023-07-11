#include "UImGuiTextUtils.hpp"

UImGui::TextUtilsData& UImGui::TextUtils::getData() noexcept
{
    static TextUtilsData data;
    return data;
}

void UImGui::TextUtils::initTextUtilsData(const UImGui::TextUtilsData& data) noexcept
{
    getData() = data;
}