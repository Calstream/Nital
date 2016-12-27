#include<string>
#include<fstream>
#include<vector>
#include<list>
#include<algorithm>
#include<iostream>
#include<climits>

using namespace std;

string const iname = "input.txt";
string const oname = "output.txt";

struct DisjointSets
{
	vector<int> parent;
	vector<int> rank;
	int size;

	// Constructor.
	DisjointSets(int n) : size(n)
	{
		for (size_t i = 0; i < n; i++)
		{
			parent.push_back(i);
			rank.push_back(0);
		}
	}

	bool is_United()
	{
		bool res = true;
		for (size_t i = 0; i < size-1; i++)
		{
			res = res && (parent[i] == parent[i + 1]);
		}
		return res;
	}

	// Find the parent of a node 'u'
	// Path Compression
	int Find(int el)
	{
		//!!
		//el -= 1;
		
		if (el != parent[el])
			parent[el] = Find(parent[el]);
		return parent[el];
	}

	// Union by rank
	void Union(int e1, int e2)
	{
		//!!
		//e1 -= 1;
		//e2 -= 1;

		e1 = Find(e1);
		e2 = Find(e2);

		/* Make tree with smaller height
		a subtree of the other tree  */
		if (rank[e1] > rank[e2])
			parent[e2] = e1;
		else // If rnk[x] <= rnk[y]
			parent[e1] = e2;

		if (rank[e1] == rank[e2])
			rank[e2]++;
	}
};

struct _edge
{
	int v1;
	int v2;
	int w;
	_edge(int a, int b, int c) : v1(a), v2(b), w(c) {}
	bool operator==(_edge const & other)
	{
		return (v1 == other.v1) && (v2 == other.v2) && (w == other.w);
	}
};




class Graph
{
public:
	int vert_n;
	int edge_n;

	vector<_edge> g;
	vector<bool> visited;
	Graph(int v, int e) : vert_n(v), edge_n(e) {}
	//Graph(const Graph & other)
	//{
	//	vert_n = other.vert_n;
	//	edge_n = other.edge_n;
	//	//g = new vector<_edge>(other.g);
	//}

	// true если существует ребро из v1 в v2, resedge - результат
	bool find_edge(int v1, int v2, _edge & resedge)
	{
		for (auto x : g)
		{
			if (((x.v1 == v1) && (x.v2 == v2)) || ((x.v1 == v2) && (x.v2 == v1)))
			{
				resedge = x;
				return true;
			}
		}
		return false;
	}
	
	bool is_Connected()
	{
		
		for (size_t i = 0; i < vert_n; i++)
		{
			visited.push_back(false);
		}
		//Graph dfse = *this;
		//visited[g[0].v1 - 1] = true; // start dfs here
		dfs(g[0],*this);

		for (size_t i = 0; i < vert_n-1; i++)
		{
			if (!visited[i])
				return false;
		}
		return true;
		/*Mark vertex u as gray(visited).
			For each edge(u, v), where u is white, run depth - first search for u recursively.
			Mark vertex u as black and backtrack to the parent.*/


	}

	void dfs(_edge e, Graph dfse)
	{
		int v1 = e.v1;
		int v2 = e.v2;
		if (visited[v2 - 1] && visited[v1 - 1])
			return;
		int vv = v1;
		if (!visited[v2 - 1])
		{
			visited[v2 - 1] = true;
			vv = v2;
		}
		else visited[v1 - 1] = true;

		for (int v = 1; v <= dfse.vert_n; v++)
		{
			_edge eres(-1, -1, -1);
			if (v != vv)
			{
				bool isEdge = find_edge(vv, v, eres);
				if (isEdge/* && !visited[v - 1]*/)
					dfs(eres, dfse);
			}
		}
		/*int v1 = e.v1;
		int v2 = e.v2;
		visited[v1-1] = true;
		dfse.remove_edge(e);
		for (int v = 0; v < dfse.vert_n; v++)
		{
			_edge eres(-1,-1,-1);
			bool isEdge = find_edge(v1, v+1, eres);
			if (isEdge && !visited[v-1])
				dfs(eres, dfse);

		}*/
	}

	void AddEdge(int v1, int v2, int w)
	{
		g.push_back(_edge(v1,v2,w));
	}

	void remove_edge(_edge tbd)
	{
		g.erase(find(g.begin(), g.end(), tbd));
	}

	struct compare_edges{
		bool operator()(_edge e1, _edge e2)
		{
			return e1.w < e2.w;
		}
	};
	
	void sort_edges()
	{
		sort(g.begin(), g.end(), compare_edges());
	}

	int MST(Graph & mst)
	{
		int weight = 0;
		DisjointSets ds(vert_n);
		sort(g.begin(), g.end(), compare_edges());
		for (auto edge : g)
		{
			int v1 = edge.v1;
			int v2 = edge.v2;

			int set_v1 = ds.Find(v1-1);
			int set_v2 = ds.Find(v2-1);

			// Check if the selected edge is creating
			// a cycle or not (Cycle is created if u
			// and v belong to same set)
			if (set_v1 != set_v2)
			{
				// Current edge will be in the MST
				// so print it
				mst.AddEdge(edge.v1, edge.v2, edge.w);

				// Update MST weight
				weight += edge.w;

				// Merge two sets
				ds.Union(set_v1, set_v2);
			}
			
		}	
		return weight;
	}

	void test()
	{
		Graph test = *this;
		vert_n = -1;
		vert_n = -2;
	}
	
	void print()
	{
		for (auto edge : g)
		{
			int w = edge.w;
			int v1 = edge.v1;
			int v2 = edge.v2;
			cout << v1 << "--" << w << "--" << v2 << endl;
		}
	}
};


//Build first MST
//L = list of edges in the first mst, sorted by weight
//second_best_cost = INF
//for (i = 0; i<L.size; i++) {
//	try to build a mst without using edge L[i]
//		if it's possible and its cost is < second_best_cost {
//			second_mst = the new found mst
//			second_best_cost = its cost
//}
//}

int find_2nd_best(Graph g, Graph mst)
{
	mst.sort_edges();
	int sbw = INT_MAX;
	for (auto e : mst.g)
	{
		Graph temp = g;
		temp.remove_edge(e);
		if (temp.is_Connected())
		{
			Graph newmst(0, 0);
			int nw = temp.MST(newmst);
			if (nw < sbw)
				sbw = nw;
		}
		
	}
	return sbw;
}



int main()
{
	//int V = 9, E = 14;
	//Graph g(V, E);

	////vector<string> dict;
	ifstream input;
	input.open(iname);
	string s = "";
	int n = 0;
	input >> n;
	int m = 0;
	input >> m;
	//input.ignore();
	Graph g1(n, m);
	for (size_t i = 0; i <= m-1; i++)
	{
		int v1;
		int v2;
		int w;
		input >> v1;
		input >> v2;
		input >> w;
		g1.AddEdge(v1, v2, w);
	}
	input.close();


	////  making above shown graph
	//g.AddEdge(0, 1, 4);
	//g.AddEdge(0, 7, 8);
	//g.AddEdge(1, 2, 8);
	//g.AddEdge(1, 7, 11);
	//g.AddEdge(2, 3, 7);
	//g.AddEdge(2, 8, 2);
	//g.AddEdge(2, 5, 4);
	//g.AddEdge(3, 4, 9);
	//g.AddEdge(3, 5, 14);
	//g.AddEdge(4, 5, 10);
	//g.AddEdge(5, 6, 2);
	//g.AddEdge(6, 7, 1);
	//g.AddEdge(6, 8, 6);
	//g.AddEdge(7, 8, 7);

	Graph mst(0,0);

	//cout << "Edges of MST are \n";
	//int mst_wt = g1.MST(mst);

	//cout << "\nWeight of MST is " << mst_wt << endl << endl;
	//mst.print();
	//cout << "\n 2nd best weight of MST is " << find_2nd_best(g1,mst) << endl << endl;
	//system("pause");

	Graph g(7, 8);
	g.AddEdge(1, 2, 1);
	g.AddEdge(1, 3, 6);
	g.AddEdge(2, 3, 3);
	g.AddEdge(2, 4, 12);
	g.AddEdge(4, 7, 4);
	g.AddEdge(4, 5, 5);
	g.AddEdge(5, 6, 2);
	g.AddEdge(7, 6, 7);

	ofstream output;
	output.open(oname);
	output.clear();
	g1.MST(mst);
	int t = find_2nd_best(g1, mst);
	//int t = find_2nd_best(g, mst);
	output << t;
	//cout << t;
	
	////g.test();

	//cout << g.is_Connected();
	//	/*1 2 1
	//	1 3 6
	//	2 3 3
	//	2 4 12
	//	4 7 4
	//	4 5 5
	//	5 6 2
	//	7 6 7*/


	system("pause");
}
