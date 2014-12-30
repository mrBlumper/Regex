#include <iostream>

using namespace std;

#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
#include <bitset>

#include "declarations.h"
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
    std::vector <int> test = {1, 2, 3, 4, 5, 7, 8, 9, 10};
    for (int i = 0; i <= 10; i++){
        std::cout<<i<<" "<<in<int>(test, i)<<"\n";
    }

    return 0;
}
