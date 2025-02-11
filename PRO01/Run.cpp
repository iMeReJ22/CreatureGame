//
// Created by Jeremi on 14.06.2022.
//

#include <iostream>
#include <fstream>
#include "Run.h"
#include "Battle.h"
#include "CustomExceptions.h"
#include "Help.h"

Run::Run(std::vector<Creature> &allCreatures, std::vector<std::vector<SpecialAbility>> &all) {
    battleCounter = 1;
    std::cout << "~~~~~~~~~~~~~~~~~ WELCOME ~~~~~~~~~~~~~~~~~\n"
                 "1 - New Game.\n"
                 "2 - Load Game.\n"
                 "~~~~~~~~~~~~~~~~~         ~~~~~~~~~~~~~~~~~\n";
    std::string tmp;
    bool go = true;
    while (go){
        std::cout << "Type in your choice:";
        std::cin >> tmp;
        try {
               if(tmp == "-h" || tmp == "--help")
                   throw CallHelpException();

            int choice = std::stoi(tmp);
            if(choice != 1 && choice != 2)
                throw std::invalid_argument("");
            if(choice == 1){
                myTeam = Team(allCreatures, 6, true);
                std::cout << "\n0 - 1 Battle.\n"
                             "1 - Normal\n"
                             "2 - Hard\n"
                             "3 - Impossible / Endless\n"
                             "Type in the difficulty.\n";
                bool go2 = true;
                while(go2){
                    std::string tmp2;
                    std::cin >> tmp2;
                    try{
                        if(tmp == "-h" || tmp == "--help")
                            throw CallHelpException();
                        int choice2 = std::stoi(tmp2);
                        diffuculty = choice2;
                        switch (choice2) {
                            case 0:{
                                maxBattles = 1;
                                go = false;
                                go2 = false;
                                break;
                            }
                            case 1:{
                                maxBattles = 4;
                                go = false;
                                go2 = false;
                                break;
                            }
                            case 2:{
                                maxBattles = 10;
                                go = false;
                                go2= false;
                                break;
                            }
                            case 3:{
                                maxBattles = 1000000;
                                go = false;
                                go2 = false;
                                break;
                            }
                            default:{
                                std::cout << "Wrong number, try again.\n";
                                break;
                            }
                        }
                    }catch(std::invalid_argument &e){
                        std::cout << "Invalid number, try again.\n";
                    } catch (CallHelpException &e) {
                        Help::difficultyHelp();
                    }
                }
            }
            if (choice == 2) {
                go = !loadGame(all);
            }
        } catch (std::invalid_argument &e) {
            std::cout << "Invalid number, try again.\n";
        } catch (CallHelpException &e) {
            Help::mainMenuHelp();
        }
    }
    run(allCreatures);
}

void Run::saveGame() {
    std::ofstream savefile;
    savefile.open("savefile.txt");
    savefile << diffuculty << std::endl;
    savefile << battleCounter << std::endl;
    savefile << maxBattles << std::endl;
    for(Creature &cr : myTeam.getCreatures()) {
        savefile << cr.toString();
    }
    savefile.close();
    std::cout << "**********\n"
                 "GAME SAVED\n"
                 "**********";
}

bool Run::loadGame(std::vector<std::vector<SpecialAbility>> &all) {
    std::string line;
    std::ifstream savefile("savefile.txt");
    if(savefile.is_open()){
        int i = 0;
        std::getline(savefile, line);
        diffuculty = std::stoi(line);
        std::getline(savefile, line);
        battleCounter = std::stoi(line);
        std::getline(savefile, line);
        maxBattles = std::stoi(line);
        std::string name;
        int str;
        int dex;
        int hp;
        int xp;
        int type;
        while(std::getline(savefile, line)){
            if(i == 0)
                name = line;
            if(i == 1)
                str = std::stoi(line);
            if(i == 2)
                dex = std::stoi(line);
            if(i == 3)
                hp = std::stoi(line);
            if(i == 4)
                xp = std::stoi(line);
            if(i == 5) {
                type = std::stoi(line);
                i = 0;
                myTeam.getCreatures().emplace_back(Creature(name, str, dex, hp, xp, type, all));
            }else
                i++;
        }
        savefile.close();
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ YOUR TEAM ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        for(Creature cr : myTeam.getCreatures()){
            cr.choiceInfo();
        }
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        return true;
    }else {
        std::cout << "Sorry, cant reach the file.\n";
        savefile.close();
        return false;
    }
}

void Run::nextBattle(std::vector<Creature> &allCreatures) {
    int enemySize = battleCounter + 3;
    if(enemySize > 16)
        enemySize = 16;
    Battle newBattle(myTeam, enemySize, allCreatures, battleCounter, diffuculty);
}

void Run::run(std::vector<Creature> all) {
    for(;battleCounter <= maxBattles;){
        std::cout << "\n~~~~~~~~~~~~~~~~~ OPTIONS ~~~~~~~~~~~~~~~~~\n";
        std::cout << "1 - Next Battle.\n"
                     "2 - Save Game.\n"
                     "3 - Exit Game.\n";
        std::cout << "~~~~~~~~~~~~~~~~~         ~~~~~~~~~~~~~~~~~\n"
                     "Type in your next move:";
        std::string tmp;
        std::cin >> tmp;

        try{
            if(tmp == "-h" || tmp == "--help")
                throw CallHelpException();
            int choice = std::stoi(tmp);
            switch (choice) {
                case 1:{
                    nextBattle(all);
                    battleCounter++;
                    break;
                }
                case 2:{
                    saveGame();
                    break;
                }
                case 3:{
                    exit(-1);
                }
                default:{
                    std::cout << "Invalid number, try again.";
                    break;
                }
            }
        }catch(std::invalid_argument &e){
            std::cout << "Invalid number, try again.\n";
        } catch(CallHelpException &e) {
            Help::mainMenuHelp();
        }
    }
    std::cout << "~~~~~~~~~~~~~~~~~ CONGRATULATIONS ~~~~~~~~~~~~~~~~~\n"
                 "\t\tYou WON the whole game.\n"
                 "~~~~~~~~~~~~~~~~~                 ~~~~~~~~~~~~~~~~~\n";
}
