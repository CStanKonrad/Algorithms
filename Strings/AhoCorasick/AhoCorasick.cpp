/*
The MIT License (MIT)
Copyright (c) 2015 CStanKonrad
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

#include <cstdio>
#include <map>
#include <queue>


struct SAhoNode
{
    SAhoNode()
    {
        numOfEnds = 0;
        sufLnk = nullptr;
        patLnk = nullptr;
    }
    int numOfEnds;
    SAhoNode *sufLnk;
    SAhoNode *patLnk;
    std::map <char, SAhoNode*> son;
};

class CAhoCorasick
{
private:
    SAhoNode root;
    SAhoNode* move(SAhoNode *_node, char _letter)
    {
        while ((_node != &root) && (_node->son.find(_letter) == _node->son.end()))
               _node = _node->sufLnk;

        if (_node->son.find(_letter) != _node->son.end())
            _node = _node->son[_letter];

        return _node;
    }
public:
    CAhoCorasick()
    {
    }
    void insert(char *_pattern)
    {
        SAhoNode *j = &root;
        for (int i = 0; _pattern[i] != '\0'; i++)
        {
            if (j->son.find(_pattern[i]) == j->son.end())
            {
                j->son[_pattern[i]] = new SAhoNode();
            }
            j = j->son[_pattern[i]];
        }
        j->numOfEnds++;
    }
    void calc()
    {
        std::queue<SAhoNode*> kolejka;
        for (std::map <char, SAhoNode*>::iterator i = root.son.begin(); i != root.son.end(); i++)
        {
            i->second->sufLnk = &root;
            kolejka.push(i->second);
        }

        SAhoNode *proc;
        while (!kolejka.empty())
        {
            proc = kolejka.front();
            kolejka.pop();

            proc->patLnk = (proc->sufLnk->numOfEnds != 0 ? proc->sufLnk : proc->sufLnk->patLnk);

            for (std::map <char, SAhoNode*>::iterator i = proc->son.begin(); i != proc->son.end(); i++)
            {
                i->second->sufLnk = move(proc->sufLnk, i->first);
                kolejka.push(i->second);
            }
        }
    }
    int search(char *_text)
    {
        int result = 0;
        SAhoNode *j = &root, *e;
        for (int i = 0; _text[i] != '\0'; i++)
        {
            j = move(j, _text[i]);
            e = j;
            while (e != nullptr)
            {
                if (e->numOfEnds != 0)
                    result += e->numOfEnds;
                e = e->patLnk;
            }
        }
        return result;
    }
};



#define MAX_TEXT_SIZE 1000000
int n;
char text[MAX_TEXT_SIZE + 7];
char pattern[MAX_TEXT_SIZE + 7];
CAhoCorasick aho;
int main()
{
    scanf("%d", &n);
    scanf("%s", text);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", pattern);
        aho.insert(pattern);
    }
    aho.calc();
    printf("%d\n", aho.search(text));
    return 0;
}
