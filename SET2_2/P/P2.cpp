#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>

std::vector<std::pair<int, int> > parentRank;
std::vector<std::size_t> minGraph;

void makeSet(int v) {
    parentRank[v] = std::make_pair(v, 0);
}

int findSet(int v) {
    if (v == parentRank[v].first) {
        return v;   
    }
    return parentRank[v].first = findSet(parentRank[v].first);
}

void unionSet(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a == b) {
        return;
    }
    if (parentRank[a].second < parentRank[b].second) {
        std::swap(a, b);
    }
    parentRank[b].first = a;
    if (parentRank[a].second == parentRank[b].second) {
        parentRank[a].second++;
    }
}

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

int kruskalNoSortWithSkip(std::vector<Edge> &edges, int n, int skip) {
    int cost = 0, unionCounter = 1;
    parentRank.resize(n);
    for (int i = 0; i < n; i++) {
        makeSet(i);
    }

    for (std::size_t i = 0; i < edges.size() && unionCounter != n; i++) {
        if (i == skip) {
            continue;
        }
        if (findSet(edges[i].u) == findSet(edges[i].v)) {
            continue;
        }
        unionSet(edges[i].u, edges[i].v);
        cost += edges[i].weight;
        unionCounter++;
        if (INT32_MAX == skip) {
            minGraph.push_back(i);
        }
    }
    if (unionCounter != n) {
        return INT32_MAX;
    }
    return cost;
}

int kruskal(std::vector<Edge> &edges, int n) {
    sort(edges.begin(), edges.end());
    return kruskalNoSortWithSkip(edges, n, INT32_MAX);
}

int findSecondKruskal(std::vector<Edge> &edges, int n) {
    int minimum = INT32_MAX;
    for (const std::size_t& i : minGraph) {
        minimum = std::min(minimum, kruskalNoSortWithSkip(edges, n, i));
    }
    return minimum;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges(m);
    for (std::size_t i = 0; i < m; i++) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        edges[i].u--;
        edges[i].v--;
    }
    std::cout << kruskal(edges, n) << " " << findSecondKruskal(edges, n);
}