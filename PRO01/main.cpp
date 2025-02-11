#include "Creature.h"
#include "SpecialAbility.h"
#include <vector>
#include "Run.h"

int main() {
    std::vector<SpecialAbility> abilitiesWater;
    {
        abilitiesWater.emplace_back(SpecialAbility("Wave Bash","Hits the target for [strength] and has a 50% chance to DISORIENT them for 1 turn.",1, 1, false));
        abilitiesWater.emplace_back(SpecialAbility("Flush", "Hits the target for 2 x [strength]", 3, 2, false));
        abilitiesWater.emplace_back(SpecialAbility("Healing water", "Heals the target for [strength]", 4, 3, true));
        abilitiesWater.emplace_back(SpecialAbility("Cleansing Water","Heals the target for [strength] and removes all their NEGATIVE effects.",0, 40, 4, true));
        abilitiesWater.emplace_back(SpecialAbility("Big Heal", "Heals the target to full HP and applies SLOW HEAL for 1 turn.", 0,40, 5, true));
    }
    std::vector<SpecialAbility> abilitiesEarth;
    {
        abilitiesEarth.emplace_back(SpecialAbility("Rock Throw", "Hits the target for [strength] / 3 and DISORIENTS them for 3 turns.", 2,6, false));
        abilitiesEarth.emplace_back(SpecialAbility("Fortify", "Fortifies an ally for 5 turns.", 10, 7, true));
        abilitiesEarth.emplace_back(SpecialAbility("Raging Boulder", "Hits the target for your [missing HP] / 4.", 3, 8, false));
        abilitiesEarth.emplace_back(SpecialAbility("Rock UP", "Heals an ally for [streangth] x 2 and Fortifies for 10 turns.", 0, 50, 9, false));
        abilitiesEarth.emplace_back(SpecialAbility("Knockout", "Hits the target for [strength] and DISORIENTS him for 10 turns.", 0, 60,10, false));
    }
    std::vector<SpecialAbility> abilitiesWind;
    {
        abilitiesWind.emplace_back(SpecialAbility("Leaf Strike", "Applies BLEEDING and VULNERABLE to the target for 4 turns.", 2, 11, false));
        abilitiesWind.emplace_back(SpecialAbility("Quick Wind", "Hits the target 5 times for [strength] / 10.", 1, 12, false));
        abilitiesWind.emplace_back(SpecialAbility("Thick Wind", "Hits the target for [strength] and SLOWS them for 3 TURNS.", 3, 13, false));
        abilitiesWind.emplace_back(SpecialAbility("Tornado", "Hits the target 15 times for [strength] / 10.", 0, 70, 14, false));
        abilitiesWind.emplace_back(SpecialAbility("Wind Wall", "Applies  STRENGTHEN for 5 turns and DODGE x 3 for 10 turns an ally.", 0, 50, 15, true));
    }
    std::vector<SpecialAbility> abilitiesFire;
    {
        abilitiesFire.emplace_back(SpecialAbility("Ignite", "Hits the target for [strength] / 2 and BURNS them for 3 turns.", 4, 16, false));
        abilitiesFire.emplace_back(SpecialAbility("Fire Blast", "Hits the target for [strength] and has a 10% chance to BURN for 2 turns.",1, 17, false));
        abilitiesFire.emplace_back(SpecialAbility("Burning Rage", "Applies STRENGTHEN for 3 turns and HEALS for [strength]", 3, 18, true));
        abilitiesFire.emplace_back(SpecialAbility("BUUUUURN", "BURNS the target 5 times for 5 turns.", 0, 70, 19, false));
        abilitiesFire.emplace_back(SpecialAbility("Fire wave.", "Hits the target for [strength] x 3. and BURNS for 2 turns.", 0, 90, 20, false));
    }
    std::vector<SpecialAbility> abilitiesIce;
    {
        abilitiesIce.emplace_back(SpecialAbility("Igloo", "FORTIFIES an ally for 3 turns.", 4, 21, true));
        abilitiesIce.emplace_back(SpecialAbility("Snowball", "Hits the target for [strength] and has a 20% chance to SLOW for 3 turns.", 1, 22, false));
        abilitiesIce.emplace_back(SpecialAbility("Icicle Throw", "Hits the target for [strength] / 2 and applies BLEED for 3 turns.", 3,23, false));
        abilitiesIce.emplace_back(SpecialAbility("Freeze!", "FREEZES the target for 2 turns.", 0, 100, 24, false));
        abilitiesIce.emplace_back(SpecialAbility("Blizzard", "Hits target 3 times for [strength] and SLOWS him for 6 turns.", 0,60, 25, false));
    }
    std::vector<SpecialAbility> abilitiesSteel;
    {
        abilitiesSteel.emplace_back(SpecialAbility("Focus Up!", "Applies FOCUSED to an ally for 5 turns.", 3, 26, true));
        abilitiesSteel.emplace_back(SpecialAbility("Hard Hit","Hits the target for [strength] and has a 10% chance to apply BLEED for 2 turns.",1, 27, false));
        abilitiesSteel.emplace_back(SpecialAbility("Terrifying Roar", "Hits the target for [strength] and WEAKENS him for 5 turns.", 3, 28,false));
        abilitiesSteel.emplace_back(SpecialAbility("Micro Waves", "DISORIENT and SLOW the target from 5 turns.", 0, 40, 29, false));

        abilitiesSteel.emplace_back(SpecialAbility("Pure Magic","Applies: BURNING, DISORIENTED, BLEEDING, SLOWED, WEAKEN and VULNERABLE to the target for 2 turns.",0, 60, 30, false));
    }
    std::vector<std::vector<SpecialAbility>> allAbilities
    {
        abilitiesWater,
        abilitiesEarth,
        abilitiesWind,
        abilitiesFire,
        abilitiesIce,
        abilitiesSteel
    };
    Creature cr1("Waterlo", 30, 25, 150, 90, 0, allAbilities);
    Creature cr2("Wavy", 20, 25, 130, 90, 0,  allAbilities);
    Creature cr3("Grunt", 10, 5, 250, 80, 1, allAbilities);
    Creature cr4("Mordesh", 30, 15, 150, 90, 1, allAbilities);
    Creature cr5("Rocker", 25, 10, 200, 100, 1, allAbilities);
    Creature cr6("Quickon", 25, 50, 100, 100, 2, allAbilities);
    Creature cr7("Speddor", 50, 350, 50, 50, 2, allAbilities);
    Creature cr8("Leafy", 40, 50, 100, 150, 2, allAbilities);
    Creature cr9("Blaster", 50, 20, 130, 120, 3, allAbilities);
    Creature cr10("Burner", 55, 10, 180, 120, 3, allAbilities);
    Creature cr11("Ronglon",20 , 100, 200, 100, 3, allAbilities);
    Creature cr12("Icer", 30, 25, 200, 100, 4, allAbilities);
    Creature cr13("Winterion", 35, 30, 180, 100, 4, allAbilities);
    Creature cr14("Thamruld", 20, 70, 180, 90, 4, allAbilities);
    Creature cr15("Techron", 10, 150, 200, 80, 5, allAbilities);
    Creature cr16("Minder", 30, 25, 150, 90, 5, allAbilities);

    std::vector<Creature> allCreatures {cr1, cr2, cr3, cr4, cr5, cr6, cr7, cr8,
                                        cr9, cr10,cr11, cr12, cr13, cr14, cr15, cr16};


    //ready
    Run startGame(allCreatures, allAbilities);

    return 0;
}
