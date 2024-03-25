#include <climits>
#include <iostream>
#include <vector>
#include <queue>


struct Edge {
   std::size_t u, v;
   double weight;
};


struct FirstGreater {
   bool operator()(const std::pair<double, std::size_t>& lhs, const std::pair<double, std::size_t>& rhs) const {
       return lhs.first > rhs.first;
   }
};


std::vector<double> DijkstraMULT(std::vector<std::vector<Edge>> &graph, std::size_t start) {
    std::size_t n = graph.size();
    std::vector<double> distances(n, 0);
    distances[start] = 1;
    std::priority_queue<std::pair<double, std::size_t>, std::vector<std::pair<double, std::size_t>>, FirstGreater> pq;
    pq.emplace(1, start);

    while (!pq.empty()) {
        std::size_t cur = pq.top().second;
        double distCur = pq.top().first;
        pq.pop();
        if (distances[cur] && distCur > distances[cur]) {
            continue;
        }
        for (const Edge &edge: graph[cur]) {
            if (distances[edge.v] && distances[cur] * edge.weight >= distances[edge.v]) {
                continue;
            }
            distances[edge.v] = distances[cur] * edge.weight;
            pq.emplace(distances[cur] * edge.weight, edge.v);
        }
    }

    return distances;
}

int main() {
    std::vector<std::vector<Edge>> graph(5);
    graph[0].push_back({0, 1, 8.5});
    graph[0].push_back({0, 2, 2.8});
    graph[1].push_back({1, 2, 3.2});
    graph[1].push_back({1, 3, 4.9});
    graph[2].push_back({2, 3, 5.4});
    graph[2].push_back({2, 4, 2.6});
    graph[3].push_back({3, 4, 1.3});

    std::vector<double> result = DijkstraMULT(graph, 0);

    for (std::size_t i = 0; i < result.size(); i++) {
        std::cout << "Distance from vertex 0 to vertex " << i << ": " << result[i] << std::endl;
    }
}