/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "Config.h"

void AddVanillaNaxxramasScripts();
void AddNaxxramas_Scripts();
void AddScourgeEvent_Scripts();

void Addmod_vanilla_naxxramasScripts()
{
    AddVanillaNaxxramasScripts();

    if (!sConfigMgr->GetOption<bool>("VanillaNaxxramas.LoadScripts", true))
        return;

    AddNaxxramas_Scripts();
    AddScourgeEvent_Scripts();
}
