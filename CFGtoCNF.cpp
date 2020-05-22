#include "CFG.h"
#include <iostream>
using namespace std;

int main()
{
	CFG g2;
	config2(g2);
	g2.removeUnusable();
	g2.printGrammar();
	cout << endl;
	//right answer

	CFG g4;
	config4(g4);
	g4.removeUnusable();
	g4.printGrammar();
	cout << endl;
	//right answer

	CFG g1;
	config1(g1);
	g1.removeInaccessible();
	g1.printGrammar();
	//right answer

	cout << "------------" << endl;

	CFG dani;
	config5(dani);
	dani.step1();
	dani.printGrammar();

}
