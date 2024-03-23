#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>

struct Path
{
    int next = 0;
    int dist = 0;
};

struct Node
{
    std::vector<Path> paths;
    int distance = std::numeric_limits<int>::max();
    int parent = -1;
    bool done = false;
};

std::vector<Node> nodes;

bool operator<(std::pair<int, int> a, std::pair<int, int> b)
{
    if (a.first == b.first) { return a.second < b.second; }
    return a.first < b.first;
}

void djkstra(int s)
{
    std::set<std::pair<int, int>> q;
    q.insert({ 0, s });
    nodes[s].distance = 0;
    nodes[s].done = true;
    while (!q.empty())
    {
        auto [dist, c] = *q.begin();
        q.erase(q.begin());
        nodes[c].done = true;
        for (auto& next : nodes[c].paths)
        {
            if (nodes[next.next].done) { continue; }
            int d = dist + next.dist;
            if (d >= nodes[next.next].distance) { continue; }

            auto it = q.find({ nodes[next.next].distance, next.next });
            if (it != q.end()) { q.erase(it); }
            nodes[next.next].distance = d;
            nodes[next.next].parent = c;
            q.insert({ d, next.next });
        }
    }
}

void alg()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    nodes.clear();
    nodes.resize(n);
    while (m--)
    {
        int a = 0, b = 0, v = 0;
        std::cin >> a >> b >> v;
        a--; b--;
        nodes[a].paths.push_back({ b, v });
        nodes[b].paths.push_back({ a, v });
    }

    int s = 0;
    std::cin >> s;
    djkstra(s);
    for (auto& node : nodes) { std::cout << node.distance << ' '; }
    std::cout << '\n';
}

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);
    int n = 0;
    std::cin >> n;
    while (n--) { alg(); }
}
