#include <string>

namespace BanManager 
{
    bool get_isBanned();
    void set_isBanned(bool value);
    std::string get_displayMessage();
    void set_displayMessage(std::string value);
}