#include <iostream>

using namespace std;

#include "Regex.h"

/* a simple implementation of Regex
Supports: -    + * ? | operators
          - [] & () & [^] groups
          - repetitions
          - '.', \\d, \\D, \\w, \\W, \\s, \\S & [:...:] patterns
          - repetitions {a}, {a,}, {a, b}
          - $ & ^ operators
Use of Fhompson algorithm -> NO BACKREFERENCE!
*/

/* to use:
create a regex by creating a regex instance
use 'find' or 'match' functions to match a string
*/

int main(){
    Regex regex("aaa");
    std::string to_match = "aaa";
    if (regex.match(to_match))
        std::cout<<"find "<<"\n";
    else
        std::cout<<"not find\n";
    return 0;
}
