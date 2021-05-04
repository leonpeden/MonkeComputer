#include "GorillaUI/BaseGameInterface.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/utils.h"
#include <vector>
#include <algorithm>

#include "Photon/Pun/PhotonNetwork.hpp"
#include "Photon/Pun/PhotonView.hpp"
#include "Photon/Pun/RpcTarget.hpp"
#include "Photon/Realtime/Player.hpp"
#include "Photon/Realtime/Room.hpp"

#include "UnityEngine/PlayerPrefs.hpp"
#include "UnityEngine/UI/Text.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/SkinnedMeshRenderer.hpp"

#include "GorillaLocomotion/Player.hpp"

#include "GlobalNamespace/GorillaNetworkJoinTrigger.hpp"
#include "GlobalNamespace/GorillaLevelScreen.hpp"
#include "GlobalNamespace/GorillaFriendCollider.hpp"
#include "GlobalNamespace/GorillaComputer.hpp"
#include "GlobalNamespace/GorillaTagManager.hpp"
#include "GlobalNamespace/GorillaTagger.hpp"
#include "GlobalNamespace/GorillaScoreboardSpawner.hpp"
#include "GlobalNamespace/VRRig.hpp"
#include "GlobalNamespace/PhotonNetworkController.hpp"

#include "UnityEngine/XR/Interaction/Toolkit/GorillaSnapTurn.hpp"

extern Logger& getLogger();

using namespace UnityEngine;
using namespace GlobalNamespace;
using namespace Photon::Pun;
using namespace Photon::Realtime;

namespace GorillaUI::BaseGameInterface
{
    static Il2CppString* redValue = nullptr;
    static Il2CppString* greenValue = nullptr;
    static Il2CppString* blueValue = nullptr;
    static Il2CppString* playerName = nullptr;
    static Il2CppString* stickTurning = nullptr;
    static Il2CppString* turnFactor = nullptr;
    static Il2CppString* pttType = nullptr;
    static Il2CppString* currentQueue = nullptr;
    static Il2CppString* groupMapJoin = nullptr;
    static Il2CppString* voiceChatOn = nullptr;

    void SetColor(float r, float g, float b)
    {
        using namespace GlobalNamespace;
        if (!redValue) redValue = il2cpp_utils::createcsstr("redValue", il2cpp_utils::StringType::Manual);
        if (!greenValue) greenValue = il2cpp_utils::createcsstr("greenValue", il2cpp_utils::StringType::Manual);
        if (!blueValue) blueValue = il2cpp_utils::createcsstr("blueValue", il2cpp_utils::StringType::Manual);
        PlayerPrefs::SetFloat(redValue, r);
        PlayerPrefs::SetFloat(greenValue, g);
        PlayerPrefs::SetFloat(blueValue, b);

        GorillaTagger* gorillaTagger = GorillaTagger::get_Instance();
        gorillaTagger->UpdateColor(r, g, b);
        PlayerPrefs::Save();

        if (PhotonNetwork::get_InRoom())
        {
            VRRig* myVRRig = gorillaTagger->myVRRig;
            PhotonView* photonView = myVRRig->get_photonView();
            static Il2CppString* initializeNoobMaterial = il2cpp_utils::createcsstr("InitializeNoobMaterial", il2cpp_utils::StringType::Manual);

            std::vector<float> floatVector = {};
            floatVector.push_back(r);
            floatVector.push_back(g);
            floatVector.push_back(b);
            Array<float>* floatArr = il2cpp_utils::vectorToArray(floatVector);
            photonView->RPC(initializeNoobMaterial, RpcTarget::All, floatArr);
        }
    }

    bool SetName(std::string name)
    {
        GorillaComputer* gorillaComputer = GorillaComputer::_get_instance();
        if (!gorillaComputer) return false;

        Il2CppString* csName = il2cpp_utils::createcsstr(name);

        if (!gorillaComputer->CheckAutoBanList(csName)) return false;

        PhotonNetwork::get_LocalPlayer()->set_NickName(csName);

        gorillaComputer->offlineVRRigNametagText->set_text(csName);
        gorillaComputer->savedName = csName;

        if (!playerName) playerName = il2cpp_utils::createcsstr("playerName", il2cpp_utils::StringType::Manual);
        PlayerPrefs::SetString(playerName, csName);
        PlayerPrefs::Save();

        if (PhotonNetwork::get_InRoom())
        {
            
            static Il2CppString* initializeNoobMaterial = il2cpp_utils::createcsstr("InitializeNoobMaterial", il2cpp_utils::StringType::Manual);

            std::vector<float> floatVector = {};
            floatVector.push_back(gorillaComputer->redValue);
            floatVector.push_back(gorillaComputer->greenValue);
            floatVector.push_back(gorillaComputer->blueValue);
            Array<float>* floatArr = il2cpp_utils::vectorToArray(floatVector);
            GlobalNamespace::GorillaTagger::_get__instance()->myVRRig->get_photonView()->RPC(initializeNoobMaterial, RpcTarget::All, floatArr);
        }
        return true;
    }

    void Disconnect()
    {
        if (PhotonNetwork::get_InRoom())
        {
            PhotonNetworkController::_get_instance()->AttemptDisconnect();
        }
    }

    void JoinRoom(std::string roomID)
    {
        GorillaComputer* gorillaComputer = GorillaComputer::_get_instance();
        if (!gorillaComputer) return;
        if (roomID == "") return;        
        PhotonNetworkController* networkController = gorillaComputer->networkController;

        Photon::Realtime::Room* currentRoom = PhotonNetwork::get_CurrentRoom();

        std::string currentRoomName = "";
        if (currentRoom)
        {
            Il2CppString* currentRoomCsName = currentRoom->get_Name();
            currentRoomName = to_utf8(csstrtostr(currentRoomCsName));
        }

        if (currentRoomName != roomID)
        {
            PhotonNetworkController::_get_instance()->AttemptToJoinSpecificRoom(il2cpp_utils::createcsstr(roomID));
        }
    }

    void ChangeTurnMode(std::string turnType, int turnValue)
    {
        Il2CppString* turnTypeCS = il2cpp_utils::createcsstr(turnType);

        if (!stickTurning) stickTurning = il2cpp_utils::createcsstr("stickTurning", il2cpp_utils::StringType::Manual);
        if (!turnFactor) turnFactor = il2cpp_utils::createcsstr("turnFactor", il2cpp_utils::StringType::Manual);

        PlayerPrefs::SetString(stickTurning, turnTypeCS);
        PlayerPrefs::SetInt(turnFactor, turnValue);

        PlayerPrefs::Save();

        GorillaComputer* gorillaComputer = GorillaComputer::_get_instance();

        UnityEngine::XR::Interaction::Toolkit::GorillaSnapTurn* gorillaTurn = gorillaComputer->gorillaTurn;

        gorillaComputer->turnType = turnTypeCS;
        gorillaComputer->turnValue = turnValue;
        if (gorillaTurn) gorillaTurn->ChangeTurnMode(turnTypeCS, turnValue);
    }

    void InitColorState()
    {
        Color color = PlayerColor::get_color();

        GorillaTagger* gorillaTagger = GorillaTagger::get_Instance();
        gorillaTagger->UpdateColor(color.r, color.g, color.b);
    }

    void InitNameState()
    {
        if (!playerName) playerName = il2cpp_utils::createcsstr("playerName", il2cpp_utils::StringType::Manual);
        Il2CppString* csName = PlayerPrefs::GetString(playerName, il2cpp_utils::createcsstr(string_format("gorilla%d", rand() % 10000)));
        std::string name = to_utf8(csstrtostr(csName));
        SetName(name);
    }

    void InitTurnState()
    {
        if (!stickTurning) stickTurning = il2cpp_utils::createcsstr("stickTurning", il2cpp_utils::StringType::Manual);
        if (!turnFactor) turnFactor = il2cpp_utils::createcsstr("turnFactor", il2cpp_utils::StringType::Manual);

        GorillaTagger* gorillaTagger = GorillaTagger::get_Instance();
        using namespace UnityEngine::XR::Interaction::Toolkit;
        GorillaSnapTurn* gorillaTurn = gorillaTagger->GetComponent<GorillaSnapTurn*>();
        Il2CppString* turnType = PlayerPrefs::GetString(stickTurning, il2cpp_utils::createcsstr("NONE"));
        int turnValue = PlayerPrefs::GetInt(turnFactor, 4);
        gorillaTurn->ChangeTurnMode(turnType, turnValue);
    }

    void InitAll()
    {
        InitColorState();
        InitNameState();
        InitTurnState();
    }

    std::string get_gameVersion()
    {
        PhotonNetworkController* photonNetworkController = PhotonNetworkController::_get_instance();
        Il2CppString* gameVersion = photonNetworkController->gameVersion;
        return to_utf8(csstrtostr(gameVersion));
    }

    void SetpttType(std::string pttType)
    {
        if (!BaseGameInterface::pttType) BaseGameInterface::pttType = il2cpp_utils::createcsstr("pttType", il2cpp_utils::StringType::Manual);
        Il2CppString* pttTypeCS = il2cpp_utils::createcsstr(pttType);
        GorillaComputer* gorillaComputer = GorillaComputer::_get_instance();
        gorillaComputer->pttType = pttTypeCS;

        PlayerPrefs::SetString(BaseGameInterface::pttType, pttTypeCS);
        PlayerPrefs::Save();
    }

    void SetQueue(std::string queue)
    {
        if (!currentQueue) currentQueue = il2cpp_utils::createcsstr("currentQueue", il2cpp_utils::StringType::Manual);
        Il2CppString* queueCS = il2cpp_utils::createcsstr(queue);
        GorillaComputer* gorillaComputer = GorillaComputer::_get_instance();
        gorillaComputer->currentQueue = queueCS;

        PlayerPrefs::SetString(currentQueue, queueCS);
        PlayerPrefs::Save();
    }

    void SetGroup(std::string group)
    {
        if (!groupMapJoin) groupMapJoin = il2cpp_utils::createcsstr("groupMapJoin", il2cpp_utils::StringType::Manual);
        GorillaComputer* gorillaComputer = GorillaComputer::_get_instance();
        Il2CppString* toJoin = il2cpp_utils::createcsstr(group);
        gorillaComputer->groupMapJoin = toJoin;

        PlayerPrefs::SetString(groupMapJoin, toJoin);

        bool inRoom = PhotonNetwork::get_InRoom();
        
        Photon::Realtime::Room* currentRoom = PhotonNetwork::get_CurrentRoom();
        bool isVisible = currentRoom ? currentRoom->get_IsVisible() : false;

        bool flag = inRoom && !isVisible && (group == "FOREST" || group == "CAVE" || group == "CANYON");

		if (flag)
		{
            PhotonNetworkController* networkController = gorillaComputer->networkController;

            // get all player ids for checking who to send
            List<Il2CppString*>* playerIDsCurrentlyTouching = gorillaComputer->friendJoinCollider->playerIDsCurrentlyTouching;
            std::vector<std::string> playerIDsCurrentlyTouchingVector = {};

            for (int i = 0; i < playerIDsCurrentlyTouching->size; i++)
            {
                Il2CppString* playerIDcs = playerIDsCurrentlyTouching->items->values[i];
                if (!playerIDcs) continue;
                std::string playerID = to_utf8(csstrtostr(playerIDcs));
                playerIDsCurrentlyTouchingVector.push_back(playerID);
            }
            
            // set list
            networkController->friendIDList = playerIDsCurrentlyTouching;

            static Il2CppString* empty = il2cpp_utils::createcsstr("", il2cpp_utils::StringType::Manual);
            networkController->currentGameType = empty;

            Array<Photon::Realtime::Player*>* playerList = PhotonNetwork::get_PlayerList();

            Photon::Realtime::Player* localPlayer = PhotonNetwork::get_LocalPlayer();
            GorillaTagManager* gorillaTagManager = GorillaTagManager::_get_instance();
            PhotonView* photonView = gorillaTagManager->get_photonView();

            for (int i = 0; i < playerList->Length(); i++)
            {
                Photon::Realtime::Player* roomPlayer = playerList->values[i];
                if (!roomPlayer) continue;
                Il2CppString* userIDCS = roomPlayer->get_UserId();
                std::string userID = to_utf8(csstrtostr(userIDCS));
                std::vector<std::string>::iterator it = std::find(playerIDsCurrentlyTouchingVector.begin(), playerIDsCurrentlyTouchingVector.end(), userID);

                // if player is close, that means join them
                if (it != playerIDsCurrentlyTouchingVector.end() && !roomPlayer->Equals(localPlayer))
                {
                    // method name
                    static Il2CppString* joinPubWithFriends = il2cpp_utils::createcsstr("JoinPubWithFreinds", il2cpp_utils::StringType::Manual);
                    photonView->RPC(joinPubWithFriends, roomPlayer, System::Array::Empty<Il2CppObject*>());
                }
            }

            PhotonNetwork::SendAllOutgoingCommands();

            GorillaNetworkJoinTrigger* triggeredTrigger = nullptr;

			if (group == "FOREST")
			{
				triggeredTrigger = gorillaComputer->forestMapTrigger;
			}
			else if (group == "CAVE")
			{
				triggeredTrigger = gorillaComputer->caveMapTrigger;
			}
            else if (group == "CANYON")
			{
				triggeredTrigger = gorillaComputer->canyonMapTrigger;
			}

            PhotonNetworkController::_get_instance()->AttemptJoinPublicWithFriends(triggeredTrigger);
		}
    }

    void SetVoiceChat(bool value)
    {
        GorillaComputer* gorillaComputer = GorillaComputer::_get_instance();
        if (!gorillaComputer) return;

        if (!voiceChatOn) voiceChatOn = il2cpp_utils::createcsstr("voiceChatOn", il2cpp_utils::StringType::Manual);

        std::string stringToSet = value ? "TRUE" : "FALSE";
        Il2CppString* stringToSetCS = il2cpp_utils::createcsstr(stringToSet);

        gorillaComputer->voiceChatOn = stringToSetCS;
        PlayerPrefs::SetString(voiceChatOn, stringToSetCS);
        PlayerPrefs::Save();
    }


    namespace SnapTurn
    {
        int get_turnValue()
        {
            if (!turnFactor) turnFactor = il2cpp_utils::createcsstr("turnFactor", il2cpp_utils::StringType::Manual);
            return PlayerPrefs::GetInt(turnFactor, 4);
        }

        void set_turnValue(int turnValue)
        {
            if (!turnFactor) turnFactor = il2cpp_utils::createcsstr("turnFactor", il2cpp_utils::StringType::Manual);
            PlayerPrefs::SetInt(turnFactor, turnValue);
        }

        std::string get_turnType()
        {
            if (!stickTurning) stickTurning = il2cpp_utils::createcsstr("stickTurning", il2cpp_utils::StringType::Manual);
            static Il2CppString* defaultValue = il2cpp_utils::createcsstr("NONE");
            Il2CppString* turnTypeCS = PlayerPrefs::GetString(stickTurning, defaultValue);
            return to_utf8(csstrtostr(turnTypeCS));
        }

        void set_turnType(std::string turnType)
        {
            if (!stickTurning) stickTurning = il2cpp_utils::createcsstr("stickTurning", il2cpp_utils::StringType::Manual);
            PlayerPrefs::SetString(stickTurning, il2cpp_utils::createcsstr(turnType));
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
            if (!redValue) redValue = il2cpp_utils::createcsstr("redValue", il2cpp_utils::StringType::Manual);
            if (!greenValue) greenValue = il2cpp_utils::createcsstr("greenValue", il2cpp_utils::StringType::Manual);
            if (!blueValue) blueValue = il2cpp_utils::createcsstr("blueValue", il2cpp_utils::StringType::Manual);

            float r = PlayerPrefs::GetFloat(redValue, 0.0f);
            float g = PlayerPrefs::GetFloat(greenValue, 0.0f);
            float b = PlayerPrefs::GetFloat(blueValue, 0.0f);
            return {r, g, b};
        }
    }

    namespace Name
    {
        std::string get_name()
        {
            if (!playerName) playerName = il2cpp_utils::createcsstr("playerName", il2cpp_utils::StringType::Manual);
            Il2CppString* csMonke = PlayerPrefs::GetString(playerName, il2cpp_utils::createcsstr(string_format("gorilla%d", rand() % 10000)));
            std::string monke = to_utf8(csstrtostr(csMonke));
            return monke;
        }
    }

    namespace Room
    {
        bool get_isConnectedToMaster()
        {
            return GorillaComputer::_get_instance()->isConnectedToMaster;
        }

        std::string get_roomID()
        {
            std::string currentRoomName = "";

            Photon::Realtime::Room* currentRoom = PhotonNetwork::get_CurrentRoom();

            if (currentRoom)
            {
                Il2CppString* currentRoomCsName = currentRoom->get_Name();
                currentRoomName = to_utf8(csstrtostr(currentRoomCsName));
            }

            return currentRoomName;
        }

        int get_currentPlayers()
        {
            return PhotonNetwork::get_CountOfPlayersInRooms();
        }

        char get_playerCount()
        {
            Photon::Realtime::Room* currentRoom = Photon::Pun::PhotonNetwork::get_CurrentRoom();
            if (!currentRoom) return 0;
            return currentRoom->get_PlayerCount();
        }

        int get_collidingPlayers()
        {
            GorillaFriendCollider* friendJoinCollider = GorillaComputer::_get_instance()->friendJoinCollider;
            return friendJoinCollider->playerIDsCurrentlyTouching->size;
        }

        int get_bannedPlayers()
        {
            GorillaComputer* gorillaComputer = GorillaComputer::_get_instance();
            if (!gorillaComputer) return -1;
            return gorillaComputer->usersBanned;
        }
    }

    namespace Mic
    {
        std::string get_pttType()
        {
            if (!BaseGameInterface::pttType) BaseGameInterface::pttType = il2cpp_utils::createcsstr("pttType", il2cpp_utils::StringType::Manual);
            Il2CppString* pttType = PlayerPrefs::GetString(BaseGameInterface::pttType, il2cpp_utils::createcsstr("ALL CHAT"));
            return to_utf8(csstrtostr(pttType));
        }

        int pttTypeToIndex(std::string pttType)
        {
            if (pttType == "PUSH TO MUTE") return 2;
            else if (pttType == "PUSH TO TALK") return 1;
            else return 0;
        }
    }

    namespace Queue
    {
        std::string get_Queue()
        {
            if (!currentQueue) currentQueue = il2cpp_utils::createcsstr("currentQueue", il2cpp_utils::StringType::Manual);
            Il2CppString* currentQueueCS = PlayerPrefs::GetString(currentQueue, il2cpp_utils::createcsstr("DEFAULT"));
            return to_utf8(csstrtostr(currentQueueCS));
        }

        int queueToIndex(std::string queue)
        {
            if (queue == "CASUAL") return 2;
            else if (queue == "COMPETITIVE") return 1;
            else return 0;
        }
    }

    namespace Group
    {
        std::string get_group()
        {
            if (!groupMapJoin) groupMapJoin = il2cpp_utils::createcsstr("groupMapJoin", il2cpp_utils::StringType::Manual);
            Il2CppString* currentGroup = PlayerPrefs::GetString(groupMapJoin, il2cpp_utils::createcsstr("FOREST"));
            return to_utf8(csstrtostr(currentGroup));
        }

        int groupToIndex(std::string group)
        {
            if (group == "CAVE") return 1;
            else if (group == "CANYON") return 2;
            else return 0;
        }
    }

    namespace Voice
    {
        bool get_voiceChat()
        {
            if (!voiceChatOn) voiceChatOn = il2cpp_utils::createcsstr("voiceChatOn", il2cpp_utils::StringType::Manual);
            static Il2CppString* defaultVal = il2cpp_utils::createcsstr("TRUE", il2cpp_utils::StringType::Manual);

            Il2CppString* value = PlayerPrefs::GetString(voiceChatOn, defaultVal);
            return value ? value->Contains(defaultVal) : true;
        }
    }
}