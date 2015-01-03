#include "NFA.h"

NFA::NFA()
{
    //ctor
}

unsigned int NFA::getFirstEmptyNode(){
    unsigned int i = 0;
    if (this->_empty.empty()){
        this->nodes.push_back(std::vector<NodeLink>());
        i = this->nodes.size() - 1;
    } else {
        i = POP<unsigned int>(this->_empty);
    }
    return i;
}

void NFA::build(std::vector<short> postfix){
    this->start = 0;
    this->getFirstEmptyNode();
    std::stack<Sub_Nfa> stack;
    for (auto& c : postfix){
        if (c == SYMBOL::ZEROORONE){
            stack.push(buildBranchZeroorone(POP<Sub_Nfa>(stack)));
        } else if (c == SYMBOL::ZEROORMORE) {
            stack.push(buildBranchZeroormore(POP<Sub_Nfa>(stack)));
        } else if (c == SYMBOL::ONEORMORE) {
            stack.push(buildBranchOneormore(POP<Sub_Nfa>(stack)));
        } else if (c == SYMBOL::CONCATENATION) {
            stack.push(buildBranchConcat(POP<Sub_Nfa>(stack), POP<Sub_Nfa>(stack)));
        } else if (c == SYMBOL::OR) {
            stack.push(buildBranchOr(POP<Sub_Nfa>(stack), POP<Sub_Nfa>(stack)));
        } else {
            stack.push(buildBranchNormal(c));
        }
    }
    if (stack.empty()){
        std::cout<<"PROBLEM WITH THE REGEX\n";
        return;
    }
    while (!stack.empty()){
        this->start = std::get<0>(stack.top());
        this->end = std::get<1>(stack.top());
        stack.pop();
    }
}

void NFA::show(){
    std::cout<<"creating file\n";
    std::ofstream file;
    file.open ("nfa.gv");
    file << "digraph{\n";
    for (int i = 0; i < this->nodes.size(); ++i){
        if (this->nodes[i].size() == 0 && i != this->end)
            continue;
        file<<"    "<<i<<" [label="<<i<<" shape="<<((i == this->end)?"doublecircle":"circle")<<"]\n";
        for (int j = 0; j < this->nodes[i].size(); ++j){
            short c = this->nodes[i][j].c;
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
            file<<"        "<<i<<" -> "<<this->nodes[i][j].to<<" [label="<<label<<"]\n";
        }
    }
    file<<"}\n";
    file.close();
    system("dot -Tpng -onfa.png nfa.gv");
    system("nfa.png");
}

Sub_Nfa NFA::buildBranchZeroorone(Sub_Nfa a){
    unsigned int s = std::get<0>(a);
    unsigned int e = std::get<1>(a);
    this->nodes[s].push_back(NodeLink(e, 0));
    return Sub_Nfa(s, e);
}

Sub_Nfa NFA::buildBranchZeroormore(Sub_Nfa a){
    Sub_Nfa temp = this->buildBranchOneormore(a);
    this->nodes[std::get<0>(temp)].push_back(NodeLink(std::get<1>(temp), 0));
    return temp;
}

Sub_Nfa NFA::buildBranchOneormore(Sub_Nfa a){
    unsigned int t_s = std::get<0>(a), t_e = std::get<1>(a);
    unsigned int s = this->getFirstEmptyNode(), e = this->getFirstEmptyNode();
    this->nodes[t_e].push_back(NodeLink(t_s, 0));
    this->nodes[s].push_back(NodeLink(t_s, 0));
    this->nodes[t_e].push_back(NodeLink(e, 0));
    return Sub_Nfa(s, e);
}

Sub_Nfa NFA::buildBranchOr(Sub_Nfa a, Sub_Nfa b){
    unsigned int n1_s = std::get<0>(a), n1_e = std::get<1>(a);
    unsigned int n2_s = std::get<0>(b), n2_e = std::get<1>(b);
    unsigned int s = this->getFirstEmptyNode(), e = this->getFirstEmptyNode();
    this->nodes[s].push_back(NodeLink(n1_s, 0));
    this->nodes[s].push_back(NodeLink(n2_s, 0));
    this->nodes[n1_e].push_back(NodeLink(e, 0));
    this->nodes[n2_e].push_back(NodeLink(e, 0));
    return Sub_Nfa(s, e);
}
Sub_Nfa NFA::buildBranchConcat(Sub_Nfa a, Sub_Nfa b){
    unsigned int n2_s = std::get<0>(a), n2_e = std::get<1>(a);
    unsigned int n1_s = std::get<0>(b), n1_e = std::get<1>(b);
    for (auto& o : this->nodes[n1_s]){
        this->nodes[n2_e].push_back(o);
    }
    this->nodes[n1_s].clear();
    this->_empty.push(n1_s);
    return Sub_Nfa(n2_s, n1_e);
}

Sub_Nfa NFA::buildBranchNormal(short c){
    unsigned int s = this->getFirstEmptyNode(), e = this->getFirstEmptyNode();
    this->nodes[s].push_back(NodeLink(e, c));
    return Sub_Nfa(s, e);
}


std::vector<unsigned int>   NFA::findEpsilons(std::vector<unsigned int> &nodes){
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
        for (auto& n : this->nodes[current]){
            if (!n.c && cache.find(n.to) == cache.end()){
                stack.push(n.to);
                results.push_back(n.to);
            }
        }
    }
    return results;
}


std::vector<unsigned int>   NFA::move_NFA(std::vector<unsigned int> &nodes, short symbol){
    std::vector<unsigned int> results;
    for (auto& n : nodes){
        for (auto& link : this->nodes[n]){
            if (symbolCorresponds(link.c, symbol)){
                results.push_back(link.to);
            }
        }
    }
    return results;
}


std::vector<unsigned int>   NFA::move_DFA(std::vector<unsigned int> &nodes, short symbol){
    std::vector<unsigned int> temp = move_NFA(nodes, symbol);
    return findEpsilons(temp);
}

NFA::~NFA()
{
    //dtor
}
