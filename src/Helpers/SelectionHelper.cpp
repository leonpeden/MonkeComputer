#include "Helpers/SelectionHelper.hpp"

namespace GorillaUI::SelectionHelper
{
    void DrawSelection(std::vector<std::string>& options, int selected, std::string& out)
    {
        int size = options.size();
        for (int i = 0; i < size; i++)
        {
            out += (selected == i ? "<color=#ed6540>></color> " : "  ");
            out += options[i];
            out += "\n";
        }
    }
}