#include "automaton.h"
#include <stdexcept>

Automaton::Automaton(map<char, int> A, vector<vector<int>> M, vector<int> S) : alphabet(A), transition_matrix(M), accepting_states(S) {}

bool Automaton::Read(string word)
{

    if (accepting_states.size() < 1)
    {
        throw std::invalid_argument("No accepted states input");
    }

    if (word.size() < 1)
    {
        throw std::invalid_argument("No string input");
    }

    vector<int> alphabetValues;
    for (map<char, int>::iterator i = alphabet.begin(); i != alphabet.end(); ++i)
    {
        alphabetValues.push_back(i->second);
    }
    for (auto &i : accepting_states)
    {
        vector<int>::iterator it = std::find(alphabetValues.begin(), alphabetValues.end(), i);
        if (it == alphabetValues.end())
        {
            std::string errorMessage = "One (or more) accepted state value(s) not found in alphabet";
            throw std::invalid_argument(errorMessage);
        }
    }

    for (auto &c : word)
    {
        // a map's find method returns an iterator to the key-value pair for the given key
        // iterators have syntax similar to pointers:
        // (*it) gives the key-value pair
        // -> can be used to access methods of the key value pair
        auto it = alphabet.find(c);
        if (it == alphabet.end())
        {
            std::string errorMessage = "Character in input word not found in alphabet";
            throw std::invalid_argument(errorMessage);
        }

        // it->first gives the key, it->second gives the value
        int j = it->second;
        state = transition_matrix[state][j];
    }

    return std::find(accepting_states.begin(), accepting_states.end(), state) != accepting_states.end();
}
