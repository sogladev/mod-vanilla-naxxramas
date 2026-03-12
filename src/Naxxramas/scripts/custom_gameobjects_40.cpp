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

bool CanEnterNaxx40(Player const* player)
{
    return IsAttuned(player) || !sVanillaNaxxramas->requireAttunement;
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
        bool meetNaxx40TeleportSkipRequirement = !sVanillaNaxxramas->requireNaxxStrath
            || (player->GetQuestStatus(NAXX40_ENTRANCE_FLAG) == QUEST_STATUS_REWARDED);
        if (meetNaxx40TeleportSkipRequirement && CanEnterNaxx40(player))
        {
            player->SetRaidDifficulty(RAID_DIFFICULTY_10MAN_HEROIC);
            player->TeleportTo(533, 3005.51f, -3434.64f, 304.195f, 6.2831f);
        }
        return true;
    }
};

void AddSC_custom_gameobjects_40()
{
    new gobject_naxx40_tele();
}
