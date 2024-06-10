
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"
#include "naxxramas.h"

class boss_heigan_eye_stalk_40 : public CreatureScript
{
public:
    boss_heigan_eye_stalk_40() : CreatureScript("boss_heigan_eye_stalk_40") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetNaxxramasAI<boss_heigan_eye_stalk_40AI>(creature);
    }

    struct boss_heigan_eye_stalk_40AI : public ScriptedAI
    {
        explicit boss_heigan_eye_stalk_40AI(Creature* creature) : ScriptedAI(creature)
        {
            timeSinceSpawn = 0;
            haveSubmerged = false;
            haveCastSubmerge = false;
        }

        uint32 timeSinceSpawn;
        bool haveSubmerged;
        bool haveCastSubmerge;
        const uint32 SPELL_MIND_FLAY = 29407;

        void Reset() override
        {
            me->SetNoCallAssistance(true);
            me->SetUnitFlag(UNIT_FLAG_DISABLE_MOVE);
        }

        void KilledUnit(Unit* who) override
        {
            if (who->GetTypeId() == TYPEID_PLAYER && me->GetInstanceScript())
            {
                me->GetInstanceScript()->SetData(DATA_IMMORTAL_FAIL, 0);
            }
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (timeSinceSpawn < 3000)
                return;

            if (!who || !(who->GetDistance2d(me) <= 19.0f))
                return;

            if (me->HasReactState(REACT_AGGRESSIVE) && me->CanStartAttack(who))
            {
                if (!me->IsWithinLOSInMap(who))
                {
                    return;
                }
                me->SetNoCallAssistance(true);
                if (!me->GetVictim())
                {
                    AttackStart(who);
                }
                else if (me->GetMap()->IsDungeon())
                {
                    who->SetInCombatWith(me);
                    me->AddThreat(who, 0.0f);
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            me->SetNoCallAssistance(true);
            timeSinceSpawn += std::min(diff, std::numeric_limits<uint32>::max() - timeSinceSpawn);

            if (haveSubmerged)
            {
                if (!haveCastSubmerge)
                {
                    haveCastSubmerge = true;
                    me->CastSpell(me, 26234, false);
                }
                return;
            }

            if (!UpdateVictim())
                return;

            if (!me->IsNonMeleeSpellCast(false))
            {
                if (me->GetDistance(me->GetVictim()) < 35.0f)
                {
                    int32 bp0 = 750; // damage
                    int32 bp1 = -20; // movement speed
                    me->CastCustomSpell(me->GetVictim(), SPELL_MIND_FLAY, &bp0, &bp1, 0, false, nullptr, nullptr, ObjectGuid::Empty);
                }
                else
                {
                    DoStopAttack();
                }
            }
            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_custom_creatures_40()
{
    new boss_heigan_eye_stalk_40();
}
