//
// Created by Jeremi on 30.05.2022.
//

#ifndef PRO01_SPECIALABILITY_H
#define PRO01_SPECIALABILITY_H
#include <string>
#include "Values.h"
#include "vector"

class SpecialAbility {
protected:
    std::string name;
    std::string description;
    Values cooldown;
    bool type; // 0 - normal, 1 - ultimate;
    int ultCost;
    int abilityID;
    bool friendly;


public:
/*!
 * Konstruktor dla super umiejętności.
 * @param name
 * @param description
 * @param cooldown
 * @param ultCost
 * @param abilityID
 * @param friendly
 */
SpecialAbility(const std::string &name, const std::string &description, const Values &cooldown, int ultCost, int abilityID, bool friendly);
/*!
 * Konstruktor dla normalnej umiejętności.
 * @param name
 * @param description
 * @param cooldown
 * @param abilityID
 * @param friendly
 */
SpecialAbility(const std::string &name, const std::string &description, const Values &cooldown, int abilityID, bool friendly);
/*!
 * Sprawdza czy można użyć umiejetności.
 * @param ultPoints
 * @return
 * Zwraca true albo false w zależności czy umiejętność
 * można wykorzystać.
 */
bool isReady(int ultPoints);
/*!
 * Zmniejsza cooldown tej umiejętności o 1 ture.
 */
void turnMinus();
/*!
 * Wyswietla informacje o użyciu umiejętności
 * oraz ustawia jej cooldown.
 * @param ultPoints
 */
void abilityUsed(int &ultPoints);
/*!
 * Wyswietla informacje o umiejętności.
 * @param ultPoints
 */
void combatInfo(int ultPoints);

int getAbilityId() const;

bool isFriendly() const;
};


#endif //PRO01_SPECIALABILITY_H
