#include <bits/stdc++.h>
#include "main.h"
using namespace std;


int main()
{
	spellChecker spell;

	while (1)
	{
		string s;
		cout << "\nEnter the String to be Checked\n";
		cin >> s;
		if (to_simple_string(s) == "exit")
			break;
		spell.isWordEnteredCorrect(s);
	}
	return 0;
}