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

bool Regex::match(std::string m){
    return this->find(m) == m.size();
}


int Regex::find(std::string m, bool change){
    if (!this->_compiled) {
        this->compile();
    }
    if (change) {
        if (this->_start_symbol){
            m.insert(0, toStr(SYMBOL::BEGIN_WORD));
        } else if (this->_end_symbol){
            m += SYMBOL::END_WORD;
        }
    }
    unsigned int state = 0;
    int end = -1;
    for (int i = 0; i < m.size(); i++){
        char c = m[i];
        if (_dfa.links[state].out.find(c) == _dfa.links[state].out.end()){
            break;
        }
        if (_dfa.links[_dfa.links[state].out[c]].isEnd()){
            end = i + 1;
        }
        state = _dfa.links[state].out[c];
    }
    if (change)
        end -= (this->_end_symbol + this->_start_symbol);
    return end;
}

Regex::Regex(std::string reg):
    _base(reg), _end_symbol(false), _start_symbol(false), _compiled (false)
{
    //ctor
}

void Regex::compile(){
    this->_compiled = true;
    this->format();
    this->toPostfix();
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
    this->_postfix = convertToPostfix<short>(_formated, (short)SYMBOL::OPEN_PAR, SYMBOL::CLOSE_PAR, REGEX_precedence);
}

Regex::~Regex()
{
    //dtor
}
