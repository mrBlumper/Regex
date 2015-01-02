#include "NFA.h"

NFA::NFA()
{
    //ctor
}

unsigned int NFA::getFirstEmptyNode(){
    unsigned int i = 0;
    if (this->_empty.empty()){
        this->nodes.push_back(std::vector<NFALink>());

        i = this->nodes.size() - 1;
    } else {
        i = POP<unsigned int>(this->_empty);
    }
    std::cout<<i<<"\n";
    return i;
}

void NFA::build(std::vector<short> postfix){
    this->start = 0;
    this->getFirstEmptyNode();

    std::stack<Sub_Nfa> stack;
    for (auto& c : postfix){
           std::cout<<"--- "<<c<<"\n";
        if (c == SYMBOL::ZEROORONE){
            stack.push(buildBranchZeroorone(POP<Sub_Nfa>(stack), c));
        } else if (c == SYMBOL::ZEROORMORE) {
            stack.push(buildBranchZeroormore(POP<Sub_Nfa>(stack), c));
        } else if (c == SYMBOL::ONEORMORE) {
            stack.push(buildBranchOneormore(POP<Sub_Nfa>(stack), c));
        } else if (c == SYMBOL::CONCATENATION) {
            stack.push(buildBranchConcat(POP<Sub_Nfa>(stack), POP<Sub_Nfa>(stack), c));
        } else if (c == SYMBOL::OR) {
            stack.push(buildBranchOr(POP<Sub_Nfa>(stack), POP<Sub_Nfa>(stack), c));
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

Sub_Nfa NFA::buildBranchZeroorone(Sub_Nfa a, short c){
    unsigned int s = std::get<0>(a);
    unsigned int e = std::get<1>(a);
    this->nodes[s].push_back(NFALink(e, 0));
    return Sub_Nfa(s, e);
}

Sub_Nfa NFA::buildBranchZeroormore(Sub_Nfa a, short c){
    Sub_Nfa temp = this->buildBranchOneormore(a, c);
    this->nodes[std::get<0>(temp)].push_back(NFALink(std::get<1>(temp), 0));
    return temp;/*
    unsigned int t_s = a.get(0), t_e = a.get(1);
    unsigned int s, e = this->getFirstEmptyNode(), this->getFirstEmptyNode();
    this->nodes[t_e].append(NFALink(t_s, 0));
    this->nodes[s].append(NFALink(t_s, 0));
    this->nodes[t_e].append(NFALink(e, 0));
    this->nodes[s].append(NFALink(e, 0));
    return Sub_Nfa(s, e);*/
}

Sub_Nfa NFA::buildBranchOneormore(Sub_Nfa a, short c){
    unsigned int t_s = std::get<0>(a), t_e = std::get<1>(a);
    unsigned int s = this->getFirstEmptyNode(), e = this->getFirstEmptyNode();
    this->nodes[t_e].push_back(NFALink(t_s, 0));
    this->nodes[s].push_back(NFALink(t_s, 0));
    this->nodes[t_e].push_back(NFALink(e, 0));
    return Sub_Nfa(s, e);
}

Sub_Nfa NFA::buildBranchOr(Sub_Nfa a, Sub_Nfa b, short c){
    unsigned int n1_s = std::get<0>(a), n1_e = std::get<1>(a);
    unsigned int n2_s = std::get<0>(b), n2_e = std::get<1>(b);
    unsigned int s = this->getFirstEmptyNode(), e = this->getFirstEmptyNode();
    this->nodes[s].push_back(NFALink(n1_s, 0));
    this->nodes[s].push_back(NFALink(n2_s, 0));
    this->nodes[n1_e].push_back(NFALink(e, 0));
    this->nodes[n2_e].push_back(NFALink(e, 0));
    return Sub_Nfa(s, e);
}
Sub_Nfa NFA::buildBranchConcat(Sub_Nfa a, Sub_Nfa b, short c){
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
    this->nodes[s].push_back(NFALink(e, c));
    return Sub_Nfa(s, e);
}

NFA::~NFA()
{
    //dtor
}
