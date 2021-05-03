#include "BanManager.hpp"

static bool isBanned = false;
static std::string displayMessage = "";

using namespace std;

namespace BanManager 
{
    bool get_isBanned()
    {
        return isBanned;
    }

    string get_displayMessage()
    {
        return displayMessage;
    }

    void set_displayMessage(string value)
    {
        isBanned = true;
        displayMessage = value;
    }
}