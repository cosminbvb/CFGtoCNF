#include "CFG.h"
void config(CFG& x) {
    x.S = "S";
    x.N.insert("S"); x.N.insert("A"); x.N.insert("B");
    x.N.insert("C"); x.N.insert("D"); x.N.insert("F");
    x.T.insert("a"); x.T.insert("b"); x.T.insert("c");
    x.T.insert("#"); //lambda 
    x.P["S"].insert("aBb"); x.P["S"].insert("BC"); x.P["S"].insert("#");
    x.P["A"].insert("AaB"); x.P["A"].insert("Db");
    x.P["B"].insert("b"); x.P["B"].insert("c");
    x.P["C"].insert("#");  x.P["C"].insert("ab");
    x.P["D"].insert("#"); x.P["F"].insert("a");
}
void CFG::step1() {
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
    for (auto i : usable)cout << i << " ";
    cout << endl;
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
    for (auto i : usable)cout << i << " ";
    cout << endl;
}