#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <vector>
#include <string>
#include <iostream>
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

    extern std::string escaped_char;
    extern std::vector<char> operators;
}


#endif // DECLARATIONS_H
