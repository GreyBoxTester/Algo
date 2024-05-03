#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

struct Node
{
    std::vector<int> paths;
    int parent = -1;
    int distance = -1;
    bool v = false;
};

std::vector<Node> nodes;

void bfs(int s)
{
    std::queue<int> q;
    q.push(s);
    nodes[s].v = true;
    nodes[s].distance = 0;
    while (!q.empty())
    {
        int c = q.front();
        q.pop();
        for (int next : nodes[c].paths)
        {
            if (nodes[next].v) { continue; }
            nodes[next].v = true;
            nodes[next].parent = c;
            nodes[next].distance = nodes[c].distance + 1;
            q.push(next);
        }
    }
}

bool findPath(int s, int e, std::vector<int>& path)
{
    if (s == e) { return true; }
    bfs(s);
    if (nodes[e].distance == -1) { return false; }

    path.reserve(nodes[e].distance + 1);
    for (int c = e; c != -1; c = nodes[c].parent) { path.push_back(c); }
    std::reverse(path.begin(), path.end());
    return true;
}

/*int n = 0, m = 0;
    std::cin >> n >> m;
    nodes.resize(n);
    while (m--)
    {
        int a = 0, b = 0;
        std::cin >> a >> b;
        a--; b--;
        nodes[a].paths.push_back(b);
        nodes[b].paths.push_back(a);
    }*/

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);
    int n = 0;
    std::cin >> n;
    nodes.resize(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            bool v = 0;
            std::cin >> v;
            if (v) { nodes[i].paths.push_back(j); }
        }
    }

    int s = 0, e = 0;
    std::cin >> s >> e;
    s--; e--;
    std::vector<int> path;
    if (!findPath(s, e, path)) { std::cout << "-1"; return 0; }
    if (path.size() == 0) { std::cout << '0'; return 0; }
    std::cout << (path.size() - 1) << '\n';
    for (int i : path) { std::cout << (i + 1) << ' '; }
}
