#include "DFA.h"


bool operator==(const DFALink& lhs, const DFALink& rhs){
    if (lhs.ids.size() != rhs.ids.size() || lhs._sum != rhs._sum)
        return false;
    for (unsigned int i = 0; i < lhs.ids.size(); ++i)
        if (lhs.ids[i] != rhs.ids[i])
            return false;
    return true;
}

std::vector<unsigned int>   findEpsilons(std::vector<unsigned int> &nodes, NFA &nfa){
    std::vector<unsigned int> results;
    std::stack<unsigned int> stack;
    std::map<unsigned int, bool> cache;
    for (auto& n : nodes){
        results.push_back(n);
        stack.push(n);
        cache[n] = true;
    }
    while (!stack.empty()){
        unsigned int current = POP(stack);
        cache [current] = true;

        for (auto& n : nfa.nodes[current]){
            if (!n.c && cache.find(n.to) == cache.end()){
                stack.push(n.to);
                results.push_back(n.to);
            }
        }
    }
    return results;
}


std::vector<unsigned int>   move_NFA(std::vector<unsigned int> &nodes, short symbol, NFA &nfa){
    std::vector<unsigned int> results;
    for (auto& n : nodes){
        for (auto& link : nfa.nodes[n]){
            if (symbolCorresponds(link.c, symbol)){
                results.push_back(link.to);
            }
        }
    }
    return results;
}


std::vector<unsigned int>   move_DFA(std::vector<unsigned int> &nodes, short symbol, NFA &nfa){
    std::vector<unsigned int> temp = move_NFA(nodes, symbol, nfa);
    return findEpsilons(temp, nfa);
}

DFALink::DFALink(std::vector<unsigned int> ids, unsigned int end){
    this->_end = false;
    this->_sum = 0;
    for (auto& n : ids){
        this->_sum += n;
        if (n == end)
            this->_end = true;
    }
    this->ids = ids;
    std::sort(this->ids.begin(), this->ids.end());/*
    if (this->_sum){
            std::cout<<end<<"\n";
            for (auto & e : ids)
                std::cout<<e<<" ";
            std::cout<<"\n";
            std::cout<<this->_end<<"\n";
    }//*/
}



DFA::DFA()
{
    //ctor
}

void DFA::show(){
    std::cout<<"creating file dfa\n";
    std::ofstream file;
    file.open ("dfa.gv");
    file << "digraph{\n";

    for (int i = 0; i < this->links.size(); ++i){

        file<<"    "<<i<<" [label="<<i<<" shape="<<((this->links[i].isEnd())?"doublecircle":"circle")<<"]\n";
        for (auto it = this->links[i].out.begin(); it != this->links[i].out.end(); ++it){
            short c = it->first;
            std::string label = "";
            if (isRange(c)){
                label += (char)(c%0xff);
                label += '-';
                label += (char)(c>>8);
            } else if (!c){
                label =  "\"&#949;\"";
            } else {
                label = (char)c;
            }
            file<<"        "<<i<<" -> "<<it->second<<" [label="<<label<<"]\n";
        }
    }
    file<<"}\n";

    file.close();
    system("dot -Tpng -odfa.png dfa.gv");
    system("dfa.png");
}

void DFA::build(NFA &nfa){
    std::cout<<"creating dfa\n";
    std::vector<unsigned int> first_node = {nfa.start};
    this->links.push_back(DFALink(findEpsilons(first_node, nfa), nfa.end));
    std::stack<unsigned int> stack;
    stack.push(0);

    while (!stack.empty()){
        unsigned int current = POP(stack);
        for (char c = 1; c < 127; c++){
            std::vector<unsigned int> temp_ids = move_DFA(this->links[current].ids, c, nfa);
            DFALink temp(temp_ids, nfa.end);
            if (!temp_ids.size()){
                continue;
            }
            int pos = this->find(temp);
            if (pos < 0){
                std::cout<<"not found\n";
                this->links.push_back(temp);
                stack.push(this->links.size() - 1);
                pos = stack.top();
            }
            this->links[current].addLink(pos, c);
        }
    }
}

int DFA::find(DFALink &current){
    for (int i = 0; i < this->links.size(); ++i){
        if (this->links[i] == current){
            return i;
        }
    }
    return -1;
}

DFA::~DFA()
{
    //dtor
}
