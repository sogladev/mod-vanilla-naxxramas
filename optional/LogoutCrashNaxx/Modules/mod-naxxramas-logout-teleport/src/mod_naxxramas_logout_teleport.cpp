#include "ScriptMgr.h"
#include "Player.h"
#include "Map.h"
#include "WorldSession.h"

class NaxxramasLogoutTeleport : public PlayerScript
{
	public:
		NaxxramasLogoutTeleport() : PlayerScript("NaxxramasLogoutTeleport") { }

		void OnLogin(Player* player) override
		{
			if (player->GetMapId() == 533)
			{
				player->TeleportTo(0, 3082.641602f, -3725.781250f, 132.418884f, 0.002488f);
			}
		}
};

void AddSC_mod_naxxramas_logout_teleport()
{
    new NaxxramasLogoutTeleport();
}
