/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "VanillaNaxxramas.h"
#include "DBUpdater.h"

inline std::vector<std::string> GetDatabaseDirectories(std::string const& folderName)
{
    std::vector<std::string> directories;

    std::string const path = "/modules/mod-vanilla-naxxramas/src/";
    for (std::string const& bracketName : NaxxramasPhasesNames)
    {
        if (!(sConfigMgr->GetOption<bool>("VanillaNaxxramas." + bracketName, false)))
        {
            continue;
        }

        std::string bracketPath = path + bracketName + "/sql/" + folderName;
        directories.push_back(std::move(bracketPath));
    }

    return directories;
}

class VanillaNaxxramasLoadingDBUpdates : public DatabaseScript
{
public:
    VanillaNaxxramasLoadingDBUpdates() : DatabaseScript("VanillaNaxxramasLoadingDBUpdates") {}

    void OnAfterDatabasesLoaded(uint32 updateFlags) override
    {
        LOG_INFO("server.server", "Loading mod-vanilla-naxxramas updates...");

        if (DBUpdater<LoginDatabaseConnection>::IsEnabled(updateFlags))
        {
            if (sConfigMgr->GetOption<bool>("VanillaNaxxramas.ReapplyUpdates", true))
            {
                LoginDatabase.Query("DELETE FROM updates WHERE name LIKE '%naxx40%'");
            }

            std::vector<std::string> loginDatabaseDirectories = GetDatabaseDirectories("auth");
            if (!loginDatabaseDirectories.empty())
            {
                DBUpdater<LoginDatabaseConnection>::Update(LoginDatabase, &loginDatabaseDirectories);
            }
        }

        if (DBUpdater<CharacterDatabaseConnection>::IsEnabled(updateFlags))
        {
            if (sConfigMgr->GetOption<bool>("VanillaNaxxramas.ReapplyUpdates", true))
            {
                CharacterDatabase.Query("DELETE FROM updates WHERE name LIKE '%naxx40%'");
            }

            std::vector<std::string> charactersDatabaseDirectories = GetDatabaseDirectories("characters");
            if (!charactersDatabaseDirectories.empty())
            {
                DBUpdater<CharacterDatabaseConnection>::Update(CharacterDatabase, &charactersDatabaseDirectories);
            }
        }

        if (DBUpdater<WorldDatabaseConnection>::IsEnabled(updateFlags))
        {
            if (sConfigMgr->GetOption<bool>("VanillaNaxxramas.ReapplyUpdates", true))
            {
                WorldDatabase.Query("DELETE FROM updates WHERE name LIKE '%naxx40%'");
            }

            std::vector<std::string> worldDatabaseDirectories = GetDatabaseDirectories("world");
            if (!worldDatabaseDirectories.empty())
            {
                DBUpdater<WorldDatabaseConnection>::Update(WorldDatabase, &worldDatabaseDirectories);
            }
        }
    }
};

VanillaNaxxramas* VanillaNaxxramas::instance()
{
    static VanillaNaxxramas instance;
    return &instance;
}

class VanillaNaxxramas_WorldScript : public WorldScript
{
private:
    static void LoadConfig()
    {
        sVanillaNaxxramas->enabled = sConfigMgr->GetOption<bool>("VanillaNaxxramas.Enable", true);
        // sVanillaNaxxramas->requireAttunement = sConfigMgr->GetOption<bool>("VanillaNaxxramas.Naxxramas.RequireAttunement", true);
        sVanillaNaxxramas->requireNaxxStrath = sConfigMgr->GetOption<bool>("VanillaNaxxramas.Naxxramas.RequireNaxxStrathEntrance", true);
    }

public:
    VanillaNaxxramas_WorldScript() : WorldScript("VanillaNaxxramas_WorldScript") { }

    void OnBeforeConfigLoad(bool /*reload*/) override
    {
        LoadConfig();
    }
};

void AddVanillaNaxxramasScripts()
{
    if (sConfigMgr->GetOption<bool>("VanillaNaxxramas.LoadDatabase", true))
    {
        new VanillaNaxxramasLoadingDBUpdates();
    }
    new VanillaNaxxramas_WorldScript();
}
