#include <iostream>
#include <string>

using namespace std;

int howManyPatternsInText(string _pattern, string _text)
{
	int howMany = 0;
	for (unsigned int i = 0, j; i < _text.size(); i++)
	{
		for (j = 0; (j < _pattern.size()) && (j + i < _text.size()); j++)
		{
			if (_pattern[j] != _text[i + j])
				break;
		}
		if (j == _pattern.size())
			howMany++;
	}
	return howMany;
}

string pattern, text, combined;

int cmpWords(int _b1, int _e1, int _b2, int _e2)
{
	int len = std::min(_e1 - _b1 + 1, _e2 - _b2 + 1);
	
	for (int i = 0; i < len; ++i)
	{
		if (combined[_b1 + i] == combined[_b2 + i])
			continue;
		else if (combined[_b1 + i] < combined[_b2 + i])
			return -1;
		else
			return 1;
	}
	if (_e1 - _b1 + 1 > _e2 - _b2 + 1)
		return 1;
	else if (_e1 - _b1 + 1 < _e2 - _b2 + 1)
		return -1;
	else 
		return 0;
}

int t;
int main()
{
	cin >> pattern >> text;
	cout << howManyPatternsInText(pattern, text) << endl;
	cin >> t;
	combined = pattern + string("#") + text;
	for (int i = 0, b1, e1, b2, e2; i < t; ++i)
	{
		cin >> b1 >> e1 >> b2 >> e2;
		cout << cmpWords(b1, e1, b2, e2) << endl;
	}
}
