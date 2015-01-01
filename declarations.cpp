#include "declarations.h"


std::string toStr(char c){
    std::string temp = "";
    temp += c;
    return temp;
}
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
bool in(const std::string str, const char element){
    for (auto& e : str){
        if (e == element)
            return true;
    }
    return false;
}



namespace SYMBOL{

    bool isOp(char c){
        return !(c == 9 || c == 10 || c > 20);
    }
    char BEGIN_WORD     = 1;
    char END_WORD       = 2;
    char CONCATENATION  = 3;    // '.'
    char ZEROORMORE     = 4;    // '*'
    char ONEORMORE      = 5;    // '+'
    char ZEROORONE      = 6;    // '?'
    char BACKSLASH      = 7;    // '\'
    char CARET          = 8;    // '^'
    //put space for char 9 & 10 & 11 ('\n' and '\t' and vertical tab)
    char DOLLAR         = 19;   // '$'
    char OR             = 12;   // '|'
    char OPEN_PAR       = 13;   // '('
    char CLOSE_PAR      = 14;   // ')'
    char OPEN_BRACKET   = 15;   // '('
    char CLOSE_BRACKET  = 16;   // ']'
    char OPEN_CURLY     = 17;   // '{'
    char CLOSE_CURLY    = 18;   // '}'
    char INTERVAL       = 20;   // '}'
    //*/
/*
    char CONCATENATION='.';
    char ZEROORMORE='*';
    char ONEORMORE='+';
    char ZEROORONE='?';
    char OR='|';
    char OPEN_PAR='(';
    char CLOSE_PAR=')';
//*/
    std::string escaped_char = R"(\^$.|?*+()[]{})"; //raw string litteral
    std::vector<char> operators = {CONCATENATION, ZEROORMORE, ONEORMORE, ZEROORMORE, OR};
    std::map<char, char> special_chars = {{'(', OPEN_PAR}, {')', CLOSE_PAR}, {'[', OPEN_BRACKET}, {']', CLOSE_BRACKET}, {'{', OPEN_CURLY}, {'}', CLOSE_CURLY},
                                          {'*', ZEROORMORE}, {'+', ONEORMORE}, {'?', ZEROORONE}, {'$', DOLLAR}, {'^', CARET}, {'|', OR}};
    std::vector<ReplacedExpression> replace_expressions = {ReplacedExpression(".", {"[\t",toStr((char)21),"-",toStr((char)127),"]"}),
                                                           ReplacedExpression("$", ""+END_WORD),
                                                           ReplacedExpression("^", {BEGIN_WORD}),
                                                           ReplacedExpression("\\d", "[0-9]"),
                                                           ReplacedExpression("\\D", "[^0-9]"),
                                                           ReplacedExpression("\\w", "[_A-Za-z0-9]"),
                                                           ReplacedExpression("\\W", "[^_A-Za-z0-9]"),
                                                           ReplacedExpression("\\s", {"[\n\t\r ",toStr((char)12),toStr((char)11),"]"}),
                                                           ReplacedExpression("\\S", {"[^\n\t\r ",toStr((char)12),toStr((char)11),"]"}),
                                                           ReplacedExpression("[:alnum:]", "[a-zA-Z0-9]"),
                                                           ReplacedExpression("[:alpha:]", "[a-zA-Z]"),
                                                           ReplacedExpression("[:blank:]", "[\t ]"),
                                                           ReplacedExpression("[:digits:]", "[0-9]"),
                                                           ReplacedExpression("[:graph:]", {"[!-",toStr((char)127),"]"}),
                                                           ReplacedExpression("[:lower:]", "[a-z]"),
                                                           ReplacedExpression("[:print:]", {"[ -",toStr((char)127),"]"}),
                                                           ReplacedExpression("[:punct:]", "[<>,\\?;.:/!§\\*µù%\\$£¤¨=\\+\\}\\)\\]°@\\^_`\\|-\\[\\(\\{'\"#~\\\\&]"),
                                                           ReplacedExpression("[:space:]", {"[ \r\t",toStr((char)12),toStr((char)11),"]"}),
                                                           ReplacedExpression("[:upper:]", "[A-Z]"),
                                                           ReplacedExpression("[:xdigit:]", "[0-9a-fA-F]")};
}
