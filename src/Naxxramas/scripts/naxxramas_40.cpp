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
