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
        return materials->values[1]->get_color();
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

    void CustomScreenInfo::set_texture(Texture2D* tex)
    {
        static Il2CppString* mainTex = il2cpp_utils::createcsstr("_MainTex");
        Object::DestroyImmediate(get_texture());
        materials->values[1]->SetTexture(mainTex, tex);
    }

    Texture2D* CustomScreenInfo::get_texture()
    {
        static Il2CppString* mainTex = il2cpp_utils::createcsstr("_MainTex");
        return (Texture2D*)materials->values[1]->GetTexture(mainTex);
    }
}