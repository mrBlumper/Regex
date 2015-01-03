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
        void format();
        void toPostfix();
        void compile();
        int match(std::string m);
        virtual ~Regex();
    protected:
        std::string         _base;
        std::vector<short>  _formated;
        std::vector<short>  _postfix;
        NFA                 _nfa;
        DFA                 _dfa;

        bool _start_symbol;
        bool _end_symbol;
    private:
};

#endif // REGEX_H
