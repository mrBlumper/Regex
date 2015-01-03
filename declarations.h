#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <stack>

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

template <typename T>
std::vector<T> convertToPostfix(std::vector<T> expression, T open_par, T close_par, int (*precedence)(T) ){
    std::vector<T> output;
    std::stack<T> stack;

    for (auto &c : expression){
        if (c == open_par){
            stack.push(c);
        } else if (c == close_par) {
            while (!stack.empty() && stack.top() != open_par){
                output.push_back(stack.top());
                stack.pop();
            }
            if (!stack.empty()){
                stack.pop();
            } else {
                std::cout<<"ERREUR DE PARANTHESE\n";
                return std::vector<T>();
            }
        } else {
            while (!stack.empty()){
                T last = stack.top();
                if (precedence(last) >= precedence(c)){
                    output.push_back(last);
                    stack.pop();
                } else {
                    break;
                }
            }
            stack.push(c);
        }
    }
    while (!stack.empty()){
        output.push_back(stack.top());
        stack.pop();
    }
    return output;
}


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
        }
        ReplacedExpression(std::string p, std::initializer_list<std::string> t, bool c = true){
            pattern = p;
            std::string temp = "";
            for (auto& e : t)
                temp += e;
            translate = temp;
            convert = c;
        }
        std::string pattern;
        std::string translate;
        bool convert;
    };
}


#endif // DECLARATIONS_H
