#include<string>
#include<fstream>
#include<vector>
#include<cassert>
#include<list>
#include<map>
#include<stack>
using namespace std;

string const iname = "input1.txt";
string const oname = "output.txt";

class Graph
{
public:
	int Size;
	map<char, list<char>> Adj;
	vector<char> ks;
	Graph() : Size(0) {}

	void AddVertex(char v)
	{
		if (Adj.find(v) == Adj.end())
		{
			++Size;
			Adj.emplace(pair<char, list<char>>(v, *(new list<char>())));
			ks.push_back(v);
		}
	}

	void AddEdge(char v1, char v2)
	{
		Adj[v1].emplace_back(v2);
	}

	// A recursive function used by topologicalSort
	void Graph::topologicalSortUtil(char v, bool visited[],
		stack<char> &Stack)
	{
		// Mark the current node as visited.
		visited[v] = true;

		// Recur for all the vertices adjacent to this vertex
		//list<int>::iterator i;
		for (char x : Adj[v])
		//for (i = Adj[v].begin(); i != Adj[v].end(); ++i)
			if (!visited[x])
				topologicalSortUtil(x, visited, Stack);

		// Push current vertex to stack which stores result
		Stack.push(v);
	}

	// The function to do Topological Sort. It uses recursive 
	// topologicalSortUtil()
	void Graph::topologicalSort()
	{
		stack<char> Stack;

		// Mark all the vertices as not visited
		
		bool *visited = new bool[Size];
		for (int i = 0; i < Size; i++)
			visited[i] = false;

		// Call the recursive helper function to store Topological
		// Sort starting from all vertices one by one
		for each (auto x in Adj)
			if (!visited[x.first])
				topologicalSortUtil(x.first, visited, Stack);
		/*for (int j = 0; j < Size; j++)
			if (visited[j] == false)
				topologicalSortUtil(j, visited, Stack);*/
		ofstream output;
		output.open(oname, ios_base::app);
		output.clear();
		// Print contents of stack
		while (Stack.empty() == false)
		{
			output << Stack.top() << " ";
			Stack.pop();
		}
	}

};

//индекс пары первых несовпадающих символов
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

	for each (string s in dict)
		make_vertices(s, graph);
	for (size_t i = 1; i < dict.size(); i++)
	{
		int mm = find_mismatch(dict[i-1], dict[i]);
		graph.AddEdge(dict[i - 1][mm], dict[i][mm]);
	}
 	graph.topologicalSort();
	

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