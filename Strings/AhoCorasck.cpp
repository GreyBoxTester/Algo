#include <vector>
#include <string>
#include <memory>

using i64 = int64_t;

class AhoCorasick
{
public:
    struct Node
    {
        std::unique_ptr<Node> next[26] = {};
        Node* go[26] = {};
        Node* link = nullptr;
        Node* p = nullptr;
        i64 cnt = -1;
        bool term = false;
        char pc = 0;

        Node() {}
        Node(Node* p, char pc) : p(p), pc(pc) {}
    };

    void add(const std::string& s)
    {
        Node* nd = &root;
        for (char c : s)
        {
            auto& next = nd->next[c - 'a'];
            if (!next) { next.reset(new Node(nd, c)); }
            nd = next.get();
        }
        nd->term = true;
    }

    Node* link(Node* nd)
    {
        if (nd->link) { return nd->link; }
        if (nd == &root || nd->p == &root) { return nd->link = &root; }
        return nd->link = go(link(nd->p), nd->pc);
    }

    Node* go(Node* nd, char c)
    {
        if (nd->go[c - 'a']) { return nd->go[c - 'a']; }
        if (nd->next[c - 'a']) { return nd->go[c - 'a'] = nd->next[c - 'a'].get(); }
        if (nd == &root) { return nd->go[c - 'a'] = &root; }
        return nd->go[c - 'a'] = go(link(nd), c);
    }

    i64 cnt(Node* nd)
    {
        if (nd->cnt != -1) { return nd->cnt; }
        if (nd == &root) { return 0; }
        return nd->cnt = nd->term + cnt(link(nd));
    }

    void clear()
    {
        root = Node();
    }

public:
    Node root;
};


class DynamicAhoCorasick
{
public:
    void add(std::string s)
    {
        std::vector<std::string> str;
        str.push_back(std::move(s));

        i64 i = 0;
        for (; i < p.size() && !p[i].first.empty(); i++)
        {
            for (auto& si : p[i].first) { str.push_back(std::move(si)); }
            p[i].first.clear();
            p[i].second.clear();
        }
        if (i == p.size()) { p.push_back({}); }

        for (auto& si : str) { p[i].second.add(si); }
        p[i].first.swap(str);
    }

    i64 cnt(const std::string& s)
    {
        i64 cnt = 0;
        for (auto& [w, ac] : p)
        {
            if (w.empty()) { continue; }

            auto* st = &ac.root;
            for (char c : s)
            {
                st = ac.go(st, c);
                cnt += ac.cnt(st);
            }
        }
        return cnt;
    }

private:
    std::vector<std::pair<std::vector<std::string>, AhoCorasick>> p;
};
