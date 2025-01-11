/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "VanillaNaxxramas.h"

VanillaNaxxramas* VanillaNaxxramas::instance()
{
    static VanillaNaxxramas instance;
    return &instance;
}

class VanillaNaxxramas_WorldScript : public WorldScript
{
public:
    VanillaNaxxramas_WorldScript() : WorldScript("VanillaNaxxramas_WorldScript") { }

    void OnBeforeConfigLoad(bool /*reload*/) override
    {
        sVanillaNaxxramas->requireAttunement = sConfigMgr->GetOption<bool>("VanillaNaxxramas.Naxxramas.RequireAttunement", true);
        sVanillaNaxxramas->requireNaxxStrath = sConfigMgr->GetOption<bool>("VanillaNaxxramas.Naxxramas.RequireNaxxStrathEntrance", true);
    }
};

void AddVanillaNaxxramasScripts()
{
    new VanillaNaxxramas_WorldScript();
}
