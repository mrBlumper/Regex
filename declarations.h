#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <vector>
#include <string>
#include <iostream>
#include <map>

class RegexFormater;

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
    struct ReplacedExpression;

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


    struct ReplacedExpression{
        ReplacedExpression(std::string p, std::string t, bool c = true){
            pattern = p;
            translate = t;
            convert = c;

            if (!convert)
                return;
            /*RegexFormater f1(pattern);
            f1.treatSpecialCharacters();
            pattern = f1.getStr();
            RegexFormater f2(translate);
            f2.treatSpecialCharacters();
            translate = f2.getStr();*/
                /*
            pattern = "";
            translate = "";
            for (auto& c : p){
                if (special_chars.find(c) != special_chars.end()){
                    pattern += special_chars[c];
                }else
                    pattern += c;
            }
            for (auto& c : t){
                if (special_chars.find(c) != special_chars.end())
                    translate += special_chars[c];
                else
                    translate += c;
            }*/
        }
        ReplacedExpression(std::string p, std::initializer_list<std::string> t, bool c = true){
            pattern = p;
            translate = "";
            std::string temp = "";
            for (auto& e : t)
                temp += e;
            //    std::cout<<p<<" "<<temp<<"\n";
            translate = temp;
            //ReplacedExpression(p, temp, c);
            convert = c;
        }
        std::string pattern;
        std::string translate;
        bool convert;
    };
}


#endif // DECLARATIONS_H
