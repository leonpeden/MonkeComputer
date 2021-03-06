#include "Elements/Canvas.hpp"

namespace GorillaUI
{
    Canvas::Canvas()
    {
        if (!canvasPrefab) FindCanvasPrefab();
        static Il2CppString* name = il2cpp_utils::createcsstr("GUICanvas", il2cpp_utils::StringType::Manual);

        gameObject = CRASH_UNLESS(il2cpp_utils::RunMethod("UnityEngine", "Object", "Instantiate", canvasPrefab));
        CRASH_UNLESS(il2cpp_utils::RunMethod(gameObject, "set_name", name));
    }

    Canvas::Canvas(Vector3 position, Vector3 rotation) : Canvas()
    {
        set_position(position);
        set_localEulerAngles(rotation);
    }

    Canvas::Canvas(Vector3 scale, Vector3 position, Vector3 rotation) : Canvas(position, rotation)
    {
        set_scale(scale);
    }


    Canvas* Canvas::CreateCanvas(Vector3 position, Vector3 rotation)
    {
        static Vector3 defaultSize = {0.005f, 0.005f, 0.005f};
        return CreateCanvas(defaultSize, position, rotation);
    }

    Canvas* Canvas::CreateCanvas(Vector3 scale, Vector3 position, Vector3 rotation)
    {
        return new Canvas(scale, position, rotation);
    }

    Il2CppObject* Canvas::get_gameObject()
    {
        return gameObject;
    }

    Il2CppObject* Canvas::get_transform()
    {
        return CRASH_UNLESS(il2cpp_utils::RunMethod(gameObject, "get_transform"));
    }

    void Canvas::set_scale(Vector3 scale)
    {
        il2cpp_utils::RunMethod(get_transform(), "set_localScale", scale);
    }

    void Canvas::set_position(Vector3 position)
    {
        il2cpp_utils::RunMethod(get_transform(), "set_position", position);
    }

    void Canvas::set_localEulerAngles(Vector3 angles)
    {
        il2cpp_utils::RunMethod(get_transform(), "set_localEulerAngles", angles);
    }

    void Canvas::set_rotation(Quaternion rotation)
    {
        il2cpp_utils::RunMethod(get_transform(), "set_rotation", rotation);
    }

    Vector3 Canvas::get_scale()
    {
        return *il2cpp_utils::RunMethod<Vector3>(get_transform(), "get_localScale");
    }

    Vector3 Canvas::get_position()
    {
        return *il2cpp_utils::RunMethod<Vector3>(get_transform(), "get_position");
    }

    Vector3 Canvas::get_localEulerAngles()
    {
        return *il2cpp_utils::RunMethod<Vector3>(get_transform(), "get_localEulerAngles");
    }

    Quaternion Canvas::get_rotation()
    {
        return *il2cpp_utils::RunMethod<Quaternion>(get_transform(), "get_rotation");
    }

    void Canvas::FindCanvasPrefab()
    {
        Il2CppObject* gorillaUI = CRASH_UNLESS(il2cpp_utils::RunMethod("UnityEngine", "GameObject", "Find", il2cpp_utils::createcsstr("GorillaUI")));
        canvasPrefab = CRASH_UNLESS(il2cpp_utils::RunMethod("UnityEngine", "Object", "Instantiate", gorillaUI));

        Il2CppObject* canvasTransform = CRASH_UNLESS(il2cpp_utils::RunMethod(canvasPrefab, "get_transform"));
        Il2CppObject* scoreboardAnchor = CRASH_UNLESS(il2cpp_utils::RunMethod(canvasTransform, "Find", il2cpp_utils::createcsstr("CaveScoreboardAnchor")));

        CRASH_UNLESS(il2cpp_utils::RunMethod("UnityEngine", "Object", "Destroy", scoreboardAnchor));

        scoreboardAnchor = CRASH_UNLESS(il2cpp_utils::RunMethod(canvasTransform, "Find", il2cpp_utils::createcsstr("ForestScoreboardAnchor")));
        CRASH_UNLESS(il2cpp_utils::RunMethod("UnityEngine", "Object", "Destroy", scoreboardAnchor));
    }
}