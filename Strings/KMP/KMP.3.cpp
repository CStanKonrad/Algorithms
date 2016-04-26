/*
The MIT License (MIT)

Copyright (c) 2016 CStanKonrad

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <bits/stdc++.h>

const int MAX_INPUT_LENGTH = 2*1000000;


int prefikso_sufiks[MAX_INPUT_LENGTH + 7];	//prefikso_sufiks[i] oznacza długość najdłuższego prefikso-sufiksu właściwego dla słowa zaczynającego się na pozycji 1 i kończącego się na pozycji i

void kmp(char *_text, int _dlugosc)
{
	prefikso_sufiks[1] = 0; //bo interesują nas prefikso-sufiksy właściwe (czyli takie, które nie są całym rozważanym słowem)
	int p = 0;
	for (int i = 2; i <= _dlugosc; ++i)
	{
		while (p != 0 && _text[p + 1] != _text[i])	//iteruję po prefikso-sufiksach i sprawdzam czy mogę przedłużyć
			p = prefikso_sufiks[p];
		
		if (_text[p + 1] == _text[i])	//jak mogę to przedłużam
			++p;
		
		prefikso_sufiks[i] = p;
	}
}


char wejscie[MAX_INPUT_LENGTH + 7];
int main()
{
	scanf("%s", &wejscie[1]);	//bo iterujemy od 1
	int dlugosc_wzorca = strlen(&wejscie[1]);	//zwraca długość wczytanego wzorca
	wejscie[dlugosc_wzorca + 1] = '#';	//separator
	
	scanf("%s", &wejscie[dlugosc_wzorca + 2]);	//tekst
	int dlugosc_calosci = strlen(&wejscie[1]);
	
	kmp(wejscie, dlugosc_calosci);	//obliczamy tablicę prefikso-sufiksów właściwych
	
	/* Zliczamy wystąpienia wzorca */
	int ile = 0;
	for (int i = dlugosc_wzorca; i <= dlugosc_calosci; ++i)
	{
		if (prefikso_sufiks[i] == dlugosc_wzorca)
			++ile;
	}
	
	printf("%d\n", ile);
	
	return 0;
}
