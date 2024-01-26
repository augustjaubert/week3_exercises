#include <catch2/catch_test_macros.hpp>
#include "automaton.h"
#include <vector>
#include <map>

using std::map;
using std::vector;

TEST_CASE("Check that a simple automaton accepts", "[simple accept]")
{
    vector<vector<int>> M{{0, 1}, {1, 1}};
    vector<int> S_A{0};
    map<char, int> A{{'a', 0}, {'b', 1}};
    Automaton only_As(A, M, S_A);

    REQUIRE(only_As.Read("aaaaa"));
    REQUIRE(!only_As.Read("aaaabaaa"));
}

TEST_CASE("large alphabet, matrix and accepted state vector")
{
    vector<vector<int>> M{{0, 1, 2, 3, 4}, {0, 1, 2, 3, 4}, {0, 1, 2, 3, 4}, {0, 1, 2, 3, 4}, {0, 1, 2, 3, 4}};
    vector<int> S{2, 1, 0};
    map<char, int> A{{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}};
    Automaton testing(A, M, S);
    REQUIRE(testing.Read("abcedaedbdc"));
}

TEST_CASE("multiple accepted states")
{
    vector<vector<int>> M{{0, 1, 2, 3, 4}, {0, 4, 3, 2, 1}, {0, 3, 4, 1, 2}, {0, 1, 2, 3, 4}, {0, 1, 2, 3, 4}};
    vector<int> S{2, 3, 4};
    map<char, int> A{{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}};
    Automaton testing(A, M, S);
    REQUIRE(testing.Read("abcedaedbdc"));
}

TEST_CASE("one accepted state is valid, others are not")
{
    vector<vector<int>> M{{0, 1, 2, 3, 4}, {0, 1, 2, 3, 4}, {0, 1, 2, 3, 4}, {0, 1, 2, 3, 4}, {0, 1, 2, 3, 4}};
    vector<int> S{2, 8, 5};
    map<char, int> A{{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}};
    Automaton testing(A, M, S);
    CHECK_THROWS_AS(testing.Read("abcedaedbdc"), std::invalid_argument);
}

TEST_CASE("empty string input")
{
    vector<vector<int>> M{{0, 1}, {0, 1}};
    vector<int> S{0};
    map<char, int> A{{'a', 0}, {'b', 1}};
    Automaton testing(A, M, S);
    CHECK_THROWS_AS(testing.Read(""), std::invalid_argument);
}


TEST_CASE("word character not found in other variables")
{
    vector<vector<int>> M{{0, 1}, {0, 1}};
    vector<int> S{1};
    map<char, int> A{{'a', 0}, {'b', 1}};
    Automaton testing(A, M, S);
    CHECK_THROWS_AS(testing.Read("abc"), std::invalid_argument);
}

TEST_CASE("empty accepted state vector")
{
    vector<vector<int>> M{{0, 1}, {0, 1}};
    vector<int> S{};
    map<char, int> A{{'a', 0}, {'b', 1}};
    Automaton testing(A, M, S);
    CHECK_THROWS_AS(testing.Read("ab"), std::invalid_argument);
}

TEST_CASE("no accepted state vector value found in alphabet")
{
    vector<vector<int>> M{{0, 1}, {0, 1}};
    vector<int> S{2};
    map<char, int> A{{'a', 0}, {'b', 1}};
    Automaton testing(A, M, S);
    CHECK_THROWS_AS(testing.Read("ab"), std::invalid_argument);
}




/*
-


*/