#include <iostream>

using namespace std;

#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
#include <bitset>

//#include "declarations.h"
#include "RegexFormater.h"
//\n->10
//\t->9
int main(){/*
    short c = 49;
    std::cout<<std::bitset<sizeof(short)*8>(c)<<"\n";
    c<<=8;
    std::cout<<std::bitset<sizeof(short)*8>(c)<<"\n";
    c+=52;
    unsigned char a = c&0xFF;
    unsigned char b = c>>8;
    std::cout<<std::bitset<sizeof(short)*8>(c)<<"\n";
    std::cout<<(int)a<<" "<<(int)b<<'\n';*/
/*
    short symbol = makeRange('k', 'p');
    std::cout<<(char)(symbol>>8)<<" "<<(char)(symbol&0xFF)<<"\n";
    std::cout<<symbol<<"\n";
    short symbol_2 = (short)'l';
    for (char c = 'a'; c <= 't'; c++){
        std::cout<<c<<" "<<symbolCorresponds(symbol, c)<<' '<<symbolCorresponds(symbol_2, c)<<"\n";
    }*/
    /*
    std::vector <int> test = {1, 2, 3, 4, 5, 7, 8, 9, 10};
    for (int i = 0; i <= 10; i++){
        std::cout<<i<<" "<<in<int>(test, i)<<"\n";
    }
    */
    /*RegexFormater formater("bla(bla){0,3}");
    std::string test = "bla(bla){0,3}";
    std::cout<<formater.getPreviousGroup(8)<<"\n";*/
    RegexFormater f(R"(aazeze\(az\n)\+\\\*)");
    std::cout<<f.getStr()<<"\n";
    f.escapeCharacters();
    std::cout<<f.getStr();
    /*
    std::vector<std::string> tests = {"bla(bla){0,3}", "bla(){0,3}", "(blabla){0,3}", "(bla(bla)){0,3}", "b{0,3}", "+{}", "{}"};
    for (auto& e : tests){
        int i = 0;
        RegexFormater formater(e);
        for (; i < e.size(); i++){
            if (e[i] == '{')
                break;
        }
        std::cout<<e<<" "<<formater.getPreviousGroup(i)<<"\n";
    }
*/
    return 0;
}
