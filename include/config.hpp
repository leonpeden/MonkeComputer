#pragma once
#include "UnityEngine/Color.hpp"

struct config_t {
    UnityEngine::Color screenColor = {0.0f, 0.0f, 0.0f};
};

extern config_t config;
bool LoadConfig();
void SaveConfig();