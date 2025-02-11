//
// Created by Jeremi on 14.06.2022.
//

#ifndef PRO01_TEAM_H
#define PRO01_TEAM_H


#include <vector>
#include "Creature.h"

class Team {
    std::vector<Creature> creatures;
    Creature inPlay;
    int ultPoints;

public:
    /*!
     * Podstawowy konstruktor.
     * @param optional
     * @param size
     * @param player jesli true, konstruktor dla gracza,
     * jesli false konstruktor automatyczny dla komputera.
     */
    Team(std::vector<Creature> optional, int size, bool player);

    Team();
/*!
 * Metoda wyświtla po koleji informacje o
 * każdym Stworku.
 */
    void showTeamCreatures();
/*!
 * Metoda sprawdza czy Stworek żyje.
 * @return
 */
    bool checkIfAlive();
/*!
 * Metoda zamienia Stworka, który aktualnie jest inPlay.
 * @param player jesli true wersja dla gracza,
 * jeśli false wersja dla komputera.
 */
    void swapInPlay(bool player);

    std::vector<Creature> &getCreatures();

    Creature &getInPlay();
/*!
 * Metoda wyświetla informacje o drużynie.
 */
    void showTeam();

    void setInPlay(const Creature &inPlay);
/*!
 * Metoda zwieksza ultPoints o 10.
 */
    void bumpUltPoints();

    int &getUltPoints();
/*!
 * Metoda zmniejsza wszystkie cooldowny u każdego
 * Stowrka o 1 ture.
 */
    void teamCooldowns();

    void setUltPoints(int ultPoints);
};


#endif //PRO01_TEAM_H
