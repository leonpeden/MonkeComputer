#include "ViewLib/CustomScreenInfo.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

using namespace UnityEngine;

namespace GorillaUI
{
    void CustomScreenInfo::set_fontSize(int size)
    {
        text->set_fontSize(size);
    }
    
    int CustomScreenInfo::get_fontSize()
    {
        return text->get_fontSize();
    }

    void CustomScreenInfo::set_color(Color color)
    {
        materials->values[1]->set_color(color);
    }

    Color CustomScreenInfo::get_color()
    {
        return *il2cpp_utils::RunMethod<Color>(materials->values[1], "get_color");
    }

    void CustomScreenInfo::set_text(std::string newText)
    {
        text->set_text(il2cpp_utils::createcsstr(newText));
    }

    std::string CustomScreenInfo::get_text()
    {
        Il2CppString* csString = text->get_text();
        return to_utf8(csstrtostr(csString));
    }
}