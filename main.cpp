#include <iostream>

using namespace std;

#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <queue>

class Regex{
public:
    Regex(){
        //_precedence['('] = 1;
        _precedence['|'] = 2;
        _precedence['.'] = 0;
        /*_precedence['?'] = 4;
        _precedence['*'] = 4;
        _precedence['+'] = 4;*/
    }
    std::string toPostFix(std::string regex){
        std::string output = "";
        std::queue<char> stack;
        regex = this->format(regex);

        std::cout<<regex<<"\n";
        for (unsigned int i = 0; i < regex.size(); i++){
            char c = regex[i];
            if (c == '('){
                stack.push(c);
            } else if (c == ')'){
                while (!stack.empty() && stack.front() != '('){
                    output += stack.front();
                    stack.pop();
                }
                if (!stack.empty())
                    stack.pop();
            } else {
                while (!stack.empty()){
                    char front = stack.front();
                    if (front == '('){stack.pop(); continue;}
                    //std::cout<<front<<"\n";
                    char precedence_front = this->get_precedence(front);
                    char precedence_current = this->get_precedence(c);
                    //std::cout<<c<<" "<<(int)precedence_current<<" "<<front<<" "<<(int)precedence_front<<"\n";
                    if (precedence_front >= precedence_current){
                        output += front;
                        stack.pop();
                    } else {
                        break;
                    }
                }
                stack.push(c);
            }
        }
        while (!stack.empty()){
            if (stack.front() == '(') continue;
            output += stack.front();
            //std::cout<<stack.front()<<" ";
            stack.pop();
        }
        //std::cout<<"\n";
        return output;
    }
    std::string format(std::string regex){
        std::string output = "";
        for (unsigned int i = 0; i < regex.size(); i++){
            char c = regex[i];
            if (i + 1 < regex.size()){
                char n = regex[i + 1];
                output += c;
                if (c != '(' && n != ')' && c != '|' && n != '|' && n != '.' && n != '?' && n != '*' && n != '+'){
                    output += '.';
                }
            }
        }
        output += regex[regex.size() - 1];
        return output;
    }
private:
    char get_precedence(char c) {
        if (_precedence.find(c) == _precedence.end()){
            return 6;
        }
        return _precedence[c];
    }
    std::map<char, char> _precedence;

};


int main(){
    //cout << "Hello world!" << endl;
    char *re = "hello";
    std::cout<<re<<"\n";
    for(; *re; re++){
            std::cout<<*re<<"\n";
    }
    std::string reg = "a(bc|d)+a?b*c";
    Regex regex;
    std::cout<<regex.toPostFix(reg)<<"\n";

    return 0;
}
