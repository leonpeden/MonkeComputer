#include "Utils/LoadUtils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
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

        std::vector<char> charvector = readbytes(filePath);
        std::vector<uint8_t>& bytevector = *reinterpret_cast<std::vector<uint8_t>*>(&charvector);
        Array<uint8_t>* byteArray = il2cpp_utils::vectorToArray(bytevector);
        loadImage(texture, byteArray, false);
        Object::DontDestroyOnLoad(texture);
        return texture;
    }
}