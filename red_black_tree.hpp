#pragma once

#include <iomanip>
#include <functional>
#include <string>
#include <sstream>
#include <valarray>

#ifdef DEBUG
#include <map>
#include <unordered_set>
#endif

enum class node_color
{
    black,
    red
};

template<class T>
struct _rb_tree_node
{
    size_t uniq_id;
    enum node_color color = node_color::red;

    _rb_tree_node<T> *parent = nullptr;
    _rb_tree_node<T> *left_child = nullptr;
    _rb_tree_node<T> *right_child = nullptr;

    T data;

    _rb_tree_node(T data, size_t uniq_id)
        : data(data), uniq_id(uniq_id)
    {};
};

template<class T>
struct node_with_depth
{
    _rb_tree_node<T> *node;
    size_t depth;
};

template<class T>
class red_black_tree
{
private:
    _rb_tree_node<T> *root = nullptr;
    size_t tree_size = 0;
    size_t uniq_id_cnt = 0;

public:
    ///@param cmpr - compare function, should return negative value if a < b, positive if a > b, 0 if a == b. Use a - b if possible.
    void add(T data, std::function<int(const T &, const T &)> cmpr);

    size_t get_height() const;

    T *find(const T &data, std::function<bool(const T &, const T &)> cmpr) const;

    void clear();

    std::string to_string() const;

    std::string to_html() const;

    ~red_black_tree()
    { clear(); }

#ifdef DEBUG
    bool inf_loop_check() const;
#endif

private:

    void insert_fixup(_rb_tree_node<T> *node);

    void rotate_left(_rb_tree_node<T> *P);

    void rotate_right(_rb_tree_node<T> *P);

    _rb_tree_node<T> *next_preorder(_rb_tree_node<T> *node) const;

    node_with_depth<T> next_preorder(node_with_depth<T> node_w_depth) const;

    _rb_tree_node<T> *next_inorder(_rb_tree_node<T> *node) const;

    _rb_tree_node<T> *find_node(const T &data, std::function<int(const T &, const T &)> cmpr) const;

    ///@brief cases from: https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Insertion
    int insert_case(_rb_tree_node<T> *node) const;
};

#ifdef DEBUG
    template<class T>
    bool _inf_loop_check(_rb_tree_node<T> *node, std::unordered_set<_rb_tree_node<T>*> &hashset){
        auto *lc = node->left_child;
        auto *rc = node->right_child;

        hashset.insert(node);

        if(lc && hashset.find(node->left_child) != hashset.end()) return true;
        if(rc && hashset.find(node->right_child) != hashset.end()) return true;

        if(lc && _inf_loop_check(lc, hashset)) return true;
        if(rc && _inf_loop_check(rc, hashset)) return true;
        return false;
    }

    template<class T>
    bool red_black_tree<T>::inf_loop_check() const
    {
        auto hashset = std::unordered_set<_rb_tree_node<T>*>{};
        if(_inf_loop_check(root, hashset)) return true;

        return false;
    }

#endif

template<class T>
int red_black_tree<T>::insert_case(_rb_tree_node<T> *node) const
{
    _rb_tree_node<T> *P = node->parent;
    _rb_tree_node<T> *G = P ? P->parent : nullptr;
    _rb_tree_node<T> *U = G ? (P == G->left_child ? G->right_child : G->left_child) : nullptr;

    if (P && P->color == node_color::black)
        return 1;

    if (U && U->color == node_color::red)
        return 2;

    // Parent is red, uncle is black from here
    if (node == root)
        return 3;

    if (P == root)
        return 4;

    if ((node == P->right_child && P == G->left_child)
        || (node == P->left_child && P == G->right_child))
        return 5;

    return 6;
}

template<class T>
void red_black_tree<T>::rotate_left(_rb_tree_node<T> *P)
{
    auto *N = P->right_child;
    auto *G = P->parent;

    if (!N) return;

    N->parent = G;
    P->right_child = N->left_child;
    if(P->right_child) P->right_child->parent = P;
    P->parent = N;
    N->left_child = P;


    if (!G) {
        root = N; // new root
        return;
    }

    if (G->left_child == P) G->left_child = N;
    else G->right_child = N;
}

template<class T>
void red_black_tree<T>::rotate_right(_rb_tree_node<T> *P)
{
    auto *N = P->left_child;
    auto *G = P->parent;

    if (!P) return;

    N->parent = G;
    P->left_child = N->right_child;
    if(P->left_child) P->left_child->parent = P;
    P->parent = N;
    N->right_child = P;

    if (!G) {
        root = N; // new root
        return;
    }

    if (G->left_child == P) G->left_child = N;
    else G->right_child = N;
}

template<class T>
void red_black_tree<T>::insert_fixup(_rb_tree_node<T> *node)
{
    // while insert case 2 and Parent is not nullptr
    while (true) {
        _rb_tree_node<T> *P = node->parent;
        _rb_tree_node<T> *G = P ? P->parent : nullptr;
        _rb_tree_node<T> *U = G ? (P == G->left_child ? G->right_child : G->left_child) : nullptr;

        if(!P) return;

        switch (insert_case(node)) {
            case 1:
            case 3:return;
            case 2:P->color = node_color::black;
                U->color = node_color::black;
                G->color = node_color::red;
                node = G;
                break;
            case 4:P->color = node_color::black;
                return;
            case 5:
                if (node == P->left_child)
                    rotate_right(P);
                else
                    rotate_left(P);
                node = P;
                break;
            case 6:
                if (P == G->left_child) rotate_right(G);
                else rotate_left(G);
                P->color = node_color::black;
                G->color = node_color::red;
                return;
        }
    }
}

template<class T>
T *red_black_tree<T>::find(const T &data, std::function<bool(const T &, const T &)> cmpr) const
{
    auto *node = find_node(data, cmpr);
    return node ? &node->data : nullptr;
}

template<class T>
void _rbt_rremove(_rb_tree_node<T> *node)
{
    if (node == nullptr) return;
    _rbt_rremove(node->left_child);
    _rbt_rremove(node->right_child);
    delete node;
}

template<class T>
void red_black_tree<T>::clear()
{
    if(!root) return;
    _rbt_rremove(root);
    uniq_id_cnt = 0;
    root = nullptr;
}


template<class T>
_rb_tree_node<T> *red_black_tree<T>::find_node(const T &data, std::function<int(const T &, const T &)> cmpr) const
{
    if (root == nullptr) return nullptr;
    auto *node = root;
    int res;

    while (node) {
        if ((res = cmpr(data, node->data)) == 0) break;
        if (res <= -1) node = node->left_child;
        else node = node->right_child;
    }
    return node;
}

template<class T>
std::string red_black_tree<T>::to_string() const
{
    std::stringstream ss{};
    ss << "{\n\theight: " << get_height() << ",\n\tsize: " << tree_size << ",\n\troot: " << root;

    ss << ",\n\tvalues inorder: [  ";

    _rb_tree_node<T> *node = nullptr;
    while ((node = next_inorder(node)) != nullptr) {
        ss << node->data << ", ";
    }
    ss.seekp(-2, std::ios_base::end);

    ss << "  ],\n\tvalues preorder: [  ";
    node = nullptr;
    while ((node = next_preorder(node)) != nullptr) {
        ss << node->data << ", ";
    }
    ss.seekp(-2, std::ios_base::end);
    ss << "  ],\n";
    ss << "\tnodes: [";

    node = nullptr;
    while ((node = next_preorder(node))) {
        ss << "\n\t\t[" << node->uniq_id << "] = {" << "data: " << node->data
           << ", color: \"" << (node->color == node_color::red ? "red" : "black")  << "\""
           << ", parent: " << node->parent;
        if (node->parent) ss << " ([" << node->parent->uniq_id << "])";
        ss << ", left child: " << node->left_child;
        if (node->left_child) ss << " ([" << node->left_child->uniq_id << "])";
        ss << ", right child: " << node->right_child;
        if (node->right_child) ss << " ([" << node->right_child->uniq_id << "])";
        ss << "}";
    }

    ss << "\n\t]\n}";
    return ss.str();
}

template<class T>
size_t red_black_tree<T>::get_height() const
{
    if (root == nullptr) return 0;

    node_with_depth<T> node_w_depth{nullptr, 0};
    size_t max_depth = 0;
    while ((node_w_depth = next_preorder(node_w_depth)).node != nullptr) {
        max_depth = std::max(node_w_depth.depth, max_depth);
    }
    return max_depth + 1;
}

template<class T>
std::string red_black_tree<T>::to_html() const
{
    auto *r = this->root;
    auto h = this->get_height();
    auto get_node_of_lvl = [r](size_t level, size_t ind) -> _rb_tree_node<T> * {
        auto *node = r;
        for (size_t i = 0; i < level; i++) {
            node = (ind >> (level - i - 1)) & 1 ? node->right_child : node->left_child;
            if (node == nullptr) return nullptr;
        }
        return node;
    };

    if (r == nullptr) return "";

    std::stringstream ss{};
    ss << "<table><tr><td colspan=\"8098\"";
    ss << " class=\"" << (r->color == node_color::red ? "red" : "black") << "\">";
    ss << r->data << "</tr></td>\n";


    for (size_t i = 1; i < h; i++) {
        ss << "<tr>";

        for (size_t ii = 0; ii < (1 << i); ii++) {
            auto *node = get_node_of_lvl(i, ii);
            if (i != h - 1) {
                ss << "<td colspan=\"" << (1 << (h - i - 1)) << "\"";
            }
            else ss << "<td";

            ss << " class=\"" << (node && node->color == node_color::red ? "red" : "black") << "\">";

            if (node != nullptr)
                ss << "<sub>[" << node->uniq_id << "]</sub> " << node->data;

            ss << "</td>";
        }
        ss << "</td>\n";
    }
    ss << "</table>";
    return ss.str();
}

template<class T>
void red_black_tree<T>::add(T data, std::function<int(const T &, const T &)> cmpr)
{
    auto *node = new _rb_tree_node<T>(data, uniq_id_cnt++);
    tree_size++;
    if (root == nullptr) {
        node->color = node_color::black;
        root = node;
        return;
    }
    node->color = node_color::red;

    // Searching place
    for (auto *cur_node = root; true;) {
        if (cmpr(data, cur_node->data) <= -1) {
            if (!cur_node->left_child) {
                cur_node->left_child = node;
                node->parent = cur_node;
                break;
            }
            cur_node = cur_node->left_child;
        } else {
            if (!cur_node->right_child) {
                cur_node->right_child = node;
                node->parent = cur_node;
                break;
            }
            cur_node = cur_node->right_child;
        }
    }

    if (node->parent->color == node_color::red) {
        insert_fixup(node);
    }

}

template<class T>
_rb_tree_node<T> *red_black_tree<T>::next_inorder(_rb_tree_node<T> *node) const
{
    if (root == nullptr) return nullptr;

    if (node == nullptr || node->right_child) {
        node = node ? node->right_child : root;
        while (node->left_child) {
            node = node->left_child;
        }
        return node;
    }

    while (node->parent && node->parent->right_child == node) {
        node = node->parent;
    }
    if (!node->parent) return nullptr;


    return node->parent;
}

template<class T>
node_with_depth<T> red_black_tree<T>::next_preorder(node_with_depth<T> node_w_depth) const
{
    if (root == nullptr) return {nullptr, 0};

    auto *node = node_w_depth.node;
    auto depth = node_w_depth.depth;

    if (node == nullptr)
        return {root, 0};
    if (node->left_child)
        return {node->left_child, depth + 1};
    if (node->right_child)
        return {node->right_child, depth + 1};
    if (node == root)
        return {nullptr, 0};

    while (!node->parent->right_child || node->parent->right_child == node) {
        node = node->parent;
        depth--;
        if (node == root)
            return {nullptr, 0};
    }

    return {node->parent->right_child, depth};
}

template<class T>
_rb_tree_node<T> *red_black_tree<T>::next_preorder(_rb_tree_node<T> *node) const
{
    return next_preorder({node, 0}).node;
}
