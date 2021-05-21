#include "BillboardedWatch.hpp"
#include "UnityEngine/Camera.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Quaternion.hpp"

using namespace UnityEngine;

DEFINE_TYPE(GorillaUI::Components::BillboardedWatch);
extern Logger& getLogger();

namespace GorillaUI::Components
{
    void BillboardedWatch::Update()
    {
        Vector3 currentPos = get_transform()->get_position();
        Vector3 camPos = camTransform->get_position();

        Vector3 dir = (camPos - currentPos).get_normalized();

        dir.y = 0;

        Quaternion look = Quaternion::LookRotation(dir.get_normalized());

        get_transform()->set_rotation(look);
    }

    void BillboardedWatch::OnEnable()
    {
        camTransform = Camera::get_main()->get_transform();
    }
}