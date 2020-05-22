#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

class CFG {

protected:
    // G = (N,T,S,P)
    map<string, set<string>>P; //productions
    set<string>N; //non-terminals
    set<string>T; //terminals
    string S; //start symbol

public:
    CFG() = default;
    CFG(map<string, set<string>>P, set<string>N, set<string>T, string S) :P(P), N(N), T(T), S(S) {};
    friend void config(CFG&); //used a custom CFG for testing
    void step1();
};

