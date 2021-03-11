#include "ViewLib/View.hpp"
#include "typedefs.h"

DEFINE_CLASS(GorillaUI::Components::View);

extern Logger& getLogger();

namespace GorillaUI::Components
{
    void View::Activate()
    {
        static Vector3 zero = {0.0f, 0.0f, 0.0f};
        il2cpp_utils::RunMethod(this, "DidActivate", !activatedBefore);
        activatedBefore = true;
    }

    void View::Deactivate()
    {
        il2cpp_utils::RunMethod(this, "DidDeactivate");
    }
}
