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

string pattern, text;
int main()
{
	cin >> pattern >> text;
	cout << howManyPatternsInText(pattern, text) << endl;
}
