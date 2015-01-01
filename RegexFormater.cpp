#include "RegexFormater.h"

RegexFormater::RegexFormater(std::string regex):
    _current(regex)
{
    //ctor
}



void  RegexFormater::createDuplicatas(){
    std::string temp = "";
    int i = 0;
    while (i < this->_current.size()){
        if (this->_current[i] == SYMBOL::OPEN_CURLY){
            RegexRepetition repetition = this->treatRepetition(i);

            if (repetition.size == 0 || (repetition.min >= repetition.max && repetition.min && repetition.max)){
                    std::cout<<"bad\n";
                temp += this->_current[i];
                i++;
            } else {
                std::cout<<repetition.size<<" "<<repetition.min<<" "<<repetition.max<<"\n";
                std::cout<<"previous group is: "<<this->getPreviousGroup(i)<<"\n";
                std::string previous = this->getPreviousGroup(i);
                for (int r = 1; r < repetition.min; r++){
                    temp += previous;
                }
                if (repetition.interval){
                    if (repetition.max == 0){
                        temp += SYMBOL::ZEROORMORE;
                    } else {
                        for (int r = 0; r < repetition.max - repetition.min; r++){
                            temp += previous;
                            temp += SYMBOL::ZEROORONE;
                        }
                    }
                }
                i+=repetition.size+1;
            }
        } else {
            temp += this->_current[i];
            i++;
        }
    }
    this->_current = temp;
}

RegexRepetition RegexFormater::treatRepetition(int index){
    RegexRepetition repetition;
    std::string sub = "";
    for (int i = index + 1; i < this->_current.size(); ++i){
        sub += this->_current[i];
        if (this->_current[i] == SYMBOL::CLOSE_CURLY){
            repetition.size = sub.size();
            sub.pop_back();
            int nbr[] = {0, 0};
            int id_working = 0;
            for (auto& c : sub){
                if (c == ' ' || c == '\t')
                    continue;
                if (c == ','){
                    id_working = 1;
                    if (repetition.interval){
                        repetition.size = 0;
                        break;
                    }
                    repetition.interval = true;
                } else if (c >= '0' && c <= '9') {
                    nbr[id_working] *= 10;
                    nbr[id_working] += (c - '0');
                    //std::cout<<c<<" "<<(c - '0')<<" "<<nbr[id_working]<<"\n";
                } else {
                    repetition.size = 0;
                    break;
                }
            }
            repetition.min = nbr[0];
            repetition.max = nbr[1];
            break;
        }
    }
    return repetition;
}

int RegexFormater::findBestReplace(int index){
    int temp = -1;
    int len = 1;
    for (int i = 0; i < SYMBOL::replace_expressions.size(); ++i){
        std::string pattern = SYMBOL::replace_expressions[i].pattern;
        std::string sub = this->_current.substr(index, pattern.size());
        if (sub == pattern && len <= sub.size()){
            temp = i;
            len = sub.size();
        }
    }
    return temp;
}

void RegexFormater::replaceGroups(){
    std::string temp = "";
    int i = 0;
    while (i < this->_current.size()){
        int match = this->findBestReplace(i);
        if (match >= 0){
            temp += SYMBOL::replace_expressions[match].translate;
            i += SYMBOL::replace_expressions[match].pattern.size();

        } else {
            temp += this->_current[i];
            ++i;
        }
    }
    this->_current = temp;
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

    if (in(SYMBOL::operators, this->_current[pos - 1])){
        return "";
    } else if (this->_current[pos - 1] == SYMBOL::CLOSE_PAR){
        int nb = 0;
        for (int i = pos - 1; i >= 0; --i){
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
