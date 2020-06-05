
  Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
 */

#include <iostream>
#include <cassert>
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
    void Print() const;
private:
    BinaryNode<T> *root;
    Comparator comp;

};

template<class T, class Comparator>
void BinaryTree<T, Comparator>::Print() const {
    stack<BinaryNode<T>*> s;

    if (root == nullptr) {
        cout << endl;
        return;
    }

    BinaryNode<T> *curr = root;
    while (true) {
        while (curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        }

        if (!s.empty()) {
            curr = s.top();
            s.pop();

            cout << curr->value << " ";
            curr = curr->right;
        } else {
            break;
        }
    }

    cout << endl;
}

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

    queue<BinaryNode<T>*> q;
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

int main(){
    int n = 0;
    cin >> n;
    assert(n > 0);

    BinaryTree<int, Comparator<int>> b_tree;
    for(int i = 0; i < n; i++){
        int value = 0;
        cin >> value;
        b_tree.Add(value);
    }

    b_tree.Print();
    return 0;
}
