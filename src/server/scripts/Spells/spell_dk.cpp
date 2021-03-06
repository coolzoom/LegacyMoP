 /*
 * Copyright (C) 2020 LegacyProjectMoP
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

/*
 * Scripts for spells with SPELLFAMILY_DEATHKNIGHT and SPELLFAMILY_GENERIC spells used by deathknight players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_dk_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum DeathKnightSpells
{
    DK_SPELL_RUNIC_POWER_ENERGIZE               = 49088,
    DK_SPELL_ANTI_MAGIC_SHELL_TALENT            = 51052,
    DK_SPELL_SCOURGE_STRIKE_TRIGGERED           = 70890,
    DK_SPELL_BLOOD_BOIL_TRIGGERED               = 65658,
    SPELL_DK_ITEM_T8_MELEE_4P_BONUS             = 64736,
    DK_SPELL_BLACK_ICE_R1                       = 49140,
    DK_SPELL_BLOOD_PLAGUE                       = 55078,
    DK_SPELL_PLAGUE_STRIKE                      = 45462,
    DK_SPELL_FROST_FEVER                        = 55095,
    DK_SPELL_MASTER_OF_GHOULS                   = 52143,
    DK_SPELL_GHOUL_AS_GUARDIAN                  = 46585,
    DK_SPELL_GHOUL_AS_PET                       = 52150,
    DK_SPELL_ROILING_BLOOD                      = 108170,
    DK_SPELL_PESTILENCE                         = 50842,
    DK_SPELL_CHILBLAINS                         = 50041,
    DK_SPELL_CHAINS_OF_ICE_ROOT                 = 53534,
    DK_SPELL_PLAGUE_LEECH                       = 123693,
    DK_SPELL_PERDITION                          = 123981,
    DK_SPELL_SHROUD_OF_PURGATORY                = 116888,
    DK_SPELL_PURGATORY_INSTAKILL                = 123982,
    DK_SPELL_BLOOD_RITES                        = 50034,
    DK_SPELL_DEATH_SIPHON_HEAL                  = 116783,
    DK_SPELL_BLOOD_CHARGE                       = 114851,
    DK_SPELL_PILLAR_OF_FROST                    = 51271,
    DK_SPELL_SOUL_REAPER_HASTE                  = 114868,
    DK_SPELL_SOUL_REAPER_DAMAGE                 = 114867,
    DK_SPELL_REMORSELESS_WINTER_STUN            = 115001,
    DK_SPELL_REMORSELESS_WINTER                 = 115000,
    DK_SPELL_CONVERSION                         = 119975,
    DK_SPELL_WEAKENED_BLOWS                     = 115798,
    DK_SPELL_SCARLET_FEVER                      = 81132,
    DK_SPELL_SCENT_OF_BLOOD_AURA                = 50421,
    DK_SPELL_CHAINS_OF_ICE                      = 45524,
    DK_SPELL_EBON_PLAGUEBRINGER                 = 51160,
    DK_SPELL_DESECRATED_GROUND                  = 118009,
    DK_SPELL_DESECRATED_GROUND_IMMUNE           = 115018,
    DK_SPELL_ASPHYXIATE                         = 108194,
    DK_SPELL_DARK_INFUSION_STACKS               = 91342,
    DK_SPELL_DARK_INFUSION_AURA                 = 93426,
    DK_NPC_WILD_MUSHROOM                        = 59172,
    DK_SPELL_RUNIC_CORRUPTION_REGEN             = 51460,
    DK_SPELL_RUNIC_EMPOWERMENT                  = 81229,
    DK_SPELL_GOREFIENDS_GRASP_GRIP_VISUAL       = 114869,
    DK_SPELL_DEATH_GRIP_ONLY_JUMP               = 146599,
    DK_SPELL_GLYPH_OF_CORPSE_EXPLOSION          = 127344,
    DK_SPELL_GLYPH_OF_HORN_OF_WINTER            = 58680,
    DK_SPELL_GLYPH_OF_HORN_OF_WINTER_EFFECT     = 121920,
    DK_SPELL_GLYPH_OF_DEATH_AND_DECAY           = 58629,
    DK_SPELL_DEATH_AND_DECAY_DECREASE_SPEED     = 143375,
    DK_SPELL_NECROTIC_STRIKE                    = 73975,
    DK_SPELL_RIPOSTE                            = 145677,
    DK_SPELL_GEIST_FORM                         = 121916,
    DK_SPELL_SOUL_REAPER_BUFF                   = 114868,
    DK_SPELL_ANTIMAGIC_SHELL_SELF               = 48707,
    DK_GLYPH_OF_REGENERATIVE_MAGIC              = 146648,
    DK_SPELL_STRANGULATE                        = 47476,
    DK_GLYPH_OF_THE_LOUD_HORN                   = 146646
};

// Death and Decay - 43265
class spell_dk_death_and_decay : public SpellScriptLoader
{
    public:
        spell_dk_death_and_decay() : SpellScriptLoader("spell_dk_death_and_decay") { }

        class spell_dk_death_and_decay_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_and_decay_SpellScript);

            void HandleAfterCast()
            {
                WorldLocation* dest = const_cast<WorldLocation*>(GetExplTargetDest());
                if (dest && GetCaster()->HasAura(DK_SPELL_GLYPH_OF_DEATH_AND_DECAY))
                    GetCaster()->CastSpell(dest->GetPositionX(), dest->GetPositionY(), dest->GetPositionZ(), DK_SPELL_DEATH_AND_DECAY_DECREASE_SPEED, true);
            }

            void Register() override
            {
                AfterCast += SpellCastFn(spell_dk_death_and_decay_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_and_decay_SpellScript();
        }
};

// Gorefiend's Grasp - 108199
class spell_dk_gorefiends_grasp : public SpellScriptLoader
{
    public:
        spell_dk_gorefiends_grasp() : SpellScriptLoader("spell_dk_gorefiends_grasp") { }

        class spell_dk_gorefiends_grasp_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_gorefiends_grasp_SpellScript);

            void HandleScript(SpellEffIndex effIndex)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        std::list<Unit*> list;

                        target->GetAttackableUnitListInRange(list, 20.0f);

                        for (auto itr : list)
                        {
                            if (itr->GetGUID() == _player->GetGUID())
                                continue;

                            if (!_player->IsValidAttackTarget(itr))
                                continue;

                            if (!itr->IsWithinLOSInMap(target))
                                continue;

                            // TODO: we must use aoe effects of the spell to trigger other spells
                            if (itr->IsImmunedToSpell(GetSpellInfo()))
                                continue;

                            itr->CastSpell(target, DK_SPELL_DEATH_GRIP_ONLY_JUMP, true);
                            itr->CastSpell(target, DK_SPELL_GOREFIENDS_GRASP_GRIP_VISUAL, true);
                        }
                    }
                }
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_gorefiends_grasp_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_gorefiends_grasp_SpellScript();
        }
};

// Called by Death Coil (damage) - 47632, Frost Strike - 49143 and Runic Strike - 56815
// Runic Empowerment - 81229
class spell_dk_runic_empowerment : public SpellScriptLoader
{
    public:
        spell_dk_runic_empowerment() : SpellScriptLoader("spell_dk_runic_empowerment") { }

        class spell_dk_runic_empowerment_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_runic_empowerment_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasAura(DK_SPELL_RUNIC_EMPOWERMENT))
                    {
                        if (roll_chance_i(45))
                        {
                            std::set<uint8> runes;
                            for (uint8 i = 0; i < MAX_RUNES; i++)
                                if (_player->GetRuneCooldown(i) == _player->GetRuneBaseCooldown(i))
                                    runes.insert(i);
                            if (!runes.empty())
                            {
                                std::set<uint8>::iterator itr = runes.begin();
                                std::advance(itr, urand(0, runes.size()-1));
                                _player->SetRuneCooldown((*itr), 0);
                                _player->ResyncRunes(MAX_RUNES);
                            }
                        }
                    }
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_runic_empowerment_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_runic_empowerment_SpellScript();
        }
};

// Called by Death Coil (damage) - 47632, Frost Strike - 49143 and Runic Strike - 56815
// Runic Corruption - 51462
class spell_dk_runic_corruption : public SpellScriptLoader
{
    public:
        spell_dk_runic_corruption() : SpellScriptLoader("spell_dk_runic_corruption") { }

        class spell_dk_runic_corruption_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_runic_corruption_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (AuraEffect const* runicCorruption = _player->GetDummyAuraEffect(SPELLFAMILY_DEATHKNIGHT, 4068, 0))
                    {
                        if (roll_chance_i(45))
                        {
                            int32 basepoints0 = runicCorruption->GetAmount();
                            if (Aura* aur = _player->GetAura(DK_SPELL_RUNIC_CORRUPTION_REGEN))
                                aur->SetDuration(aur->GetDuration() + 3000);
                            else
                                _player->CastCustomSpell(_player, DK_SPELL_RUNIC_CORRUPTION_REGEN, &basepoints0, NULL, NULL, true);
                        }
                    }
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_runic_corruption_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_runic_corruption_SpellScript();
        }
};

// Might of Ursoc - 113072
class spell_dk_might_of_ursoc : public SpellScriptLoader
{
    public:
        spell_dk_might_of_ursoc() : SpellScriptLoader("spell_dk_might_of_ursoc") { }

        class spell_dk_might_of_ursoc_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_might_of_ursoc_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    if (caster->GetHealthPct() < 15.0f)
                        caster->SetHealth(caster->CountPctFromMaxHealth(15));
            }

            void Register() override
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dk_might_of_ursoc_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_might_of_ursoc_AuraScript();
        }
};

// Wild Mushroom : Plague - 113517
class spell_dk_wild_mushroom_plague : public SpellScriptLoader
{
    public:
        spell_dk_wild_mushroom_plague() : SpellScriptLoader("spell_dk_wild_mushroom_plague") { }

        class spell_dk_wild_mushroom_plague_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_wild_mushroom_plague_AuraScript);

            void OnTick(AuraEffect const* aurEff)
            {
                if (!GetCaster())
                    return;

                std::list<Creature*> tempList;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    _player->GetCreatureListWithEntryInGrid(tempList, DK_NPC_WILD_MUSHROOM, 200.0f);

                    // Remove other players mushrooms
                    for (std::list<Creature*>::iterator i = tempList.begin(); i != tempList.end();)
                    {
                        Unit* owner = (*i)->GetOwner();
                        if (owner && owner == _player && (*i)->IsSummon())
                        {
                            ++i;
                            continue;
                        }

                        i = tempList.erase(i);
                    }

                    if (!tempList.empty())
                    {
                        std::list<Unit*> tempUnitList;
                        for (auto itr : tempList)
                        {
                            itr->GetAttackableUnitListInRange(tempUnitList, 10.0f);

                            for (auto itr2 : tempUnitList)
                            {
                                if (itr2->GetGUID() == _player->GetGUID())
                                    continue;

                                if (itr2->GetGUID() == itr->GetGUID())
                                    continue;

                                if (!_player->IsValidAttackTarget(itr2))
                                    continue;

                                _player->CastSpell(itr2, DK_SPELL_BLOOD_PLAGUE, true);
                                _player->CastSpell(itr2, DK_SPELL_FROST_FEVER, true);
                            }
                        }
                    }
                }
            }

            void Register() override
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_dk_wild_mushroom_plague_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_wild_mushroom_plague_AuraScript();
        }
};

// Dark transformation - transform pet spell - 63560
class spell_dk_dark_transformation_form : public SpellScriptLoader
{
    public:
        spell_dk_dark_transformation_form() : SpellScriptLoader("spell_dk_dark_transformation_form") { }

        class spell_dk_dark_transformation_form_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_dark_transformation_form_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* pet = GetHitUnit())
                    {
                        if (pet->HasAura(DK_SPELL_DARK_INFUSION_STACKS))
                        {
                            _player->RemoveAura(DK_SPELL_DARK_INFUSION_STACKS);
                            pet->RemoveAura(DK_SPELL_DARK_INFUSION_STACKS);
                        }
                    }
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_dark_transformation_form_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_dark_transformation_form_SpellScript();
        }
};

// Desecrated ground - 118009
class spell_dk_desecrated_ground : public SpellScriptLoader
{
    public:
        spell_dk_desecrated_ground() : SpellScriptLoader("spell_dk_desecrated_ground") { }

        class spell_dk_desecrated_ground_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_desecrated_ground_AuraScript);

            void OnTick(AuraEffect const* aurEff)
            {
                if (GetCaster())
                    if (DynamicObject* dynObj = GetCaster()->GetDynObject(DK_SPELL_DESECRATED_GROUND))
                        if (GetCaster()->GetDistance(dynObj) <= 8.0f)
                            GetCaster()->CastSpell(GetCaster(), DK_SPELL_DESECRATED_GROUND_IMMUNE, true);
            }

            void Register() override
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_dk_desecrated_ground_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_desecrated_ground_AuraScript();
        }
};

// Necrotic Strike - 73975
class spell_dk_necrotic_strike : public SpellScriptLoader
{
    public:
        spell_dk_necrotic_strike() : SpellScriptLoader("spell_dk_necrotic_strike") { }

        class spell_dk_necrotic_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_necrotic_strike_SpellScript);

            int32 newBonus;

            void HandleBeforeHit()
            {
                if (Unit* target = GetHitUnit())
                {
                    if (Aura* necroticHealAbsorb = target->GetAura(DK_SPELL_NECROTIC_STRIKE))
                        newBonus = target->GetRemainingPeriodicAmount(GetCaster()->GetGUID(), DK_SPELL_NECROTIC_STRIKE, SPELL_AURA_SCHOOL_HEAL_ABSORB, 0);
                    else
                        newBonus = 0;
                }
            }

            void HandleAfterHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        // amount of heal absorb
                        if (Aura* necroticHealAbsorb = target->GetAura(DK_SPELL_NECROTIC_STRIKE))
                        {
                            float amount = _player->GetTotalAttackPowerValue(WeaponAttackType::BASE_ATTACK) * 2.25f;
                            float PvPPower = (1 + GetCaster()->GetFloatValue(PLAYER_FIELD_PVP_POWER_DAMAGE) / 100);

                            auto add = int32(amount * PvPPower);
                            add = add - target->GetDamageReduction(uint32(add));
                            newBonus += add;

                            necroticHealAbsorb->GetEffect(0)->SetAmount(newBonus);
                        }

                        /*for (uint32 i = 0; i < MAX_RUNES; ++i)
                        {
                            RuneType rune = _player->GetCurrentRune(i);

                            if (!_player->GetRuneCooldown(i) && rune == RUNE_DEATH)
                            {
                                uint32 cooldown = _player->GetRuneBaseCooldown(i);
                                _player->SetRuneCooldown(i, cooldown);

                                bool takePower = true;
                                if (uint32 spell = _player->GetRuneConvertSpell(i))
                                    takePower = spell != 54637;

                                if (_player->IsRunePermanentlyConverted(i))
                                    takePower = false;

                                // keep Death Rune type if player has Blood of the North
                                if (takePower)
                                {
                                    _player->RestoreBaseRune(i);
                                    _player->SetDeathRuneUsed(i, true);
                                }

                                break;
                            }
                        }*/
                    }
                }
            }
            void Register() override
            {
                BeforeHit += SpellHitFn(spell_dk_necrotic_strike_SpellScript::HandleBeforeHit);
                AfterHit += SpellHitFn(spell_dk_necrotic_strike_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_necrotic_strike_SpellScript();
        }
};

// Festering Strike - 85948
class spell_dk_festering_strike : public SpellScriptLoader
{
    public:
        spell_dk_festering_strike() : SpellScriptLoader("spell_dk_festering_strike") { }

        class spell_dk_festering_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_festering_strike_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (Aura* BP = target->GetAura(DK_SPELL_BLOOD_PLAGUE, _player->GetGUID()))
                        {
                            uint32 dur = BP->GetDuration() + 6000;
                            BP->SetDuration(dur);

                            if (dur > uint32(BP->GetMaxDuration()))
                                BP->SetMaxDuration(dur);

                            if (Aura* PV = target->GetAura(81326, _player->GetGUID()))
                            {
                                PV->SetDuration(dur);

                                if (dur > uint32(PV->GetMaxDuration()))
                                    PV->SetMaxDuration(dur);
                            }
                        }
                        if (Aura* FF = target->GetAura(DK_SPELL_FROST_FEVER, _player->GetGUID()))
                        {
                            uint32 dur = FF->GetDuration() + 6000;
                            FF->SetDuration(dur);

                            if (dur > uint32(FF->GetMaxDuration()))
                                FF->SetMaxDuration(dur);
                        }
                        if (Aura* COI = target->GetAura(DK_SPELL_CHAINS_OF_ICE, _player->GetGUID()))
                        {
                            uint32 dur = COI->GetDuration() + 6000;
                            COI->SetDuration(dur);

                            if (dur > uint32(COI->GetMaxDuration()))
                                COI->SetMaxDuration(dur);
                        }
                    }
                }
            }
            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_festering_strike_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_festering_strike_SpellScript();
        }
};

// Death Strike heal - 45470
class spell_dk_death_strike_heal : public SpellScriptLoader
{
    public:
        spell_dk_death_strike_heal() : SpellScriptLoader("spell_dk_death_strike_heal") { }

        class spell_dk_death_strike_heal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_strike_heal_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (Aura* scentOfBlood = _player->GetAura(DK_SPELL_SCENT_OF_BLOOD_AURA))
                        {
                            uint8 chg = scentOfBlood->GetStackAmount();
                            uint32 hl = GetHitHeal() * 0.2 * chg;
                            SetHitHeal(GetHitHeal() + hl);
                        }

                        // Death Strike heal depends on PvP Power
                        int32 heal = GetHitHeal();
                        float PvPPower = _player->GetPvpHealingBonus();
                        heal = int32(heal * PvPPower);
                        SetHitHeal(heal);

                        _player->RemoveAura(DK_SPELL_SCENT_OF_BLOOD_AURA);
                    }
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_death_strike_heal_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_strike_heal_SpellScript();
        }
};

// Howling Blast - 49184
class spell_dk_howling_blast : public SpellScriptLoader
{
    public:
        spell_dk_howling_blast() : SpellScriptLoader("spell_dk_howling_blast") { }

        class spell_dk_howling_blast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_howling_blast_SpellScript);

            uint64 tar;

            void HandleBeforeCast()
            {
                Unit* target = GetExplTargetUnit();
                Unit* caster = GetCaster();

                if (!caster || !target)
                    return;

                tar = target->GetGUID();
            }

            void HandleOnHit()
            {
                Unit* target = GetHitUnit();
                Unit* caster = GetCaster();

                if (!caster || !target || !tar)
                    return;

                if (target->GetGUID() != tar)
                    SetHitDamage(int32(GetHitDamage() / 2));

                caster->CastSpell(target, DK_SPELL_FROST_FEVER, true);
            }

            void Register() override
            {
                BeforeCast += SpellCastFn(spell_dk_howling_blast_SpellScript::HandleBeforeCast);
                OnHit += SpellHitFn(spell_dk_howling_blast_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_howling_blast_SpellScript();
        }
};

// Remorseless Winter - 115000
class spell_dk_remorseless_winter : public SpellScriptLoader
{
    public:
        spell_dk_remorseless_winter() : SpellScriptLoader("spell_dk_remorseless_winter") { }

        class spell_dk_remorseless_winter_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_remorseless_winter_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (Aura* remorselessWinter = target->GetAura(DK_SPELL_REMORSELESS_WINTER))
                            if (remorselessWinter->GetStackAmount() == 5 && !target->HasAura(DK_SPELL_REMORSELESS_WINTER_STUN))
                                _player->CastSpell(target, DK_SPELL_REMORSELESS_WINTER_STUN, true);
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_remorseless_winter_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_remorseless_winter_SpellScript();
        }
};

// Soul Reaper - 130736 (unholy) or 130735 (frost) or 114866 (blood)
class spell_dk_soul_reaper : public SpellScriptLoader
{
    public:
        spell_dk_soul_reaper() : SpellScriptLoader("spell_dk_soul_reaper") { }

        class spell_dk_soul_reaper_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_soul_reaper_AuraScript);

            void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetCaster())
                {
                    AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                    if (removeMode == AURA_REMOVE_BY_DEATH)
                        GetCaster()->CastSpell(GetCaster(), DK_SPELL_SOUL_REAPER_HASTE, true);
                    else if (removeMode == AURA_REMOVE_BY_EXPIRE && GetTarget()->GetHealthPct() < 35.0f)
                        GetCaster()->CastSpell(GetTarget(), DK_SPELL_SOUL_REAPER_DAMAGE, true);
                }
            }

            void Register() override
            {
                AfterEffectRemove += AuraEffectApplyFn(spell_dk_soul_reaper_AuraScript::HandleRemove, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_soul_reaper_AuraScript();
        }
};

// Pillar of Frost - 51271
class spell_dk_pillar_of_frost : public SpellScriptLoader
{
    public:
        spell_dk_pillar_of_frost() : SpellScriptLoader("spell_dk_pillar_of_frost") { }

        class spell_dk_pillar_of_frost_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_pillar_of_frost_AuraScript);

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->ApplySpellImmune(DK_SPELL_PILLAR_OF_FROST, IMMUNITY_MECHANIC, MECHANIC_KNOCKOUT, false);
            }

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->ApplySpellImmune(DK_SPELL_PILLAR_OF_FROST, IMMUNITY_MECHANIC, MECHANIC_KNOCKOUT, true);
            }

            void Register() override
            {
                OnEffectApply += AuraEffectApplyFn(spell_dk_pillar_of_frost_AuraScript::OnApply, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_dk_pillar_of_frost_AuraScript::OnRemove, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_pillar_of_frost_AuraScript();
        }
};

// Called by Death Coil - 47541, Rune Strike - 56815 and Frost Strike - 49143
// Blood Charges - 114851 for Blood Tap - 45529
class spell_dk_blood_charges : public SpellScriptLoader
{
    public:
        spell_dk_blood_charges() : SpellScriptLoader("spell_dk_blood_charges") { }

        class spell_dk_blood_charges_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_blood_charges_SpellScript);

            enum eSpells
            {
                GlyphofDeathsEmbrace        = 58677,
                GlyphofDeathsEmbraceAura    = 58679,
                DeathCoil                   = 47541
            };

            void HandleOnHit()
            {
                if (Player* l_Player = GetCaster()->ToPlayer())
                {
                    if (Unit* l_Target = GetHitUnit())
                    {
                        if (GetSpellInfo()->Id == eSpells::DeathCoil && l_Player->HasGlyph(eSpells::GlyphofDeathsEmbrace) && l_Target->IsPet() && l_Player->IsValidAssistTarget(l_Target))
                            l_Player->CastSpell(l_Player, GlyphofDeathsEmbraceAura, true);
                        else if (l_Player->HasSpell(45529))
                        {
                            l_Player->CastSpell(l_Player, DK_SPELL_BLOOD_CHARGE, true);
                            l_Player->CastSpell(l_Player, DK_SPELL_BLOOD_CHARGE, true);
                        }
                    }
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_blood_charges_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_blood_charges_SpellScript();
        }
};

// Blood Tap - 45529
class spell_dk_blood_tap : public SpellScriptLoader
{
    public:
        spell_dk_blood_tap() : SpellScriptLoader("spell_dk_blood_tap") { }

        class spell_dk_blood_tap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_blood_tap_SpellScript);

            SpellCastResult CheckBloodCharges()
            {
                if (GetCaster()->ToPlayer())
                {
                    if (Aura* bloodCharges = GetCaster()->ToPlayer()->GetAura(DK_SPELL_BLOOD_CHARGE))
                    {
                        if (bloodCharges->GetStackAmount() < 5)
                            return SPELL_FAILED_DONT_REPORT;
                    }
                    else
                        return SPELL_FAILED_DONT_REPORT;

                    bool cooldown = false;

                    for (uint8 i = 0; i < MAX_RUNES; ++i)
                    {
                        if (GetCaster()->ToPlayer()->GetCurrentRune(i) == RuneType::RUNE_DEATH || !GetCaster()->ToPlayer()->GetRuneCooldown(i))
                            continue;

                        cooldown = true;
                    }

                    if (!cooldown)
                        return SPELL_FAILED_DONT_REPORT;
                }

                return SPELL_CAST_OK;
            }

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (Aura* bloodCharges = _player->GetAura(DK_SPELL_BLOOD_CHARGE))
                        {
                            int32 newAmount = bloodCharges->GetStackAmount();

                            if ((newAmount - 5) <= 0)
                                _player->RemoveAura(DK_SPELL_BLOOD_CHARGE);
                            else
                                bloodCharges->SetStackAmount(newAmount - 5);
                        }
                    }
                }
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_blood_tap_SpellScript::CheckBloodCharges);
                OnHit += SpellHitFn(spell_dk_blood_tap_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_blood_tap_SpellScript();
        }
};

// Death Siphon - 108196
class spell_dk_death_siphon : public SpellScriptLoader
{
    public:
        spell_dk_death_siphon() : SpellScriptLoader("spell_dk_death_siphon") { }

        class spell_dk_death_siphon_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_siphon_SpellScript);

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        int32 bp = GetHitDamage() * 1.5f;
                        bool runeDeath = false;

                        _player->CastCustomSpell(_player, DK_SPELL_DEATH_SIPHON_HEAL, &bp, NULL, NULL, true);
                    }
                }
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_death_siphon_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_siphon_SpellScript();
        }
};

// Improved Blood Presence - 50371
class spell_dk_improved_blood_presence : public SpellScriptLoader
{
    public:
        spell_dk_improved_blood_presence() : SpellScriptLoader("spell_dk_improved_blood_presence") { }

        class spell_dk_improved_blood_presence_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_improved_blood_presence_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->UpdateAllRunesRegen();
            }

            void Register() override
            {
                AfterCast += SpellCastFn(spell_dk_improved_blood_presence_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_improved_blood_presence_SpellScript();
        }
};

// Unholy Presence - 48265 and Improved Unholy Presence - 50392
class spell_dk_unholy_presence : public SpellScriptLoader
{
    public:
        spell_dk_unholy_presence() : SpellScriptLoader("spell_dk_unholy_presence") { }

        class spell_dk_unholy_presence_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_unholy_presence_AuraScript);

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->UpdateAllRunesRegen();
            }

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->UpdateAllRunesRegen();
            }

            void Register() override
            {
                OnEffectApply += AuraEffectApplyFn(spell_dk_unholy_presence_AuraScript::OnApply, EFFECT_1, SPELL_AURA_MOD_INCREASE_SPEED, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_dk_unholy_presence_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_MOD_INCREASE_SPEED, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_unholy_presence_AuraScript();
        }
};

// Death Strike - 49998
class spell_dk_death_strike : public SpellScriptLoader
{
    public:
        spell_dk_death_strike() : SpellScriptLoader("spell_dk_death_strike") { }

        class spell_dk_death_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_strike_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        // Apply Blood Rites effects
                        if (_player->HasAura(DK_SPELL_BLOOD_RITES))
                        {
                            SetHitDamage(int32(GetHitDamage() * 1.4f));

                            bool runeFrost = false;
                            bool runeUnholy = false;

                            for (uint8 i = 0; i < MAX_RUNES; ++i)
                            {
                                if (_player->GetCurrentRune(i) == RuneType::RUNE_DEATH
                                    || _player->GetCurrentRune(i) == RuneType::RUNE_BLOOD
                                    || _player->GetBaseRune(i) == RuneType::RUNE_BLOOD)
                                    continue;

                                if (runeUnholy && _player->GetCurrentRune(i) == RuneType::RUNE_UNHOLY)
                                    continue;

                                if (runeFrost && _player->GetCurrentRune(i) == RuneType::RUNE_FROST)
                                    continue;

                                if (_player->GetRuneCooldown(i))
                                {
                                    if (_player->GetCurrentRune(i) == RuneType::RUNE_FROST)
                                        runeFrost = true;
                                    else
                                        runeUnholy = true;

                                    _player->ConvertRune(i, RuneType::RUNE_DEATH);
                                }
                            }
                        }
                    }
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_death_strike_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_strike_SpellScript();
        }
};

// Purgatory - 116888
class spell_dk_purgatory : public SpellScriptLoader
{
    public:
        spell_dk_purgatory() : SpellScriptLoader("spell_dk_purgatory") { }

        class spell_dk_purgatory_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_purgatory_AuraScript);

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                {
                    AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                    if (removeMode == AURA_REMOVE_BY_EXPIRE)
                        _player->CastSpell(_player, DK_SPELL_PURGATORY_INSTAKILL, true);
                }
            }

            void Register() override
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_dk_purgatory_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_HEAL_ABSORB, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_purgatory_AuraScript();
        }
};

// Purgatory - 114556
class spell_dk_purgatory_absorb : public SpellScriptLoader
{
    public:
        spell_dk_purgatory_absorb() : SpellScriptLoader("spell_dk_purgatory_absorb") { }

        class spell_dk_purgatory_absorb_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_purgatory_absorb_AuraScript);

            void CalculateAmount(AuraEffect const* /*auraEffect*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                amount = -1;
            }

            void Absorb(AuraEffect* /*auraEffect*/, DamageInfo& dmgInfo, uint32& absorbAmount)
            {
                Unit* target = GetTarget();

                if (dmgInfo.GetDamage() < target->GetHealth())
                    return;

                // No damage received under Shroud of Purgatory
                if (target->ToPlayer()->HasAura(DK_SPELL_SHROUD_OF_PURGATORY))
                {
                    absorbAmount = dmgInfo.GetDamage();
                    return;
                }

                if (target->ToPlayer()->HasAura(DK_SPELL_PERDITION))
                    return;

                int32 bp = dmgInfo.GetDamage();

                target->CastCustomSpell(target, DK_SPELL_SHROUD_OF_PURGATORY, &bp, NULL, NULL, true);
                target->CastSpell(target, DK_SPELL_PERDITION, true);
                target->SetHealth(1);
                absorbAmount = dmgInfo.GetDamage();
            }

            void Register() override
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_purgatory_absorb_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_purgatory_absorb_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_purgatory_absorb_AuraScript();
        }
};

// Plague Leech - 123693
class spell_dk_plague_leech : public SpellScriptLoader
{
    public:
        spell_dk_plague_leech() : SpellScriptLoader("spell_dk_plague_leech") { }

        class spell_dk_plague_leech_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_plague_leech_SpellScript);

            std::queue<uint8> m_RunesInCharge;

            SpellCastResult CheckRunes()
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    for (uint8 index = 0; index < MAX_RUNES; ++index)
                    {
                        if (player->GetRuneCooldown(index))
                            m_RunesInCharge.push(index);
                    }

                    if (m_RunesInCharge.empty())
                        return SPELL_FAILED_DONT_REPORT;

                    if (Unit* target = GetExplTargetUnit())
                    {
                        if (!target->HasAura(DK_SPELL_BLOOD_PLAGUE) || !target->HasAura(DK_SPELL_FROST_FEVER))
                            return SPELL_FAILED_DONT_REPORT;
                    }
                }
                else
                    return SPELL_FAILED_DONT_REPORT;

                return SPELL_CAST_OK;
            }

            void HandleOnHit()
            {
                if (Player* l_Player = GetCaster()->ToPlayer())
                {
                    if (Unit* l_Target = GetHitUnit())
                    {
                        l_Target->RemoveAura(DK_SPELL_FROST_FEVER);
                        l_Target->RemoveAura(DK_SPELL_BLOOD_PLAGUE);

                        uint8 l_Count = std::min(uint8(2), uint8(m_RunesInCharge.size()));

                        while (l_Count)
                        {
                            uint8 l_RuneID = m_RunesInCharge.front();

                            l_Player->SetRuneCooldown(l_RuneID, 0);
                            l_Player->ConvertRune(l_RuneID, RuneType::RUNE_DEATH);
                            --l_Count;
                            m_RunesInCharge.pop();
                        }

                        l_Player->ResyncRunes(MAX_RUNES);
                    }
                }
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_plague_leech_SpellScript::CheckRunes);
                OnHit += SpellHitFn(spell_dk_plague_leech_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_plague_leech_SpellScript();
        }
};

// Unholy Blight - 115994
class spell_dk_unholy_blight : public SpellScriptLoader
{
    public:
        spell_dk_unholy_blight() : SpellScriptLoader("spell_dk_unholy_blight") { }

        class spell_dk_unholy_blight_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_unholy_blight_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        _player->CastSpell(target, DK_SPELL_BLOOD_PLAGUE, true);
                        _player->CastSpell(target, DK_SPELL_FROST_FEVER, true);
                    }
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_unholy_blight_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_unholy_blight_SpellScript();
        }
};

// Called by Chains of Ice - 45524
// Chilblains - 50041
class spell_dk_chilblains : public SpellScriptLoader
{
    public:
        spell_dk_chilblains() : SpellScriptLoader("spell_dk_chilblains") { }

        class spell_dk_chilblains_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_chilblains_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (_player->HasAura(DK_SPELL_CHILBLAINS))
                            _player->CastSpell(target, DK_SPELL_CHAINS_OF_ICE_ROOT, true);
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_chilblains_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_chilblains_SpellScript();
        }
};

// Outbreak - 77575
class spell_dk_outbreak : public SpellScriptLoader
{
    public:
        spell_dk_outbreak() : SpellScriptLoader("spell_dk_outbreak") { }

        class spell_dk_outbreak_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_outbreak_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        _player->CastSpell(target, DK_SPELL_BLOOD_PLAGUE, true);
                        _player->CastSpell(target, DK_SPELL_FROST_FEVER, true);
                    }
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_outbreak_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_outbreak_SpellScript();
        }
};

// Raise Dead - 46584
class spell_dk_raise_dead : public SpellScriptLoader
{
    public:
        spell_dk_raise_dead() : SpellScriptLoader("spell_dk_raise_dead") { }

        class spell_dk_raise_dead_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_raise_dead_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasAura(DK_SPELL_MASTER_OF_GHOULS))
                        _player->CastSpell(_player, DK_SPELL_GHOUL_AS_PET, true);
                    else
                        _player->CastSpell(_player, DK_SPELL_GHOUL_AS_GUARDIAN, true);
                }
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_raise_dead_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_raise_dead_SpellScript();
        }
};

// 50462 - Anti-Magic Shell (on raid member)
class spell_dk_anti_magic_shell_raid : public SpellScriptLoader
{
    public:
        spell_dk_anti_magic_shell_raid() : SpellScriptLoader("spell_dk_anti_magic_shell_raid") { }

        class spell_dk_anti_magic_shell_raid_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_anti_magic_shell_raid_AuraScript);

            uint32 absorbPct;

            bool Load() override
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                // TODO: this should absorb limited amount of damage, but no info on calculation formula
                amount = -1;
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                 absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
            }

            void Register() override
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_anti_magic_shell_raid_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_shell_raid_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_anti_magic_shell_raid_AuraScript();
        }
};

// 48707 - Anti-Magic Shell (on self)
class spell_dk_anti_magic_shell_self : public SpellScriptLoader
{
    public:
        spell_dk_anti_magic_shell_self() : SpellScriptLoader("spell_dk_anti_magic_shell_self") { }

        class spell_dk_anti_magic_shell_self_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_anti_magic_shell_self_AuraScript);

            uint32 absorbPct, hpPct, absorbDmg, battleFatiguePct;
            int32 leftAbsorb;

            bool Load() override
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                hpPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster());
                const SpellInfo* battleFatigue = sSpellMgr->GetSpellInfo(134735);
                battleFatiguePct = 100 + battleFatigue->Effects[EFFECT_0].BasePoints;
                absorbDmg = 0;
                return true;
            }

            bool Validate(SpellInfo const* /*spellEntry*/) override
            {
                if (!sSpellMgr->GetSpellInfo(DK_SPELL_RUNIC_POWER_ENERGIZE))
                    return false;
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (GetCaster())
                {
                    if (GetCaster()->HasAura(134735))
                        absorbDmg = CalculatePct(GetCaster()->CountPctFromMaxHealth(hpPct), battleFatiguePct);
                    else
                        absorbDmg = GetCaster()->CountPctFromMaxHealth(hpPct);

                    amount = absorbDmg;
                    leftAbsorb = absorbDmg;
                }
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                absorbAmount = std::min(CalculatePct(dmgInfo.GetDamage(), absorbPct), GetTarget()->CountPctFromMaxHealth(hpPct));
                leftAbsorb -= absorbAmount;
            }

            void Trigger(AuraEffect* aurEff, DamageInfo & /*dmgInfo*/, uint32 & absorbAmount)
            {
                Unit* target = GetTarget();
                // damage absorbed by Anti-Magic Shell energizes the DK with additional runic power.
                // This, if I'm not mistaken, shows that we get back ~20% of the absorbed damage as runic power.
                int32 bp = int32(absorbAmount / 140);
                target->CastCustomSpell(target, DK_SPELL_RUNIC_POWER_ENERGIZE, &bp, NULL, NULL, true, NULL, aurEff);
            }

            void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (leftAbsorb > 0 && caster->HasAura(DK_GLYPH_OF_REGENERATIVE_MAGIC))
                    {
                        AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                        if (removeMode == AURA_REMOVE_BY_EXPIRE)
                        {
                            float modifier = ((float)leftAbsorb / (float)absorbDmg) * 100.0f * 0.5f;
                            int32 cooldownMod = (int32)CalculatePct(45.0f, modifier) * IN_MILLISECONDS;

                            caster->ToPlayer()->ReduceSpellCooldown(DK_SPELL_ANTIMAGIC_SHELL_SELF, cooldownMod);
                        }
                    }
                }
            }

            void Register() override
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_anti_magic_shell_self_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_shell_self_AuraScript::Absorb, EFFECT_0);
                 AfterEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_shell_self_AuraScript::Trigger, EFFECT_0);
                 OnEffectRemove += AuraEffectRemoveFn(spell_dk_anti_magic_shell_self_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_anti_magic_shell_self_AuraScript();
        }
};

// 50461 - Anti-Magic Zone
class spell_dk_anti_magic_zone : public SpellScriptLoader
{
    public:
        spell_dk_anti_magic_zone() : SpellScriptLoader("spell_dk_anti_magic_zone") { }

        class spell_dk_anti_magic_zone_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_anti_magic_zone_AuraScript);

            uint32 absorbPct;

            bool Load() override
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                return true;
            }

            bool Validate(SpellInfo const* /*spellEntry*/) override
            {
                if (!sSpellMgr->GetSpellInfo(DK_SPELL_ANTI_MAGIC_SHELL_TALENT))
                    return false;
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                SpellInfo const* talentSpell = sSpellMgr->GetSpellInfo(DK_SPELL_ANTI_MAGIC_SHELL_TALENT);
                amount = 136800;
                if (Player* player = GetCaster()->ToPlayer())
                     amount += int32(player->GetStat(STAT_STRENGTH) * 4);
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                 absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
            }

            void Register() override
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_anti_magic_zone_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_zone_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_anti_magic_zone_AuraScript();
        }
};

// Death Gate - 53822
class spell_dk_death_gate_teleport : public SpellScriptLoader
{
    public:
        spell_dk_death_gate_teleport() : SpellScriptLoader("spell_dk_death_gate_teleport") {}

        class spell_dk_death_gate_teleport_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_gate_teleport_SpellScript);

            SpellCastResult CheckClass()
            {
                if (GetCaster()->getClass() != CLASS_DEATH_KNIGHT)
                {
                    SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_MUST_BE_DEATH_KNIGHT);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }
                return SPELL_CAST_OK;
            }

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->GetAreaId() == 4281)
                        _player->TeleportTo(_player->m_recallMap, _player->m_recallX, _player->m_recallY, _player->m_recallZ, _player->m_recallO);
                    else
                    {
                        _player->SaveRecallPosition();
                        _player->TeleportTo(0, 2359.41f, -5662.084f, 382.259f, 0.60f);
                    }
                }
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_death_gate_teleport_SpellScript::CheckClass);
                AfterCast += SpellCastFn(spell_dk_death_gate_teleport_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_gate_teleport_SpellScript();
        }
};

// Corpse Explosion (Glyph) - 127344
class spell_dk_corpse_explosion : public SpellScriptLoader
{
    public:
        spell_dk_corpse_explosion() : SpellScriptLoader("spell_dk_corpse_explosion") { }

        class spell_dk_corpse_explosion_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_corpse_explosion_SpellScript);

            SpellCastResult CheckTarget()
            {
                // Any effect on Mechanical, Elemental units or player corpses
                if (Unit* caster = GetCaster())
                {
                    Unit* target = GetExplTargetUnit();
                    if (!target)
                        return SPELL_FAILED_NO_VALID_TARGETS;

                    if (Creature* c = target->ToCreature())
                    {
                        if (target->IsAlive() || (c->GetCreatureTemplate() && 
                            (c->GetCreatureTemplate()->type == CREATURE_TYPE_MECHANICAL ||
                             c->GetCreatureTemplate()->type == CREATURE_TYPE_ELEMENTAL)))
                            return SPELL_FAILED_BAD_TARGETS;
                        else if (c->IsDungeonBoss())
                            return SPELL_FAILED_BAD_TARGETS;
                    }
                    else if (target->GetGUID() == caster->GetGUID() || target->GetTypeId() == TypeID::TYPEID_PLAYER ||
                             target->IsAlive() || target->HasAura(127344))
                        return SPELL_FAILED_BAD_TARGETS;

                    return SPELL_CAST_OK;
                }

                return SPELL_FAILED_DONT_REPORT;
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_corpse_explosion_SpellScript::CheckTarget);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_corpse_explosion_SpellScript();
        }
};

// Death Gate - 52751
class spell_dk_death_gate : public SpellScriptLoader
{
    public:
        spell_dk_death_gate() : SpellScriptLoader("spell_dk_death_gate") {}

        class spell_dk_death_gate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_gate_SpellScript);

            SpellCastResult CheckClass()
            {
                if (GetCaster()->getClass() != CLASS_DEATH_KNIGHT)
                {
                    SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_MUST_BE_DEATH_KNIGHT);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }

                return SPELL_CAST_OK;
            }

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, GetEffectValue(), false);
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_death_gate_SpellScript::CheckClass);
                OnEffectHitTarget += SpellEffectFn(spell_dk_death_gate_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_gate_SpellScript();
        }
};

class spell_dk_death_pact : public SpellScriptLoader
{
    public:
        spell_dk_death_pact() : SpellScriptLoader("spell_dk_death_pact") { }

        class spell_dk_death_pact_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_pact_SpellScript);

            SpellCastResult CheckCast()
            {
                // Check if we have valid targets, otherwise skip spell casting here
                if (Player* player = GetCaster()->ToPlayer())
                    for (Unit::ControlList::const_iterator itr = player->m_Controlled.begin(); itr != player->m_Controlled.end(); ++itr)
                        if (Creature* undeadPet = (*itr)->ToCreature())
                            if (undeadPet->IsAlive() &&
                                undeadPet->GetOwnerGUID() == player->GetGUID() &&
                                undeadPet->GetCreatureType() == CREATURE_TYPE_UNDEAD &&
                                undeadPet->IsWithinDist(player, 100.0f, false))
                                return SPELL_CAST_OK;

                return SPELL_FAILED_NO_PET;
            }

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                Unit* unit_to_add = NULL;
                for (std::list<WorldObject*>::iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
                {
                    if (Unit* unit = (*itr)->ToUnit())
                    if (unit->GetOwnerGUID() == GetCaster()->GetGUID() && unit->GetCreatureType() == CREATURE_TYPE_UNDEAD)
                    {
                        unit_to_add = unit;
                        break;
                    }
                }

                unitList.clear();
                if (unit_to_add)
                    unitList.push_back(unit_to_add);
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_death_pact_SpellScript::CheckCast);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dk_death_pact_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_pact_SpellScript();
        }
};

// Scourge Strike - 55090
class spell_dk_scourge_strike : public SpellScriptLoader
{
    public:
        spell_dk_scourge_strike() : SpellScriptLoader("spell_dk_scourge_strike") { }

        class spell_dk_scourge_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_scourge_strike_SpellScript);
            float multiplier;

            bool Load() override
            {
                multiplier = 1.0f;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* unitTarget = GetHitUnit())
                {
                    multiplier = (GetEffectValue() * unitTarget->GetDiseasesByCaster(caster->GetGUID()) / 100.f);
                    // Death Knight T8 Melee 4P Bonus
                    if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_DK_ITEM_T8_MELEE_4P_BONUS, EFFECT_0))
                        AddPct(multiplier, aurEff->GetAmount());
                }
            }

            void HandleAfterHit()
            {
                Unit* caster = GetCaster();
                if (Unit* unitTarget = GetHitUnit())
                {
                    int32 bp = (GetHitDamage() + GetAbsorbedDamage()) * multiplier;

                    if (AuraEffect* aurEff = caster->GetAuraEffectOfRankedSpell(DK_SPELL_BLACK_ICE_R1, EFFECT_0))
                        AddPct(bp, aurEff->GetAmount());

                    if (multiplier != 0.0f)
                        caster->CastCustomSpell(unitTarget, DK_SPELL_SCOURGE_STRIKE_TRIGGERED, &bp, NULL, NULL, true);
                }
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_scourge_strike_SpellScript::HandleDummy, EFFECT_2, SPELL_EFFECT_DUMMY);
                AfterHit += SpellHitFn(spell_dk_scourge_strike_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_scourge_strike_SpellScript();
        }
};

// Blood Boil - 48721
class spell_dk_blood_boil : public SpellScriptLoader
{
    public:
        spell_dk_blood_boil() : SpellScriptLoader("spell_dk_blood_boil") {}

        class spell_dk_blood_boil_SpellScript : public SpellScript
        {
        public:
            bool m_hasScarletFever;
            bool m_hasRoilingBlood;

            spell_dk_blood_boil_SpellScript()
            {
                m_hasRoilingBlood = false;
                m_hasScarletFever = false;
            }

            PrepareSpellScript(spell_dk_blood_boil_SpellScript);

            bool Load() override
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasSpellCooldown(48721))
                        return false;

                    m_hasScarletFever = _player->HasAura(DK_SPELL_SCARLET_FEVER);
                    m_hasRoilingBlood = _player->HasAura(DK_SPELL_ROILING_BLOOD);
                }

                return true;
            }

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    GetCaster()->CastSpell(GetCaster(), DK_SPELL_BLOOD_BOIL_TRIGGERED, true);
            }

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        // GetCaster()->CastSpell(GetCaster(), DK_SPELL_BLOOD_BOIL_TRIGGERED, true);

                        if (m_hasScarletFever)
                        {
                            _player->CastSpell(target, DK_SPELL_WEAKENED_BLOWS, true);
                        }
                        
                        const static uint32 s_Auras[2] = { DK_SPELL_FROST_FEVER, DK_SPELL_BLOOD_PLAGUE };
                        
                        bool hasDieses = false;
                        for (uint32 const dieses : s_Auras)
                        {
                            auto dieses_aura = target->GetAura(dieses);
                            if (!dieses_aura)
                                continue;

                            if (m_hasScarletFever)
                                dieses_aura->RefreshDuration();

                            hasDieses = true;
                        }
                            
                        if (hasDieses)
                        {
                            // Deals 50% additional damage to targets infected with Blood Plague or Frost Fever
                            SetHitDamage(int32(GetHitDamage() * 1.5f));

                            // Roiling Blood
                            if (m_hasRoilingBlood)
                                _player->CastSpell(target, DK_SPELL_PESTILENCE, true);
                        }

                        // add cooldown to prevent spam
                       // _player->AddSpellCooldown(48721, 0, time(NULL) + 1);
                    }
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_blood_boil_SpellScript::HandleOnHit);
                AfterCast += SpellCastFn(spell_dk_blood_boil_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_blood_boil_SpellScript();
        }

};

// Death Grip - 49560
class spell_dk_death_grip : public SpellScriptLoader
{
    public:
        spell_dk_death_grip() : SpellScriptLoader("spell_dk_death_grip") { }

        class spell_dk_death_grip_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_grip_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                Position const* pos = GetExplTargetDest();
                if (Unit* target = GetHitUnit())
                {
                    if (!target->HasAuraType(SPELL_AURA_DEFLECT_SPELLS)) // Deterrence
                        target->CastSpell(pos->GetPositionX(), pos->GetPositionY(), pos->GetPositionZ(), damage, true);
                }
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_death_grip_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_grip_SpellScript();
        }
};

// Glyph of Corpse Explosion - 59336
class spell_dk_glyph_of_corpse_explosion : public SpellScriptLoader
{
    public:
        spell_dk_glyph_of_corpse_explosion() : SpellScriptLoader("spell_dk_glyph_of_corpse_explosion") { }

        class spell_dk_glyph_of_corpse_explosion_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_glyph_of_corpse_explosion_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->learnSpell(DK_SPELL_GLYPH_OF_CORPSE_EXPLOSION, false);
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    if (_player->HasSpell(DK_SPELL_GLYPH_OF_CORPSE_EXPLOSION))
                        _player->removeSpell(DK_SPELL_GLYPH_OF_CORPSE_EXPLOSION, false, false);
            }

            void Register() override
            {
                OnEffectApply += AuraEffectApplyFn(spell_dk_glyph_of_corpse_explosion_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_dk_glyph_of_corpse_explosion_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_glyph_of_corpse_explosion_AuraScript();
        }
};

// Glyph of Horn of Winter - 58680
// Called by Horn of Winter - 57330
class spell_dk_glyph_of_horn_of_winter : public SpellScriptLoader
{
    public:
        spell_dk_glyph_of_horn_of_winter() : SpellScriptLoader("spell_dk_glyph_of_horn_of_winter") { }

        class spell_dk_glyph_of_horn_of_winter_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_glyph_of_horn_of_winter_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (!_player->IsInCombat() && _player->HasAura(DK_SPELL_GLYPH_OF_HORN_OF_WINTER))
                        _player->CastSpell(_player, DK_SPELL_GLYPH_OF_HORN_OF_WINTER_EFFECT, true);

                    if (_player->HasAura(DK_GLYPH_OF_THE_LOUD_HORN))
                        _player->EnergizeBySpell(_player, GetSpellInfo()->Id, 100, POWER_RUNIC_POWER);
                }
            }
            
            void Register() override
            {
                AfterCast += SpellCastFn(spell_dk_glyph_of_horn_of_winter_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_glyph_of_horn_of_winter_SpellScript();
        }
};
// Ebon Plaguebringer - 51160
// Called by plague strike - 45462
class spell_dk_plague_strike : public SpellScriptLoader
{
    public:
        spell_dk_plague_strike() : SpellScriptLoader("spell_dk_plague_strike") { }

        class spell_dk_plague_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_plague_strike_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->HasAura(DK_SPELL_EBON_PLAGUEBRINGER))
                            _player->CastSpell(target, DK_SPELL_FROST_FEVER, true);
                    }
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_plague_strike_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_plague_strike_SpellScript();
        }
};


// Riposte - 145676
class spell_dk_riposte : public SpellScriptLoader
{
    public:
        spell_dk_riposte() : SpellScriptLoader("spell_dk_riposte") { }

        class spell_dk_riposte_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_riposte_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Aura* riposte = _player->GetAura(DK_SPELL_RIPOSTE))
                    {
                        float valueParry = _player->GetRatingBonusValue(CR_PARRY) * 885;
                        float valueDodge = _player->GetRatingBonusValue(CR_DODGE) * 885;
                        int32 effectAmount = int32((valueParry + valueDodge) * 0.75f);
                        riposte->GetEffect(0)->ChangeAmount(effectAmount);
                    }
                }
            }

            void Register() override
            {
                               OnHit += SpellHitFn(spell_dk_riposte_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_riposte_SpellScript();
        }
};

// Blood Presence - 48263, Frost Presence - 48266, Unholy Presence - 48265
class spell_dk_presences : public SpellScriptLoader
{
    public:
        spell_dk_presences() : SpellScriptLoader("spell_dk_presences") { }

        class spell_dk_presences_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_presences_SpellScript);

            void HandleBeforeHit()
            {
                if (Player* _player = GetHitUnit()->ToPlayer())
                {
                    if (_player->getLevel() > 86 && _player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_DEATH_KNIGHT_UNHOLY)
                    {
                        if (_player->HasAura(DK_SPELL_SOUL_REAPER_BUFF))
                            _player->RemoveAura(DK_SPELL_SOUL_REAPER_BUFF);
                   }
                }
            }

            void Register() override
            {
                BeforeHit += SpellHitFn(spell_dk_presences_SpellScript::HandleBeforeHit);
            }
        };
        
        /*class spell_dk_presences_AuraScript : public AuraScript
        {
        public:
            spell_dk_presences_AuraScript() : m_timer(0) { }

            PrepareAuraScript(spell_dk_presences_AuraScript);

            void OnUpdate(uint32 diff)
            {
                if (m_timer >= 5000)
                {
                    if (auto caster = GetCaster())
                    {
                        if (caster->ToPlayer()->GetSpecializationId() != SPEC_DK_BLOOD)
                        {
                            uint32 power = caster->GetPower(POWER_RUNIC_POWER);
                            caster->RemoveAura(GetId());
                            caster->AddAura(GetId(), caster);

                            caster->SetPower(POWER_RUNIC_POWER, power);
                        }
                    }
                    m_timer = 0;
                }
                else
                    m_timer += diff;
            }

            void Register()
            {
                if (m_scriptSpellId == 48263)
                    OnAuraUpdate += AuraUpdateFn(spell_dk_presences_AuraScript::OnUpdate);
            }
            
            uint32 m_timer;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dk_presences_AuraScript();
        }*/

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_presences_SpellScript();
        }
};

// Conversion heal - 119980
class spell_dk_conversion_heal_aura : public SpellScriptLoader
{
    public:
        spell_dk_conversion_heal_aura() : SpellScriptLoader("spell_dk_conversion_heal_aura") { }

        class spell_dk_conversion_heal_aura_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_conversion_heal_aura_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    int32 heal = GetHitHeal();

                    // PvP Power affects on Conversion heal
                    float PvPPower = _player->GetPvpHealingBonus();
                    int32 finalHeal = int32(heal * PvPPower);
                    SetHitHeal(finalHeal);
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_conversion_heal_aura_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_conversion_heal_aura_SpellScript();
        }
};

// Gargoyle Strike - 51963
class spell_dk_gargoyle_strike : public SpellScriptLoader
{
    public:
        spell_dk_gargoyle_strike() : SpellScriptLoader("spell_dk_gargoyle_strike") { }

        class spell_dk_gargoyle_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_gargoyle_strike_SpellScript);

            void HandleOnHit()
            {
                if (Unit* owner = GetCaster()->GetOwner())
                {
                    float value = 1 + (owner->GetFloatValue(PLAYER_FIELD_MASTERY) * 2.5f / 100.0f);
                    SetHitDamage(int32(GetHitDamage() * value));
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_gargoyle_strike_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_gargoyle_strike_SpellScript();
        }
};

// Asphyxiate - 108194
class spell_dk_asphyxiate : public SpellScriptLoader
{
    public:
        spell_dk_asphyxiate() : SpellScriptLoader("spell_dk_asphyxiate") { }

        class spell_dk_asphyxiate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_asphyxiate_SpellScript);
            

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (target->IsImmunedToSpell(GetSpellInfo()))
                            caster->AddAura(DK_SPELL_STRANGULATE, target);
                    }
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_asphyxiate_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_asphyxiate_SpellScript();
        }
};

// Scourge Strike - 70890
class spell_dk_scourge_strike_trigger : public SpellScriptLoader
{
    public:
        spell_dk_scourge_strike_trigger() : SpellScriptLoader("spell_dk_scourge_strike_trigger") { }

        class spell_dk_scourge_strike_trigger_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_scourge_strike_trigger_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* _player = caster->ToPlayer())
                    {
                        int32 hitDamage = GetHitDamage();

                        float Mastery = 1 + ((_player->GetFloatValue(PLAYER_FIELD_MASTERY) * 2.5f) / 100.0f);
                        hitDamage = int32(hitDamage * Mastery);
                        SetHitDamage(hitDamage);
                    }
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_dk_scourge_strike_trigger_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_scourge_strike_trigger_SpellScript();
        }
};

void AddSC_deathknight_spell_scripts()
{
    new spell_dk_death_and_decay();
    new spell_dk_gorefiends_grasp();
    new spell_dk_runic_empowerment();
    new spell_dk_runic_corruption();
    new spell_dk_might_of_ursoc();
    new spell_dk_wild_mushroom_plague();
    new spell_dk_dark_transformation_form();
    new spell_dk_desecrated_ground();
    new spell_dk_necrotic_strike();
    new spell_dk_festering_strike();
    new spell_dk_death_strike_heal();
    new spell_dk_howling_blast();
    new spell_dk_remorseless_winter();
    new spell_dk_soul_reaper();
    new spell_dk_pillar_of_frost();
    new spell_dk_blood_charges();
    new spell_dk_blood_tap();
    new spell_dk_death_siphon();
    new spell_dk_improved_blood_presence();
    new spell_dk_unholy_presence();
    new spell_dk_death_strike();
    new spell_dk_purgatory();
    new spell_dk_purgatory_absorb();
    new spell_dk_plague_leech();
    new spell_dk_unholy_blight();
    new spell_dk_chilblains();
    new spell_dk_outbreak();
    new spell_dk_raise_dead();
    new spell_dk_anti_magic_shell_raid();
    new spell_dk_anti_magic_shell_self();
    new spell_dk_anti_magic_zone();
    new spell_dk_corpse_explosion();
    new spell_dk_death_gate_teleport();
    new spell_dk_death_gate();
    new spell_dk_death_pact();
    new spell_dk_scourge_strike();
    new spell_dk_blood_boil();
    new spell_dk_death_grip();
    new spell_dk_glyph_of_corpse_explosion();
    new spell_dk_glyph_of_horn_of_winter();
    new spell_dk_plague_strike();
    new spell_dk_riposte();
    new spell_dk_presences();
    new spell_dk_conversion_heal_aura();
    new spell_dk_gargoyle_strike();
    new spell_dk_asphyxiate();
    new spell_dk_scourge_strike_trigger();
}
