/*
 * Copyright (C) 2020 LegacyGroupProject <https://github.com/ReyDonovan/LegacyMoP>
 * Copyright (C) 2016 Firestorm Servers <https://firestorm-servers.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "CreatureTextMgr.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "Player.h"

enum eSpells
{
    SPELL_CRUSH             = 137504,
    SPELL_ALPHA_MALE        = 138391, // Boss Passive Aura. Triggers 138390 Tank Threat Multiplier.
    SPELL_FRILL_BLAST       = 137505,
    SPELL_GROWING_FURY      = 137502,
    SPELL_PIERCING_ROAR     = 137457,
    SPELL_SPIRITFIRE_BEAM   = 137511  // Or 137508??
};

enum eEvents
{
    EVENT_CRUSH             = 1,// 60s from start. Every 25 - 30s.
    EVENT_FRILL_BLAST,          // 40s from start. Every 25 - 30s.
    EVENT_GROWING_FURY,         // Every 30s.
    EVENT_PIERCING_ROAR,        // 20s from start. Every 25 - 30s.
    EVENT_SPIRITFIRE_BEAM       // 15s from start. Every 25 - 30s.
};

// Oondasta - 69161
class boss_oondasta : public CreatureScript
{
    public:
        boss_oondasta() : CreatureScript("boss_oondasta") { }

        struct boss_oondastaAI : public ScriptedAI
        {
            boss_oondastaAI(Creature* creature) : ScriptedAI(creature) { }

            EventMap _events;

            void InitializeAI() override
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset() override
            {
                //me->ReenableEvadeMode();
                me->RemoveAurasDueToSpell(SPELL_CRUSH);
                me->RemoveAura(SPELL_GROWING_FURY);

                _events.Reset();

                if (!me->HasAura(SPELL_ALPHA_MALE))
                    me->AddAura(SPELL_ALPHA_MALE, me);
            }

            void EnterCombat(Unit* /*who*/) override
            {
                _events.ScheduleEvent(EVENT_SPIRITFIRE_BEAM, 15000);
                _events.ScheduleEvent(EVENT_PIERCING_ROAR, 20000);
                _events.ScheduleEvent(EVENT_FRILL_BLAST, 40000);
                _events.ScheduleEvent(EVENT_CRUSH, 60000);

                _events.ScheduleEvent(EVENT_GROWING_FURY, 30000); // Soft Enrage.
            }

            void EnterEvadeMode() override
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(false);

                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustReachedHome() override
            {
                if (!me->HasAura(SPELL_ALPHA_MALE))
                    me->AddAura(SPELL_ALPHA_MALE, me);
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                _events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                switch (_events.ExecuteEvent())
                {
                    case EVENT_CRUSH:
                        DoCastVictim(SPELL_CRUSH);
                        _events.ScheduleEvent(EVENT_CRUSH, urand(25000, 30000));
                        break;
                    case EVENT_FRILL_BLAST:
                        DoCast(me, SPELL_FRILL_BLAST);
                        _events.ScheduleEvent(EVENT_FRILL_BLAST, urand(25000, 30000));
                        break;
                    case EVENT_PIERCING_ROAR:
                        DoCast(me, SPELL_PIERCING_ROAR);
                        _events.ScheduleEvent(EVENT_PIERCING_ROAR, urand(25000, 30000));
                        break;
                    case EVENT_SPIRITFIRE_BEAM:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                            DoCast(target, SPELL_SPIRITFIRE_BEAM);
                        _events.ScheduleEvent(EVENT_SPIRITFIRE_BEAM, urand(25000, 30000));
                        break;
                    case EVENT_GROWING_FURY: // Soft Enrage.
                        DoCast(me, SPELL_GROWING_FURY);
                        _events.ScheduleEvent(EVENT_GROWING_FURY, 30000);
                        break;
                    default:
                        break;
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new boss_oondastaAI(creature);
        }
};

void AddSC_boss_oondasta()
{
    new boss_oondasta();
}