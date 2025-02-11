//
// Created by Jeremi on 30.05.2022.
//

#ifndef PRO01_EFFECT_H
#define PRO01_EFFECT_H
#include <string>
#include "Values.h"
#include <vector>
class Effect {
    bool type;
    int strength;
    int effectNR;
    std::string name;
    std::string description;
    Values turns;

public:
    Effect(bool type, const std::string &name, const std::string &description, int duration, int effectNR);
    Effect(bool type, const std::string &name, const std::string &description, int duration, int strength, int effectNR);

public:
    const std::string &getName() const;

    int getEffectNr() const;

/*!
 * Wyswietla informacje o efekcie.
 */
void showInfo() const;
/*!
 * Odejmuję jedną turę od pozostałych tur trwania efektu.
 */
void turnMinus();

const Values &getTurns() const;

int getStrength() const;

bool isType() const;
};


#endif //PRO01_EFFECT_H
