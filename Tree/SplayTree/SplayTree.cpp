#include <cstdint>
#include <utility>

using i64 = int64_t;

struct SplayTreeNode
{
    SplayTreeNode* l = nullptr;
    SplayTreeNode* r = nullptr;
    SplayTreeNode* p = nullptr;
    i64 val = 0;
};


void rotl(SplayTreeNode* x)
{
    SplayTreeNode* p = x->p;
    SplayTreeNode* g = p->p;
    SplayTreeNode* b = x->l;

    x->p = g; x->l = p;
    p->p = x; p->r = b;
    if (b) { b->p = p; }
    if (g) { (g->l == p ? g->l : g->r) = x; }
}

void rotr(SplayTreeNode* x)
{
    SplayTreeNode* p = x->p;
    SplayTreeNode* g = p->p;
    SplayTreeNode* b = x->r;

    x->p = g; x->r = p;
    p->p = x; p->l = b;
    if (b) { b->p = p; }
    if (g) { (g->l == p ? g->l : g->r) = x; }
}

void zig(SplayTreeNode* x)
{
    if (x->p->l == x) { rotr(x); }
    else { rotl(x); }
}

void zigzig(SplayTreeNode* x)
{
    if (x->p->l == x) { rotr(x->p); rotr(x); }
    else { rotl(x->p); rotl(x); }
}

void zigzag(SplayTreeNode* x)
{
    if (x->p->l == x) { rotr(x); rotl(x); }
    else { rotl(x); rotr(x); }
}

void splay(SplayTreeNode* x)
{
    while (x->p)
    {    
        SplayTreeNode* p = x->p;
        SplayTreeNode* g = p->p;
        if (g == nullptr) { zig(x); }
        else if (g->l == p && p->l == x || g->r == p && p->r == x) { zigzig(x); }
        else { zigzag(x); }
    }
}

//lower bound. does nothing if all elements are less than val
SplayTreeNode* find(SplayTreeNode* t, i64 val)
{
    SplayTreeNode* x = t;
    while (x->val != val)
    {
        if (x->l && val < x->val) { x = x->l; }
        else if (x->r && x->val < val) { x = x->r; }
        else { break; }
    }
    if (x->val < val) { return t; }
    splay(x);
    return x;
}

SplayTreeNode* merge(SplayTreeNode* t1, SplayTreeNode* t2)
{
    if (!t1) { return t2; }
    if (!t2) { return t1; }
    while (t1->r) { t1 = t1->r; }
    splay(t1);
    t1->r = t2;
    t2->p = t1;
    return t1;
}

std::pair<SplayTreeNode*, SplayTreeNode*> split(SplayTreeNode* t, i64 val)
{
    if (!t) { return { nullptr, nullptr }; }
    t = find(t, val);
    if (t->val < val) { return { t, nullptr }; }
    SplayTreeNode* t1 = t->l;
    t->l = nullptr;
    if (t1) { t1->p = nullptr; }
    return { t1, t };
}

SplayTreeNode* insert(SplayTreeNode* t, i64 val)
{
    auto [t1, t2] = split(t, val);
    SplayTreeNode* e = new SplayTreeNode{ .val = val };
    return merge(t1, merge(e, t2));
}

void destroy(SplayTreeNode* t)
{
    if (!t) { return; }
    destroy(t->l);
    destroy(t->r);
    delete t;
}

SplayTreeNode* erase(SplayTreeNode* t, i64 val)
{
    auto [t1, tt] = split(t, val);
    auto [m, t2]  = split(tt, val + 1);
    destroy(m);
    return merge(t1, t2);
}

void iterate(SplayTreeNode* t, const auto& func)
{
    if (!t) { return; }
    iterate(t->l, func);
    func(t);
    iterate(t->r, func);
}
