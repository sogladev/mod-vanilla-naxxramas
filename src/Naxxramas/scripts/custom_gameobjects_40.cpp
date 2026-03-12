#include "Chat.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "GameObjectAI.h"
#include "Player.h"
#include "VanillaNaxxramas.h"
#include "naxxramas_40.h"

bool IsAttuned(Player const* player)
{
    if ((player->GetQuestStatus(NAXX40_ATTUNEMENT_1) == QUEST_STATUS_REWARDED) ||
        (player->GetQuestStatus(NAXX40_ATTUNEMENT_2) == QUEST_STATUS_REWARDED) ||
        (player->GetQuestStatus(NAXX40_ATTUNEMENT_3) == QUEST_STATUS_REWARDED))
    {
        return true;
    }
    return false;
}

class gobject_naxx40_tele : public GameObjectScript
{
public:
    gobject_naxx40_tele() : GameObjectScript("gobject_naxx40_tele") { }

    struct gobject_naxx40_teleAI: GameObjectAI
    {
        explicit gobject_naxx40_teleAI(GameObject* object) : GameObjectAI(object) { };
    };

    GameObjectAI* GetAI(GameObject* object) const override
    {
        return new gobject_naxx40_teleAI(object);
    }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        bool meetLevelRequirement = player->GetLevel() >= 51;
        if (!meetLevelRequirement)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You must be level 51+, in a Raid group, and be attuned to Naxxramas to enter.");
            return true;
        }

        bool meetTeleportSkipRequirement = (player->GetQuestStatus(NAXX40_ENTRANCE_FLAG) == QUEST_STATUS_REWARDED) || !sVanillaNaxxramas->requireNaxxStrath;
        if (!meetTeleportSkipRequirement)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You do not meet the requirements to use the skip.");
            return true;
        }

        bool isAttuned = IsAttuned(player) || !sVanillaNaxxramas->requireAttunement;
        if (!isAttuned)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You must be level 51+, in a Raid group, and be attuned to Naxxramas to enter.");
            return true;
        }

        player->SetRaidDifficulty(RAID_DIFFICULTY_10MAN_HEROIC);
        player->TeleportTo(533, 3005.51f, -3434.64f, 304.195f, 6.2831f);

        return true;
    }
};

void AddSC_custom_gameobjects_40()
{
    new gobject_naxx40_tele();
}
