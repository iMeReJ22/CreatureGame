//
// Created by mario on 16.06.2022.
//

#ifndef PRO01_CUSTOMEXCEPTIONS_H
#define PRO01_CUSTOMEXCEPTIONS_H
#include "iostream"
class FrozenException : public std::exception{};

class NotReadyException : public std::exception{};

class CallHelpException : public std::exception{};

class CreatureUnconsciousException : public std::exception{};

class DevKillCommandException : public std::exception{};
#endif //PRO01_CUSTOMEXCEPTIONS_H
