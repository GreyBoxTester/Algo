#include <vector>
#include <map>
#include <string>
#include <algorithm>

using i64 = int64_t;

class SuffixAutomaton
{
public:
    struct Node
    {
        std::map<char, Node*> next;
        Node* link = nullptr;
        i64 len = 0;
        i64 szep = 0;
    };
public:
    void extend(const std::string& s)
    {
        for (char c : s) { extend(c); }
    }

    void extend(char c)
    {
        Node* curr = new Node();
        curr->len = prev->len + 1;
        curr->szep = 1;
        ord.push_back(curr);

        Node* p = prev;
        for (; p && !p->next.contains(c); p = p->link) { p->next[c] = curr; }

        if (!p)
        {
            curr->link = &root;
            prev = curr;
            return;
        }
        Node* q = p->next[c];
        if (p->len + 1 == q->len)
        {
            curr->link = q;
            prev = curr;
            return;
        }

        Node* clone = new Node();
        clone->next = q->next;
        clone->link = q->link;
        clone->len = p->len + 1;
        for (; p && p->next[c] == q; p = p->link) { p->next[c] = clone; }
        curr->link = q->link = clone;

        ord.push_back(clone);

        prev = curr;
    }

    void szep()
    {
        std::sort(ord.begin(), ord.end(), [](const Node* a, const Node* b) { return a->len > b->len; });
        for (Node* node : ord)
        {
            node->link->szep += node->szep;
        }
    }

public:
    Node root;
    Node* prev = &root;
    std::vector<Node*> ord;
};
