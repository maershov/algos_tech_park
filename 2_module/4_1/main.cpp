/*
 * 4_1. Солдаты. В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
Требования: скорость выполнения команды - O(log n).
Формат входных данных.
Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000). В каждой следующей строке содержится описание команды: число 1 и X если солдат приходит в строй (X – рост солдата, натуральное число до 100 000 включительно) и число 2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя. Солдаты в строе нумеруются с нуля.
Формат выходных данных.
На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции, на которую должен встать этот солдат (все стоящие за ним двигаются назад).

 */

#include <iostream>
#include <cassert>

using namespace std;

template <class T>
struct Node{
    explicit Node(const T &value) : value(value), left(nullptr), right(nullptr), height(1), dif(1){}

    T value;
    Node *left;
    Node *right;
    int height;
    int dif;
};

template <class T>
class Comparator {
public:
    bool operator() (const T &left, const T &right) {
        return left < right;
    }
};

template <class T, class Comparator = std::less<T> >
class AVL;

template<class T, class Comparator>
class AVL{
public:
    explicit AVL();
    ~AVL();

    void insert(const T &value);
    void delete_position(unsigned int position);
    unsigned int get_position(const T &value);

private:
    Node<T> *root;
    Comparator comp;

    void delete_tree(Node<T> *node);
    Node<T>* rotate_left(Node<T> *node);
    Node<T>* rotate_right(Node<T> *node);
    Node<T> *find_left(Node<T> *node);
    Node<T> *find_right(Node<T> *node);
    Node<T> *remove(Node<T> *node, unsigned int pos);
    Node<T> *remove_left(Node<T> *node);
    Node<T> *remove_right(Node<T> *node);
    Node<T>* insert(Node<T> *node, const T &value);
    Node<T>* balance(Node<T> *node);
    int get_balance(Node<T> *node);
    void check_height(Node<T> *node);
    unsigned int get_height(Node<T> *node);
    void check_dif(Node<T> *node);
    unsigned int get_dif(Node<T> *node);
};


int main() {
    AVL<int, Comparator<int> > tree;

    int n = 0;
    cin >> n;
    assert(n > 0);
    int operation = 0, value = 0;

    for(int i = 0; i < n; ++i){
        cin >> operation >> value;
        if (operation == 1){
                tree.insert(value);
                cout << tree.get_position(value) << endl;
        } else if (operation == 2){
                tree.delete_position(value);
        }
    }

    return 0;
}

template<class T, class Comparator>
AVL<T, Comparator>::AVL() {
    this->root = nullptr;
    this->comp = Comparator();
}

template<class T, class Comparator>
AVL<T, Comparator>::~AVL() {
    delete_tree(root);
}

template<class T, class Comparator>
void AVL<T, Comparator>::insert(const T &value) {
    root = insert(root, value);
}

template<class T, class Comparator>
void AVL<T, Comparator>::delete_position(unsigned int position) {
    root = remove(root, position);
}

template<class T, class Comparator>
unsigned int AVL<T, Comparator>::get_position(const T &value) {
    Node<T> *curr_node = root;
    unsigned int position = 0;

    while (curr_node) {
        if (curr_node->value == value) {
            return position + get_dif(curr_node->left);
        }

        if (comp(value, curr_node->value)) {
            position += get_dif(curr_node->left) + 1;
            curr_node = curr_node->right;
        } else {
            curr_node = curr_node->left;
        }
    }

    return 0;
}

template <class T, class Comparator>
Node<T>* AVL<T, Comparator>::rotate_left(Node<T> *node) {
    Node<T> *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    check_height(node);
    check_height(tmp);
    check_dif(node);
    check_dif(tmp);

    return tmp;
}

template <class T, class Comparator>
Node<T>* AVL<T, Comparator>::rotate_right(Node<T> *node) {
    Node<T> *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    check_height(node);
    check_height(tmp);
    check_dif(node);
    check_dif(tmp);

    return tmp;
}

template <class T, class Comparator>
void AVL<T, Comparator>::delete_tree(Node<T> *node) {
    if (node) {
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
}

template <class T, class Comparator>
Node<T> *AVL<T, Comparator>::remove(Node<T> *node, unsigned int pos) {
    if (node == nullptr) {
        return nullptr;
    }

    unsigned int current_pos = get_dif(node->left);
    if (current_pos < pos) {
        node->right = remove(node->right, pos - current_pos - 1);
    } else if (current_pos > pos) {
        node->left = remove(node->left, pos);
    } else {
        Node<T> *left = node->left;
        Node<T> *right = node->right;
        delete node;

        if (left == nullptr && right == nullptr) {
            return nullptr;
        }

        if (get_height(left) > get_height(right)) {
            Node<T> *min = find_right(left);
            min->left = remove_right(left);
            min->right = right;

            return balance(min);
        } else {
            Node<T> *min = find_left(right);
            min->right = remove_left(right);
            min->left = left;

            return balance(min);
        }
    }

    return balance(node);
}

template <class T, class Comparator>
Node<T> *AVL<T, Comparator>::find_left(Node<T> *node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <class T, class Comparator>
Node<T> *AVL<T, Comparator>::find_right(Node<T> *node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

template <class T, class Comparator>
Node<T> *AVL<T, Comparator>::remove_left(Node<T> *node) {
    if (!node->left)
        return node->right;
    node->left = remove_left(node->left);
    return balance(node);
}

template <class T, class Comparator>
Node<T> *AVL<T, Comparator>::remove_right(Node<T> *node) {
    if (!node->right)
        return node->left;
    node->right = remove_right(node->right);
    return balance(node);
}

template <class T, class Comparator>
Node<T> *AVL<T, Comparator>::insert(Node<T> *node, const T &value) {
    if (node == nullptr) {
        return new Node<T>(value);
    }

    if (comp(value, node->value)) {
        node->right = insert(node->right, value);
    } else {
        node->left = insert(node->left, value);
    }

    return balance(node);
}

template <class T, class Comparator>
Node<T>* AVL<T, Comparator>::balance(Node<T> *node) {
    check_height(node);
    check_dif(node);

    if (get_balance(node) == 2){
        if (get_balance(node->right) < 0) {
            node->right = rotate_right(node->right);
        }
        return rotate_left(node);
    } else if (get_balance(node) == -2){
        if (get_balance(node->left) > 0) {
            node->left = rotate_left(node->left);
        }
        return rotate_right(node);
    } else{
        return node;
    }
}

template <class T, class Comparator>
void AVL<T, Comparator>::check_height(Node<T> *node) {
    node->height = std::max(get_height(node->left), get_height(node->right)) + (unsigned char) 1;
}

template <class T, class Comparator>
unsigned int AVL<T, Comparator>::get_height(Node<T> *node) {
    return node ? node->height : 0;
}

template <class T, class Comparator>
void AVL<T, Comparator>::check_dif(Node<T> *node) {
    node->dif = get_dif(node->left) + get_dif(node->right) + 1;
}

template <class T, class Comparator>
unsigned int AVL<T, Comparator>::get_dif(Node<T> *node) {
    return node ? node->dif : 0;
}

template <class T, class Comparator>
int AVL<T, Comparator>::get_balance(Node<T> *node) {
    return get_height(node->right) - get_height(node->left);
}

