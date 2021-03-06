/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Areatrigger_Scripts
SD%Complete: 100
SDComment: Scripts for areatriggers
SDCategory: Areatrigger
EndScriptData */

/* ContentData
at_aldurthar_gate               q13315/q13351
at_coilfang_waterfall           4591
at_legion_teleporter            4560 Teleporter TO Invasion Point: Cataclysm
at_ravenholdt
at_warsong_slaughterhouse
at_warsong_grainery
at_torp_farm
at_warsong_farms                q11686
at_stormwright_shelf            q12741
at_last_rites                   q12019
at_sholazar_waygate             q12548
at_stormwind_counting_house
at_stormwind_auction_house
at_stormwind_barber_shop
at_orgrimmar_bank
at_orgrimmar_auction_house
at_orgrimmar_barber_shop
at_bring_your_orphan_to         q910 q910 q1800 q1479 q1687 q1558 q10951 q10952
EndContentData */

#include "ScriptPCH.h"

/*######
## AreaTrigger_at_aldurthar_gate
######*/

enum eAldurtharGate
{
    TRIGGER_SOUTH                               = 5284,

    TRIGGER_CENTRAL                             = 5285,
    TRIGGER_NORTH                               = 5286,
    TRIGGER_NORTHWEST                           = 5287,

    NPC_SOUTH_GATE                              = 32195,
    NPC_CENTRAL_GATE                            = 32196,
    NPC_NORTH_GATE                              = 32197,
    NPC_NORTHWEST_GATE                          = 32199
};

class AreaTrigger_at_aldurthar_gate : public AreaTriggerScript
{
    public:

        AreaTrigger_at_aldurthar_gate()
            : AreaTriggerScript("at_aldurthar_gate")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            switch (trigger->id)
            {
                case TRIGGER_SOUTH:     player->KilledMonsterCredit(NPC_SOUTH_GATE, 0);     break;
                case TRIGGER_CENTRAL:   player->KilledMonsterCredit(NPC_CENTRAL_GATE, 0);   break;
                case TRIGGER_NORTH:     player->KilledMonsterCredit(NPC_NORTH_GATE, 0);     break;
                case TRIGGER_NORTHWEST: player->KilledMonsterCredit(NPC_NORTHWEST_GATE, 0); break;
            }
            return true;
        }
};

/*######
## at_coilfang_waterfall
######*/

enum eCoilfangGOs
{
    GO_COILFANG_WATERFALL   = 184212
};

class AreaTrigger_at_coilfang_waterfall : public AreaTriggerScript
{
    public:

        AreaTrigger_at_coilfang_waterfall()
            : AreaTriggerScript("at_coilfang_waterfall")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            if (GameObject* go = GetClosestGameObjectWithEntry(player, GO_COILFANG_WATERFALL, 35.0f))
                if (go->getLootState() == GO_READY)
                    go->UseDoorOrButton();

            return false;
        }
};

/*#####
## at_legion_teleporter
#####*/

enum eLegionTeleporter
{
    SPELL_TELE_A_TO         = 37387,
    QUEST_GAINING_ACCESS_A  = 10589,

    SPELL_TELE_H_TO         = 37389,
    QUEST_GAINING_ACCESS_H  = 10604
};

class AreaTrigger_at_legion_teleporter : public AreaTriggerScript
{
    public:

        AreaTrigger_at_legion_teleporter()
            : AreaTriggerScript("at_legion_teleporter")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            if (player->isAlive() && !player->isInCombat())
            {
                if (player->GetTeam() == ALLIANCE && player->GetQuestRewardStatus(QUEST_GAINING_ACCESS_A))
                {
                    player->CastSpell(player, SPELL_TELE_A_TO, false);
                    return true;
                }

                if (player->GetTeam() == HORDE && player->GetQuestRewardStatus(QUEST_GAINING_ACCESS_H))
                {
                    player->CastSpell(player, SPELL_TELE_H_TO, false);
                    return true;
                }

                return false;
            }
            return false;
        }
};

enum eRavenholdt
{
    QUEST_MANOR_RAVENHOLDT  = 6681,
    NPC_RAVENHOLDT          = 13936
};

class AreaTrigger_at_ravenholdt : public AreaTriggerScript
{
    public:

        AreaTrigger_at_ravenholdt()
            : AreaTriggerScript("at_ravenholdt")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            if (player->GetQuestStatus(QUEST_MANOR_RAVENHOLDT) == QUEST_STATUS_INCOMPLETE)
                player->KilledMonsterCredit(NPC_RAVENHOLDT, 0);

            return false;
        }
};

/*######
## at_warsong_farms
######*/

enum eWarsongFarms
{
    QUEST_THE_WARSONG_FARMS                     = 11686,

    NPC_CREDIT_SLAUGHTERHOUSE                   = 25672,
    NPC_CREDIT_GRAINERY                         = 25669,
    NPC_CREDIT_TORP_FARM                        = 25671,

    AT_SLAUGHTERHOUSE                           = 4873,
    AT_GRAINERY                                 = 4871,
    AT_TORP_FARM                                = 4872
};

class AreaTrigger_at_warsong_farms : public AreaTriggerScript
{
    public:

        AreaTrigger_at_warsong_farms()
            : AreaTriggerScript("at_warsong_farms")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (!player->isDead() && player->GetQuestStatus(QUEST_THE_WARSONG_FARMS) == QUEST_STATUS_INCOMPLETE)
            {
                switch (trigger->id)
                {
                    case AT_SLAUGHTERHOUSE: player->KilledMonsterCredit(NPC_CREDIT_SLAUGHTERHOUSE, 0); break;
                    case AT_GRAINERY:       player->KilledMonsterCredit(NPC_CREDIT_GRAINERY, 0);       break;
                    case AT_TORP_FARM:      player->KilledMonsterCredit(NPC_CREDIT_TORP_FARM, 0);      break;
                }
            }
            return true;
        }
};

/*######
## at_stormwright_shelf
######*/

enum eStormwrightShelf
{
    QUEST_STRENGTH_OF_THE_TEMPEST               = 12741,

    SPELL_CREATE_TRUE_POWER_OF_THE_TEMPEST      = 53067
};

class AreaTrigger_at_stormwright_shelf : public AreaTriggerScript
{
    public:

        AreaTrigger_at_stormwright_shelf()
            : AreaTriggerScript("at_stormwright_shelf")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            if (!player->isDead() && player->GetQuestStatus(QUEST_STRENGTH_OF_THE_TEMPEST) == QUEST_STATUS_INCOMPLETE)
                player->CastSpell(player, SPELL_CREATE_TRUE_POWER_OF_THE_TEMPEST, false);

            return true;
        }
};

/*######
## at_scent_larkorwi
######*/

enum eScentLarkorwi
{
    QUEST_SCENT_OF_LARKORWI                     = 4291,
    NPC_LARKORWI_MATE                           = 9683
};

class AreaTrigger_at_scent_larkorwi : public AreaTriggerScript
{
    public:

        AreaTrigger_at_scent_larkorwi()
            : AreaTriggerScript("at_scent_larkorwi")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            if (!player->isDead() && player->GetQuestStatus(QUEST_SCENT_OF_LARKORWI) == QUEST_STATUS_INCOMPLETE)
            {
                if (!player->FindNearestCreature(NPC_LARKORWI_MATE, 15))
                    player->SummonCreature(NPC_LARKORWI_MATE, player->GetPositionX()+5, player->GetPositionY(), player->GetPositionZ(), 3.3f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100000);
            }

            return false;
        }
};

/*#####
## at_last_rites
#####*/

enum eAtLastRites
{
    QUEST_LAST_RITES                          = 12019,
    QUEST_BREAKING_THROUGH                    = 11898,
};

class AreaTrigger_at_last_rites : public AreaTriggerScript
{
    public:

        AreaTrigger_at_last_rites()
            : AreaTriggerScript("at_last_rites")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (!(player->GetQuestStatus(QUEST_LAST_RITES) == QUEST_STATUS_INCOMPLETE ||
                player->GetQuestStatus(QUEST_LAST_RITES) == QUEST_STATUS_COMPLETE ||
                player->GetQuestStatus(QUEST_BREAKING_THROUGH) == QUEST_STATUS_INCOMPLETE ||
                player->GetQuestStatus(QUEST_BREAKING_THROUGH) == QUEST_STATUS_COMPLETE))
                return false;

            WorldLocation pPosition;

            switch (trigger->id)
            {
                case 5332:
                case 5338:
                    pPosition = WorldLocation(571, 3733.68f, 3563.25f, 290.812f, 3.665192f);
                    break;
                case 5334:
                    pPosition = WorldLocation(571, 3802.38f, 3585.95f, 49.5765f, 0.0f);
                    break;
                case 5340:
                    pPosition = WorldLocation(571, 3687.91f, 3577.28f, 473.342f, 0.0f);
                    break;
                default:
                    return false;
            }

            player->TeleportTo(pPosition);

            return false;
        }
};

/*######
## at_sholazar_waygate
######*/

enum eWaygate
{
    SPELL_SHOLAZAR_TO_UNGORO_TELEPORT           = 52056,
    SPELL_UNGORO_TO_SHOLAZAR_TELEPORT           = 52057,

    AT_SHOLAZAR                                 = 5046,
    AT_UNGORO                                   = 5047,

    QUEST_THE_MAKERS_OVERLOOK                   = 12613,
    QUEST_THE_MAKERS_PERCH                      = 12559,
};

class AreaTrigger_at_sholazar_waygate : public AreaTriggerScript
{
    public:

        AreaTrigger_at_sholazar_waygate()
            : AreaTriggerScript("at_sholazar_waygate")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->GetQuestStatus(QUEST_THE_MAKERS_OVERLOOK) == QUEST_STATUS_REWARDED && !player->isDead() &&
                player->GetQuestStatus(QUEST_THE_MAKERS_PERCH)    == QUEST_STATUS_REWARDED)
            {
                switch (trigger->id)
                {
                    case AT_SHOLAZAR: player->CastSpell(player, SPELL_SHOLAZAR_TO_UNGORO_TELEPORT, false); break;
                    case AT_UNGORO:   player->CastSpell(player, SPELL_UNGORO_TO_SHOLAZAR_TELEPORT, false); break;
                }
            }

            return false;
        }
};

/*######
## Quest 24849
######*/

enum
{
    QUEST_HOT_ON_THE_TRAIL_ALI           = 24849,
    NPC_CREDIT_STORMWIND_COUNTING_HOUSE  = 45672,
    NPC_CREDIT_STORMWIND_AUCTION_HOUSE   = 45669,
    NPC_CREDIT_STORMWIND_BARBER_SHOP     = 45671
};

class AreaTrigger_at_stormwind_counting_house : public AreaTriggerScript
{
    public:

        AreaTrigger_at_stormwind_counting_house()
            : AreaTriggerScript("at_stormwind_counting_house")
        {
        }
        
        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (!player->isDead() && player->GetQuestStatus(QUEST_HOT_ON_THE_TRAIL_ALI) == QUEST_STATUS_INCOMPLETE)
               player->KilledMonsterCredit(NPC_CREDIT_STORMWIND_COUNTING_HOUSE, 0);
            
            return true;
        }
};

class AreaTrigger_at_stormwind_auction_house : public AreaTriggerScript
{
    public:

        AreaTrigger_at_stormwind_auction_house()
            : AreaTriggerScript("at_stormwind_auction_house")
        {
        }
        
        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (!player->isDead() && player->GetQuestStatus(QUEST_HOT_ON_THE_TRAIL_ALI) == QUEST_STATUS_INCOMPLETE)
                player->KilledMonsterCredit(NPC_CREDIT_STORMWIND_AUCTION_HOUSE, 0);
            
            return true;
        }
};

class AreaTrigger_at_stormwind_barber_shop : public AreaTriggerScript
{
    public:

        AreaTrigger_at_stormwind_barber_shop()
            : AreaTriggerScript("at_stormwind_barber_shop")
        {
        }
        
        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (!player->isDead() && player->GetQuestStatus(QUEST_HOT_ON_THE_TRAIL_ALI) == QUEST_STATUS_INCOMPLETE)
                player->KilledMonsterCredit(NPC_CREDIT_STORMWIND_BARBER_SHOP, 0);
            
            return true;
        }
};

/*######
## Quest 24851
######*/

enum
{
    QUEST_HOT_ON_THE_TRAIL_HORDE        = 24851,
    NPC_CREDIT_ORGRIMMAR_BANK           = 45673,
    NPC_CREDIT_ORGRIMMAR_AUCTION_HOUSE  = 45674,
    NPC_CREDIT_ORGRIMMAR_BARBER_SHOP    = 45675
};

class AreaTrigger_at_orgrimmar_bank : public AreaTriggerScript
{
    public:

        AreaTrigger_at_orgrimmar_bank()
            : AreaTriggerScript("at_orgrimmar_bank")
        {
        }
        
        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (!player->isDead() && player->GetQuestStatus(QUEST_HOT_ON_THE_TRAIL_HORDE) == QUEST_STATUS_INCOMPLETE)
               player->KilledMonsterCredit(NPC_CREDIT_ORGRIMMAR_BANK, 0);
            
            return true;
        }
};

class AreaTrigger_at_orgrimmar_auction_house : public AreaTriggerScript
{
    public:

        AreaTrigger_at_orgrimmar_auction_house()
            : AreaTriggerScript("at_orgrimmar_auction_house")
        {
        }
        
        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (!player->isDead() && player->GetQuestStatus(QUEST_HOT_ON_THE_TRAIL_HORDE) == QUEST_STATUS_INCOMPLETE)
                player->KilledMonsterCredit(NPC_CREDIT_ORGRIMMAR_AUCTION_HOUSE, 0);
            
            return true;
        }
};

class AreaTrigger_at_orgrimmar_barber_shop : public AreaTriggerScript
{
    public:

        AreaTrigger_at_orgrimmar_barber_shop()
            : AreaTriggerScript("at_orgrimmar_barber_shop")
        {
        }
        
        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (!player->isDead() && player->GetQuestStatus(QUEST_HOT_ON_THE_TRAIL_HORDE) == QUEST_STATUS_INCOMPLETE)
                player->KilledMonsterCredit(NPC_CREDIT_ORGRIMMAR_BARBER_SHOP, 0);
            
            return true;
        }
};

/*######
## at_bring_your_orphan_to
######*/

enum BringYourOrphanTo
{
    QUEST_DOWN_AT_THE_DOCKS         = 910,
    QUEST_GATEWAY_TO_THE_FRONTIER   = 911,
    QUEST_LORDAERON_THRONE_ROOM     = 1800,
    QUEST_BOUGHT_OF_ETERNALS        = 1479,
    QUEST_SPOOKY_LIGHTHOUSE         = 1687,
    QUEST_STONEWROUGHT_DAM          = 1558,
    QUEST_DARK_PORTAL_H             = 10951,
    QUEST_DARK_PORTAL_A             = 10952,

    AT_DOWN_AT_THE_DOCKS            = 3551,
    AT_GATEWAY_TO_THE_FRONTIER      = 3549,
    AT_LORDAERON_THRONE_ROOM        = 3547,
    AT_BOUGHT_OF_ETERNALS           = 3546,
    AT_SPOOKY_LIGHTHOUSE            = 3552,
    AT_STONEWROUGHT_DAM             = 3548,
    AT_DARK_PORTAL                  = 4356,

    AURA_ORPHAN_OUT                 = 58818,
};

class AreaTrigger_at_bring_your_orphan_to : public AreaTriggerScript
{
    public:
        AreaTrigger_at_bring_your_orphan_to() : AreaTriggerScript("at_bring_your_orphan_to") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            uint32 questId = 0;

            if (player->isDead() || !player->HasAura(AURA_ORPHAN_OUT))
                return false;

            switch (trigger->id)
            {
                case AT_DOWN_AT_THE_DOCKS:
                    questId = QUEST_DOWN_AT_THE_DOCKS;
                    break;
                case AT_GATEWAY_TO_THE_FRONTIER:
                    questId = QUEST_GATEWAY_TO_THE_FRONTIER;
                    break;
                case AT_LORDAERON_THRONE_ROOM:
                    questId = QUEST_LORDAERON_THRONE_ROOM;
                    break;
                case AT_BOUGHT_OF_ETERNALS:
                    questId = QUEST_BOUGHT_OF_ETERNALS;
                    break;
                case AT_SPOOKY_LIGHTHOUSE:
                    questId = QUEST_SPOOKY_LIGHTHOUSE;
                    break;
                case AT_STONEWROUGHT_DAM:
                    questId = QUEST_STONEWROUGHT_DAM;
                    break;
                case AT_DARK_PORTAL:
                    questId = player->GetTeam() == ALLIANCE ? QUEST_DARK_PORTAL_A : QUEST_DARK_PORTAL_H;
                    break;
            }

            if (questId && player->GetQuestStatus(questId) == QUEST_STATUS_INCOMPLETE)
                player->AreaExploredOrEventHappens(questId);

            return true;
        }
};

void AddSC_areatrigger_scripts()
{
    new AreaTrigger_at_aldurthar_gate();
    new AreaTrigger_at_coilfang_waterfall();
    new AreaTrigger_at_legion_teleporter();
    new AreaTrigger_at_ravenholdt();
    new AreaTrigger_at_warsong_farms();
    new AreaTrigger_at_stormwright_shelf();
    new AreaTrigger_at_scent_larkorwi();
    new AreaTrigger_at_last_rites();
    new AreaTrigger_at_sholazar_waygate();
    new AreaTrigger_at_stormwind_counting_house();
    new AreaTrigger_at_stormwind_auction_house();
    new AreaTrigger_at_stormwind_barber_shop();
    new AreaTrigger_at_orgrimmar_bank();
    new AreaTrigger_at_orgrimmar_auction_house();
    new AreaTrigger_at_orgrimmar_barber_shop();
    new AreaTrigger_at_bring_your_orphan_to();
}
