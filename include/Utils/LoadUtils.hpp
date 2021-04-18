#pragma once

#include <string>
#include "UnityEngine/Texture2D.hpp"

namespace LoadUtils
{
    UnityEngine::Texture2D* LoadTextureFromFile(std::string filePath);
}