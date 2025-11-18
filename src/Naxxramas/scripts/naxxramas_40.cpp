#include "Player.h"
#include "naxxramas_40.h"

bool IsAttuned(Player* player)
{
    if ((player->GetQuestStatus(NAXX40_ATTUNEMENT_1) == QUEST_STATUS_REWARDED) ||
        (player->GetQuestStatus(NAXX40_ATTUNEMENT_2) == QUEST_STATUS_REWARDED) ||
        (player->GetQuestStatus(NAXX40_ATTUNEMENT_3) == QUEST_STATUS_REWARDED))
    {
        return true;
    }
    return false;
}
