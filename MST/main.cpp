#include<string>
#include<fstream>
#include<vector>
#include<list>
#include<algorithm>
#include<iostream>

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

	// Find the parent of a node 'u'
	// Path Compression
	int Find(int el)
	{
		/* Make the parent of the nodes in the path
		from u--> parent[u] point to parent[u] */
		if (el != parent[el])
			parent[el] = Find(parent[el]);
		return parent[el];
	}

	// Union by rank
	void Union(int e1, int e2)
	{
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
};

class Graph
{
public:
	int vert_n;
	int edge_n;

	vector<_edge> g;
	
	Graph(int v, int e) : vert_n(v), edge_n(e) {}
	
	void AddEdge(int v1, int v2, int w)
	{
		g.push_back(_edge(v1,v2,w));
	}

	struct compare_edges{
		bool operator()(_edge e1, _edge e2)
		{
			return e1.w < e2.w;
		}
	};
	

	int MST(Graph & mst)
	{
		int weight = 0;
		DisjointSets ds(vert_n);
		sort(g.begin(), g.end(), compare_edges());
		for (auto edge : g)
		{
			int v1 = edge.v1;
			int v2 = edge.v2;

			int set_v1 = ds.Find(v1);
			int set_v2 = ds.Find(v2);

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


int main()
{
	int V = 9, E = 14;
	Graph g(V, E);

	//  making above shown graph
	g.AddEdge(0, 1, 4);
	g.AddEdge(0, 7, 8);
	g.AddEdge(1, 2, 8);
	g.AddEdge(1, 7, 11);
	g.AddEdge(2, 3, 7);
	g.AddEdge(2, 8, 2);
	g.AddEdge(2, 5, 4);
	g.AddEdge(3, 4, 9);
	g.AddEdge(3, 5, 14);
	g.AddEdge(4, 5, 10);
	g.AddEdge(5, 6, 2);
	g.AddEdge(6, 7, 1);
	g.AddEdge(6, 8, 6);
	g.AddEdge(7, 8, 7);

	Graph mst(0,0);

	cout << "Edges of MST are \n";
	int mst_wt = g.MST(mst);

	cout << "\nWeight of MST is " << mst_wt << endl << endl;
	mst.print();

	system("pause");
}


/*struct DisjointSet
{
list<int> set;
DisjointSet(int a)
{
set.push_back(a);
}
void Union(DisjointSet ds)
{
set.merge(ds.set);
}

int Find()
{

}
};*/