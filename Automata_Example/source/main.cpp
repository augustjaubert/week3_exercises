#include "automaton.h"
#include <vector>
#include <map>
#include <iostream>


using std::vector;
using std::map;
using std::string;

int main()
{
    vector<vector<int>> M{{0, 1}, {0, 1}};
    map<char, int> A{{'a', 0}, {'b', 1}}; 
    vector<int> S{1};
    Automaton ends_with_b(A, M, S);
    std::cout << "Read abab = " << ends_with_b.Read("acab") << std::endl;
    std::cout << "Read aaba = " << ends_with_b.Read("aaba") << std::endl;



    return 0;
}

/*
Notes:
- spaces in string input -> ignore spaces
- accepting state not matching with matrix or map -> warning
- string character is not found in map -> warning
- S size < 1
*/