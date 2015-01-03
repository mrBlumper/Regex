#ifndef NFA_H
#define NFA_H

#include "declarations.h"

#include <tuple>
#include <fstream>
#include <cstdlib>

typedef std::tuple<unsigned int, unsigned int> Sub_Nfa;
template<typename T>
T POP(std::stack<T> &s){
    //if (s.empty()) return T();
    T temp = s.top();
    s.pop();
    return temp;
}

struct NodeLink {
    short c;
    unsigned int to;
    NodeLink(unsigned int to, short c){
        this->to = to;
        this->c = c;
    }
};

class NFA
{
    public:
        NFA();
        virtual ~NFA();

        void build(std::vector<short> postfix);
        void show();

        unsigned int start;
        unsigned int end;
        std::vector<std::vector<NodeLink>> nodes;
    protected:
        std::stack<unsigned int> _empty;
    private:
        Sub_Nfa         buildBranchZeroorone(Sub_Nfa a, short c);
        Sub_Nfa         buildBranchZeroormore(Sub_Nfa a, short c);
        Sub_Nfa         buildBranchOneormore(Sub_Nfa a, short c);
        Sub_Nfa         buildBranchOr(Sub_Nfa a, Sub_Nfa b, short c);
        Sub_Nfa         buildBranchConcat(Sub_Nfa a, Sub_Nfa b, short c);
        Sub_Nfa         buildBranchNormal(short c);
        unsigned int    getFirstEmptyNode();

};

#endif // NFA_H
