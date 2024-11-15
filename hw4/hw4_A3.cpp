#include <bits/stdc++.h>
using namespace std;

mt19937 rng(77897179); // mygo

// fhq_treap
struct treap_node {
    char c;
    int priority, size;
    treap_node *left, *right;
    treap_node(char c) : c(c), priority(rng()), size(1), left(nullptr), right(nullptr) {}
};

int get_size(treap_node *node) { return node ? node->size : 0; }

void split(treap_node *node, treap_node *&left, treap_node *&right, int k) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    if (get_size(node->left) < k) {
        split(node->right, node->right, right, k - get_size(node->left) - 1);
        left = node;
    } else {
        split(node->left, left, node->left, k);
        right = node;
    }
    node->size = get_size(node->left) + get_size(node->right) + 1;
}

void merge(treap_node *&treap, treap_node *left, treap_node *right) {
    if (!left or !right) {
        treap = left ? left : right;
        return;
    }
    if (left->priority < right->priority) {
        merge(left->right, left->right, right);
        treap = left;
    } else {
        merge(right->left, left, right->left);
        treap = right;
    }
    treap->size = get_size(treap->left) + get_size(treap->right) + 1;
}

// treap ostream operator
ostream &operator<<(ostream &os, treap_node *node) {
    if (!node) return os;
    os << node->left;
    os << node->c;
    os << node->right;
    return os;
}

int main() {
    treap_node *root = nullptr;
    size_t str_len, operation_count;
    string str;
    cin >> str_len >> operation_count >> str;
    for (const auto &c : str) merge(root, root, new treap_node(c));
    while (operation_count--) {
        int l, r;
        cin >> l >> r;
        treap_node *a, *b, *c, *d;
        split(root, a, b, l - 1);
        split(b, c, d, r - l + 1);
        merge(root, a, d);
        merge(root, root, c);
    }
    cout << root << '\n';
}