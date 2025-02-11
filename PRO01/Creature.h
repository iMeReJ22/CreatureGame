//
// Created by Jeremi on 30.05.2022.
//

#ifndef PRO01_CREATURE_H
#define PRO01_CREATURE_H
#include "Values.h"
#include <string>
#include <vector>
#include "Effect.h"
#include "SpecialAbility.h"
class Creature {
    static constexpr double dmgMod [6][6] = { //first [] attacking  | second [] defending
            {0.7,   1.3,    1,      1.3,    1,      1},
            {1,     1,      0.7,    1.3,    1.3,    1.3},
            {1,     0.7,    1,      1,      1.3,    0.7},
            {0.7,   0.7,    1,      1,      1.3,    1.3},
            {0.7,   1.3,    1,      0.7,    0.7,    1},
            {1.3,   1,      1.3,    0.7,    1,      0.7}
    };
    std::string name;
    Values strength;
    Values dexterity;
    Values hitPoints;
    Values exp;
    std::vector<SpecialAbility> abilities;
    std::vector<Effect> effects;
    int lvl;
    Values hitChance;
    int type;   //0-water 1-earth 2-air 3-fire 4-ice 5-steel

public:
    Creature(std::string name, int str, int dex, int hp, int exp, int type, std::vector<std::vector<SpecialAbility>> &all);

    Creature();
/*!
 * Funkcja powoduję że Stworek traci przytomność.
 */
    void kill();
/*!
 * Funkcja odpowiedzalna za ulepszanie Stworka.
 * @param player
 * @return Zwraca true, gdy można, false, gdy nie można.
 */
    bool levelUP(bool player);
/*!
 * Dodaje punkty doświadczenie w zależności od poziomu pokonanego przeciwnika.
 * @param enemyLVL
 */
    void gainExperience(int enemyLVL);
/*!
 * Wyswietla informacje o Stworku w trakcie bitwy.
 */
    void creatureInfo();
/*!
 * Sprawdza możliwe efekty na początku tury.
 */
    void checkForStartEffects();

/*!
 * Usuwa 1 ture ze wszystkich efektów na Stworku.
 */
void minusTurns();
/*!
 * Zajmuje się efektami występującymi na koniec tury.
 */
void checkForEndEffects();
/*!
 * Usuwa efekty, które już się skończyły.
 */
void removeExpiredEffects();
/*!
 * Ile razy Stowrek posiada dany efekt.
 * @param effectNR
 * @return
 */
int checkForEffect(int effectNR);
/*!
 * Dodaje efekt do stworka.
 * @param effect
 */
void addEffect(const Effect& effect);
/*!
 * Zajmuje się nakladaniem efektów na innego Stworka.
 * @param effectNR
 * @param duration
 * @param strength
 * @param target
 */
static void applyEffect( int effectNR, int duration, int strength, Creature &target);
/*!
 * Zajmuje się używaniem umiejętności Stworków.
 * @param abilityNR
 * @param ultPoints
 * @param caster
 * @param target
 */
static void useAbility(int abilityNR,int &ultPoints, Creature &caster, Creature &target);

const std::string &getName() const;
/*!
 * Wyswietla informacje o efektach na Stworku.
 */
void effectInfo();
/*!
 * Sprawdza czy umiejetność trafi przeciwnika.
 * @param caster
 * @param target
 * @return
 */
static bool checkForHit(Creature &caster, Creature &target);
/*!
 * Wyswietla informacje o umiejetnościach na Stworku.
 * @param points
 */
void combatAbilityInfo(int points);

int getLvl() const;
/*!
 * Wyswietla informacje o Stworku.
 */
void choiceInfo();

bool isAlive();
/*!
 * Resetuje życie i usuwa wszystkie efekty ze Stworka.
 */
void resetCreature();

std::vector<SpecialAbility> &getAbilities();

std::string toString();
};


#endif //PRO01_CREATURE_H
