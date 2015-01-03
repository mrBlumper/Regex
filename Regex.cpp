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

int Regex::match(std::string m){
    unsigned int state = 0;
    int end = -1;
    for (int i = 0; i < m.size(); i++){
        char c = m[i];
    std::cout<<state<<" "<<c<<"\n";
        if (_dfa.links[state].out.find(c) == _dfa.links[state].out.end()){
                std::cout<<"quit\n";
            break;
        }
        if (_dfa.links[_dfa.links[state].out[c]].isEnd()){
                std::cout<<"end\n";
            end = i + 1;
        }
        state = _dfa.links[state].out[c];
    }
    return end;
}

Regex::Regex(std::string reg):
    _base(reg)
{
    //ctor
}

void Regex::compile(){
    this->format();
    std::map<char, char> reversed;
    for (auto it = SYMBOL::special_chars.begin(); it != SYMBOL::special_chars.end(); ++it){
        reversed[it->second] = it->first;
    }
    for (auto &c : this->_formated){
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
    this->toPostfix();
    std::cout<<"postfix\n";
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
    _nfa.build(this->_postfix);
    //_nfa.show();
    _dfa.build(_nfa);
    //_dfa.show();
}

void Regex::format(){
    RegexFormater f(this->_base);
    f.convert();
    this->_formated = f.getFinalRep();
}

void Regex::toPostfix(){
    this->_postfix = convertToPostfix<short>(_formated, (short)SYMBOL::OPEN_PAR, SYMBOL::CLOSE_PAR, REGEX_precedence);/*

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
    }*/
}

Regex::~Regex()
{
    //dtor
}
