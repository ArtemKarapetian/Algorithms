#include <vector>

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};
// ALG_1


class GraphInterface1 {
public:
    virtual void removeEdge(int u, int v) = 0;
    virtual bool isConnected(int u, int v) = 0;
    virtual bool dfs(int u, int v, std::vector<bool>& visited) = 0;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> adj;
};

// ALG_2

class DisjointSetInterface2 {
public:
    virtual void makeSet(int v) = 0;
    virtual int findSet(int v) = 0;
    virtual void unionSets(int a, int b) = 0;
};

class GraphInterface2 {
public:
    virtual void addEdge(int u, int v, int weight) = 0;
    std::vector<Edge> edgesVector;
    std::vector<std::pair<int, int> > edges;
};

// ALG_3

class GraphInterface3 {
public:
    virtual void addEdge(int u, int v, int weight) = 0;
    virtual void removeEdge(int u, int v) = 0;
    virtual void dfs(int u) = 0;
    std::vector<Edge> edges;
    std::vector<std::vector<int> > adj;
};