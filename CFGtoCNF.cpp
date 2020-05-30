#include "CFG.h"
#include <iostream>
using namespace std;


int main()
{
	cout << "Test Lab: " << endl;
	CFG g1;
	config1(g1);
	g1.printGrammar();
	cout << endl;
	g1.toCNF();
	g1.printGrammar();

	cout << "-------------------a" << endl;

	cout << "Test Sem: " << endl;
	CFG testSeminar;
	config2(testSeminar);
	testSeminar.printGrammar();
	cout << endl;
	testSeminar.toCNF();
	testSeminar.printGrammar();

	cout << "-------------------" << endl;

}
