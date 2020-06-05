/*
 Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
 */

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

#define REHASH_FULL 0.75
#define INITIAL_SIZE_TABLE 8
#define FIRST_INDEX 0.5
#define SECOND_INDEX 0.5
#define A_INDEX 127


using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::endl;


template<class T> struct HashNode{
    T key;
    bool is_deleted;
    bool is_empty;
    //constructor
    HashNode(){ is_deleted = false; is_empty = true;}
    explicit HashNode(T &data) : key(data), is_deleted(false), is_empty(false) {

    }

};


template<class T> class HashT{

public:
    HashT() : t(INITIAL_SIZE_TABLE), size(0), capacity(INITIAL_SIZE_TABLE) {};
    ~HashT(){
        for (int i = 0; i < t.size(); i++){
            t[i].is_empty = true;
        }
    }
    bool insert(T key);
    bool delete_key(T key);
    bool check(T key);

private:
    vector< HashNode<T> > t;
    unsigned int size;
    unsigned int capacity;

    void rehash() {
        //cout << "rehash";
        int new_size = capacity * 2;

        vector< HashNode<T> > buffer = t;
        HashNode<T> buf = HashNode<T>();
        capacity *= 2;
        vector< HashNode<T> >my_vector(capacity);
        t = my_vector;
        for (int i = 0; i < buffer.size(); i++) {
            if ((!buffer[i].is_empty) && (buffer[i].is_deleted == false)) {
                insert(buffer[i].key);
            }
        }
    }


};

unsigned int Hash(string &key, unsigned int t_size){
    int hash = 0;
    for (int i = 0; i < key.size(); i++){
        hash = (hash*A_INDEX + key[i]) % t_size;
    }
    return hash;
}

template<class T> bool HashT<T>::insert(T key){
    assert(key.size() > 0);
    unsigned int hash_insert = Hash(key, t.size());

    if (((double)size / (double)capacity) >= REHASH_FULL){
        rehash();
    }

    int proba = 0;
    int position = (hash_insert + 1 / 2 * proba + 1 / 2 * proba * proba) % capacity;
    int pos_insert = -1;



    for (int i = 0; i < t.size(); i++){
        if (i > 0) {
            position = (position + i) % t.size();
        }

        if (!t[position].is_empty) {

            if ((t[position].is_deleted)) {
                pos_insert = position;
            }

            if (!(t[position].is_deleted) && (t[position].key == key)) {
                return false;
            }
        } else {
            if (pos_insert == -1) {
                pos_insert = position;
            }

            break;
        }

    }

    t[pos_insert] = HashNode<T>(key);
    size++;

    return true;

}

template<class T> bool HashT<T>::delete_key(T key){
    unsigned int hash_delete = Hash(key, t.size());
    int proba = 0;
    int position = (hash_delete + 1 / 2 * proba + 1 / 2 * proba * proba) % capacity;


    for (int i = 0; i < t.size(); i++) {
        if (i > 0) {
            position = (position + i) % t.size();
        }

        if (t[position].is_empty) {
            return false;
        }

        if ((t[position].is_deleted == false) && (t[position].key == key)){
            t[position].is_deleted = true;
            size--;
            return true;
        }


    }
    return false;

}

template<class T> bool HashT<T>::check(T key){
    unsigned int hash_check = Hash(key, t.size());
    int proba = 0;
    int position = (hash_check + 1 / 2 * proba + 1 / 2 * proba * proba) % capacity;


    for (int i = 0; i < t.size(); i++) {
        if (i > 0) {
            position = (position + i) % t.size();
        }

        if (t[position].is_empty) {
            return false;
        }

        if ((t[position].is_deleted == false) && (t[position].key == key)){
            return true;
        }



    }

    return false;
}



int main() {
    HashT<string> table;
    char command = ' ';
    string key;

    while (cin >> command >> key) {
        switch (command) {
            case '+':
                cout << (table.insert(key) ? "OK" : "FAIL") << endl;
                break;
            case '-':
                cout << (table.delete_key(key) ? "OK" : "FAIL") << endl;
                break;
            case '?':
                cout << (table.check(key) ? "OK" : "FAIL") << endl;
                break;
            default:
                assert(false);
        }
    }

    return 0;
}