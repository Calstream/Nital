#include<string>
#include<fstream>
#include<vector>
#include<cassert>
#include<list>
#include<map>
#include<stack>
#include<iostream>
using namespace std;

string const iname = "loop.txt";
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
	
	/*bool is_DAG()
	{
		return is_DAG();
	}*/

	bool is_DAGutil(char v)
	{
		used[v] = 1;
		for (auto x : Adj[v])
		{
			if (used[x] == 0)
			{
				if (is_DAGutil(x))
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

	bool check_ham_path()
	{
		for (size_t i = 0; i < order.size() - 1; i++)
		{
			if (find(Adj[order[i]].begin(), Adj[order[i]].end(), order[i + 1]) == Adj[order[i]].end())
				return false;
		}
		return true;
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
		if (find(Adj[v1].begin(), Adj[v1].end(), v2) == Adj[v1].end())
			Adj[v1].emplace_back(v2);
	}

	void Graph::topologicalSortUtil(char v)//, stack<char> &Stack)
	{
		visited[v] = true;

		for (auto i = Adj[v].begin(); i != Adj[v].end(); ++i)
			if (!visited[*i])
				topologicalSortUtil(*i);//, Stack);

		// Push current vertex to stack which stores result
			order.push_back(v);
		//Stack.push(v);
	}

	void Graph::topologicalSort()
	{
		for (auto v: Adj)
			if (!visited[v.first])
				topologicalSortUtil(v.first);// , Stack);

		ofstream output;
		output.open(oname);
		output.clear();

		for (int i = order.size() - 1; i >= 0; --i)
			output << order[i] << " ";		
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
	if (graph.is_DAGutil(dict[0][0]))
 		graph.topologicalSort();
	else cout << ":)))))))";

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



/*

// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(char v, bool visited[],
stack<char> &Stack)
{
// Mark the current node as visited.
visited[v] = true;

// Recur for all the vertices adjacent to this vertex
//list<int>::iterator i;

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
/*ofstream output;
output.open(oname, ios_base::app);
output.clear();
// Print contents of stack
while (Stack.empty() == false)
{
	output << Stack.top() << " ";
	Stack.pop();
}
	}

*/