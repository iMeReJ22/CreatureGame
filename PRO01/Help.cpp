//
// Created by Jeremi on 14.06.2022.
//

#include <iostream>
#include "Help.h"

void Help::mainMenuHelp() {
    std::cout << "******************** HELP ********************\n"
                 "Just follow the instructions on the screen,\n"
                 "there isn't much helping here. :/\n"
                 "********************      ********************\n";
    system("pause");
}

void Help::effectHelp() {
    std::cout << "******************** HELP ********************\n"
                 "ALL EFECTS TYPES: \n"
                 "negative: \n"
                 "1\tBurning - Causes host to LOSE 10 HP\n\tat the START of turn. \n"
                 "2\tDisoriented - Causes host to MISS \n\tthe target 30% more likely.\n"
                 "3\tFrozen - Causes host to not be able \n\tto PERFORM ACTIONS.\n"
                 "4\tBleeding - Causes host to lose HP equal to \n\t5 * turns left at the START.\n"
                 "5\tSlowed - Causes host to lose 20% DEXTERITY.\n"
                 "6\tWeaken - Causes host to lose 10% STRENGTH.\n"
                 "7\tVulnerable - Causes host to LOSE 2HP MORE \n\tfrom all sources.\n"
                 "\n"
                 "positive:\n"
                 "10\tFoccused - Causes host to HIT the target \n\t30% more likely.\n"
                 "11\tDodge - Causes host to DODGE next enemy attack. \n\tDissapears once host DODGES\n"
                 "12\tStrengthen - Causes host to gain 10% STRENGTH.\n"
                 "13\tFortified - Causes host to LOSE 5HP LESS \n\tfrom all sources.\n"
                 "14\tSlow Heal - Causes host to be HEALED  \n\tfor [num] at the START of turn.\n"
                 "********************      ********************\n";
    system("pause");
}

void Help::creatueHelp() {
    std::cout << "******************** HELP ********************\n"
                 "All Creatures have: \n"
                 "HitPoints - Their Health, if it hits 0, \n\tthey become unconscious.\n"
                 "Strength - Self explanatory, this statistic \n\tdictates their ability strength.\n"
                 "Dexterity - Their chance to doge an enemy attack. "
                 "\n\t5 dexterity = 1% chance to dodge.\n"
                 "Experience - If they gain their experience threshold, \n"
                 "\tthey can evolve to the next LVL gaining statics.\n"
                 "Abilities - That depend on their element type.\n"
                 "Effects - They are only visible during battle,\n"
                 "\tand last a limited time.\n"
                 "Baseline Accuracy which is 100% offset by \n\tenemy's dexterity.\n"
                 "********************      ********************\n";
    system("pause");
}

void Help::battleHelp() {
    std::cout << "******************** HELP ********************\n"
                 "In the battle your main goal is to bring down\n"
                 "all enemy creatures to 0 HP.\n\n"
                 "You can use your abilities, swap your Creatures,\n"
                 "or evolve you Creature, on each given action.\n\n"
                 "Your Creatures will gain temporary effects\n"
                 "during the battle phase, but they will expire\n"
                 "once you exit the battle.\n\n"
                 "All Creature type affect each other in some way\n"
                 "either having: normal, higher or lover dmg ouput\n"
                 "to other Creature types.\n\n"
                 "Once your creature gets unconscious, \n"
                 "you have to swap to another.\n\n"
                 "Your Creatures have 2 different types of abilities\n"
                 "Normal - they operate on a turn based cooldown system\n"
                 "Ultimate - the operate on a UltPoints system.\n"
                 "You gain 10 UltPoints every round of a battle.\n"
                 "********************      ********************\n";
    system("pause");
}

void Help::makeATeamHelp() {
    std::cout << "******************** HELP ********************\n"
                 "While choosing a team, you have to chose 4\n"
                 "Creatures, that will assist you till the end of\n\tyour journey.\n"
                 "Try to mix and match different types of Creatures\n"
                 "********************      ********************\n";
    system("pause");
}

void Help::difficultyHelp() {
    std::cout << "******************** HELP ********************\n"
                 "1 Battle, and ultPoints start at:\n"
                 "\t YOUR: 100, ENEMY'S: 0\n"
                 "Normal - 4 Battles, and ultPoints start at:\n"
                 "\t YOUR: 40, ENEMY'S: 30\n"
                 "Hard - 10 Battles, and ultPoints start at:\n"
                 "\t YOUR: 30, ENEMY'S: 70\n"
                 "Endless - Infinite Battles, and ultPoints start at:\n"
                 "\t YOUR: 0, ENEMY'S: 100\n"
                 "You start with 6 and the enemy starts with 4 \n"
                 "\tCreatures, and each battle will have 1 more \n"
                 "\topponent Creature, up to 16 MAX.\n"
                 "********************      ********************\n";
    system("pause");
}

void Help::swapHelp() {
    std::cout << "******************** HELP ********************\n"
                 "When you swap your Creature, you need to remember\n"
                 "that they will keep all their Effects until they\n"
                 "expire in their given amount of turn.\n"
                 "********************      ********************\n";
    system("pause");
}

void Help::showTable() {
    std::cout << "******************** INTERACTION TABLE ********************\n"
                 "DEFENDING\tWATER\tEARTH\tWIND\tFIRE\tICE\tSTEEL\n"
                 "ATTACKING\n"
                 "WATER\t\t0.7\t1.3\t1\t1.3\t1\t1\n"
                 "EARTH\t\t1\t1\t0.7\t1.3\t1.3\t1.3\n"
                 "WIND\t\t1\t0.7\t1\t1\t1.3\t0.7\n"
                 "FIRE\t\t0.7\t0.7\t1\t1\t1.3\t1.3\n"
                 "ICE\t\t0.7\t1.3\t1\t0.7\t0.7\t1\n"
                 "STEEL\t\t1.3\t1\t1.3\t0.7\t1\t0.7\n"
                 "********************                   ********************\n"
                 "The values in the table reflect the DMG modifier applied to\n"
                 "\tall the attacks between Creatures.\n"
                 "********************                   ********************\n";
    system("pause");
}

