#include <utility>
#include <random>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

struct TreapNode
{
    i64 size, priority, val;
    TreapNode* l = nullptr;
    TreapNode* r = nullptr;
};

i64 size(TreapNode* t) { return t ? t->size : 0; }

void upd(TreapNode* t) { t->size = 1 + size(t->l) + size(t->r); }

std::pair<TreapNode*, TreapNode*> split(TreapNode* t, i64 k)
{
    if (!t) { return { nullptr, nullptr }; }

    if (size(t->l) + 1 <= k)
    {
        auto [t1, t2] = split(t->r, k - size(t->l) - 1);
        t->r = t1;
        upd(t);
        return { t, t2 };
    }
    else
    {
        auto [t1, t2] = split(t->l, k);
        t->l = t2;
        upd(t);
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
        upd(t1);
        return t1;
    }
    else
    {
        t2->l = merge(t1, t2->l);
        upd(t2);
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

i64 randomPriority()
{
    static std::mt1993764 re((std::random_device())());
    return std::uniform_int_distribution<i64>()(re);
}

TreapNode* insert(TreapNode* t, i64 i, i64 val)
{
    auto [l, r] = split(t, i);
    TreapNode* element = new TreapNode{ 1, randomPriority(), val };
    return merge(merge(l, element), r);
}

TreapNode* erase(TreapNode* t, i64 i)
{
    auto [l, t1] = split(t, i);
    auto [m, r] = split(t1, 1);
    destroy(m);
    return merge(l, r);
}

std::pair<TreapNode*, TreapNode*> cut(TreapNode* t, i64 l, i64 r)
{
    auto [t1, rt] = split(t, r);
    auto [lt, m] = split(t1, l);
    return { merge(lt, rt), m };
}

TreapNode* insert(TreapNode* t1, TreapNode* t2, i64 i)
{
    auto [lt, rt] = split(t1, i);
    return merge(merge(lt, t2), rt);
}

void iterate(TreapNode* t, auto&& func)
{
    if (t == nullptr) { return; }
    iterate(t->l, func);
    func(t);
    iterate(t->r, func);
}