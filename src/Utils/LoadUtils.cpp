#include "Utils/LoadUtils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include <fstream>

using namespace UnityEngine;

extern Logger& getLogger();

namespace LoadUtils
{
    Texture2D* LoadTextureFromFile(std::string filePath)
    {
        if (!fileexists(filePath))
        {
            getLogger().info("Requested file %s did not exist", filePath.c_str());
            return nullptr;
        }
        getLogger().info("Loading image from file %s", filePath.c_str());
        Texture2D* texture = Texture2D::New_ctor(0, 0, 4, false);
        using LoadImage = function_ptr_t<unsigned int, Texture2D*, Array<uint8_t>*, bool>;
        static LoadImage loadImage = reinterpret_cast<LoadImage>(il2cpp_functions::resolve_icall("UnityEngine.ImageConversion::LoadImage"));

        std::ifstream instream(filePath, std::ios::in | std::ios::binary);
        std::vector<uint8_t> data((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());
        Array<uint8_t>* bytes = il2cpp_utils::vectorToArray(data);

        loadImage(texture, bytes, false);
        Object::DontDestroyOnLoad(texture);
        return texture;
    }
}