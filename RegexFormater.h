#ifndef REGEXFORMATER_H
#define REGEXFORMATER_H

#include "declarations.h"
#include <iostream>

class RegexFormater
{
    public:
        RegexFormater(std::string regex);
        virtual ~RegexFormater();

        std::string getPreviousGroup(const unsigned int pos);
        void        treatSpecialCharacters();

        std::string getStr(){return _current;}
        void debug();
    protected:
        std::string _current;
    private:
};

#endif // REGEXFORMATER_H
