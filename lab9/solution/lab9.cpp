#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>

bool DFS(int v, std::set<int>& used, std::vector<std::vector<int>>& graph, std::vector<int>& matching) {
    if (used.count(v)) {
        return false;
    }
    used.insert(v);
    for (int& elem : graph[v]) {
        if (matching[elem] == -1 || DFS(matching[elem], used, graph, matching)) {
            matching[elem] = v;
            return true;
        }
    }
    return false;
}

std::vector<std::pair<int, int>> KuhnAlgorithm(std::vector<std::vector<int>>& graph) {
    std::vector<int> matching(graph.size(), -1);
    std::set<int> used;
    for (int i = 0; i < graph.size(); ++i) {
        used.clear();
        DFS(i, used, graph, matching);
    }
    std::vector<std::pair<int, int>> answer;
    for (int i = 0; i < matching.size(); ++i) {
        if (matching[i] != -1) {
            answer.push_back(std::make_pair(std::min(i, matching[i]), std::max(i, matching[i])));
        }
    }
    std::sort(answer.begin(), answer.end(), [](std::pair<int, int> l, std::pair<int, int> r) { return l.first < r.first; });
    return answer;

}


std::vector<int> SplitForPart(std::vector<std::vector<int>>& graph) {
    std::vector<int> part(graph.size(), -1);
    std::vector<bool> used(graph.size(), false);
    std::queue<int> queue;
    for (int i = 0; i < graph.size(); ++i) {
        if (part[i] == -1) {
            part[i] = 0;
            queue.push(i);
            used[i] = true;
            while (!queue.empty()) {
                int curr = queue.front();
                queue.pop();
                int parent = curr;
                for (int j = 0; j < graph[curr].size(); ++j) {
                    if (part[graph[curr][j]] == -1 && !used[graph[curr][j]]) {
                        part[graph[curr][j]] = !part[parent];
                        used[graph[curr][j]] = true;
                        queue.push(graph[curr][j]);
                    }
                }
            }
        }
    }
    return part;

}

int main() {
    int n, m, begin, end;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n);

    for (int i = 0; i < m; ++i) {
        std::cin >> begin >> end;
        graph[begin - 1].push_back(end - 1);
        graph[end - 1].push_back(begin - 1);
    }
    std::vector<int> part = SplitForPart(graph);
    std::vector<std::vector<int>> biGraph(graph.size());
    for (size_t i = 0; i < graph.size(); ++i) {
        if (!graph[i].empty())
            std::sort(graph[i].begin(), graph[i].end());
    }
    for (int i = 0; i < graph.size(); ++i) {
        if (!part[i]) {
            biGraph[i] = graph[i];
        }
    }
    std::vector<std::pair<int, int>> result = KuhnAlgorithm(biGraph);
    std::cout << result.size() << '\n';
    for (const std::pair<int, int>& pair : result) {
        std::cout << pair.first + 1 << ' ' << pair.second + 1 << '\n';
    }
    return 0;
}