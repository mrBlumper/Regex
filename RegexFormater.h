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
        void        replaceGroups();
        void        createDuplicatas();
        void        convert();

        std::string getStr(){return _current;}
        void debug();
    protected:
        std::string _current;
        std::vector<short>  _temp_shorts;
    private:
        int         findBestReplace(int index);
};

#endif // REGEXFORMATER_H
