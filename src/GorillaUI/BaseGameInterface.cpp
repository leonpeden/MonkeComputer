#include "GorillaUI/BaseGameInterface.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/utils.h"

extern Logger& getLogger();

namespace GorillaUI::BaseGameInterface
{
    void SetColor(float r, float g, float b)
    {
        il2cpp_utils::RunMethod("UnityEngine", "PlayerPrefs", "SetFloat", il2cpp_utils::createcsstr("redValue"), r);
        il2cpp_utils::RunMethod("UnityEngine", "PlayerPrefs", "SetFloat", il2cpp_utils::createcsstr("greenValue"), g);
        il2cpp_utils::RunMethod("UnityEngine", "PlayerPrefs", "SetFloat", il2cpp_utils::createcsstr("blueValue"), b);

        Il2CppObject* gorillaTagger = *il2cpp_utils::RunMethod("", "GorillaTagger", "get_Instance");
        il2cpp_utils::RunMethod(gorillaTagger, "UpdateColor", r, g, b);
        il2cpp_utils::RunMethod("UnityEngine", "PlayerPrefs", "Save");

        if (*il2cpp_utils::RunMethod<bool>("Photon.Pun", "PhotonNetwork", "get_InRoom"))
        {
            Il2CppObject* myVRRig = *il2cpp_utils::GetFieldValue(gorillaTagger, "myVRRig");
            Il2CppObject* photonView = *il2cpp_utils::GetFieldValue(myVRRig, "photonView");
            il2cpp_utils::RunMethod(photonView, "RPC", il2cpp_utils::createcsstr("InitializeNoobMaterial"), 0, r, g, b);            
        }
    }

    void SetName(std::string name)
    {
        Il2CppObject* gorillaComputer = *il2cpp_utils::GetFieldValue("", "GorillaComputer", "instance");
        if (!gorillaComputer) return;

        Il2CppObject* localPlayer = *il2cpp_utils::RunMethod("Photon.Pun", "PhotonNetwork", "get_LocalPlayer");

        Il2CppString* csName = il2cpp_utils::createcsstr(name);
        il2cpp_utils::RunMethod(localPlayer, "set_NickName", csName);

        Il2CppObject* offlineVRRigNametagText = *il2cpp_utils::GetFieldValue(gorillaComputer, "offlineVRRigNametagText");
        il2cpp_utils::RunMethod(offlineVRRigNametagText, "set_text", csName);
        il2cpp_utils::SetFieldValue(gorillaComputer, "savedName", csName);
        
        il2cpp_utils::RunMethod("UnityEngine", "PlayerPrefs", "SetString", il2cpp_utils::createcsstr("playerName"), csName);
        il2cpp_utils::RunMethod("UnityEngine", "PlayerPrefs", "Save");
    }

    void Disconnect()
    {
        Il2CppObject* gorillaComputer = *il2cpp_utils::GetFieldValue("", "GorillaComputer", "instance");
        if (!gorillaComputer) return;

        if (*il2cpp_utils::RunMethod<bool>("Photon.Pun", "PhotonNetwork", "get_InRoom"))
        {
            Il2CppObject* networkController = *il2cpp_utils::GetFieldValue(gorillaComputer, "networkController");

            il2cpp_utils::SetFieldValue(networkController, "attemptingToConnect", false);
            
            Il2CppObject* photonNetworkController = *il2cpp_utils::GetFieldValue("", "PhotonNetworkController", "instance");
            Il2CppObject* currentGorillaParent = *il2cpp_utils::GetFieldValue(photonNetworkController, "currentGorillaParent");

            std::vector<Il2CppClass*> spawnerKlass = {il2cpp_utils::GetClassFromName("", "GorillaScoreboardSpawner")};
            Array<Il2CppObject*>* scoreBoardSpawners = *il2cpp_utils::RunGenericMethod<Array<Il2CppObject*>*>(currentGorillaParent, "GetComponentsInChildren", spawnerKlass);

            for (int i = 0; i < scoreBoardSpawners->Length(); i++)
            {
                il2cpp_utils::RunMethod(scoreBoardSpawners->values[i], "OnLeftRoom");
            }
            
            std::vector<Il2CppClass*> skinnedMeshRendererKlass = {il2cpp_utils::GetClassFromName("UnityEngine", "SkinnedMeshRenderer")};
            Array<Il2CppObject*>* offlineVRRig = *il2cpp_utils::GetFieldValue<Array<Il2CppObject*>*>(networkController, "offlineVRRig");
            for (int i = 0; i < offlineVRRig->Length(); i++)
            {

                if (offlineVRRig->values[i] != nullptr)
                {
                    il2cpp_utils::RunMethod(offlineVRRig->values[i], "set_enabled", true);
                }
            }

            Array<Il2CppObject*>* levelScreens = *il2cpp_utils::GetFieldValue<Array<Il2CppObject*>*>(gorillaComputer, "levelScreens");
            
            for (int i = 0; i < levelScreens->Length(); i++)
            {
                Il2CppObject* screen = levelScreens->values[i];
                Il2CppString* startingText = *il2cpp_utils::GetFieldValue<Il2CppString*>(screen, "startingText");
                il2cpp_utils::RunMethod(screen, "UpdateText", startingText, true);
            }

            Il2CppObject* player = *il2cpp_utils::RunMethod("GorillaLocomotion", "Player", "get_Instance");

            il2cpp_utils::SetFieldValue(player, "maxJumpSpeed", 6.5f);
            il2cpp_utils::SetFieldValue(player, "jumpMultiplier", 1.1f);

            il2cpp_utils::RunMethod("Photon.Pun", "PhotonNetwork", "Disconnect");
            il2cpp_utils::RunMethod("Photon.Pun", "PhotonNetwork", "ConnectUsingSettings");
        }
    }

    void JoinRoom(std::string roomID)
    {
        Il2CppObject* gorillaComputer = *il2cpp_utils::GetFieldValue("", "GorillaComputer", "instance");
        if (!gorillaComputer) return;
        if (roomID == "") return;
        Il2CppObject* networkController = *il2cpp_utils::GetFieldValue(gorillaComputer, "networkController");
        Il2CppString* currentGameType = il2cpp_utils::createcsstr("privatetag");
        Il2CppString* customRoomID = il2cpp_utils::createcsstr(roomID);

        il2cpp_utils::SetFieldValue(networkController, "currentGameType", currentGameType);
        il2cpp_utils::SetFieldValue(networkController, "customRoomID", customRoomID);
        il2cpp_utils::SetFieldValue(networkController, "isPrivate", true);

        std::string currentRoomName = "";

        Il2CppObject* currentRoom = *il2cpp_utils::RunMethod("Photon.Pun", "PhotonNetwork", "get_CurrentRoom");

        if (currentRoom)
        {
            Il2CppString* currentRoomCsName = *il2cpp_utils::RunMethod<Il2CppString*>(currentRoom, "get_Name");
            currentRoomName = to_utf8(csstrtostr(currentRoomCsName));
        }

        if (*il2cpp_utils::RunMethod<bool>("Photon.Pun", "PhotonNetwork", "get_InRoom") && currentRoomName != roomID)
        {
            Il2CppObject* photonNetworkController = *il2cpp_utils::GetFieldValue("", "PhotonNetworkController", "instance");
            Il2CppObject* currentGorillaParent = *il2cpp_utils::GetFieldValue(photonNetworkController, "currentGorillaParent");

            std::vector<Il2CppClass*> spawnerKlass = {il2cpp_utils::GetClassFromName("", "GorillaScoreboardSpawner")};
            Array<Il2CppObject*>* scoreBoardSpawners = *il2cpp_utils::RunGenericMethod<Array<Il2CppObject*>*>(currentGorillaParent, "GetComponentsInChildren", spawnerKlass);

            for (int i = 0; i < scoreBoardSpawners->Length(); i++)
            {
                il2cpp_utils::RunMethod(scoreBoardSpawners->values[i], "OnLeftRoom");
            }
            
            il2cpp_utils::SetFieldValue(networkController, "attemptingToConnect", true);

            std::vector<Il2CppClass*> skinnedMeshRendererKlass = {il2cpp_utils::GetClassFromName("UnityEngine", "SkinnedMeshRenderer")};
            Array<Il2CppObject*>* offlineVRRig = *il2cpp_utils::GetFieldValue<Array<Il2CppObject*>*>(networkController, "offlineVRRig");
            for (int i = 0; i < offlineVRRig->Length(); i++)
            {
                if (offlineVRRig->values[i] != nullptr)
                {
                    il2cpp_utils::RunMethod(offlineVRRig->values[i], "set_enabled", true);
                }
            }

            il2cpp_utils::RunMethod("Photon.Pun", "PhotonNetwork", "Disconnect");

            Il2CppObject* player = *il2cpp_utils::RunMethod("GorillaLocomotion", "Player", "get_Instance");
            il2cpp_utils::SetFieldValue(player, "maxJumpSpeed", 6.5f);
            il2cpp_utils::SetFieldValue(player, "jumpMultiplier", 1.1f);
            return;
        }

        if (!*il2cpp_utils::RunMethod<bool>("Photon.Pun", "PhotonNetwork", "get_InRoom") && !*il2cpp_utils::GetFieldValue<bool>(networkController, "attemptingToConnect"))
        {
            il2cpp_utils::SetFieldValue(networkController, "attemptingToConnect", true);
            il2cpp_utils::RunMethod(networkController, "AttemptToConnectToRoom");
        }
    }

    void ChangeTurnMode(std::string turnType, int turnValue)
    {
        Il2CppString* turnTypeCS = il2cpp_utils::createcsstr(turnType);

        il2cpp_utils::RunMethod("UnityEngine", "PlayerPrefs", "SetString", il2cpp_utils::createcsstr("stickTurning"), turnTypeCS);
        il2cpp_utils::RunMethod("UnityEngine", "PlayerPrefs", "SetInt", il2cpp_utils::createcsstr("turnFactor"), turnValue);

        il2cpp_utils::RunMethod("UnityEngine", "PlayerPrefs", "Save");
        Il2CppObject* gorillaComputer = *il2cpp_utils::GetFieldValue("", "GorillaComputer", "instance");
        Il2CppObject* gorillaTurn = *il2cpp_utils::GetFieldValue(gorillaComputer, "gorillaTurn");

        il2cpp_utils::SetFieldValue(gorillaComputer, "turnType", turnTypeCS);
        il2cpp_utils::SetFieldValue(gorillaComputer, "turnValue", turnValue);

        il2cpp_utils::RunMethod(gorillaTurn, "ChangeTurnMode", turnTypeCS, turnValue);
    }

    void InitColorState()
    {
        float r = *il2cpp_utils::RunMethod<float>("UnityEngine", "PlayerPrefs", "GetFloat", il2cpp_utils::createcsstr("redValue"), 0.0f);
        float g = *il2cpp_utils::RunMethod<float>("UnityEngine", "PlayerPrefs", "GetFloat", il2cpp_utils::createcsstr("greenValue"), 0.0f);
        float b = *il2cpp_utils::RunMethod<float>("UnityEngine", "PlayerPrefs", "GetFloat", il2cpp_utils::createcsstr("blueValue"), 0.0f);

        Il2CppObject* gorillaTagger = *il2cpp_utils::RunMethod("", "GorillaTagger", "get_Instance");
        il2cpp_utils::RunMethod(gorillaTagger, "UpdateColor", r, g, b);
    }

    void InitNameState()
    {
        Il2CppString* csName = *il2cpp_utils::RunMethod<Il2CppString*>("UnityEngine", "PlayerPrefs", "GetString", il2cpp_utils::createcsstr("playerName"), il2cpp_utils::createcsstr(string_format("gorilla%d", rand() % 10000)));
        std::string name = to_utf8(csstrtostr(csName));
        SetName(name);
    }

    void InitTurnState()
    {
        static std::vector<Il2CppClass*> klass = {il2cpp_utils::GetClassFromName("", "GorillaSnapTurn")};
        Il2CppObject* gorillaTagger = *il2cpp_utils::RunMethod("", "GorillaTagger", "get_Instance");
        Il2CppObject* gorillaTurn = *il2cpp_utils::RunGenericMethod(gorillaTagger, "GetComponent", klass);
        Il2CppString* defaultValue = il2cpp_utils::createcsstr("NONE");
        Il2CppString* turnType = *il2cpp_utils::RunMethod<Il2CppString*>("UnityEngine", "PlayerPrefs", "GetString", il2cpp_utils::createcsstr("stickTurning"), defaultValue);
        int turnValue = *il2cpp_utils::RunMethod<int>("UnityEngine", "PlayerPrefs", "GetInt", il2cpp_utils::createcsstr("turnFactor"), 4);
        il2cpp_utils::RunMethod(gorillaTurn, "ChangeTurnMode", turnType, turnValue);
    }

    void InitAll()
    {
        InitColorState();
        InitNameState();
        InitTurnState();
    }

    namespace SnapTurn
    {
        int get_turnValue()
        {
            return *il2cpp_utils::RunMethod<int>("UnityEngine", "PlayerPrefs", "GetInt", il2cpp_utils::createcsstr("turnFactor"), 4);
        }

        void set_turnValue(int turnValue)
        {
            il2cpp_utils::RunMethod<int>("UnityEngine", "PlayerPrefs", "SetInt", il2cpp_utils::createcsstr("turnFactor"), turnValue);
        }

        std::string get_turnType()
        {
            static Il2CppString* defaultValue = il2cpp_utils::createcsstr("NONE");
            Il2CppString* turnTypeCS = *il2cpp_utils::RunMethod<Il2CppString*>("UnityEngine", "PlayerPrefs", "GetString", il2cpp_utils::createcsstr("stickTurning"), defaultValue);
            return to_utf8(csstrtostr(turnTypeCS));
        }

        void set_turnType(std::string turnType)
        {
            il2cpp_utils::RunMethod<Il2CppString*>("UnityEngine", "PlayerPrefs", "SetString", il2cpp_utils::createcsstr("stickTurning"), il2cpp_utils::createcsstr(turnType));
        }

        int turnTypeToIndex(std::string turnType)
        {
            if (turnType.find("SNAP") != std::string::npos) return 0;
            else if (turnType.find("SMOOTH") != std::string::npos) return 1;
            else return 2;
        }
    }

    namespace PlayerColor
    {
        Color get_color()
        {
            float r = *il2cpp_utils::RunMethod<float>("UnityEngine", "PlayerPrefs", "GetFloat", il2cpp_utils::createcsstr("redValue"), 0.0f);
            float g = *il2cpp_utils::RunMethod<float>("UnityEngine", "PlayerPrefs", "GetFloat", il2cpp_utils::createcsstr("greenValue"), 0.0f);
            float b = *il2cpp_utils::RunMethod<float>("UnityEngine", "PlayerPrefs", "GetFloat", il2cpp_utils::createcsstr("blueValue"), 0.0f);
            return {r, g, b};
        }
    }

    namespace Name
    {
        std::string get_name()
        {
            Il2CppString* csName = *il2cpp_utils::RunMethod<Il2CppString*>("UnityEngine", "PlayerPrefs", "GetString", il2cpp_utils::createcsstr("playerName"), il2cpp_utils::createcsstr(string_format("gorilla%d", rand() % 10000)));
            return to_utf8(csstrtostr(csName));
        }
    }

    namespace Room
    {
        bool get_isConnectedToMaster()
        {
            Il2CppObject* gorillaComputer = *il2cpp_utils::GetFieldValue("", "GorillaComputer", "instance");
            return *il2cpp_utils::GetFieldValue<bool>(gorillaComputer, "isConnectedToMaster");
        }

        std::string get_roomID()
        {
            std::string currentRoomName = "";

            Il2CppObject* currentRoom = *il2cpp_utils::GetPropertyValue("Photon.Pun", "PhotonNetwork", "CurrentRoom");

            if (currentRoom)
            {
                Il2CppString* currentRoomCsName = *il2cpp_utils::RunMethod<Il2CppString*>(currentRoom, "get_Name");
                currentRoomName = to_utf8(csstrtostr(currentRoomCsName));
            }

            return currentRoomName;
        }

        int get_currentPlayers()
        {
            return *il2cpp_utils::RunMethod<int>("Photon.Pun", "PhotonNetwork", "get_CountOfPlayersInRooms");
        }

        char get_playerCount()
        {
            Il2CppObject* currentRoom = *il2cpp_utils::RunMethod("Photon.Pun", "PhotonNetwork", "get_CurrentRoom");
            if (!currentRoom) return 0;
            return *il2cpp_utils::RunMethod<char>(currentRoom, "get_PlayerCount");
        }
    }
}