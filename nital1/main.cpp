#include<string>
#include<fstream>
#include<vector>
#include<cassert>
#include<list>
#include<map>
using namespace std;

string const iname = "input.txt";
string const oname = "output.txt";

int find_mismatch(string s1, string s2)
{
	int length = 0;
	if (s1.length() > s2.length())
		length = s2.length();
	else length = s1.length();
	int res = length;
	for (size_t i = 0; i <= length - 1; i++)
	{
		if (s1[i] != s2[i])
		{
			res = i;
			return res;
		}
	}
	return res;
}

class Graph
{
	int Size;
	map<char,list<char>> Adj;
	Graph() : Size(0) {}
	void AddVertex(char v)
	{
		Adj.emplace(v,nullptr);
	}

	void AddEdge(char v1, char v2)
	{
		Adj[v1].push_back(v2);
		Adj[v2].push_back(v1);
	}
};

int main()
{
	/*vector<string> dict;
	ifstream input;
	input.open(iname);
	string s = "";
	int n_words = 0;
	input >> n_words;
	input.ignore();
	while (getline(input, s))
	{
		dict.push_back(s);
	}
	input.close();*/
	
	

	system("pause");
}


//assert(find_mismatch("abc", "bbc") == 0);
//int reslt = find_mismatch("aac", "aab");
//assert(reslt == 2);
//assert(find_mismatch("aa", "aaa") == 2);
//reslt = find_mismatch("aaaaaaaaa", "aaaaa");
//assert(reslt == 5);
//assert(find_mismatch("abacus", "abacup") == 5);
//assert(find_mismatch("ab", "acc") == 1);