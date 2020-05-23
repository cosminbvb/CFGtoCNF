#include "CFG.h"
#include <iostream>
using namespace std;

void config6(CFG& x) {
	x.S = "S";
	x.T.insert("a"); x.T.insert("b"); x.T.insert("#");
	x.N.insert("S"); x.N.insert("B"); x.N.insert("C"); x.N.insert("A");
	x.P["S"].insert("aAbC"); x.P["S"].insert("aB"); x.P["A"].insert("aAC");
	x.P["A"].insert("#"); x.P["B"].insert("#"); x.P["B"].insert("C");
	x.P["C"].insert("CA"); x.P["C"].insert("b");
}

int main()
{
	CFG g1;
	config1(g1);
	g1.step1();
	g1.step2();
	g1.printGrammar();

	cout << "-------------------" << endl;

	CFG testSeminar;
	config5(testSeminar);
	testSeminar.step2();
	testSeminar.printGrammar();
	//step2 correct

	cout << "-------------------" << endl;


	CFG test;
	config6(test);
	test.step2();
	test.printGrammar();
}
