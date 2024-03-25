#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <string>

using namespace std;

int digitSum(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

vector<int> neighbors(int num, int n) {
    vector<int> result;
    string numStr = to_string(num);
    for (int i = 1; i <= numStr.length(); ++i) {
        for (int j = 0; j < i; ++j) {
            int substr = stoi(numStr.substr(j, i - j));
            if (num + substr <= n) {
                result.push_back(num + substr);
            }
            if (num - substr > 0) {
                result.push_back(num - substr);
            }
        }
    }
    return result;
}

struct Compare {
    bool operator()(const pair<int, long long> &p1, const pair<int, long long> &p2) const {
        return p1.second > p2.second;
    }
};

vector<int> dijkstra(int start, int goal, int n) {
    priority_queue<pair<int, long long>, vector<pair<int, long long>>, Compare> openSet;
    unordered_map<int, int> cameFrom;
    unordered_map<int, long long> sumCost;
    vector<bool> visited(n + 1, false);

    openSet.emplace(start, 0);
    sumCost[start] = 0;

    while (!openSet.empty()) {
        int v = openSet.top().first;
        if (visited[v]) {
            openSet.pop();
            continue;
        }
        openSet.pop();
        visited[v] = true;

        for (int neighbor: neighbors(v, n)) {
            if (!visited[neighbor] && (sumCost.find(neighbor) == sumCost.end() ||
                                       sumCost[neighbor] > sumCost[v] + digitSum(abs(neighbor - v)))) {
                cameFrom[neighbor] = v;
                sumCost[neighbor] = sumCost[v] + digitSum(abs(neighbor - v));
                openSet.emplace(neighbor, sumCost[neighbor]);
            }
        }
    }

    if (sumCost.find(goal) == sumCost.end()) {
        return {};
    } else {
        vector<int> path;
        int tmp = goal;
        while (cameFrom.find(tmp) != cameFrom.end()) {
            path.push_back(tmp);
            tmp = cameFrom[tmp];
        }
        path.push_back(start);
        cout << sumCost[goal] << "\n";
        return path;
    }
}

void printPath(const vector<int> &path) {
    cout << path.size() - 1 << "\n";
    for (int i = path.size() - 2; i >= 0; --i) {
        if (path[i] - path[i + 1] > 0) {
            cout << '+';
        }
        cout << path[i] - path[i + 1] << "\n";
    }
}

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    vector<int> path = dijkstra(a, b, n);
    if (!path.empty()) {
        printPath(path);
    } else {
        cout << -1;
    }

    return 0;
}