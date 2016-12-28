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
		return (((v1 == other.v1) && (v2 == other.v2)) || ((v1 == other.v2) && (v2 == other.v1))) && (w == other.w);
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
	
	bool is_Connected(_edge & ignore)
	{
		visited.clear();
		for (size_t i = 0; i < vert_n; i++)
		{
			visited.push_back(false);
		}
		dfs(g[0],*this,ignore);

		for (size_t i = 0; i < vert_n-1; i++)
		{
			if (!visited[i])
				return false;
		}
		return true;
	}

	void dfs(_edge & e, Graph & dfse, _edge & ignore)
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
				if (isEdge && !(eres == ignore))
					dfs(eres, dfse, ignore);
			}
		}
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

	int MST(Graph & mst, _edge & ignore)
	{
		int weight = 0;
		DisjointSets ds(vert_n);
		sort(g.begin(), g.end(), compare_edges());
		for (auto edge : g)
		{
			if (!(edge == ignore))
			{
				int v1 = edge.v1;
				int v2 = edge.v2;

				int set_v1 = ds.Find(v1 - 1);
				int set_v2 = ds.Find(v2 - 1);

				if (set_v1 != set_v2)
				{
					mst.AddEdge(edge.v1, edge.v2, edge.w);

					weight += edge.w;

					ds.Union(set_v1, set_v2);
				}
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


int find_2nd_best(Graph & g, Graph & mst)
{
	mst.sort_edges();
	int sbw = INT_MAX;
	for (auto ignore : mst.g)
	{
		if (g.is_Connected(ignore))
		{
			Graph newmst(0, 0);
			int nw = g.MST(newmst,ignore);
			if (nw < sbw)
				sbw = nw;
		}
	}
	return sbw;
}


int main()
{
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

	Graph mst(0,0);
	ofstream output;
	_edge ee(-1, -1, -1);
	output.open(oname);
	output.clear();
	g1.MST(mst,ee);
	int t = find_2nd_best(g1, mst);
	output << t;

	/*Graph mst1(0, 0);
	Graph g(7, 8);
	g.AddEdge(1, 2, 1);
	g.AddEdge(1, 3, 6);
	g.AddEdge(2, 3, 3);
	g.AddEdge(2, 4, 12);
	g.AddEdge(4, 7, 4);
	g.AddEdge(4, 5, 5);
	g.AddEdge(5, 6, 2);
	g.AddEdge(7, 6, 7);
	int mw = g1.MST(mst1, ee);
	int t1 = find_2nd_best(g1, mst1);
	cout << t1;*/

	system("pause");
}
