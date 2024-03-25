#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdint>

bool bfs(std::vector<std::vector<int> > &graph, std::vector<int> &parent){
    std::vector<bool> visited(graph.size(), false);
    visited[0] = true;

    std::queue<int> queue;
    queue.push(0);

    parent[0] = -1;
 
    while (!queue.empty()) {
        std::size_t u = queue.front();
        queue.pop();
 
        for (std::size_t v = 0; v < graph.size(); v++) {
            if (!visited[v] && graph[u][v] > 0) {
                queue.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}
 
int ff( std::vector<std::vector<int> >& graph)
{
    std::vector<int> parent(graph.size());
    int maxFlow = 0;
 
    while (bfs(graph, parent)) {
        int pathFlow = INT32_MAX;
        int u, v = graph.size() - 1;
        while (v) {
            u = parent[v];
            pathFlow = std::min(pathFlow, graph[u][v]);
            v = u;
        }
        v = v = graph.size() - 1;
        while (v) {
            u = parent[v];
            graph[u][v] -= pathFlow;
            graph[v][u] += pathFlow;
            v = u;
        }

        maxFlow += pathFlow;
    }
 
    return maxFlow;
}

int main() {
    int n, m;
    std::ifstream input("input.txt");
    input >> n >> m;

    std::vector<std::vector<int> > graph(n, std::vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        input >> u >> v >> c;
        u--;
        v--;
        graph[u][v] = c;
    }

    std::cout << ff(graph) << std::endl;
}