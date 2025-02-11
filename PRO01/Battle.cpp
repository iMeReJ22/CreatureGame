//
// Created by Jeremi on 14.06.2022.
//

#include <iostream>
#include "Battle.h"
#include "CustomExceptions.h"
#include "Help.h"

void Battle::battleStart() {
    srand(time(NULL));
    //wybieranie inPlay
    showTeams();
    std::cout << "\nBATTLE NR: " << battleNR << "\n";
    bool go = true;
    std::string tmp;
    int choice;
    int i = 1;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CREATURES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for(Creature &cr : playerTeam.getCreatures()){
        std::cout << i++ << ".\t";
        cr.choiceInfo();
    }std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    while (go) {
        std::cout << "Type in with which Creature you want to start:";
        std::cin >> tmp;
        try {
            if(tmp == "-h" || tmp == "--help")
                throw CallHelpException();
            choice = std::stoi(tmp)-1;
            playerTeam.setInPlay(playerTeam.getCreatures().at(choice));
            playerTeam.getCreatures().erase(playerTeam.getCreatures().begin()+choice);
            go = false;
        } catch (const std::invalid_argument &e) {
            std::cout << "Invalid number, try again.\n";
        } catch (std::out_of_range &e) {
            std::cout << "Invalid number, try again.\n";
        } catch(CallHelpException &e) {
            Help::creatueHelp();
        }
    }
    choice = rand()%enemyTeam.getCreatures().size();
    switch (difficulty) {
        case 0: {
            playerTeam.setUltPoints(100);
            enemyTeam.setUltPoints(0);
            break;
        }
        case 1: {
            playerTeam.setUltPoints(40);
            enemyTeam.setUltPoints(30);
            break;
        }
        case 2: {
            playerTeam.setUltPoints(30);
            enemyTeam.setUltPoints(70);
            break;
        }
        case 3: {
            playerTeam.setUltPoints(0);
            enemyTeam.setUltPoints(100);
            break;
        }
        default: {
            playerTeam.setUltPoints(30);
            enemyTeam.setUltPoints(30);
            std::cout << "somehow we got here 😂\n";
        }

    }
    enemyTeam.setInPlay(enemyTeam.getCreatures().at(choice));
    enemyTeam.getCreatures().erase(enemyTeam.getCreatures().begin()+choice);
}

void Battle::battleEnd() {

    if(playerTeam.checkIfAlive()){
        std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                     "\tCongratulations you WON this battle.\n"
                     "\tYour Creatures will now rest,\n"
                     "\trecover their HP and lose all effects.\n"
                     "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        playerTeam.getCreatures().push_back(playerTeam.getInPlay());
        playerTeam.getInPlay() = Creature();

        for(Creature &cr : playerTeam.getCreatures()){
            cr.resetCreature();
        }
    }else{
        std::cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                     "\t\tYou lost.\n"
                     "\t\tYou lasted: " << battleNR <<
                     " battles."
                     "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        exit(-2);
    }
}

bool Battle::checkForEnd() {
    if(playerTeam.checkIfAlive() && enemyTeam.checkIfAlive())
        return true;
    return false;
}

Battle::Battle(const Team &playerTeam, int enemySize, const std::vector<Creature> &allCreatures, int battleNR, int difficulty) {
    this->playerTeam = playerTeam;
    enemyTeam = Team(allCreatures, enemySize, false);
    turnCounter = 1;
    this->battleNR = battleNR;
    battleStart();
    while(turn());
    battleEnd();
    this->difficulty = difficulty;
}

void Battle::turnStart() {
    std::cout << "\nTURN: " << turnCounter++ << "\n";
    for(Creature &pcr : playerTeam.getCreatures())
        pcr.checkForStartEffects();
    playerTeam.getInPlay().checkForStartEffects();
    for(Creature &ecr : enemyTeam.getCreatures())
        ecr.checkForStartEffects();
    enemyTeam.getInPlay().checkForStartEffects();

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CREATURES IN PLAY ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "YOUR: \n";
    playerTeam.getInPlay().creatureInfo();
    std::cout << "ENEMY'S: \n";
    enemyTeam.getInPlay().creatureInfo();
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void Battle::turnEnd() {
    for(Creature &pcr : playerTeam.getCreatures())
        pcr.checkForEndEffects();
    playerTeam.getInPlay().checkForEndEffects();
    for(Creature &ecr : enemyTeam.getCreatures())
        ecr.checkForEndEffects();
    enemyTeam.getInPlay().checkForEndEffects();
    playerTeam.bumpUltPoints();
    enemyTeam.bumpUltPoints();
    playerTeam.teamCooldowns();
    enemyTeam.teamCooldowns();
}

bool Battle::abilities(bool player) {
    srand(time(NULL));
    if(player) {
        std::cout << "-1 - GO BACK\n\nYour UltPoints: " << playerTeam.getUltPoints() << "\n\n";
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~ ABILITIES ~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        playerTeam.getInPlay().combatAbilityInfo(playerTeam.getUltPoints());
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~           ~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        bool go = true;
        std::string tmp;
        int choice;
        while (go) {
            std::cout << "Type in which ability do you want to use:";
            std::cin >> tmp;
            try {
                if(tmp == "-h" || tmp == "--help")
                    throw CallHelpException();
                if(tmp == "-killEnemy")
                    throw DevKillCommandException();
                choice = std::stoi(tmp)-1;
                if (choice == -1)
                    return false;
                if(playerTeam.getInPlay().getAbilities().at(choice).isReady(playerTeam.getUltPoints())) {
                    Creature::useAbility(choice, playerTeam.getUltPoints(),
                                         playerTeam.getInPlay(), choseTarget(true, playerTeam.getInPlay().getAbilities().at(choice).isFriendly()));
                    go = false;
                }else
                    throw NotReadyException();
            } catch (const std::invalid_argument &e) {
                std::cout << "Invalid number, try again.\n";
            } catch (std::out_of_range &e) {
                std::cout << "Invalid number, try again.\n";
            } catch (NotReadyException &e) {
                std::cout << "Ability is not ready, try again.\n";
            } catch (CallHelpException &e) {
                Help::effectHelp();
            } catch (DevKillCommandException &e) {
                go = false;
                enemyTeam.getInPlay().kill();
                std::cout << "Enemy's Creature in play fell unconscious.\n";
            }
        }
    }else{
        bool go = true;
        while (go){
            int choice = rand()%enemyTeam.getInPlay().getAbilities().size();
            if (enemyTeam.getInPlay().getAbilities().at(choice).isReady(enemyTeam.getUltPoints())){
                Creature::useAbility(choice, enemyTeam.getUltPoints(), enemyTeam.getInPlay(), choseTarget(false, enemyTeam.getInPlay().getAbilities().at(choice).isFriendly()));
                go = false;
            }
        }
    }
    return true;
}

bool Battle::swap(bool player) {
    if(player) {
        bool allDead = true;
        for(Creature &cr : playerTeam.getCreatures())
            if(cr.isAlive()){
                allDead = false;
                break;
            }
        if (allDead)
            return false;
        playerTeam.swapInPlay(player);
    }
    else {
        bool allDead = true;
        for(Creature &cr : playerTeam.getCreatures())
            if(cr.isAlive()){
                allDead = false;
                break;
            }
        if(allDead)
            return false;
        enemyTeam.swapInPlay(player);
    }
    return true;
}

bool Battle::evolve(bool player) {
    if(player)
        return playerTeam.getInPlay().levelUP(player);
    else
        return enemyTeam.getInPlay().levelUP(player);
}

Creature &Battle::choseTarget(bool player, bool friendly) {
    srand(time(NULL));
    if (player){
        int i = 1;
        if(friendly) {
            std::cout << "~~~~~~~~~~~~~~~~~ ALLIES ~~~~~~~~~~~~~~~~~\n";
            for (Creature &cr: playerTeam.getCreatures()) {
                std::cout << i++ << ".\t";
                cr.creatureInfo();
            } std::cout << i << "\t";
            playerTeam.getInPlay().creatureInfo();
            std::cout << "~~~~~~~~~~~~~~~~~        ~~~~~~~~~~~~~~~~~\n";
            bool go = true;
            std::string tmp;
            int choice;
            while (go) {
                std::cout << "Type in which Creature to target:";
                std::cin >> tmp;
                try {
                    if(tmp == "-h" || tmp == "--help")
                        throw CallHelpException();
                    choice = std::stoi(tmp) - 1;
                    go = false;
                    return playerTeam.getCreatures().at(choice);
                } catch (const std::invalid_argument &e) {
                    std::cout << "Invalid number, try again.\n";
                } catch (std::out_of_range &e) {
                    if(choice == i)
                        return playerTeam.getInPlay();
                    else
                        std::cout << "Invalid number, try again.\n";
                } catch (CallHelpException &e){
                        Help::creatueHelp();
                }
            }
        }
        else return enemyTeam.getInPlay();
    }else{
        if(friendly) {
            int choice = rand() % (enemyTeam.getCreatures().size());
            try {
                return enemyTeam.getCreatures().at(choice);
            } catch (std::out_of_range &e) {
                std::cout << "Somehow we got here??";
                return enemyTeam.getInPlay();
            }
        }
        else return playerTeam.getInPlay();
    }
    return playerTeam.getInPlay();
}

void Battle::playerTurn() {
    bool go = true;
    std::string tmp;
    int choice;
    while (go) {
        std::cout << "~~~~~~~~~~~~~~~~~ ACTIONS ~~~~~~~~~~~~~~~~~\n";
        std::cout << "1 - Use Creature's ability.\n"
                     "2 - Swap your in play Creature.\n"
                     "3 - Evolve your Creature.\n"
                     "4 - Show DMG modifier table.\n"
                     "~~~~~~~~~~~~~~~~~         ~~~~~~~~~~~~~~~~~\n";
        std::cout << "\nType in which action do you want to perform:";
        std::cin >> tmp;
        std::cout << "\n";
        try {
            if(tmp == "-h" || tmp == "--help")
                throw CallHelpException();
            choice = std::stoi(tmp);
            switch (choice) {
                case 1:{
                    if(playerTeam.getInPlay().checkForEffect(3))
                        throw FrozenException();
                    if(!playerTeam.getInPlay().isAlive())
                        throw CreatureUnconsciousException();
                    go = !abilities(true);
                    break;
                }
                case 2:{
                    go = !swap(true);
                    break;
                }
                case 3:{
                    if(!playerTeam.getInPlay().isAlive())
                        throw CreatureUnconsciousException();
                    go = !evolve(true);
                    break;
                }
                case 4:{
                    Help::showTable();
                    break;
                }
                default:{
                    std::cout << "Invalid number, try again.\n";
                }
            }
        } catch (const std::invalid_argument &e) {
            std::cout << "Invalid number, try again.\n";
        } catch (std::out_of_range &e) {
            std::cout << "Invalid number, try again.\n";
        } catch (FrozenException &e) {
            std::cout << "Creature is FROZEN, try again.\n";
        } catch (CallHelpException &e ) {
            Help::battleHelp();
        } catch (CreatureUnconsciousException &e) {
            std::cout << "Your Creature is unconscious,\n"
                         "you have to swap it.\n";
        }
    }
}

void Battle::enemyTurn() {
    if(!enemyTeam.getInPlay().isAlive())
        swap(false);
    else
        if(!enemyTeam.getInPlay().levelUP(false))
            if(enemyTeam.getInPlay().checkForEffect(3)) {
                swap(false);
            }else {
                abilities(false);
            }
}

bool Battle::turn() {
    turnStart();
    playerTurn();
    if(checkForEnd()) {
        enemyTurn();
    }
    turnEnd();
    return checkForEnd();
}

void Battle::showTeams() {
std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ YOUR TEAM ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
playerTeam.showTeam();
std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ENEMY TEAM ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
enemyTeam.showTeam();
std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
