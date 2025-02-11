//
// Created by Jeremi on 30.05.2022.
//

#include <iostream>
#include "SpecialAbility.h"
#include "Creature.h"
#include "ctime"

SpecialAbility::SpecialAbility(const std::string &name, const std::string &description, const Values &cooldown,
                               int ultCost, int abilityID, bool friendly) : name(name), description(description), cooldown(Values(cooldown)),
                                              ultCost(ultCost), type(true), abilityID(abilityID), friendly(friendly){}

SpecialAbility::SpecialAbility(const std::string &name, const std::string &description, const Values &cooldown, int abilityID, bool friendly) : name(
        name), description(description), cooldown(Values(cooldown)), type(false), ultCost(0), abilityID(abilityID), friendly(friendly) {}

bool SpecialAbility::isReady(int ultPoints) {
    if(type)
        return ultPoints >= ultCost;
    else
        return cooldown.getCurrentValue() == cooldown.getMaxValue();
}

void SpecialAbility::abilityUsed(int &ultPoints) {
    if(type){
        ultPoints -= ultCost;
    }else{
        cooldown.setCurrentValue(0);
    }
    std::cout << name;
}

void SpecialAbility::combatInfo(int ultPoints) {
    std::cout << name << "\n" << description << "\n";
    if(type) {
        std::cout << "Type: Ulitimate\tCost: " << ultCost <<"\n";
        if(isReady(ultPoints))
            std::cout << "READY\n";
        else
            std::cout << "NEED " << ultCost - ultPoints << " MORE ULT POINTS\n";
    }else{
        std::cout << "Type: Normal\t Cooldown: " << cooldown.getMaxValue() << "\n";
        if(isReady(ultPoints))
            std::cout << "READY\n";
        else
            std::cout << "ON COOLDOWN " << cooldown.getMaxValue() - cooldown.getCurrentValue() << " TURNS LEFT\n";
    }
}

int SpecialAbility::getAbilityId() const {
    return abilityID;
}

bool SpecialAbility::isFriendly() const {
    return friendly;
}

void SpecialAbility::turnMinus() {
    cooldown.plusCurrent(1);
    if(cooldown.getCurrentValue() >= cooldown.getMaxValue())
        cooldown.setCurrentValue(cooldown.getMaxValue());
}
