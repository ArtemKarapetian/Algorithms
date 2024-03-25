#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

std::stack<std::size_t> stack;
// std::ifstream std::cin("input.txt");

void dfs(const std::vector<std::vector<std::size_t> > &graph, std::vector<bool> &visited, std::size_t index, bool addComponent, std::vector<std::size_t> &component) {
    visited[index] = true;
    for (const std::size_t& neighborInd : graph[index]) {
        if (visited[neighborInd]) {
            continue;
        }
        dfs(graph, visited, neighborInd, addComponent, component);
    }
    if (addComponent) {
        component.push_back(index);
    } else {
        stack.push(index);
    }
}

void fillGraph(std::vector<std::vector<std::size_t> > &graph, std::vector<std::vector<std::size_t> >& reversedGraph, int m) {
    for (int i = 0; i < m; ++i) {
        std::size_t a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        reversedGraph[b].push_back(a);
    }
}

std::vector<std::vector<std::size_t> > searchSCC(int n, int m) {
    std::vector<std::vector<std::size_t> > graph(n + 1), reversedGraph(n + 1);
    fillGraph(graph, reversedGraph, m);
    
    std::vector<bool> visited(n + 1);
    for (std::size_t i = 0; i <= n; ++i) {
        visited[i] = false;
    }
    std::vector<std::size_t> blank;
    for (std::size_t i = 1; i <= n; ++i) {
        if (visited[i]) {
            continue;
        }
        dfs(graph, visited, i, false, blank);
    }

    for (std::size_t i = 0; i <= n; ++i) {
        visited[i] = false;
    }
    std::vector<std::vector<std::size_t> > scc;
    while (!stack.empty()) {
        std::size_t current = stack.top();
        stack.pop();
        if (visited[current]) {
            continue;
        }
        std::vector<std::size_t> component;
        dfs(reversedGraph, visited, current, true, component);
        scc.push_back(component);
    }
    return scc;
}

void showSCC(const std::vector<std::vector<std::size_t> > &scc, int n) {
    std::cout << scc.size() << "\n";
    std::vector<std::size_t> sorted(n + 1);
    for (std::size_t i = 0; i < scc.size(); ++i) {
        for (std::size_t j = 0; j < scc[i].size(); ++j) {
            sorted[scc[i][j]] = i;
        }
    }
    for (std::size_t i = 1; i < sorted.size(); ++i) {
        std::cout << sorted[i] + 1 << " ";
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;


    std::vector<std::vector<std::size_t> > scc = searchSCC(n, m);
    showSCC(scc, n);

    return 0;
}