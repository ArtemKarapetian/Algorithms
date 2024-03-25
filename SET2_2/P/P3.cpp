#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <climits>
#include <string> 

struct Edge {
    int u, v, weight;
};

void dfs(std::vector<std::vector<std::size_t> > &graph, std::vector<bool> &visited, const std::size_t &ind) {
    visited[ind] = true;
    for (const std::size_t& neighbour : graph[ind]) {
        if (!visited[neighbour]) {
            dfs(graph, visited, neighbour);
        }
    }
}

void bellmanFord(std::size_t n, std::vector<Edge> edges, std::vector<std::vector<std::size_t> > graph) {
    std::vector<long long> distance(n);
    for (std::size_t i = 0; i < n; i++) {
        distance[i] = LLONG_MAX; // Change INT64_MAX to LLONG_MAX
    }
    distance[0] = 0;

    for (std::size_t i = 0; i < n - 1; ++i) {
        for (const Edge& edge : edges) {
            if (distance[edge.u] != LLONG_MAX && distance[edge.u] + edge.weight < distance[edge.v]) {
                distance[edge.v] = distance[edge.u] + edge.weight;
            }
        }
    }

    std::vector<bool> checkForNegCycle(n);
    for (std::size_t i = 0; i < n; i++) {
        checkForNegCycle[i] = false;
    }
    for (const Edge& edge : edges) {
        if (distance[edge.u] != LLONG_MAX && distance[edge.u] + edge.weight < distance[edge.v]) {
            dfs(graph, checkForNegCycle, edge.v);
        }
    }

    for (std::size_t i = 1; i < n; ++i) {
        std::cout << (checkForNegCycle[i] || distance[i] == LLONG_MAX ? "-inf" : std::to_string(distance[i])) << std::endl;
    }
}

int main() {
    std::size_t n, m;
    std::cin >> n >> m;

    std::vector<Edge> edges(m);
    std::vector<std::vector<std::size_t> > graph(n);
    for (std::size_t i = 0; i < m; ++i) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        graph[edges[i].u].push_back(edges[i].v);
    }

    bellmanFord(n, edges, graph);
    return 0;
}