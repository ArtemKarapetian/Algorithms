#include <vector>
#include <iostream>

struct Edge {
    int u, v, weight;
};

std::vector<std::vector<int>> restoreGraph1(const std::vector<std::vector<int>>& adj) {
   int n = adj.size();
   std::vector<std::vector<int>> graph(n, std::vector<int>(n, -1));

   for (std::size_t i = 0; i < n; ++i) {
       for (std::size_t j = 0; j < n; ++j) {
           if (adj[i][j] != -1) {
               graph[i][j] = adj[i][j];
           }
       }
   }
   return graph;
}

std::vector<std::vector<int>> restoreGraph2(const std::vector<Edge>& edges) {
    std::size_t n = edges.size();
    std::size_t v = 0;
    for (std::size_t i = 0; i < n; ++i) {
        v = std::max(v, static_cast<std::size_t>(std::max(edges[i].u, edges[i].v)));
    }
    std::vector<std::vector<int>> graph(n, std::vector<int>(v + 1, -1));

    for (std::size_t i = 0; i <= v; ++i) {
        graph[i][i] = 0;
    }
    for (std::size_t i = 0; i < n; ++i) {
        graph[edges[i].u][edges[i].v] = edges[i].weight;
    }
    return graph;
}

int main() {
    std::vector<std::vector<int>> adj1 = {
        {0, 2, -1, 4},
        {2, 0, 1, -1},
        {-1, 1, 0, 3},
        {4, -1, 3, 0}
    };

    std::vector<std::vector<int>> graph1 = restoreGraph1(adj1);

    std::cout << "Restored Graph 1:" << std::endl;
    for (const auto& row : graph1) {
        for (const auto& weight : row) {
            std::cout << weight << " ";
        }
        std::cout << std::endl;
    }

    std::vector<Edge> edges = {
        {0, 1, 2},
        {1, 2, 1},
        {2, 3, 3},
        {3, 0, 4}
    };

    std::vector<std::vector<int>> graph2 = restoreGraph2(edges);

    std::cout << "Restored Graph 2:" << std::endl;
    for (const auto& row : graph2) {
        for (const auto& weight : row) {
            std::cout << weight << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
