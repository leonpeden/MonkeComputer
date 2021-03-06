#pragma once
#include "beatsaber-hook/shared/utils/il2cpp-type-check.hpp"

// UnityEngine.Color
typedef struct Color {
    float r;
    float g;
    float b;
    float a;
} Color;

// UnityEngine.Vector2
typedef struct Vector2 {
    float x;
    float y;
} Vector2;

// UnityEngine.Vector3
typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

// UnityEngine.Vector4
typedef struct Vector4 {
    float x;
    float y;
    float z;
    float w;
} Vector4;

// UnityEngine.Quaternion
typedef struct Quaternion {
    float x;
    float y;
    float z;
    float w;
} Quaternion;

// UnityEngine.Rect
typedef struct Rect {
    float m_XMin;
    float m_YMin;
    float m_Width;
    float m_Height;
} Rect;

// UnityEngine.Scene
typedef struct Scene {
    int m_Handle;
} Scene;

DEFINE_IL2CPP_ARG_TYPE(Color, "UnityEngine", "Color");
DEFINE_IL2CPP_ARG_TYPE(Vector2, "UnityEngine", "Vector2");
DEFINE_IL2CPP_ARG_TYPE(Vector3, "UnityEngine", "Vector3");
DEFINE_IL2CPP_ARG_TYPE(Vector4, "UnityEngine", "Vector4");
DEFINE_IL2CPP_ARG_TYPE(Quaternion, "UnityEngine", "Quaternion");
DEFINE_IL2CPP_ARG_TYPE(Rect, "UnityEngine", "Rect");
DEFINE_IL2CPP_ARG_TYPE(Scene, "UnityEngine.SceneManagement", "Scene");