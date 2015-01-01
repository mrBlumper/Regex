#include "RegexFormater.h"

RegexFormater::RegexFormater(std::string regex):
    _current(regex)
{
    //ctor
}

void RegexFormater::debug(){
    std::string out = "";
    std::map<char, char> reversed;
    for (auto it = SYMBOL::special_chars.begin(); it != SYMBOL::special_chars.end(); ++it){
        reversed[it->second] = it->first;
    }
    for(auto& c : this->_current){
        if (reversed.find(c) != reversed.end()){
            out = out+"#"+reversed[c]+"#";
        } else {
            out += c;
        }
    }
    std::cout<<out<<"\n";
}

void RegexFormater::treatSpecialCharacters(){
    std::string temp = "";
    for (int i = 0; i < this->_current.size(); i++){
        char c = this->_current[i];
        if (c == '\\'){
            if (i == this->_current.size() - 1)
                break;
            if (in(SYMBOL::escaped_char, this->_current[i+1])){
                temp += this->_current[++i];
                continue;
            }
        } else if (SYMBOL::special_chars.find(c) != SYMBOL::special_chars.end()){
            temp += SYMBOL::special_chars[c];
        } else {
            temp += c;
        }
    }
    this->_current = temp;
}


std::string RegexFormater::getPreviousGroup(const unsigned int pos){
    if (pos == 0 || pos >= this->_current.size()){
        return "";
    }
    std::string output = "";
    std::cout<<pos<<"\n";

    if (in(SYMBOL::operators, this->_current[pos - 1])){
        return "";
    } else if (this->_current[pos - 1] == SYMBOL::CLOSE_PAR){
        int nb = 0;
        for (int i = pos - 1; i >= 0; --i){
                std::cout<<i<<"\n";
            nb += (this->_current[i] == SYMBOL::CLOSE_PAR);
            nb -= (this->_current[i] == SYMBOL::OPEN_PAR);
            std::string temp;
            temp = this->_current[i];
            output.insert(0, temp);
            //output.insert(0, std::string(this->_current[i]));
            if (nb == 0){
                break;
            }
        }
        return output;
    } else {
        output = this->_current[pos - 1];
        return output;
    }
    return output;
}

RegexFormater::~RegexFormater()
{
    //dtor
}
