#include <vector>
#include <cstdint>
#include <cassert>

using i64 = int64_t;

struct Node
{
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    Node* pp = nullptr;
    i64 size = 1, val = 0;
    bool rev = false;
};

i64 size(Node* x) { return x ? x->size : 0; }
void rev(Node* x) { if (x) { x->rev ^= 1; } }

void upd(Node* x) 
{
    if (!x) { return; }
    x->size = 1 + size(x->l) + size(x->r); 
}

void push(Node* x) 
{
    if (!x || !x->rev) { return; }
    x->rev = false;
    std::swap(x->l, x->r);
    rev(x->l);
    rev(x->r);
}

void rot(Node* x)
{
    Node* p = x->p;
    Node* g = p->p;
    
    push(p);
    push(x);

    if (p->r == x) //rotl (edge totates left around x)
    {
        Node* b = x->l;
        x->p = g; x->l = p;
        p->p = x; p->r = b;
        if (b) { b->p = p; }
        if (g) { (g->l == p ? g->l : g->r) = x; }
    }
    else //rotr
    {
        Node* b = x->r;
        x->p = g; x->r = p;
        p->p = x; p->l = b;
        if (b) { b->p = p; }
        if (g) { (g->l == p ? g->l : g->r) = x; }
    }

    std::swap(x->pp, p->pp);
 
    upd(p);
    upd(x);
}
 
void splay(Node* x)
{
    while (x->p)
    {
        Node* p = x->p;
        Node* g = p->p;
        if (g == nullptr) { rot(x); }
        else if (g->l == p && p->l == x || g->r == p && p->r == x) { rot(p); rot(x); }
        else { rot(x); rot(x); }
    }
}
 
bool find(Node*& t, i64 ind)
{
    Node* x = t;
    while (x)
    {
        push(x);
        if (size(x->l) == ind) { break; }
        else if (size(x->l) < ind) { ind -= size(x->l) + 1; x = x->r; }
        else { x = x->l; }
    }
 
    if (!x) { return false; }
    splay(x);
    t = x;
    return true;
}

//=== link cut ===

void swapRightChild(Node* t, Node* c)
{
    push(t);
    if (t->r)
    {
        t->r->p = nullptr;
        t->r->pp = t;
    }
    t->r = c;
    if (c)
    { 
        c->p = t;
        c->pp = nullptr;
    }
    upd(t);
}

//make path start in v and end in tree root
Node* expose(Node* v)
{
    Node* u = v;
    splay(u);
    swapRightChild(u, nullptr);
    while (Node* pp = u->pp)
    {
        splay(pp);
        swapRightChild(pp, u);
        u = pp;
    }
    splay(v);
    return u;
}

void reroot(Node* v)
{
    expose(v);
    rev(v);
    push(v);
}

Node* findRoot(Node* v)
{
    expose(v);
    find(v, 0);
    return v;
}

bool connected(Node* u, Node* v)
{
    return findRoot(u) == findRoot(v);
}

void link(Node* u, Node* v)
{
    assert(!connected(u, v));
    reroot(u);
    u->pp = v;
}

void cut(Node* u, Node* v)
{
    reroot(u);
    expose(v);
    splay(u);
    assert(v->p == u);
    swapRightChild(u, nullptr);
    v->pp = nullptr;
}

/*void link(Node* u, Node* v)
{
    u->pp = v;
}

void cut(Node* u)
{
    if (u->p)
    {    
        splay(u->p);
        swapRightChild(u->p, nullptr);
    }
    u->pp = nullptr;
}*/

Node* lca(Node* u, Node* v)
{
    expose(u);
    return expose(v);
}

class NodeMap
{
public:
    NodeMap(i64 n) : nodes(n) {}
    Node* getNode(i64 i) { return &nodes[i]; }
    i64 getInd(Node* v) { return v - nodes.data(); }
    template<typename Func, typename... Args> 
    auto call(Func&& func, Args&&... args)
    {
        using RetType = decltype(func(getNode(std::forward<Args>(args))...));
        if constexpr (std::is_same<RetType, void>::value)
        {
            func(getNode(std::forward<Args>(args))...);
        }
        else
        {
            return getInd(func(getNode(std::forward<Args>(args))...));
        }
    }
private:
    std::vector<Node> nodes;
};
