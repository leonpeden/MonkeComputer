#include "KeyExtension.hpp"
#include "Utils/TextUtils.hpp"
#include <algorithm>
#include <vector>
#include <map>

namespace GorillaUI::KeyExtension
{
    const std::vector<EKeyboardKey> functionKeys = {
        EKeyboardKey::RoomConfig,
        EKeyboardKey::ColorConfig,
        EKeyboardKey::TurnConfig,
        EKeyboardKey::NameConfig,
        EKeyboardKey::Enter,
        EKeyboardKey::Delete,
        EKeyboardKey::Option1,
        EKeyboardKey::Option2,
        EKeyboardKey::Option3,
        EKeyboardKey::Left,
        EKeyboardKey::Right,
        EKeyboardKey::Down,
        EKeyboardKey::Up,
        EKeyboardKey::Back
    };

    const std::map<EKeyboardKey, int> numberKeys = {
        {
            EKeyboardKey::NUM0,
            0
        },
        {
            EKeyboardKey::NUM1,
            1
        },
        {
            EKeyboardKey::NUM2,
            2
        },
        {
            EKeyboardKey::NUM3,
            3
        },
        {
            EKeyboardKey::NUM4,
            4
        },
        {
            EKeyboardKey::NUM5,
            5
        },
        {
            EKeyboardKey::NUM6,
            6
        },
        {
            EKeyboardKey::NUM7,
            7
        },
        {
            EKeyboardKey::NUM8,
            8
        },
        {
            EKeyboardKey::NUM9,
            9
        }
    };
    const std::map<EKeyboardKey, char> letterKeys = {
        {
            EKeyboardKey::A,
            'A'
        },
        {
            EKeyboardKey::B,
            'B'
        },
        {
            EKeyboardKey::C,
            'C'
        },
        {
            EKeyboardKey::D,
            'D'
        },
        {
            EKeyboardKey::E,
            'E'
        },
        {
            EKeyboardKey::F,
            'F'
        },
        {
            EKeyboardKey::G,
            'G'
        },
        {
            EKeyboardKey::H,
            'H'
        },
        {
            EKeyboardKey::I,
            'I'
        },
        {
            EKeyboardKey::J,
            'J'
        },
        {
            EKeyboardKey::K,
            'K'
        },
        {
            EKeyboardKey::L,
            'L'
        },
        {
            EKeyboardKey::M,
            'M'
        },
        {
            EKeyboardKey::N,
            'N'
        },
        {
            EKeyboardKey::O,
            'O'
        },
        {
            EKeyboardKey::P,
            'P'
        },
        {
            EKeyboardKey::Q,
            'Q'
        },
        {
            EKeyboardKey::R,
            'R'
        },
        {
            EKeyboardKey::S,
            'S'
        },
        {
            EKeyboardKey::T,
            'T'
        },
        {
            EKeyboardKey::U,
            'U'
        },
        {
            EKeyboardKey::V,
            'V'
        },
        {
            EKeyboardKey::W,
            'W'
        },
        {
            EKeyboardKey::X,
            'X'
        },
        {
            EKeyboardKey::Y,
            'Y'
        },
        {
            EKeyboardKey::Z,
            'Z'
        }
    };

    const std::map<std::string, EKeyboardKey> NameToEnumMap {
        {
            "0",
            EKeyboardKey::NUM0
        },
        {
            "1",
            EKeyboardKey::NUM1
        },
        {
            "2",
            EKeyboardKey::NUM2
        },
        {
            "3",
            EKeyboardKey::NUM3
        },
        {
            "4",
            EKeyboardKey::NUM4
        },
        {
            "5",
            EKeyboardKey::NUM5
        },
        {
            "6",
            EKeyboardKey::NUM6
        },
        {
            "7",
            EKeyboardKey::NUM7
        },
        {
            "8",
            EKeyboardKey::NUM8
        },
        {
            "9",
            EKeyboardKey::NUM9
        },
        {
            "a",
            EKeyboardKey::A
        },
        {
            "b",
            EKeyboardKey::B
        },
        {
            "c",
            EKeyboardKey::C
        },
        {
            "d",
            EKeyboardKey::D
        },
        {
            "e",
            EKeyboardKey::E
        },
        {
            "f",
            EKeyboardKey::F
        },
        {
            "g",
            EKeyboardKey::G
        },
        {
            "h",
            EKeyboardKey::H
        },
        {
            "i",
            EKeyboardKey::I
        },
        {
            "j",
            EKeyboardKey::J
        },
        {
            "k",
            EKeyboardKey::K
        },
        {
            "l",
            EKeyboardKey::L
        },
        {
            "m",
            EKeyboardKey::M
        },
        {
            "n",
            EKeyboardKey::N
        },
        {
            "o",
            EKeyboardKey::O
        },
        {
            "p",
            EKeyboardKey::P
        },
        {
            "q",
            EKeyboardKey::Q
        },
        {
            "r",
            EKeyboardKey::R
        },
        {
            "s",
            EKeyboardKey::S
        },
        {
            "t",
            EKeyboardKey::T
        },
        {
            "u",
            EKeyboardKey::U
        },
        {
            "v",
            EKeyboardKey::V
        },
        {
            "w",
            EKeyboardKey::W
        },
        {
            "x",
            EKeyboardKey::X
        },
        {
            "y",
            EKeyboardKey::Y
        },
        {
            "z",
            EKeyboardKey::Z
        },
        {
            "delete",
            EKeyboardKey::Delete
        },
        {
            "enter",
            EKeyboardKey::Enter
        },
        {
            "option1",
            EKeyboardKey::Option1
        },
        {
            "option2",
            EKeyboardKey::Option2
        },
        {
            "option3",
            EKeyboardKey::Option3
        },
        {
            "roomconfig",
            EKeyboardKey::RoomConfig
        },
        {
            "nameconfig",
            EKeyboardKey::NameConfig
        },
        {
            "colorconfig",
            EKeyboardKey::ColorConfig
        },
        {
            "turnconfig",
            EKeyboardKey::TurnConfig
        },
        {
            "left",
            EKeyboardKey::Left
        },
        {
            "right",
            EKeyboardKey::Right
        },
        {
            "down",
            EKeyboardKey::Down
        },
        {
            "up",
            EKeyboardKey::Up
        },
        {
            "space",
            EKeyboardKey::Space
        },
        {
            "back",
            EKeyboardKey::Back
        }
    };

    bool NameToKey(std::string name, EKeyboardKey& out)
    {
        std::string search = TextUtils::toLower(name);
        std::map<std::string, EKeyboardKey>::const_iterator it = NameToEnumMap.find(search);
        if (it != NameToEnumMap.end())
        {   
            out = it->second;
            return true;
        } 
        return false;
    }

    bool IsFunctionKey(EKeyboardKey key)
    {
       std::vector<EKeyboardKey>::const_iterator it = std::find(functionKeys.begin(), functionKeys.end(), key);

       if (it != functionKeys.end()) return true;
       return false; 
    }

    bool IsNumberKey(EKeyboardKey key)
    {
        std::map<EKeyboardKey, int>::const_iterator it = numberKeys.find(key);

       if (it != numberKeys.end()) return true;
       return false; 
    }

    bool IsLetterKey(EKeyboardKey key)
    {
        std::map<EKeyboardKey, char>::const_iterator it = letterKeys.find(key);

        if (it != letterKeys.end()) return true;
        return false;
    }

    bool TryParseNumber(EKeyboardKey key, int& out)
    {
        out = 0;
        if (!IsNumberKey(key)) return false;
        out = numberKeys.at(key);
        return true;
    }

    bool TryParseLetter(EKeyboardKey key, char& out)
    {
        out = 'A';
        if (!IsLetterKey(key)) return false;
        out = letterKeys.at(key);
        return true;
    }
}