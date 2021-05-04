#pragma once
#include <string>
#include "typedefs.h"

#include "UnityEngine/Color.hpp"

namespace GorillaUI::BaseGameInterface
{
    void SetColor(float r, float g, float b);
    bool SetName(std::string name);
    void Disconnect();
    void JoinRoom(std::string roomID);
    void SetpttType(std::string pttType);
    void SetQueue(std::string queue);
    void SetGroup(std::string group);
    void InitColorState();
    void InitNameState();
    void InitTurnState();
    void InitAll();
    void ChangeTurnMode(std::string turnType, int turnValue);
    void SetVoiceChat(bool value);
    std::string get_gameVersion();

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
        UnityEngine::Color get_color();
    }

    namespace Name
    {
        std::string get_name();
    }

    namespace Room
    {
        bool get_isConnectedToMaster();
        std::string get_roomID();
        /// @brief current online players
        int get_currentPlayers();

        /// @brief players in lobby
        char get_playerCount();

        /// @brief players close enough to the pc for group transfer
        int get_collidingPlayers();

        /// @brief count of players banned yesterday
        int get_bannedPlayers();
    }

    namespace Mic
    {
        std::string get_pttType();
        int pttTypeToIndex(std::string pttType);
    }

    namespace Queue
    {
        std::string get_Queue();
        int queueToIndex(std::string queue);
    }

    namespace Group
    {
        std::string get_group();
        int groupToIndex(std::string group);
    }

    namespace Voice
    {
        bool get_voiceChat();
    }
}
