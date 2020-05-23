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
    void printGrammar();

    //METHODS FOR TESTING

    friend void config1(CFG&); //used a custom CFG for testing
    friend void config2(CFG&); //used a custom CFG for testing
    friend void config3(CFG&); //used a custom CFG for testing
    friend void config4(CFG&); //used a custom CFG for testing
    friend void config5(CFG&); //test seminar
    friend void config6(CFG&);

    //METHODS FOR CFG->CNF conversion

    void step1(); //removes unusable and inaccesible non-terminals and productions
    void step2(); //removing lambda-productions

    //HELPER METHODS:

    set<string> usableN(); //returns the usable non-terminals
    void removeUnusable(); //removes unusable non-terminals and productions
    void removeInaccessible(); //removes inaccessbile non-terminals and productions

};

