#pragma once
#include "typedefs.h"
struct config_t {
    Color screenColor = {0.0f, 0.0f, 0.0f};
};

extern config_t config;
bool LoadConfig();
void SaveConfig();