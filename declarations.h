#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <vector>
#include <string>

/*indicates if the symbol is a range or not*/
inline bool isRange(const short symbol){
    return (symbol != (symbol&0xFF));
}
/*return if the char c is matching with the symbol*/
bool symbolCorresponds(const short symbol, const char c){
    if (isRange(symbol)){
        return ((symbol & 0xFF) <= c && c <= (symbol>>8));
    }
    return (symbol == c);
}

/*Create a range [down up]*/
short makeRange(const char down, const char up){
    short temp = up;
    temp <<= 8;
    temp += down;
    return (temp);
}

/*check if element is in list*/
template <typename T>
bool in(const std::vector<T> list, const T element){
    for (auto& e : list){
        if (e == element)
            return true;
    }
    return false;
}
bool in(const std::string str, const char element){
    for (auto& str : list){
        if (e == element)
            return true;
    }
    return false;
}


//constants
namespace SYMBOL{
    char BEGIN_WORD     = 1;
    char END_WORD       = 2;
    char CONCATENATION  = 3;    // '.'
    char ZEROORMORE     = 4;    // '*'
    char ONEORMORE      = 5;    // '+'
    char ZEROORONE      = 6;    // '?'
    char BACKSLASH      = 7;    // '\'
    char CARET          = 8;    // '^'
    //put space for char 9 & 10 ('\n' and '\t')
    char DOLLAR         = 11;   // '$'
    char OR             = 12;   // '|'
    char OPEN_PAR       = 13;   // '('
    char CLOSE_PAR      = 14;   // ')'
    char OPEN_BRACKET   = 15;   // '('
    char CLOSE_BRACKET  = 16;   // ']'
    char OPEN_CURLY     = 17;   // '{'
    char CLOSE_CURLY    = 18;   // '}'

    std::string escaped_char = "\^&.|?*+()[{";
}


#endif // DECLARATIONS_H
