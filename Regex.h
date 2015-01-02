#ifndef REGEX_H
#define REGEX_H


#include "RegexFormater.h"
#include <stack>

int REGEX_precedence(short c);

class Regex
{
    public:
        Regex(std::string reg);
        void format();
        void toPostfix();
        void compile();
        virtual ~Regex();
    protected:
        std::string         _base;
        std::vector<short>  _formated;
        std::vector<short>  _postfix;
    private:
};

#endif // REGEX_H
