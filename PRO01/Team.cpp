//
// Created by Jeremi on 14.06.2022.
//

#include <iostream>
#include "Team.h"
#include "ctime"
#include "CustomExceptions.h"
#include "Help.h"

Team::Team(std::vector<Creature> optional, int size, bool player) {
    //srand(time(nullptr));
    int choice;
    if(player){
        std::string tmp;
        std::cout << "Choose you team of " << size << " Creatures. \n";
        for(int i = 0; i < size; i++) {
            int j = 1;
            for(Creature &cr : optional){
                std::cout << j <<".\t";
                cr.choiceInfo();
                j++;
            }
            bool go = true;
            while (go) {
                std::cout << "\nType in the number of creature that you want in your team:";
                std::cin >> tmp;
                if(tmp == "-h" || tmp == "--help")
                    throw CallHelpException();
                try {
                    choice = std::stoi(tmp)-1;
                    creatures.push_back(optional.at(choice));
                    optional.erase(optional.begin() + choice);
                    go = false;
                } catch (const std::invalid_argument &e) {
                    std::cout << "Invalid number, try again.\n";
                } catch (std::out_of_range &e) {
                    std::cout << "Invalid number, try again.\n";
                } catch (CallHelpException &e) {
                    Help::makeATeamHelp();
                }
            }
            std::cout << "You chose: \n\t";
            creatures.at(i).choiceInfo();
            std::cout << "\n";
        }
        std::cout << "Your team: \n";
        showTeamCreatures();
    }else{
        for(int i = 0; i < size; i++) {
            choice = rand() % optional.size();
            creatures.push_back(optional.at(choice));
            optional.erase(optional.begin() + choice);
        }
    }
    inPlay = Creature();
    ultPoints = 30;
}

void Team::showTeamCreatures() {
    for(Creature &cr : creatures)
        cr.choiceInfo();
}

Team::Team() {}

bool Team::checkIfAlive() {
    for(Creature &cr : creatures)
        if(cr.isAlive())
            return true;
    if(getInPlay().isAlive())
        return true;
    return false;
}

void Team::swapInPlay(bool player) {
    srand(time(NULL));
    if (player) {
        int i = 1;
        for (Creature &cr: creatures) {
            std::cout << i << ".\t";
            cr.creatureInfo();
            i++;
        }
        bool go = true;
        std::string tmp;
        int choice;
        while (go) {
            std::cout << "Type in to which Creature you want to swap:";
            std::cin >> tmp;
            try {
                if(tmp == "-h" || tmp == "--help")
                    throw CallHelpException();
                choice = std::stoi(tmp) - 1;
                if (creatures.at((choice)).isAlive()) {
                    if (inPlay.getLvl() != 0)
                        creatures.push_back(inPlay);
                    inPlay = creatures.at(choice);
                    creatures.erase(creatures.begin() + choice);
                    go = false;
                } else
                    throw CreatureUnconsciousException();
            } catch (const std::invalid_argument &e) {
                std::cout << "Invalid number, try again.\n";
            } catch (std::out_of_range &e) {
                std::cout << "Invalid number, try again.\n";
            } catch (CreatureUnconsciousException &e) {
                std::cout << "This Creature is unconscious, try again.\n";
            } catch (CallHelpException &e) {
                Help::swapHelp();
            }
        }
        std::cout << "You swapped to: \n";
        inPlay.creatureInfo();
    } else {
        bool go = true;
        while (go) {
            int choice = rand() % creatures.size();
            if (creatures.at(choice).isAlive()) {
                if (inPlay.getLvl() != 0)
                    creatures.push_back(inPlay);
                inPlay = creatures.at(choice);
                creatures.erase(creatures.begin() + choice);
                go = false;
            }
        }
        std::cout << "Enemy swapped to: \n";
        inPlay.creatureInfo();
    }
}

std::vector<Creature> &Team::getCreatures()  {
    return creatures;
}

Creature &Team::getInPlay(){
    return inPlay;
}

void Team::showTeam() {
    for(Creature &cr : creatures){
        cr.choiceInfo();
    }
    if(inPlay.getLvl() != 0)
        inPlay.choiceInfo();
}

void Team::setInPlay(const Creature &inPlay) {
    Team::inPlay = inPlay;
}

void Team::bumpUltPoints() {
    ultPoints+= 10;

    if(ultPoints > 100)
        ultPoints = 100;
}

int &Team::getUltPoints(){
    return ultPoints;
}

void Team::teamCooldowns() {
    for(SpecialAbility &sp : inPlay.getAbilities())
        sp.turnMinus();

    for(Creature &cr : creatures)
        for(SpecialAbility &sp : cr.getAbilities())
            sp.turnMinus();
}

void Team::setUltPoints(int ultPoints) {
    Team::ultPoints = ultPoints;
}

