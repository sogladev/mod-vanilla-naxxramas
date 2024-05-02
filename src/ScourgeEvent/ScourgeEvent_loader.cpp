/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "VanillaNaxxramas.h"

// void AddSC_scourge_event();

void AddScourgeEvent_Scripts()
{
    if (!(sConfigMgr->GetOption<bool>("VanillaNaxxramas.ScourgeEvent", false)))
        return;
    // AddSC_scourge_event_tuning();
}
