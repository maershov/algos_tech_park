/*
 * 7_1. MSD для строк.
Дан массив строк. Количество строк не больше 105. Отсортировать массив методом поразрядной сортировки MSD по символам. Размер алфавита - 256 символов. Последний символ строки = ‘\0’.

 */

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

const int InitialCapacity = 4;
const int CounterSize = 128;

template<typename T>
class Vector{
public:
    void Assign(const T *values, int n);
    void PopBack();
    void PushBack(T value);
    bool IsEmpty() const;
    int Size() const;
    T &Front() const;
    T &Back() const;
    T &operator[](int value);
    ~Vector();
private:
    T *entities = nullptr;
    int size = 0;
    int capacity = 0;
    void Grow();
    void Reserve(int value);
};

char GetLetter(Vector<string> &str, int pos, int i);
void MSDSort(Vector<string> &str, int left, int right, int pos, string* buf);
void MSD(Vector<string> &str);
void Print(Vector<string> &str);

int main() {
    Vector<string> str;
    string buf;
    while(getline(cin, buf)){
        str.PushBack(buf);
    }
    MSD(str);
    Print(str);

    return 0;
}

template<typename T>
void Vector<T>::Reserve(int value) {
    assert(value > 0);
    T *new_entities = new T[value];
    for (int i = 0; i < this->size; i++){
        new_entities[i] = this->entities[i];
    }
    delete[] this->entities;
    this->capacity = value;
    this->entities = new_entities;
}

template<typename T>
void Vector<T>::Assign(const T *values, int n) {
    assert(values != nullptr);
    Reserve(n);
    for(int i = 0; i < n; i++){
        this->entities[i] = values[i];
    }
    this->size = n;
}

template<typename T>
void Vector<T>::Grow() {
    int new_capacity;
    if (this->capacity == 0){
        new_capacity = InitialCapacity;
    } else {
        new_capacity = capacity * 2;
    }
    Reserve(new_capacity);
}

template<typename T>
int Vector<T>::Size() const {
    return this->size;
}

template<typename T>
bool Vector<T>::IsEmpty() const {
    return this->size == 0;
}

template<typename T>
void Vector<T>::PushBack(T value) {
    if (this->size + 1 > this->capacity){
        Grow();
    }
    this->entities[this->size] = value;
    this->size++;
}

template<typename T>
void Vector<T>::PopBack() {
    assert(this->size > 0);
    this->size--;
}

template<typename T>
T & Vector<T>::Front() const {
    assert(this->size > 0);
    return this->entities[0];
}

template<typename T>
T & Vector<T>::Back() const {
    assert(this->size > 0);
    return this->entities[this->size - 1];
}

template<typename T>
T & Vector<T>::operator[](int value) {
    assert(value < this->size);
    return this->entities[value];
}

template<typename T>
Vector<T>::~Vector() {
    delete[] this->entities;
}

void MSD(Vector<string> &str){
    string *buf = new string[str.Size()];
    if (str.Size() <= 1){
        delete[] buf;
        return;
    }
    MSDSort(str, 0, str.Size(), 0, buf);
    delete[] buf;
}

void MSDSort(Vector<string> &str, int left, int right, int pos, string* buf){
    int counter[CounterSize] = {0};
    for(int i = left; i < right; i++){
        char letter = GetLetter(str, pos, i);
        counter[int(letter)]++;
    }
    int final_position = 0;
    for (int & i : counter){
        int buffer = i;
        i = final_position;
        final_position += buffer;
    }
    for (int i = left; i < right; i++){
        char letter = GetLetter(str, pos, i);
        buf[counter[int(letter)]++] = str[i];
    }
    for (int i = left, j = 0; i < right; i++, j++){
        str[i] = buf[j];
    }
    for(int i = 1; i < CounterSize; i++){
        if (counter[i] - counter[i - 1] > 1){
            MSDSort(str, left + counter[i - 1], left + counter[i], pos + 1, buf);
        }
    }
}

char GetLetter(Vector<string> &str, int pos, int i){
    char letter;
    if (pos >= str[i].length()){
        letter = '\0';
    } else {
        letter = str[i][pos];
    }
    return letter;
}

void Print(Vector<string> &str){
    for (int i = 0; i < str.Size(); i++){
        cout << str[i] << endl;
    }
}