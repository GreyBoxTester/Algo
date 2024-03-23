#include <cstdint>
#include <utility>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

struct TreapNode
{
    i64 key, priority;
    TreapNode* l = nullptr;
    TreapNode* r = nullptr;
};

std::pair<TreapNode*, TreapNode*> split(TreapNode* t, i64 key)
{
    if (!t) { return { nullptr, nullptr }; }

    if (t->key < key)
    {
        auto [t1, t2] = split(t->r, key);
        t->r = t1;
        return { t, t2 };
    }
    else
    {
        auto [t1, t2] = split(t->l, key);
        t->l = t2;
        return { t1, t };
    }
}

TreapNode* merge(TreapNode* t1, TreapNode* t2)
{
    if (!t1) { return t2; }
    if (!t2) { return t1; }

    if (t1->priority > t2->priority)
    {
        t1->r = merge(t1->r, t2);
        return t1;
    }
    else
    {
        t2->l = merge(t1, t2->l);
        return t2;
    }
}

void destroy(TreapNode* t)
{
    if (t == nullptr) { return; }
    destroy(t->l);
    destroy(t->r);
    delete t;
}

TreapNode* insert(TreapNode* t, i64 key)
{
    auto [l, r] = split(t, key);
    TreapNode* element = new TreapNode{ key, rand() };
    return merge(merge(l, element), r);
}

TreapNode* erase(TreapNode* t, i64 key)
{
    auto [l, t1] = split(t, key);
    auto [m, r] = split(t1, key + 1);
    destroy(m);
    return merge(l, r);
}

template<typename F>
void iterate(TreapNode* t, F&& func)
{
    if (t == nullptr) { return; }
    iterate(t->l, std::forward<F>(func));
    func(t);
    iterate(t->r, std::forward<F>(func));
}
