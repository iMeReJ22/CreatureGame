//
// Created by Jeremi on 30.05.2022.
//

#include "Effect.h"
#include <iostream>

const std::string &Effect::getName() const {
    return name;
}


void Effect::showInfo() const {
    std::cout << "\t\t" << name;
    std::cout << "\n\t\tDescritpion: " << description;
    std::cout << "\n\tTurns left: " << turns.getCurrentValue()
    << " out of " << turns.getMaxValue() << ".\n";

}

void Effect::turnMinus() {
    turns.plusCurrent(-1);
}

Effect::Effect(bool type, const std::string &name, const std::string &description, int duration, int effectNR) :
type(type), name(name), description(description), turns(Values(duration)), strength(0), effectNR(effectNR){}

Effect::Effect(bool type, const std::string &name, const std::string &description, int duration, int strength, int effectNR) :
        type(type), name(name), description(description), turns(Values(duration)), strength(strength), effectNR(effectNR){}

int Effect::getEffectNr() const {
    return effectNR;
}

const Values &Effect::getTurns() const {
    return turns;
}

int Effect::getStrength() const {
    return strength;
}

bool Effect::isType() const {
    return type;
}




