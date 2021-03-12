#pragma once
#include <string>
#include <vector>

namespace GorillaUI::SelectionHelper
{
    void DrawSelection(std::vector<std::string>& options, int selected, std::string& out);
}