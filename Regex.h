#ifndef REGEX_H
#define REGEX_H


#include "RegexFormater.h"
#include <stack>
#include "NFA.h"
#include "DFA.h"

int REGEX_precedence(short c);

class Regex
{
    public:
        Regex(std::string reg);
        /* format the string */
        void format();
        /* convert the string to postfix format */
        void toPostfix();
        /* transform the string in a dfa */
        void compile();
        /* find the longest match beginning at pos 0 (change arg says if we transform m according to the presence of '$' & '^' symbol in the regex */
        int find(std::string m, bool change = true);
        /* return true if m is matched by regex */
        bool match(std::string m);
        virtual ~Regex();
    protected:
        std::string         _base;
        std::vector<short>  _formated;
        std::vector<short>  _postfix;
        NFA                 _nfa;
        DFA                 _dfa;

        bool _start_symbol;
        bool _end_symbol;
        bool _compiled;
    private:
};

#endif // REGEX_H
