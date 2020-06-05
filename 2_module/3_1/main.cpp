#include <iostream>
#include <cassert>
#include <map>
#include <stack>
#include <queue>

using namespace std;

template <class T>
class Comparator {
public:
    bool operator() (const T &left, const T &right) {
        return left < right;
    }
};

template<class T, class Comparator=std::less<T>>
class Treap {
    struct TreapNode {
        TreapNode(const T &value, int priority) : value(value), priotiry(priority), left(nullptr), right(nullptr) {}

        T value;
        int priotiry;
        TreapNode *left;
        TreapNode *right;
    };

public:
    Treap() : root(nullptr) {}

    ~Treap() {
        destroy_tree(root);
    }

    void Add(const T &value, int priority) {
        if (root == nullptr) {
            root = new TreapNode(value, priority);
            return;
        }

        if (root->priotiry < priority) {
            TreapNode *tmp = root;
            root = new TreapNode(value, priority);
            split(tmp, value, root->left, root->right);
            return;
        }

        TreapNode *curr = root;
        while (true) {
            if (comp(curr->value, value)) {
                if (curr->right == nullptr) {
                    curr->right = new TreapNode(value, priority);
                    return;
                }

                if (curr->right->priotiry < priority) {
                    TreapNode *tmp = curr->right;
                    curr->right = new TreapNode(value, priority);
                    split(tmp, value, curr->right->left, curr->right->right);
                    return;
                }

                curr = curr->right;
            } else {
                if (curr->left == nullptr) {
                    curr->left = new TreapNode(value, priority);
                    return;
                }

                if (curr->left->priotiry < priority) {
                    TreapNode *tmp = curr->left;
                    curr->left = new TreapNode(value, priority);
                    split(tmp, value, curr->left->left, curr->left->right);
                    return;
                }

                curr = curr->left;
            }
        }
    }

    size_t get_height() const {
        return find_height(root);
    }

private:
    TreapNode *root;
    Comparator comp = Comparator();

    void destroy_tree(TreapNode *node) {
        if (node) {
            destroy_tree(node->left);
            destroy_tree(node->right);
            delete node;
        }
    }

    void split(TreapNode *curr, const T &value, TreapNode *&left, TreapNode *&right) {
        if (curr == nullptr) {
            left = nullptr;
            right = nullptr;
        } else if (comp(curr->value, value)) {
            split(curr->right, value, curr->right, right);
            left = curr;
        } else {
            split(curr->left, value, left, curr->left);
            right = curr;
        }
    }

    size_t find_height(TreapNode *node) const {
        if (node == nullptr) {
            return 0;
        }

        return 1 + std::max(find_height(node->left), find_height(node->right));
    }
};
template<class T>
struct BinaryNode {
    explicit BinaryNode(const T &value) : value(value), left(nullptr), right(nullptr) {}

    T value;
    BinaryNode *left;
    BinaryNode *right;
};

template <class T, class Comparator = less<T> >
class BinaryTree;

template <typename T, class Comparator>
class BinaryTree {
public:
    BinaryTree() : root(nullptr), comp(Comparator()){}
    ~BinaryTree();
    bool Add(const T &value);
    int GetHeight() const;
private:
    BinaryNode<T> *root;
    Comparator comp;

};

template<class T, class Comparator>
bool BinaryTree<T, Comparator>::Add(const T &value) {
    if (root == nullptr) {
        root = new BinaryNode<T>(value);
        return true;
    }

    BinaryNode<T> *curr = root;
    while (1) {
        if (curr->value == value) {
            return false;
        }

        if (comp(curr->value, value)) {
            if (curr->right == nullptr) {
                curr->right = new BinaryNode<T>(value);
                return true;
            }

            curr = curr->right;
        } else {
            if (curr->left == nullptr) {
                curr->left = new BinaryNode<T>(value);
                return true;
            }

            curr = curr->left;
        }
    }
}

template<class T, class Comparator>
int BinaryTree<T, Comparator>::GetHeight() const {
    int  h = 0;

    if (root == nullptr) {
        return 0;
    }

    std::queue<BinaryNode<T>*> q;
    q.push(root);
    q.push(nullptr);

    while (!q.empty()) {
        BinaryNode<T> *curr = q.front();
        q.pop();

        if (curr == nullptr) {
            if (!q.empty()) {
                q.push(nullptr);
            }
            h++;
        } else {
            if (curr->left != nullptr) {
                q.push(curr->left);
            }
            if (curr->right != nullptr) {
                q.push(curr->right);
            }
        }
    }

    return h;
}

template<class T, class Comparator>
BinaryTree<T, Comparator>::~BinaryTree() {
    queue<BinaryNode<T>*> q;

    if (root != nullptr) {
        q.push(root);
    }

    while (!q.empty()) {
        BinaryNode<T> *curr = q.front();
        q.pop();

        if (curr->left != nullptr) {
            q.push(curr->left);
            curr->left = nullptr;
        }
        if (curr->right != nullptr) {
            q.push(curr->right);
            curr->right = nullptr;
        }

        if (curr->left == nullptr && curr->right == nullptr) {
            delete curr;
        } else {
            q.push(curr);
        }
    }
}

int main() {
    int n = 0;
    cin >> n;
    assert(n > 0);

    BinaryTree<int, Comparator<int>> b_tree;
    Treap<int, Comparator<int>> treap;

    for(int i = 0; i < n; i++){
        int value = 0;
        int priority = 0;
        cin >> value >> priority;
        b_tree.Add(value);
        treap.Add(value, priority);
    }

    cout << b_tree.GetHeight() - treap.get_height();
    return 0;
}}