#include <cstdint>
#include <utility>

using i64 = int64_t;

struct SplayTreeNode
{
    SplayTreeNode* l = nullptr;
    SplayTreeNode* r = nullptr;
    SplayTreeNode* p = nullptr;
    i64 size = 1, val = 0;
};

i64 size(SplayTreeNode* x) { return x ? x->size : 0; }

void upd(SplayTreeNode* x) 
{
    if (!x) { return; }
    x->size = 1 + size(x->l) + size(x->r); 
}

void push(SplayTreeNode* x) {}

void rot(SplayTreeNode* x)
{
    SplayTreeNode* p = x->p;
    SplayTreeNode* g = p->p;

    if (p->r == x) //rotl (edge totates left around x)
    {
        SplayTreeNode* b = x->l;
        x->p = g; x->l = p;
        p->p = x; p->r = b;
        if (b) { b->p = p; }
        if (g) { (g->l == p ? g->l : g->r) = x; }
    }
    else //rotr
    {
        SplayTreeNode* b = x->r;
        x->p = g; x->r = p;
        p->p = x; p->l = b;
        if (b) { b->p = p; }
        if (g) { (g->l == p ? g->l : g->r) = x; }
    }

    upd(p);
    upd(x);
}

void splay(SplayTreeNode* x)
{
    while (x->p)
    {    
        SplayTreeNode* p = x->p;
        SplayTreeNode* g = p->p;
        if (g == nullptr) { rot(x); }
        else if (g->l == p && p->l == x || g->r == p && p->r == x) { rot(p); rot(x); }
        else { rot(x); rot(x); }
    }
}

bool find(SplayTreeNode*& t, i64 ind)
{
    SplayTreeNode* x = t;
    while (x)
    {
        if (size(x->l) == ind) { break; }
        else if (size(x->l) < ind) { ind -= size(x->l) + 1; x = x->r; }
        else { x = x->l; }
    }

    if (!x) { return false; }
    splay(x);
    t = x;
    return true;
}

SplayTreeNode* merge(SplayTreeNode* t1, SplayTreeNode* t2)
{
    if (!t1) { return t2; }
    if (!t2) { return t1; }
    push(t1);
    push(t2);
    while (t1->r) { t1 = t1->r; }
    splay(t1);
    t1->r = t2;
    t2->p = t1;
    upd(t1);
    return t1;
}

std::pair<SplayTreeNode*, SplayTreeNode*> split(SplayTreeNode* t, i64 ind)
{
    if (!t) { return { nullptr, nullptr }; } ;
    if (!find(t, ind)) { return { t, nullptr }; }
    push(t);
    SplayTreeNode* t1 = t->l;
    t->l = nullptr;
    if (t1) { t1->p = nullptr; }
    upd(t);
    return { t1, t };
}

void insert(SplayTreeNode*& t, i64 ind, i64 val)
{
    auto [t1, t2] = split(t, ind);
    SplayTreeNode* e = new SplayTreeNode{ .val = val };
    t = merge(t1, merge(e, t2));
}

void insert(SplayTreeNode*& t1, SplayTreeNode* t2, i64 ind)
{
    auto [tl, tr] = split(t1, ind);
    t1 = merge(t1, merge(t2, tr));
}

auto apply(SplayTreeNode*& t, i64 l, i64 r, auto&& func) -> decltype(func(t))
{
    auto [tt, t2] = split(t, r);
    auto [t1, m]  = split(tt, l);
    if constexpr (std::is_same_v<decltype(func(t)), void>)
    {
        func(m);
        t = merge(merge(t1, m), t2);
    }
    else
    {
        auto val = func(m);
        t = merge(merge(t1, m), t2);
        return val;
    }
}

void destroy(SplayTreeNode* t)
{
    if (!t) { return; }
    destroy(t->l);
    destroy(t->r);
    delete t;
}

void erase(SplayTreeNode*& t, i64 ind)
{
    auto [t1, tt] = split(t, ind);
    auto [m, t2]  = split(tt, 1);
    destroy(m);
    t = merge(t1, t2);
}

void iterate(SplayTreeNode* t, const auto& func)
{
    if (!t) { return; }
    iterate(t->l, func);
    func(t);
    iterate(t->r, func);
}
