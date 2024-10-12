#include <string>
#include <map>
#include <memory>


class SuffixTree
{
public:
    struct Node
    {
        std::map<char, std::unique_ptr<Node>> next;
        Node* link = nullptr;
        Node* p = nullptr;
        size_t l = 0;
        size_t r = 0;

        Node() = default;
        Node(Node* p, size_t l, size_t r) : p(p), l(l), r(r) {}
        size_t len() { return r - l; }
    };

    struct State
    {
        Node* nd = nullptr;
        size_t ind = 0;

        State() = default;
        State(Node* nd) : nd(nd), ind(nd ? nd->len() : 0) {}
        State(Node* nd, size_t ind) : nd(nd), ind(ind) {}

        bool onEdge() const { return 0 < ind && ind < nd->len(); }
        bool inParent() const { return ind == 0 && nd->len() != 0; }
        bool inNode() const { return ind == nd->len(); }
        operator bool() { return nd; }
    };
public:
    SuffixTree(std::string str)
    {
        s = std::move(str);
        s += '$';

        State st = &root;
        for (size_t i = 0; i < s.size(); i++)
        {
            while (true)
            {
                State nst = go(st, i, i + 1);
                if (nst) { st = nst; break; }

                Node* nn = split(st);
                nn->next[s[i]].reset(new Node(nn, i, s.size()));

                st = link(nn);
                if (nn == &root) { break; }
            }
        }
    }

    State go(State st, char c)
    {
        if (st.inNode())
        {
            if (!st.nd->next.contains(c)) { return nullptr; }
            return State(st.nd->next[c].get(), 1);
        }
        else
        {
            if (s[st.nd->l + st.ind] != c) { return nullptr; }
            st.ind++;
            return st;
        }
    }

    State go(State st, size_t l, size_t r)
    {
        while (l < r)
        {
            if (st.inNode())
            {
                if (!st.nd->next.contains(s[l])) { return nullptr; }
                st.nd = st.nd->next[s[l]].get();
                st.ind = 0;
            }

            if (s[st.nd->l + st.ind] != s[l]) { return nullptr; }
            size_t step = std::min(st.nd->len() - st.ind, r - l);
            st.ind += step;
            l += step;
        }
        return st;
    }

    Node* split(State st)
    {
        if (st.inNode()) { return st.nd; }
        if (st.inParent()) { return st.nd->p; }
        Node* p = st.nd->p;
        Node* n = st.nd;
        Node* c = new Node(p, n->l, n->l + st.ind);
        n->l += st.ind;
        n->p = c;
        p->next[s[c->l]].release();
        p->next[s[c->l]].reset(c);
        c->next[s[n->l]].reset(n);
        return c;
    }

    Node* link(Node* nd)
    {
        if (nd->link) { return nd->link; }
        if (nd == &root) { return nd->link = &root; }
        return nd->link = split(go(link(nd->p), nd->l + (nd->p == &root), nd->r));
    }

    State link(State st)
    {
        if (st.inNode()) { return link(st.nd); }
        if (st.inParent()) { return link(st.nd->p); }
        return go(link(st.nd->p), st.nd->p->l, st.nd->p->l + st.ind);
    }
public:
    Node root = {};
    std::string s;
};