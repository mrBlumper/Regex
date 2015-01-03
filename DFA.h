#ifndef DFA_H
#define DFA_H

#include "declarations.h"

#include <tuple>
#include <fstream>
#include <cstdlib>
#include "NFA.h"
#include <algorithm>

std::vector<unsigned int>   findEpsilons(std::vector<unsigned int>&, NFA &);
std::vector<unsigned int>   move_NFA(std::vector<unsigned int>&, short, NFA &);
std::vector<unsigned int>   move_DFA(std::vector<unsigned int>&, short, NFA &);




class DFALink {
public:
    DFALink(std::vector<unsigned int> ids, unsigned int end);
    bool isEnd(){return this->_end;}
    void addLink(unsigned int to, short c){out[c] = to;}
    std::map<char, unsigned int> out;
    std::vector<unsigned int> ids;
    friend bool operator==(const DFALink& lhs, const DFALink& rhs);
private:
    unsigned int _sum;
    bool _end;
};
bool operator==(const DFALink& lhs, const DFALink& rhs);


class DFA
{
    public:
        DFA();
        void show();
        void build(NFA &nfa);
        std::vector<DFALink> links;
        virtual ~DFA();
    protected:
        int find(DFALink &current);
    private:
};

#endif // DFA_H
