#ifndef REGEXFORMATER_H
#define REGEXFORMATER_H

#include "declarations.h"

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

        /* return the group present in the regex before the index pos */
        std::string getPreviousGroup(const unsigned int pos);
        /* convert operators to the other format (in declarations.h) and escape char */
        void        treatSpecialCharacters();
        /* replace the groups in a regex (\\d, [:digits:]...) */
        void        replaceGroups();
        /* transforms [...] groups to (.|..|.) groups */
        void        createDuplicatas();
        /* convert the formated regex to the custom short format */
        void        convertToShort();
        /* set the explicit concatenation */
        void        setExplicitConcat();
        /* mix all of the previous fonctions to transform the regex */
        void        convert();

        /*getters*/
        std::string getStr(){return _current;}
        std::vector<short>  getFinalRep(){return _temp_shorts;}
        void debug();
    protected:
        std::string _current;
        std::vector<short>  _temp_shorts;
        bool    _conversion;
    private:
        /* find the best replacement group for the sustring beginning at index index -> return the index of the group */
        int         findBestReplace(int index);
        /* parse {a, b} instructions */
        RegexRepetition treatRepetition(int index);
};

#endif // REGEXFORMATER_H
