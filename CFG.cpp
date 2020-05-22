#include "CFG.h"

void config1(CFG& x) {
    x.S = "S";
    x.N.insert("S"); x.N.insert("A"); x.N.insert("B");
    x.N.insert("C"); x.N.insert("D"); x.N.insert("F");
    x.T.insert("a"); x.T.insert("b"); x.T.insert("c");
    x.T.insert("#"); //lambda 
    x.P["S"].insert("aAb"); x.P["S"].insert("BC"); x.P["S"].insert("#");
    x.P["A"].insert("AaB"); x.P["A"].insert("Db");
    x.P["B"].insert("b"); x.P["B"].insert("c");
    x.P["C"].insert("#"); x.P["C"].insert("ab");
    x.P["D"].insert("#"); x.P["F"].insert("a");
}
void config2(CFG& x) {
    x.S = "S";
    x.N.insert("S"); x.N.insert("A"); x.N.insert("B"); x.N.insert("C");
    x.T.insert("a"); x.T.insert("b");
    x.P["S"].insert("A"); x.P["S"].insert("B");
    x.P["A"].insert("aB"); x.P["A"].insert("bS"); x.P["A"].insert("b");
    x.P["B"].insert("AB"); x.P["B"].insert("Ba");
    x.P["C"].insert("AS"); x.P["C"].insert("b");
}
void config3(CFG& x) {
    x.S = "S";
    x.N.insert("S"); x.N.insert("A"); x.N.insert("B");
    x.T.insert("#"); x.T.insert("a"); x.T.insert("b");
    x.P["S"].insert("aSb"); x.P["S"].insert("aA");
    x.P["A"].insert("aA"); x.P["A"].insert("bB"); x.P["A"].insert("#");
    x.P["B"].insert("bBb");
}
void config4(CFG& x) {
    x.S = "S";
    x.N.insert("S"); x.N.insert("A"); x.N.insert("B"); x.N.insert("C");
    x.T.insert("a"); x.T.insert("b");
    x.P["S"].insert("AB"); x.P["S"].insert("CA");
    x.P["A"].insert("a"); x.P["B"].insert("BC"); x.P["B"].insert("AB");
    x.P["C"].insert("AB"); x.P["C"].insert("b");
}
void config5(CFG& x) {
    x.S = "S";
    x.T.insert("a"); x.T.insert("b");
    x.N.insert("S"); x.N.insert("A"); x.N.insert("B"); x.N.insert("C"); 
    x.N.insert("D"); x.N.insert("E");
    x.P["S"].insert("A"); x.P["S"].insert("D"); x.P["B"].insert("bC"); 
    x.P["A"].insert("Ba"); x.P["A"].insert("E"); x.P["C"].insert("A"); 
    x.P["D"].insert("aD"); x.P["D"].insert("a"); x.P["E"].insert("C");

}


void CFG::printGrammar() {
    for (auto p : P) {
        cout << p.first << " -> ";
        for (auto rhs : p.second) {
            cout << rhs << " ";
        }
        cout << endl;
    }
}

void CFG::step1() {
    removeUnusable();
    removeInaccessible();
}

//HELPER METHODS:

set<string> CFG::usableN() {
    //eliminating unusable symbols and productions
    set<string>usable; // usable non-terminals
    for (auto p : P) {
        //for each production
        bool use = false;
        bool every = true;
        for (auto rhs : p.second) {
            //for each right hand side of the production
            //if at least one is in T* or each symbol is in T* => the non-terminal is usable
            if (T.find(rhs) != T.end()) {
                use = true;
                break;
            }
            //now we check is every symbol is in T*
            every = true;
            for (auto sy : rhs) {
                string s;
                s += sy;
                if (T.find(s) == T.end()) {//////////////
                    every = false;
                    break;
                }
            }
        }
        if (use || every) usable.insert(p.first);
    }
    bool modified = true;
    while (modified) {
        modified = false;
        for (auto p : P) {
            //for every production
            if (usable.find(p.first) == usable.end()) {
                //if the lhs was not usable before the last modification
                //we check if it is usable now
                bool every = true;
                for (auto rhs : p.second) {
                    every = true;
                    for (auto sy : rhs) {
                        string s;
                        s += sy;
                        if (T.find(s) == T.end() && usable.find(s) == usable.end()) {//////////////
                            every = false;
                            break;
                        }
                    }
                    if (every) {
                        usable.insert(p.first);
                        modified = true;
                    }
                }
            }
        }
    }
    //for (auto i : usable)cout << i << " ";
    //cout << endl;
    return usable;
}
void CFG::removeUnusable() {
    set<string>usable = usableN();
    for (auto n : N) {
        //for each non-terminal
        if (usable.find(n) == usable.end()) {
            //if it s not usable
            //we must eliminate it and any production containing it on lfs/rhs
            P.erase(n);
            for (auto p : P) {
                //for each production
                set<string> newRHS;
                for (auto rhs : p.second) {
                    //for each rhs of the production
                    bool shouldBeRemoved = false;
                    for (auto sy : rhs) {
                        string s;
                        s += sy;
                        if (s == n) {
                            //if it contains n it should be removed
                            shouldBeRemoved = true;
                            break;
                        }
                    }
                    if (!shouldBeRemoved) {
                        newRHS.insert(rhs);
                    }
                }
                P[p.first] = newRHS;
            }
        }
    }
    N = usable;
}

void CFG::removeInaccessible() {
    set<string>accessible;
    accessible.insert(S); //the start symbol is always accessible
    for (auto rhs : P[S]) {
        for (auto sy : rhs) {
            string s;
            s += sy;
            if (N.find(s) != N.end()) {
                //if we found a non-terminal in a rhs, it is accessible
                accessible.insert(s);
            }
        }
    }
    bool modified = true;
    while (modified) {
        modified = false;
        for (auto a : accessible) {
            for (auto rhs : P[a]) {
                for (auto sy : rhs) {
                    string s;
                    s += sy;
                    if (N.find(s) != N.end() && accessible.find(s) == accessible.end()) {
                        //if we found a non-terminal in a rhs and it isn t in accessible already, we add it
                        accessible.insert(s);
                        modified = true;
                    }
                }
            }
        }
    }
    for (auto n : N) {
        if (accessible.find(n) == accessible.end()) {
            //if n in inaccessible
            P.erase(n);//we remove any production with n on the lhs
        }
    }
    N = accessible;
}