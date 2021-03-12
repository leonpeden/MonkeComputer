#pragma once
#include <string>
#include "typedefs.h"

namespace GorillaUI::BaseGameInterface
{
    void SetColor(float r, float g, float b);
    void SetName(std::string name);
    void Disconnect();
    void JoinRoom(std::string roomID);
    void InitColorState();
    void InitNameState();
    void InitTurnState();
    void InitAll();
    void ChangeTurnMode(std::string turnType, int turnValue);

    namespace SnapTurn
    {
        int get_turnValue();
        void set_turnValue(int turnValue);

        std::string get_turnType();
        void set_turnType(std::string turnType);

        int turnTypeToIndex(std::string turnType);
    }

    namespace PlayerColor
    {
        Color get_color();
    }

    namespace Name
    {
        std::string get_name();
    }

    namespace Room
    {
        bool get_isConnectedToMaster();
        std::string get_roomID();
        int get_currentPlayers();
        char get_playerCount();
    }
}
