#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>

struct Edge {
    int u, v, weight;
};

void printDistances(const std::vector<std::vector<long long> >& distances) {
    for (std::size_t i = 0; i < distances.size(); ++i) {
        for (std::size_t j = 0; j < distances[i].size(); ++j) {
            if (i == j) {
                continue;
            }
            if (distances[i][j] == LLONG_MAX) {
                std::cout << i << " " << j << " -1" << std::endl;
            } else {
                std::cout << i << " " << j << " " << distances[i][j] << std::endl;
            }
        }
    }
}

void wfi(const std::vector<Edge>& edges, int n) {
    std::vector<std::vector<long long> > distances(n, std::vector<long long>(n, LLONG_MAX));
    for (int i = 0; i < n; ++i) {
        distances[i][i] = 0;
    }

    for (const Edge& edge : edges) {
        distances[edge.u][edge.v] = edge.weight;
    }

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            for (std::size_t k = 0; k < n; ++k) {
                if (distances[j][i] != LLONG_MAX && distances[i][k] != LLONG_MAX 
                    && distances[j][i] + distances[i][k] < distances[j][k]) {
                    distances[j][k] = distances[j][i] + distances[i][k];
                }
            }
        }
    }

    printDistances(distances);
}

int main() {
    std::ifstream file("input.txt");
    int n, m;
    file >> n >> m;
    std::vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        file >> edges[i].u >> edges[i].v >> edges[i].weight;
    }
    wfi(edges, n);
    return 0;
}