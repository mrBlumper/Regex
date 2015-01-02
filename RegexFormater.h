#ifndef REGEXFORMATER_H
#define REGEXFORMATER_H

#include "declarations.h"
#include <iostream>

struct RegexRepetition{
    RegexRepetition(int s=0, int mi=0, int ma=0){
        size = s;
        min = mi;
        max = ma;
        interval = false;
    }
    int size;
    int min;
    int max;
    bool interval;
};

class RegexFormater
{
    public:
        RegexFormater(std::string regex);
        virtual ~RegexFormater();

        std::string getPreviousGroup(const unsigned int pos);
        void        treatSpecialCharacters();
        void        replaceGroups();
        void        createDuplicatas();
        void        convertToShort();
        void        convert();
        void        setExplicitConcat();

        std::string getStr(){return _current;}
        std::vector<short>  getFinalRep(){return _temp_shorts;}
        void debug();
    protected:
        std::string _current;
        std::vector<short>  _temp_shorts;
        bool    _conversion;
    private:
        int         findBestReplace(int index);
        RegexRepetition treatRepetition(int index);
};

#endif // REGEXFORMATER_H
