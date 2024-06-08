/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "SpellAuraEffects.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "SpellScriptLoader.h"
#include "naxxramas.h"

enum Says
{
    SAY_AGGRO                       = 0,
    SAY_SLAY                        = 1,
    SAY_TAUNT                       = 2,
    EMOTE_DEATH                     = 3,
    EMOTE_DANCE                     = 4,
    EMOTE_DANCE_END                 = 5,
    SAY_DANCE                       = 6
};

enum Spells
{
    SPELL_SUMMON_PLAYER             = 25104,
    SPELL_DISRUPTION                = 55010, // 29310->55010: Mana Burn AoE spell similar to vanilla
    SPELL_DECREPIT_FEVER            = 29998,
    SPELL_PLAGUE_CLOUD              = 29350,
    SPELL_PLAGUE_CLOUD_TRIGGER      = 30122,
    SPELL_TELEPORT_SELF             = 30211,
    SPELL_TELEPORT_PLAYERS          = 29273 // updated target in db
};

enum Events
{
    EVENT_DISRUPTION                = 1,
    EVENT_DECEPIT_FEVER             = 2,
    EVENT_ERUPT_SECTION             = 3,
    EVENT_SWITCH_PHASE              = 4,
    EVENT_SAFETY_DANCE              = 5,
    EVENT_PLAGUE_CLOUD              = 6,
    EVENT_TELEPORT_PLAYER           = 7
};

enum Misc
{
    PHASE_SLOW_DANCE                = 0,
    PHASE_FAST_DANCE                = 1
};

const Position EyeStalkPositions[20] =
{
    { 2761.28f, -3765.37f, 275.08f, 1.24f },
    { 2770.17f, -3782.11f, 275.08f, 1.33f },
    { 2798.11f, -3788.94f, 275.08f, 2.35f },
    { 2797.91f, -3776.86f, 275.08f, 2.25f },
    { 2792.06f, -3762.52f, 275.08f, 2.9f, },
    { 2789.87f, -3752.15f, 275.08f, 2.74f },
    { 2804.21f, -3757.96f, 275.08f, 3.9f },
    { 2821.16f, -3759.75f, 275.08f, 4.47f },
    { 2834.64f, -3751.23f, 275.08f, 4.27f },
    { 2843.54f, -3768.08f, 275.08f, 3.06f },
    { 2862.4f,  -3758.3f,  275.08f, 4.8f },
    { 2877.8f,  -3762.46f, 275.08f, 4.8f },
    { 2894.11f, -3757.89f, 275.08f, 4.56f },
    { 2895.25f, -3779.5f,  275.08f, 2.4f },
    { 2881.59f, -3782.22f, 275.08f, 2.79f },
    { 2867.2f,  -3778.21f, 275.08f, 3.01f },
    { 2851.39f, -3776.54f, 275.08f, 2.69f },
    { 2846.16f, -3789.13f, 275.08f, 1.79f },
    { 2830.09f, -3776.49f, 275.08f, 0.94f },
    { 2813.34f, -3780.97f, 275.08f, 1.84f },
};

class boss_heigan_40 : public CreatureScript
{
public:
    boss_heigan_40() : CreatureScript("boss_heigan_40") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetNaxxramasAI<boss_heigan_40AI>(creature);
    }

    struct boss_heigan_40AI : public BossAI
    {
        explicit boss_heigan_40AI(Creature* c) : BossAI(c, BOSS_HEIGAN)
        {
            pInstance = me->GetInstanceScript();
        }

        InstanceScript* pInstance;
        EventMap events;
        uint8 currentPhase{};
        uint8 currentSection{};
        bool moveRight{};
        GuidList portedPlayersThisPhase;

        void Reset() override
        {
            BossAI::Reset();
            events.Reset();
            currentPhase = 0;
            currentSection = 3;
            portedPlayersThisPhase.clear();
            KillPlayersInTheTunnel();
            moveRight = true;
            if (pInstance)
            {
                if (GameObject* go = me->GetMap()->GetGameObject(pInstance->GetGuidData(DATA_HEIGAN_ENTER_GATE)))
                {
                    go->SetGoState(GO_STATE_ACTIVE);
                }
                // Close tunnel door
                if (GameObject* go = me->GetMap()->GetGameObject(pInstance->GetGuidData(DATA_HEIGAN_EXIT_GATE)))
                {
                    go->SetGoState(GO_STATE_READY);
                }
            }
        }

        void KilledUnit(Unit* who) override
        {
            if (who->GetTypeId() != TYPEID_PLAYER)
                return;

            Talk(SAY_SLAY);
            if (pInstance)
            {
                pInstance->SetData(DATA_IMMORTAL_FAIL, 0);
            }
        }

        void JustDied(Unit*  killer) override
        {
            BossAI::JustDied(killer);
            Talk(EMOTE_DEATH);
        }

        void JustEngagedWith(Unit* who) override
        {
            BossAI::JustEngagedWith(who);
            me->SetInCombatWithZone();
            Talk(SAY_AGGRO);
            if (pInstance)
            {
                if (GameObject* go = me->GetMap()->GetGameObject(pInstance->GetGuidData(DATA_HEIGAN_ENTER_GATE)))
                {
                    go->SetGoState(GO_STATE_READY);
                }
                // Open tunnel door
                if (GameObject* go = me->GetMap()->GetGameObject(pInstance->GetGuidData(DATA_HEIGAN_EXIT_GATE)))
                {
                    go->SetGoState(GO_STATE_ACTIVE);
                }
                // Close loatheb door
                if (GameObject* go = me->GetMap()->GetGameObject(pInstance->GetGuidData(DATA_HEIGAN_EXIT_GATE_OLD)))
                {
                    go->SetGoState(GO_STATE_READY);
                }
            }
            StartFightPhase(PHASE_SLOW_DANCE);
        }

        void StartFightPhase(uint8 phase)
        {
            currentSection = 3;
            currentPhase = phase;
            events.Reset();
            if (phase == PHASE_SLOW_DANCE)
            {
                me->CastStop();
                me->SetReactState(REACT_AGGRESSIVE);
                DoZoneInCombat();
                events.ScheduleEvent(EVENT_DISRUPTION, urand(12000, 15000));
                events.ScheduleEvent(EVENT_DECEPIT_FEVER, 17000);
                events.ScheduleEvent(EVENT_ERUPT_SECTION, 15000);
                events.ScheduleEvent(EVENT_SWITCH_PHASE, 90000);
                events.ScheduleEvent(EVENT_TELEPORT_PLAYER, 40000);
                portedPlayersThisPhase.clear();
            }
            else // if (phase == PHASE_FAST_DANCE)
            {
                Talk(EMOTE_DANCE);
                Talk(SAY_DANCE);
                me->AttackStop();
                me->StopMoving();
                me->SetReactState(REACT_PASSIVE);
                me->CastSpell(me, SPELL_TELEPORT_SELF, false);
                me->SetFacingTo(2.40f);
                events.ScheduleEvent(EVENT_PLAGUE_CLOUD, 1000);
                events.ScheduleEvent(EVENT_ERUPT_SECTION, 7000);
                events.ScheduleEvent(EVENT_SWITCH_PHASE, 45000);
            }
            events.ScheduleEvent(EVENT_SAFETY_DANCE, 5000);
        }

        bool IsInRoom(Unit* who)
        {
            if (who->GetPositionX() > 2826 || who->GetPositionX() < 2723 || who->GetPositionY() > -3641 || who->GetPositionY() < -3736)
            {
                if (who->GetGUID() == me->GetGUID())
                    EnterEvadeMode();

                return false;
            }
            return true;
        }

        void KillPlayersInTheTunnel()
        {
            // hackfix: kill everyone in the tunnel
            Map::PlayerList const& PlayerList = me->GetMap()->GetPlayers();
            for (const auto& itr : PlayerList)
            {
                if (Player* player = itr.GetSource())
                {
                    if (player->IsAlive() && !player->IsGameMaster())
                    {
                        if (player->GetPositionX() <= 2769.0f)
                        {
                            player->KillSelf();
                        }
                    }
                }
            }
        }

        void DoEventTeleportPlayer()
        {
            std::list<Unit*> candidates;
            SelectTargetList(candidates, 3, SelectTargetMethod::Random, 0, [&](Unit* target)
            {
                if (!target->IsPlayer()) // never target nonplayers (pets, guardians, etc.)
                    return false;
                if (!target->IsAlive())
                    return false;
                if (me->GetVictim() == target) // never target tank
                    return false;
                // skip players who already have been teleported this phase
                if (std::find(portedPlayersThisPhase.begin(), portedPlayersThisPhase.end(), target->GetGUID()) != portedPlayersThisPhase.end())
                    return false;
                return true;
            });

            if (candidates.empty())
                return;

            for (int i = 0; i < 3 ; i++)
            {
                if (candidates.empty())
                    break;
                auto itr = candidates.begin();
                if (candidates.size() > 1)
                    std::advance(itr, urand(0, candidates.size() - 1));
                Unit *target = *itr;
                candidates.erase(itr);
                portedPlayersThisPhase.push_back(target->GetGUID());
                DoModifyThreatByPercent(target, -99); // prevent heigan chasing and resetting
                target->CastSpell(target, SPELL_TELEPORT_PLAYERS, true);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!IsInRoom(me))
                return;

            if (!UpdateVictim())
                return;

            if (Unit* victim = me->GetVictim())
            {
                if (!me->IsWithinDistInMap(victim, VISIBILITY_DISTANCE_NORMAL))
                    me->CastSpell(victim, SPELL_SUMMON_PLAYER, true);
            }
            events.Update(diff);

            switch (events.ExecuteEvent())
            {
                case EVENT_DISRUPTION:
                    me->CastCustomSpell(SPELL_DISRUPTION, SPELLVALUE_RADIUS_MOD, 2500, me, false); // 25yd
                    events.RepeatEvent(10000);
                    break;
                case EVENT_DECEPIT_FEVER:
                {
                    int32 bp1 = 499;
                    me->CastCustomSpell(me, SPELL_DECREPIT_FEVER, 0, &bp1, 0, false, nullptr, nullptr, ObjectGuid::Empty);
                    events.RepeatEvent(urand(22000, 25000));
                    break;
                }
                case EVENT_PLAGUE_CLOUD:
                    me->CastSpell(me, SPELL_PLAGUE_CLOUD, false);
                    break;
                case EVENT_SWITCH_PHASE:
                    if (currentPhase == PHASE_SLOW_DANCE)
                    {
                        StartFightPhase(PHASE_FAST_DANCE);
                    }
                    else
                    {
                        StartFightPhase(PHASE_SLOW_DANCE);
                        Talk(EMOTE_DANCE_END); // avoid play the emote on aggro
                    }
                    break;
                case EVENT_ERUPT_SECTION:
                    if (pInstance)
                    {
                        if (currentPhase == PHASE_FAST_DANCE)
                        {
                            if (currentSection >= 1)
                                KillPlayersInTheTunnel();
                        }
                        pInstance->SetData(DATA_HEIGAN_ERUPTION, currentSection);
                        if (currentSection == 3)
                        {
                            moveRight = false;
                        }
                        else if (currentSection == 0)
                        {
                            moveRight = true;
                        }
                        moveRight ? currentSection++ : currentSection--;
                    }
                    if (currentPhase == PHASE_SLOW_DANCE)
                    {
                        Talk(SAY_TAUNT);
                    }
                    events.RepeatEvent(currentPhase == PHASE_SLOW_DANCE ? 10000 : 4000);
                    break;
                case EVENT_SAFETY_DANCE:
                    {
                        Map::PlayerList const& pList = me->GetMap()->GetPlayers();
                        for (const auto& itr : pList)
                        {
                            if (IsInRoom(itr.GetSource()) && !itr.GetSource()->IsAlive())
                            {
                                pInstance->SetData(DATA_DANCE_FAIL, 0);
                                pInstance->SetData(DATA_IMMORTAL_FAIL, 0);
                                return;
                            }
                        }
                        events.RepeatEvent(5000);
                        return;
                    }
                case EVENT_TELEPORT_PLAYER:
                    DoEventTeleportPlayer();
                    break;
            }
            DoMeleeAttackIfReady();
        }
    };
};

class spell_heigan_plague_cloud_40 : public SpellScriptLoader
{
public:
    spell_heigan_plague_cloud_40() : SpellScriptLoader("spell_heigan_plague_cloud_40") { }

    class spell_heigan_plague_cloud_40_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_heigan_plague_cloud_40_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_PLAGUE_CLOUD_TRIGGER });
        }

        void HandleTriggerSpell(AuraEffect const* /*aurEff*/)
        {
            Unit* caster = GetCaster();
            if (!caster || (caster->GetMap()->GetDifficulty() != RAID_DIFFICULTY_10MAN_HEROIC))
            {
                return;
            }
            PreventDefaultAction();
            int32 bp0 = 4000;
            caster->CastCustomSpell(caster, SPELL_PLAGUE_CLOUD_TRIGGER, &bp0, 0, 0, true);
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_heigan_plague_cloud_40_AuraScript::HandleTriggerSpell, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_heigan_plague_cloud_40_AuraScript();
    }
};

class spell_heigan_eruption_40 : public SpellScriptLoader
{
public:
    spell_heigan_eruption_40() : SpellScriptLoader("spell_heigan_eruption_40") { }

    class spell_heigan_eruption_40_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_heigan_eruption_40_SpellScript);

        void HandleDamageCalc(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster || (caster->GetMap()->GetDifficulty() != RAID_DIFFICULTY_10MAN_HEROIC))
            {
                return;
            }
            SetEffectValue(urand(3500, 4500));
        }

        void Register() override
        {
            OnEffectLaunchTarget += SpellEffectFn(spell_heigan_eruption_40_SpellScript::HandleDamageCalc, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_heigan_eruption_40_SpellScript();
    }
};

// 28819 - Submerge Visual
class spell_submerge_visual : public SpellScriptLoader
{
public:
    spell_submerge_visual() : SpellScriptLoader("spell_submerge_visual") { }

    class spell_submerge_visual_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_submerge_visual_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            GetTarget()->SetStandState(UNIT_STAND_STATE_SUBMERGED);
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            GetTarget()->SetStandState(UNIT_STAND_STATE_STAND);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_submerge_visual_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_submerge_visual_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_submerge_visual_AuraScript();
    }
};

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
void AddSC_boss_heigan_40()
{
    new boss_heigan_40();
    new spell_heigan_plague_cloud_40();
    new spell_heigan_eruption_40();
    new spell_submerge_visual();
    new boss_heigan_eye_stalk_40();
}
