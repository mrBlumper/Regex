#include "DFA.h"


bool operator==(const DFALink& lhs, const DFALink& rhs){
    if (lhs.ids.size() != rhs.ids.size() || lhs._sum != rhs._sum)
        return false;
    for (unsigned int i = 0; i < lhs.ids.size(); ++i)
        if (lhs.ids[i] != rhs.ids[i])
            return false;
    return true;
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
    std::sort(this->ids.begin(), this->ids.end());
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
                label += "\"";
                label += (char)(c%0xff);
                label += '-';
                label += (char)(c>>8);
                label += "\"";
            } else if (!c){
                label =  "\"&#949;\"";
            } else {
                label = "\"";
                label += (char)c;
                label += "\"";
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
    std::vector<unsigned int> first_node = {nfa.start};
    this->links.push_back(DFALink(nfa.findEpsilons(first_node), nfa.end));
    std::stack<unsigned int> stack;
    stack.push(0);
    while (!stack.empty()){
        unsigned int current = POP(stack);
        for (char c = 1; c < 127; c++){
            std::vector<unsigned int> temp_ids = nfa.move_DFA(this->links[current].ids, c);
            DFALink temp(temp_ids, nfa.end);
            if (!temp_ids.size()){
                continue;
            }
            int pos = this->find(temp);
            if (pos < 0){
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
