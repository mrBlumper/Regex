#ifndef DFA_H
#define DFA_H

#include "declarations.h"

#include <tuple>
#include <fstream>
#include <cstdlib>
#include "NFA.h"
#include <algorithm>


class DFALink {
    public:
        DFALink(std::vector<unsigned int> ids, unsigned int end);
        /* return if this node is a end of the dfa */
        bool isEnd(){return this->_end;}
        /* add an edge to an other node */
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
        /* debug the dfa */
        void show();
        /* convert a nfa to a dfa */
        void build(NFA &nfa);
        std::vector<DFALink> links;
        virtual ~DFA();
    protected:
        int find(DFALink &current);
    private:
};

#endif // DFA_H
