#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

#define edge pair<int, int>
int nodes, edges;

class Graph {
private:
	vector<pair<int, edge>> G;
	vector<pair<int, edge>> T;
	int *parent;
	int V;
	public:
	Graph(int V);
	void AddWeightedEdge(int u, int v, int w);
	int find_set(int i);
	void union_set(int u, int v);
	void kruskal();
	void print();
};

Graph::Graph(int V) {
	parent = new int[V];

	for (int i = 0; i < V; i++)
		parent[i] = i;

	G.clear();
	T.clear();
}

void Graph::AddWeightedEdge(int u, int v, int w) {
	G.push_back(make_pair(w, edge(u, v)));
}

int Graph::find_set(int i) {
// If i is the parent of itself
	if (i == parent[i])
		return i;
	else
		return parent[i] = find_set(parent[i]);
}

void Graph::union_set(int u, int v) {
	parent[u] = parent[v];
}

void Graph::kruskal() {
	int uRep, vRep;
	unsigned long i;

// Use quicksort to sort the edges by weight
	sort(G.begin(), G.end()); // increasing weight
	for (i = 0; i < G.size(); i++) {
		uRep = find_set(G[i].second.first);
		vRep = find_set(G[i].second.second);
		if (uRep != vRep) {
			T.push_back(G[i]); // add to tree
			union_set(uRep, vRep);
		}
	}
}

void Graph::print() {
	int sum = 0;
	for (unsigned long i = 0; i < T.size(); i++) {
		sum += T[i].first;
	}
	printf("%d\n", -sum); 
}

int main() {
	int a, b, cost, e;
	scanf("%d\n", &nodes); 
	scanf("%d\n", &edges);
	Graph g(nodes);
	for (e = 0; e < edges; e++) {
		scanf("%d\n", &a);
		scanf("%d\n", &b);
		scanf("%d\n", &cost);
		g.AddWeightedEdge(a, b, -cost);
	}
	g.kruskal();
	g.print();
	return 0;
}