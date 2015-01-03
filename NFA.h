#ifndef NFA_H
#define NFA_H

#include "declarations.h"

#include <tuple>
#include <fstream>
#include <cstdlib>

typedef std::tuple<unsigned int, unsigned int> Sub_Nfa;
/* pop  element from stack and return it */
template<typename T>
T POP(std::stack<T> &s){
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
        /* build nfa from postfix expression */
        void build(std::vector<short> postfix);
        /* debug the nfa */
        void show();
        /* find all nodes who can be access only by epsilons links */
        std::vector<unsigned int>   findEpsilons(std::vector<unsigned int>& nodes);
        /* return all move who can be done in the nfa for the element c */
        std::vector<unsigned int>   move_NFA(std::vector<unsigned int>& nodes, short c);
        /* blend of the two previous functions */
        std::vector<unsigned int>   move_DFA(std::vector<unsigned int>& nodes, short c);

        unsigned int start;
        unsigned int end;
        std::vector<std::vector<NodeLink>> nodes;
    protected:
        std::stack<unsigned int> _empty;
    private:
        /* build the sub nfa corresponding to a? */
        Sub_Nfa         buildBranchZeroorone(Sub_Nfa a);
        /* build the sub nfa corresponding to a* */
        Sub_Nfa         buildBranchZeroormore(Sub_Nfa a);
        /* build the sub nfa corresponding to a+ */
        Sub_Nfa         buildBranchOneormore(Sub_Nfa a);
        /* build the sub nfa corresponding to a|b */
        Sub_Nfa         buildBranchOr(Sub_Nfa a, Sub_Nfa b);
        /* build the sub nfa corresponding to a.b */
        Sub_Nfa         buildBranchConcat(Sub_Nfa a, Sub_Nfa b);
        /* build the sub nfa corresponding to c */
        Sub_Nfa         buildBranchNormal(short c);
        /* get the first empty node in the nfa or create a new one if all nodes aren't empty */
        unsigned int    getFirstEmptyNode();

};

#endif // NFA_H
