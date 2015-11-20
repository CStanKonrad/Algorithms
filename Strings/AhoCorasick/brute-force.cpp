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
long long wynik;
int n;
int main()
{
	cin >> n;
	cin >> text;
	for (int i = 0; i < n; i++)
	{
		cin >> pattern;
		wynik += howManyPatternsInText(pattern, text);
	}
	cout << wynik << endl;
}
