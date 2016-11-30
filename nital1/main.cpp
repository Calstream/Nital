#include<string>
#include<fstream>
#include<vector>
#include<list>
#include<map>
#include<stack>
#include<algorithm>
using namespace std;

string const iname = "input.txt";
string const oname = "output.txt";

class Graph
{
public:
	int Size;
	map<char, list<char>> Adj;
	map<char, bool> visited;
	vector<char> order;
	map<char, int> used;

	Graph() : Size(0) {}

	bool is_not_DAG(char v)
	{
		used[v] = 1;
		for (auto x : Adj[v])
		{
			if (used[x] == 0)
			{
				if (is_not_DAG(x))
					return true;
			}
			else if (used[x] == 1)
			{
				return true;
			}
		}
		used[v] = 2;
		return false;
	}

	void AddVertex(char v)
	{
		if (Adj.find(v) == Adj.end())
		{
			++Size;
			Adj.emplace(pair<char, list<char>>(v, *(new list<char>())));
			visited.emplace(pair<char, bool>(v, false));
			used.emplace(pair<char,int>(v,0));
		}
	}

	void AddEdge(char v1, char v2)
	{
		if (v1 == '\0' || v2 == '\0')
			return;
		if (find(Adj[v1].begin(), Adj[v1].end(), v2) == Adj[v1].end())
			Adj[v1].emplace_back(v2);
	}

	void topologicalSortUtil(char v)
	{
		visited[v] = true;
		for (auto i = Adj[v].begin(); i != Adj[v].end(); ++i)
			if (!visited[*i])
				topologicalSortUtil(*i);
			order.push_back(v);
	}

	void topologicalSort()
	{
		for (auto v: Adj)
			if (!visited[v.first])
				topologicalSortUtil(v.first);
		ofstream output;
		output.open(oname);
		output.clear();
		for (int i = order.size() - 1; i >= 0; --i)
			output << order[i];		
	}

};

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

void make_vertices(string s, Graph & G)
{
	for (int i = 0; i < s.length(); i++)
	{
		G.AddVertex(s[i]);
	}
}


int main()
{
	vector<string> dict;
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
	input.close();

	Graph graph;

	for (string s : dict)
		make_vertices(s, graph);
	for (size_t i = 1; i < dict.size(); i++)
	{
		int mm = find_mismatch(dict[i-1], dict[i]);
		graph.AddEdge(dict[i - 1][mm], dict[i][mm]);
	}
	if (!graph.is_not_DAG(dict[0][0]))
 		graph.topologicalSort();
	else
	{
		ofstream output;
		output.open(oname);
		output.clear();
		output << "-";
	}

}