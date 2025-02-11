//
// Created by Jeremi on 14.06.2022.
//

#ifndef PRO01_RUN_H
#define PRO01_RUN_H


#include "Team.h"

class Run {
    Team myTeam;
    int battleCounter;
    int maxBattles;
    int diffuculty; // 0 - easy // 1 - normal // 2 - hard // 3 - impossible

public:
    Run(std::vector<Creature> &allCreatures, std::vector<std::vector<SpecialAbility>> &all);

/*!
 * Metoda zapisuje gre do pliku.
 */
void saveGame();
/*!
 * Metoda włącza następną walkę.
 * @param allCreatures
 */
void nextBattle(std::vector<Creature> &allCreatures);
/*!
 * Rozpoczyna gre.
 * @param all
 */
void run(std::vector<Creature> all);
/*!
 * Wczytuje gre z pliku.
 * @param all
 * @return
 */
bool loadGame(std::vector<std::vector<SpecialAbility>> &all);
};


#endif //PRO01_RUN_H
