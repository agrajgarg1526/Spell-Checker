#include<bits/stdc++.h>
using namespace std;

//NODE CLASS
class node
{
public:
	char data;
	unordered_map<char, node *> h;
	bool isTerminal;
	node(char d)
	{
		data = d;
		isTerminal = false;
	}
};


class spellChecker
{
	node *root;
	set<string> closest_words;

	void addWord(string);
	bool searchWord(string);
	void editDistance(string, int);

public:
	
	spellChecker();
	void isWordEnteredCorrect(string);
    
};



//CONVERTS EVERY STRING TO LOWERCASE
string to_simple_string(string s)
{
	string str = "";
	int n = s.size();
	int i, j;
	for (i = 0; i < n; i++)
	{
		if (s[i] >= 'A' and s[i] <= 'Z')
		{
			str += s[i] + 32;
		}
		else if (s[i] >= 'a' and s[i] <= 'z')
		{
			str += s[i];
		}
	}
	return str;
}


//DOES PRECOMPUTATION AND STORES EVERY WORD INTO TRIE
void spellChecker :: addWord(string word)
{
	node *temp = root;
	for (int i = 0; word[i] != '\0'; i++)
	{
		char ch = word[i];
		if (temp->h.count(ch) == 0)
		{
			node *n = new node(ch);
			temp->h[ch] = n;
			temp = n;
		}
		else
		{
			temp = temp->h[ch];
		}
	}
	temp->isTerminal = true;
}


//SEARCHES WORD IN TRIE AND RETURNS RESULT ACCORDINGLY
bool spellChecker ::searchWord(string word)
{
	node *temp = root;

	for (int i = 0; word[i] != '\0'; i++)
	{
		char ch = word[i];

		if (temp->h.count(ch) == 0)
		{
			return false;
		}
		temp = temp->h[ch];
	}
	return temp->isTerminal;
}


//FUNCTION TO FIND ALL THE WORDS CLOSEST TO OUR INCORRECT INPUT
void spellChecker ::editDistance(string s, int curr)
{
	int count = 0;
	int n = s.size();
	int i, j, k;

	//IF BY MISTAKE THE USER HAS ENTERED ONE CHARACTER LESS
	for (i = -1; i < n; i++)
	{
		for (j = 0; j < 26; j++)
		{
			char c = 'a' + j;
			string str = s.substr(0, i + 1) + c + s.substr(i + 1, n - i - 1);
			if (searchWord(str))
			{
				closest_words.insert(str);
			}
		}
	}

	//IF BY MISTAKE THE USER HAS ENTERED ANY WRONG CHARACTER
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < 26; j++)
		{
			char c = 'a' + j;
			string str = s.substr(0, i) + c + s.substr(i + 1, n - i - 1);
			if (searchWord(str))
			{
				closest_words.insert(str);
			}
		}
	}

	//IF BY MISTAKE THE USER HAS ENTERED ONE CHARACTER MORE
	for (i = 0; i < n; i++)
	{
		string str = s.substr(0, i) + s.substr(i + 1, n - i - 1);
		if (searchWord(str))
		{
			closest_words.insert(str);
		}
	}

	//IF BY MISTAKE THE USER HAS INTERCHANGED ANY TWO ADJACENT CHARACTERS
	for (i = 0; i < n - 1; i++)
	{
		char a = s[i], b = s[i + 1];
		string str = s.substr(0, i) + b + a + s.substr(i + 2, n - i - 2);
		if ( searchWord(str))
		{
			closest_words.insert(str);
		}
	}
}


//CHECK IF THE INPUT WORD IS CORRECT ELSE CALLS EDIT DISTANCE FUNCTION
void spellChecker ::isWordEnteredCorrect(string s)
{
	closest_words.clear();
	s = to_simple_string(s);
	if (!searchWord(s))
	{
		editDistance(s, 1);
		if (closest_words.size() == 0)
		{
			cout << "\nCould'nt Find Related Words......\n";
		}
		else
		{
			cout << "\nMaybe You Were Trying To Enter One of These Words :- " << endl;

			for (auto it = closest_words.begin(); it != closest_words.end(); it++)
			{
				cout << *it << endl;
			}
		}
	}
	else
	{
		cout << "\nWord Entered is Correct\n";
	}
}


//CONSTRUCTOR
spellChecker ::spellChecker()
{
	root = new node('\0');
	ifstream fin;
	fin.open("words.txt");
	string s;
	int t;
	while (fin.eof() == 0)
	{
		fin >> s;
		s = to_simple_string(s);
		if (s != "")
		{
			addWord(s);
		}
	}
	fin.close();
	cout << "\n\nWelcome To Spell Checker Project\n\n";
	cout<<"You need to enter a string to check\nIf its spelling is incorrect,";
	cout<<"program will suggest you all the closest and valid possible words!\n";
	cout << "\nEnter 'exit' to Terminate the Program\n";
}