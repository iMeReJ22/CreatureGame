//
// Created by Jeremi on 30.05.2022.
//

#include "Creature.h"
#include "SpecialAbility.h"
#include "Effect.h"
#include <iostream>

Creature::Creature(std::string name, int str, int dex, int hp, int exp, int type, std::vector<std::vector<SpecialAbility>> &all) {
    this->name = name;
    strength = Values(str);
    dexterity = Values(dex);
    hitPoints = Values(hp);
    this->exp = Values(exp);
    std::copy(all.at(type).begin(), all.at(type).end(), std::back_inserter(abilities));
    effects = std::vector<Effect>();
    this->type = type;
    lvl = 1;
    hitChance = Values(100);
}



void Creature::addEffect(const Effect& effect) {
    effects.push_back(effect);
}

const std::string &Creature::getName() const {
    return name;
}

void Creature::effectInfo() {
    if(effects.empty())
        std::cout << "\tNO EFFECTS\n";
    else {
        std::cout << "\tPositive: \n";
        for (Effect const &effect: effects)
            if(effect.isType())
                effect.showInfo();
        std::cout << "\tNegative: \n";
        for (Effect const &effect: effects)
            if(!effect.isType())
                effect.showInfo();
    }
}

void Creature::checkForStartEffects() {
    //negative
    if(checkForEffect(1) > 0) {
        int tmp = 0;
        if(checkForEffect(7) > 0)
            tmp += 2;
        if(checkForEffect(13) > 0)
            tmp -= 5;

        hitPoints.plusCurrent((checkForEffect(1)*10 + tmp) < 0 ? 0 : -(checkForEffect(1)*10 + tmp));
    }
    if(checkForEffect(2) > 0)
        hitChance.plusCurrent(-(int)(hitChance.getCurrentValue()*0.3));
    if(checkForEffect(4) > 0) {
        int tmp = 0;
        if(checkForEffect(7) > 0)
            tmp += 2;
        if(checkForEffect(13) > 0)
            tmp -= 5;
        for(Effect &effect : effects){
            if(effect.getEffectNr() == 4){
                hitPoints.plusCurrent((effect.getTurns().getCurrentValue() + tmp) < 0 ? 0 : -(effect.getTurns().getCurrentValue() + tmp));
            }
        }
    }
    if(checkForEffect(5) > 0)
        dexterity.plusCurrent(-(int)(dexterity.getCurrentValue()*0.2));
    if(checkForEffect(6) > 0)
        strength.plusCurrent(-(int)(strength.getCurrentValue() * 0.1));

    //positive
    if(checkForEffect(10) > 0)
        hitChance.plusCurrent(+(int)(hitChance.getCurrentValue()*0.3));
    if(checkForEffect(12) > 0)
        strength.plusCurrent(+(int)(strength.getCurrentValue() * 0.1));
    if(checkForEffect(14) > 0){
        for(Effect const &effect : effects)
            if(effect.getEffectNr() == 14) {
                hitPoints.plusCurrent(effect.getStrength());
            }
    }
    if(hitPoints.getCurrentValue() > hitPoints.getMaxValue())
        hitPoints.setCurrentValue(hitPoints.getMaxValue());
    minusTurns();
}

void Creature::checkForEndEffects() {
    hitChance.resetValue();
    dexterity.resetValue();
    strength.resetValue();
    removeExpiredEffects();
}

int Creature::checkForEffect(int effectNR) {
    int n = 0;
    for(Effect const &effect : effects) {
            if (effect.getEffectNr() == effectNR)
                n++;
    }
    return n;
}

void Creature::removeExpiredEffects() {
    int i = 0;
    for(Effect effect : effects) {
        if (effect.getTurns().getCurrentValue() <= 0) {
            effects.erase(effects.begin() + i);
                std::cout << "Effect: " << effect.getName() << " expired.\n";
        }
        i++;
    }
}

void Creature::minusTurns() {
    for(Effect &effect : effects){
        effect.turnMinus();
    }
}


void Creature::creatureInfo() {
    std::cout << "Name: " << name << "\t"
              << "Strenght: " << strength.getCurrentValue() << "\t"
    << "Dexterity: " << dexterity.getCurrentValue() << "\t"
    << "HitPoints: " << hitPoints.getCurrentValue() << "\t"
    << "Experience: " << exp.getMaxValue()-exp.getCurrentValue() << "\t"
    << "Current LVL: " << lvl << "\t"
    << (isAlive() ? "ALIVE\n" : "UNCONSCIOUS\n");
    effectInfo();
}

void Creature::gainExperience(int enemyLVL) {
    if(enemyLVL < lvl)
        exp.plusCurrent(-20);
    else if(enemyLVL == lvl)
        exp.plusCurrent(-40);
    else
        exp.plusCurrent(-60);
}

bool Creature::levelUP(bool player) {
    if (player) {
        if (!exp.isZero()) {
            std::cout << "You cant evolve yet. \n";
            return false;
        } else {
            for (int i = 0; i < 2; i++) {
                std::cout << "Which attribute do you want to evolve? \n 1: strength"
                             "\n 2: dexterity"
                             "\n 3: hitPoints\n";
                int x;
                std::cin >> x;
                switch (x) {
                    case 1: {
                        strength.setMaxValue(strength.getCurrentValue() + 5);
                        strength.resetValue();
                        break;
                    }
                    case 2: {
                        dexterity.setMaxValue(dexterity.getCurrentValue() + 5);
                        dexterity.resetValue();
                        break;
                    }
                    case 3: {
                        hitPoints.setMaxValue(hitPoints.getCurrentValue() + 5);
                        hitPoints.resetValue();
                        break;
                    }
                    default: {
                        std::cout << "Wrong choice, try again.\n";
                        i--;
                    }
                }
            }
            std::cout << "Your creature has evolved!!\nCurrent LVL: " << ++lvl << std::endl;
            return true;
        }
    } else {
        if (!exp.isZero()) {
            return false;
        }else {
            for (int i = 0; i < 2; i++) {
                int x = rand() % 3;
                switch (x) {
                    case 0: {
                        strength.setMaxValue(strength.getCurrentValue() + 5);
                        strength.resetValue();
                        break;
                    }
                    case 1: {
                        dexterity.setMaxValue(dexterity.getCurrentValue() + 5);
                        dexterity.resetValue();
                        break;
                    }
                    case 2: {
                        hitPoints.setMaxValue(hitPoints.getCurrentValue() + 5);
                        hitPoints.resetValue();
                        break;
                    }
                    default: {
                        i--;
                    }
                }
            }
            std::cout << "Enemy's creature has evolved!!\nCurrent LVL: " << ++lvl << std::endl;
            return true;
        }
    }
}

void Creature::applyEffect(int effectNR, int duration, int strength, Creature &target) {
    switch (effectNR) {
        case 1:{
            target.addEffect(Effect(false, "Burning", "Causes host to LOSE 10 HP at the START of turn.", duration, effectNR));
            std::cout << "\nBurning effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
            break;
        }
        case 2:{
            target.addEffect(Effect(false, "Disoriented", "Causes host to MISS the target 30% more likely.", duration, effectNR));
            std::cout << "\nDisoriented effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
            break;
        }
        case 3:{
            target.addEffect(Effect(false, "Frozen", "Causes host to not be able to perform ACTIONS.", duration, effectNR));
            std::cout << "\nFrozen effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
            break;
        }
        case 4:{
            target.addEffect(Effect(false, "Bleeding", "Bleeding - Causes host to lose HP equal to turns left at the START.", duration, effectNR));
            std::cout << "\nBleeding effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
            break;
        }
        case 5:{
            target.addEffect(Effect(false, "Slowed", "Causes host to lose 20% DEXTERITY.", duration, effectNR));
            std::cout << "\nSlowed effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
            break;
        }
        case 6:{
            target.addEffect(Effect(false, "Weaken", "Causes host to lose 10% STRENGTH.", duration, effectNR));
            std::cout << "\nWeaken effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
            break;
        }
        case 7:{
            target.addEffect(Effect(false, "Vulnerable", "Causes host to LOSE 2HP MORE from all sources.", duration, effectNR));
            std::cout << "\nVulnerable effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
            break;
        }
        case 8:{
            target.addEffect(Effect(false, "Mind Controlled", "Host has a 1% chance to attack himself.", duration, effectNR));
            std::cout << "\nMind Controlled effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
            break;
        }
//        case 9:{
//            target.addEffect(Effect(false, "Stunned", "Host has 20% chance to miss his turn.", duration, effectNR));
//            std::cout << "Stunned effect has been applied to " << target.getName() << " for " << duration << " turns.";
//            break;
//        }
        case 10:{
            target.addEffect(Effect(true, "Foccused", "Causes host to HIT the target 30% more likely.", duration, effectNR));
            std::cout << "\nFoccused effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
            break;
        }
        case 11:{
            target.addEffect(Effect(true, "Dodge", "Causes host to DODGE next enemy attack. Disappears once host DODGES.", duration, effectNR));
            std::cout << "\nDodge effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
            break;
        }
        case 12:{
            target.addEffect(Effect(true, "Strengthen", "Causes host to gain 10% STRENGTH.", duration, effectNR));
            std::cout << "\nStrengthen effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
            break;
        }
        case 13:{
            target.addEffect(Effect(true, "Fortified", "Causes host to LOSE 5HP LESS from all sources.", duration, effectNR));
            std::cout << "\nFortified effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
            break;
        }
        case 14:{
            std::string str = "Causes host to be HEALED at the START of turn for " + std::to_string(strength);
            target.addEffect(Effect(true, "Slow Heal", str, duration, strength, effectNR));
            std::cout << "\nSlow Heal effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
            break;
        }
//        case 15:{
//            target.addEffect(Effect(true, "Faster", "Causes host to have 2 actions.", duration, effectNR));
//            std::cout << "\nFaster effect has been applied to " << target.getName() << " for " << duration << " turns." << std::endl;
//            break;
//        }
//        case 16:{
//            target.addEffect(Effect(true, "Shielded", "Host has additional HP shield of [num]", duration, strength, effectNR));
//            std::cout << "Shielded effect has been applied to " << target.getName() << " for " << duration << " turns.";
//            break;
//        }
        default: break;
    }
}

void Creature::useAbility(int abilityNR,int &ultPoints, Creature &caster, Creature &target) {

    std::cout << "~~~~~~~~~~~~~~~~~~~~ COMBAT LOG ~~~~~~~~~~~~~~~~~~~~\n";
    int abilityID = caster.abilities.at(abilityNR).getAbilityId();
    switch (abilityID) {
        case 1: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(0).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                bool rng = (rand() % 2) == 1;
                int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]);
                target.hitPoints.plusCurrent(-pow);
                std::cout << " for: " << pow << " dmg!\n";
                if (rng)
                    applyEffect(2, 1, 0, target);
            }
            break;
        }
        case 2: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(1).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            for (int i = 0; i < 2; i++)
                if (checkForHit(caster, target)) {
                    int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]);
                    target.hitPoints.plusCurrent(-pow);
                    std::cout << " for: " << pow << " dmg!\n";
                }
            break;
        }
        case 3: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(2).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            target.hitPoints.plusCurrent(caster.strength.getCurrentValue());
            break;
        }
        case 4: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(3).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            target.hitPoints.plusCurrent(caster.strength.getCurrentValue());
            int i = 0;
            for (Effect const &effect: target.effects) {
                if (!effect.isType())
                    target.effects.erase(target.effects.begin() + i);
                i++;
            }
            break;
        }
        case 5: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(4).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            target.hitPoints.resetValue();
            applyEffect(14, 1, 100, target);
            break;
        }
        case 6: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(0).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]) / 3;
                target.hitPoints.plusCurrent(-pow);
                applyEffect(2, 3, 0, target);
                std::cout << " for: " << pow << " dmg!\n";
            }
            break;
        }
        case 7: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(1).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            applyEffect(13, 5, 0, target);
            break;
        }
        case 8: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(2).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                int pow = (int) ((caster.hitPoints.getMaxValue() - caster.hitPoints.getCurrentValue()) *
                                 dmgMod[caster.type][target.type]);
                target.hitPoints.plusCurrent(-pow);
                applyEffect(2, 3, 0, target);
                std::cout << " for: " << pow << " dmg!\n";
            }
            break;
        }
        case 9: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(3).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            target.hitPoints.plusCurrent(caster.strength.getCurrentValue());
            applyEffect(13, 10, 0, target);
            break;
        }
        case 10: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(4).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]);
                target.hitPoints.plusCurrent(-pow);
                applyEffect(2, 10, 0, target);
                std::cout << " for: " << pow << " dmg!\n";
            }
            break;
        }
        case 11: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(0).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                applyEffect(4, 4, 0, target);
                applyEffect(7, 4, 0, target);
                std::cout << "n";
            }
            break;
        }
        case 12: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(1).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            for (int i = 0; i < 5; i++) {
                if (checkForHit(caster, target)) {
                    int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]) / 10;
                    target.hitPoints.plusCurrent(-pow);
                    std::cout << " for: " << pow << " dmg!\n";
                }
            }
            break;
        }
        case 13: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(2).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]);
                target.hitPoints.plusCurrent(-pow);
                applyEffect(5, 3, 0, target);
                std::cout << " for: " << pow << " dmg!\n";
            }
            break;
        }
        case 14: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(3).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            for (int i = 0; i < 15; i++) {
                if (checkForHit(caster, target)) {
                    int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]) / 10;
                    target.hitPoints.plusCurrent(-pow);
                    std::cout << " for: " << pow << " dmg!\n";
                }
            }
            break;
        }
        case 15: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(4).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            applyEffect(12, 5, 0, target);
            for (int i = 0; i < 3; i++)
                applyEffect(11, 10, 0, target);
            break;
        }
        case 16: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(0).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]) / 2;
                target.hitPoints.plusCurrent(-pow);
                std::cout << " for: " << pow << " dmg!\n";
                applyEffect(1, 3, 0, target);
            }
            break;
        }
        case 17: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(1).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                bool rng = (rand() % 10) == 1;
                int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]);
                target.hitPoints.plusCurrent(-pow);
                std::cout << " for: " << pow << " dmg!\n";
                if (rng)
                    applyEffect(1, 2, 0, target);
            }
            break;
        }
        case 18: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(2).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            target.hitPoints.plusCurrent(caster.strength.getCurrentValue());
            applyEffect(12, 3, 0, target);
            break;
        }
        case 19: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(3).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            for (int i = 0; i < 5; i++) {
                if (checkForHit(caster, target)) {
                    applyEffect(1, 5, 0, target);
                }
            }
            break;
        }
        case 20: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(4).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type] * 3);
                target.hitPoints.plusCurrent(-pow);
                std::cout << " for: " << pow << " dmg!\n";
                applyEffect(1, 2, 0, target);
            }
            break;
        }
        case 21: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(0).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            applyEffect(13, 3, 0, target);
            break;
        }
        case 22: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(1).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                bool rng = (rand() % 2) <= 1;
                int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]);
                target.hitPoints.plusCurrent(-pow);
                std::cout << " for: " << pow << " dmg!\n";
                if (rng)
                    applyEffect(5, 2, 0, target);
            }
            break;
        }
        case 23: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(2).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]);
                target.hitPoints.plusCurrent(-pow);
                std::cout << " for: " << pow << " dmg!\n";
                applyEffect(4, 3, 0, target);
            }
            break;
        }
        case 24: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(3).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                applyEffect(3, 2, 0, target);
            }
            break;
        }
        case 25: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(4).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            for (int i = 0; i < 3; i++)
                if (checkForHit(caster, target)) {
                    int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]);
                    target.hitPoints.plusCurrent(-pow);
                    std::cout << " for: " << pow << " dmg!\n";
                    applyEffect(5, 6, 0, target);

                }
            break;
        }
        case 26: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(0).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            applyEffect(10, 5, 0, target);
            break;
        }
        case 27: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(1).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                bool rng = (rand() % 2) == 1;
                int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]);
                target.hitPoints.plusCurrent(-pow);
                std::cout << " for: " << pow << " dmg!\n";
                if (rng)
                    applyEffect(4, 2, 0, target);
            }
            break;
        }
        case 28: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(2).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                int pow = (int) (caster.strength.getCurrentValue() * dmgMod[caster.type][target.type]);
                target.hitPoints.plusCurrent(-pow);
                std::cout << " for: " << pow << " dmg!\n";
                applyEffect(6, 5, 0, target);
            }
            break;
        }
        case 29: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(3).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                applyEffect(2, 5, 0, target);
                applyEffect(5, 5, 0, target);
            }
            break;
        }
        case 30: {
            std::cout << caster.getName() << " used ";
            caster.abilities.at(4).abilityUsed(ultPoints);
            std::cout << " on " << target.getName() << "\n";
            if (checkForHit(caster, target)) {
                applyEffect(1, 2, 0, target);
                applyEffect(2, 2, 0, target);
                applyEffect(4, 2, 0, target);
                applyEffect(5, 2, 0, target);
                applyEffect(6, 2, 0, target);
                applyEffect(7, 2, 0, target);
            }
            break;
        }
        default: {
            std::cout << abilityID << "\n";
            break;
        }
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~            ~~~~~~~~~~~~~~~~~~~~\n";
    if(!target.isAlive())
        caster.gainExperience(target.getLvl());
}

bool Creature::checkForHit(Creature &caster, Creature &target) {
    double missTreshold = (double)target.dexterity.getCurrentValue() / ((double)caster.hitChance.getCurrentValue()/100);
    missTreshold /= 5;
    if(rand() % 100 < missTreshold){
        std::cout << "Ability missed " << target.name << "!\n";
        return false;
    }else{
        int i = 0;
        for(Effect effect : target.effects){
            if(target.checkForEffect(11)) {
                std::cout << target.name  << " DODGED the ability!\n";
                target.effects.erase(target.effects.begin()+i);
                return false;
            }
            i++;
        }
    }
    std::cout << "ABILITY HIT "<< target.name;
    return true;

}

void Creature::combatAbilityInfo(int points) {
    int i = 1;
    for(SpecialAbility &sp : abilities){
        std::cout << i++ << ".\t";
        sp.combatInfo(points);
    }
}

int Creature::getLvl() const {
    return lvl;
}

Creature::Creature() {
    name = "0";
    strength = Values(1);
    dexterity = Values(1);
    hitPoints = Values(1);
    exp = Values(1);
    abilities = std::vector<SpecialAbility>();
    effects = std::vector<Effect>();
    lvl = 0;
    hitChance = Values(1);
}

void Creature::choiceInfo() {
    std::cout << "Name: " << name << "\tType: ";
    switch (type) {
        case 0: std::cout << "Water"; break;
        case 1: std::cout << "Earth"; break;
        case 2: std::cout << "Wind"; break;
        case 3: std::cout << "Fire"; break;
        case 4: std::cout << "Ice"; break;
        case 5: std::cout << "Steel"; break;
        default: break;
    }
    std::cout << "\tStrength: " << strength.getMaxValue()
    << "\tDexterity: " << dexterity.getMaxValue()
    << "\tHitPoints: " << hitPoints.getMaxValue()
    << "\t LVL: " << lvl << "\n";
}

bool Creature::isAlive() {
    if (hitPoints.getCurrentValue() <= 0)
        return false;
    return true;
}

void Creature::resetCreature() {
    hitPoints.resetValue();
    strength.resetValue();
    dexterity.resetValue();
    hitChance.resetValue();
    effects.clear();
}

std::vector<SpecialAbility> &Creature::getAbilities(){
    return abilities;
}

std::string Creature::toString() {
    std::string output = name
            + "\n" + std::to_string(strength.getMaxValue())
            + "\n" + std::to_string(dexterity.getMaxValue())
            + "\n" + std::to_string(hitPoints.getMaxValue())
            + "\n" + std::to_string(exp.getMaxValue())
            + "\n" + std::to_string(type) + "\n";
    return output;
}

void Creature::kill() {
    hitPoints.setCurrentValue(0);
}




