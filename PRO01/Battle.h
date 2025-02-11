//
// Created by Jeremi on 14.06.2022.
//

#ifndef PRO01_BATTLE_H
#define PRO01_BATTLE_H


#include "Team.h"

class Battle {
    int battleNR;
    Team playerTeam;
    Team enemyTeam;
    int turnCounter;
    int difficulty;
public:
    Battle(const Team &playerTeam, int enemySize, const std::vector<Creature> &allCreatures, int battleNR, int difficulty);
/*!
 * Funkcja wywoływana na początku walki.
 * Pokazuje obie drużyny.
 * Wybiera się, z którym Stworkiem się zaczyna.
 */
    void battleStart();
/*!
 * Funkcja wywoływana na końcu walki.
 * Albo resetuje Stworki i wyswietla informacje o wygranej
 * albo wyswietla informacje o przegranej i konczy program.
 */
    void battleEnd();

/*!
 * Zajmuje się przebiegiem tury.
 * Najpierw gracza potem przeciwnika.
 * Sprawdza czy gra się nie skończyła.
 * @return zwraca false jeśli gra się kończy
 * zwraca true jeśli gra ma się toczyć dalej
 */
bool turn();
/*!
 * Sprawdza czy gra się nie skończyla.
 * @return zwraca false jeśli gra się kończy
 * zwraca true jeśli gra ma się toczyć dalej
 */
bool checkForEnd();
/*!
 * Zajmuję się początkiem każdej tury,
 * sprawdza efekty poczatku tury dla każdego Stworka
 * i wyswietla informacje o aktualnych stworkach inPlay.
 */
void turnStart();
/*!
 * Zajmuje się końcem tury,
 * sprawdza efekty końca tury
 * zmniejsza cooldowny
 * i zwieksza ultPoinsty dla obu drużyn.
 */
void turnEnd();
/*!
 * Zajmuję się obslugiwaniem i wyborem umiejętności.
 * @param player
 * @return
 * Zwraca true gdy wybrana zostanie dobra umiejejtnows.
 * false gdy gracz zdecyduje się powrocic.
 */
bool abilities(bool player);
/*!
 * Zajmuje się obsługą zmiany Stworków w drużynach.
 * @param player
 * @return
 * zwraca true gdy uda się wybrać.
 * zwraca false gdy nie można wybrać.
 */
bool swap(bool player);
/*!
 * Zajmuje się obsługą zwiekszania poziomu Stworka.
 * @param player
 * @return
 * zwraca true gdy uda się evoluować
 * zwraca false gdy nie uda się evoluować.
 */
bool evolve(bool player);
/*!
 * Zajmuje się wybieraniem celu dla umiejętności Stworków.
 * @param player
 * @param friendly
 * @return
 */
Creature &choseTarget(bool player, bool friendly);
/*!
 * Zajmuje się obsługą tury gracza.
 */
void playerTurn();
/*!
 * Zajmuje się obsługa tury komputera.
 */
void enemyTurn();
/*!
 * Wyswietla całe drużyny gracza i komputera.
 */

void showTeams();

};


#endif //PRO01_BATTLE_H
