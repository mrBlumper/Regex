#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <vector>
#include <string>
#include <iostream>
#include <map>

std::string toStr(char c);
inline bool isRange(const short symbol);
bool symbolCorresponds(const short symbol, const char c);
short makeRange(const char down, const char up);
template <typename T>
bool in(std::vector<T> list, T element){
    for (auto& e : list){
        if (e == element)
            return true;
    }
    return false;
}
bool in(const std::string str, const char element);


//constants
namespace SYMBOL{
    bool isOp(char c);
    struct ReplacedExpression{
        ReplacedExpression(std::string p, std::string t){
            pattern = p;
            translate = t;
        }
        ReplacedExpression(std::string p, std::initializer_list<std::string> t){
            pattern = p;
            translate = "";
            for (auto& e : t)
                translate += e;
        }
        std::string pattern;
        std::string translate;
    };
    extern char BEGIN_WORD;
    extern char END_WORD;
    extern char CONCATENATION;
    extern char ZEROORMORE;
    extern char ONEORMORE;
    extern char ZEROORONE;
    extern char BACKSLASH;
    extern char CARET;
    //put space for char 9 & 10 ('\n' and '\t')
    extern char DOLLAR;
    extern char OR;
    extern char OPEN_PAR;
    extern char CLOSE_PAR;
    extern char OPEN_BRACKET;
    extern char CLOSE_BRACKET;
    extern char OPEN_CURLY;
    extern char CLOSE_CURLY;
    extern char INTERVAL;

    extern std::string escaped_char;
    extern std::vector<char> operators;
    extern std::map<char, char> special_chars;
    extern std::vector<ReplacedExpression> replace_expressions;
}


#endif // DECLARATIONS_H
