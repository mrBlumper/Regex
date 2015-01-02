#include "Regex.h"

int REGEX_precedence(short c){
    if (c == SYMBOL::OPEN_PAR)
        return 1;
    else if (c == SYMBOL::OR) {
        return 2;
    } else if (c == SYMBOL::CONCATENATION) {
        return 3;
    } else if (c == SYMBOL::ONEORMORE || c == SYMBOL::ZEROORMORE || c == SYMBOL::ZEROORONE){
        return 4;
    } else {
        return 6;
    }
}

Regex::Regex(std::string reg):
    _base(reg)
{
    //ctor
}

void Regex::compile(){
    this->format();
    this->toPostfix();
}

void Regex::format(){
    RegexFormater f(this->_base);
    f.convert();
    this->_formated = f.getFinalRep();
}

void Regex::toPostfix(){
    this->_postfix = convertToPostfix<short>(_formated, (short)SYMBOL::OPEN_PAR, SYMBOL::CLOSE_PAR, REGEX_precedence);

    std::map<char, char> reversed;
    for (auto it = SYMBOL::special_chars.begin(); it != SYMBOL::special_chars.end(); ++it){
        reversed[it->second] = it->first;
    }
    for (auto &c : this->_postfix){
        if (isRange(c)){
            std::cout<<"[ RANGE : "<<(char)(c&0xff)<<" "<<(char)(c>>8)<<" ]\n";
        } else {
            if (SYMBOL::isOp((char)c)){
                std::cout<<"[ OPERATOR : "<<reversed[(char)c]<<" ]\n";
            } else {
                std::cout<<"[ "<<(char)c<<" ]\n";
            }
        }
    }
}

Regex::~Regex()
{
    //dtor
}
