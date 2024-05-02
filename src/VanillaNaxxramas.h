/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#ifndef _VANILLA_NAXXRAMAS_H_
#define _VANILLA_NAXXRAMAS_H_

#include "Config.h"
#include "ScriptMgr.h"

#define NAXXRAMAS_PHASE_MAX 2
std::array<std::string, NAXXRAMAS_PHASE_MAX> const NaxxramasPhasesNames =
{
    "ScourgeEvent",
    "Naxxramas"
};

class VanillaNaxxramas
{
public:
    static VanillaNaxxramas* instance();

    bool enabled, requireNaxxStrath, requireAttunement;
};

#define sVanillaNaxxramas VanillaNaxxramas::instance()

#endif // _VANILLA_NAXXRAMAS_H_
