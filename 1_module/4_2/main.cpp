/*
 * 4_2. Быстрое сложение.
Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка вычислений.
((1+2)+3) -> 1+2 + 3+3 = 9
((1+3)+2) -> 1+3 + 4+2 = 10
((2+3)+1) -> 2+3 + 5+1 = 11
Требуется написать программу, которая определяет минимальное время, достаточное для вычисления суммы заданного набора чисел.
Формат входных данных. Вначале вводится n - количество чисел. Затем вводится n строк - значения чисел (значение каждого числа не превосходит 10^9, сумма всех чисел не превосходит 2*10^9).
Формат выходных данных. Натуральное число - минимальное время.
 */
#include <iostream>
#include <cassert>

using namespace std;

const int InitialCapacity = 10;

template <class T>
class Comparator {
public:
    bool operator() (const T &left, const T &right) {
        return left < right;
    }
};

template <class T>
class Vector;

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

template <class T, class Comparator = std::less<T> >
class Heap;

template<typename T, class Comparator>
class Heap{
public:
    explicit Heap(const T *values, int n);
    void Insert(T value);
    T ExtractMin();
    int Size() const;

private:
    void SiftDown(int value);
    void SiftUp(int value);
    Vector<T> entities;
    Comparator comp;
};

int FindMinTime(const int*, int);

int main() {
    int n;
    cin >> n;
    assert(!cin.fail() && n > 0);
    int *values = new int[n];
    for (int i = 0; i < n; i++){
        cin >> values[i];
        assert(!cin.fail());
    }
    int min = FindMinTime(values, n);
    cout << min;

    delete[] values;
    return 0;
}

template<typename T>
void Vector<T>::Reserve(int value) {
    assert(value > 0);
    int *new_entities = new T[value];
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

template<typename T, class Comparator>
Heap<T, Comparator>::Heap(const T *values, int n){
    assert(values != nullptr);
    this->comp = Comparator();
    this->entities.Assign(values,n);
    for (int i = this->Size() / 2; i > 0; i--){
        SiftDown(i - 1);
    }
}

template<typename T, class Comparator>
void Heap<T, Comparator>::SiftDown(int value) {
    assert(value < this->entities.Size());
    int left = 2 * value + 1;
    int right = 2 * value + 2;
    int least = value;
    if (left < this->entities.Size() && comp(this->entities[left], this->entities[least]))
        least = left;
    if (right < this->entities.Size() && comp(this->entities[right], this->entities[least]))
        least = right;
    if (least != value) {
        swap(this->entities[value], this->entities[least]);
        SiftDown(least);
    }
}

template<typename T, class Comparator>
void Heap<T, Comparator>::SiftUp(int value) {
    assert(value < this->entities.Size());
    while (value > 0){
        int parent = (value - 1) / 2;
        if (comp(this->entities[parent], this->entities[value])){
            return;
        }
        swap(this->entities[parent], this->entities[value]);
        value = parent;
    }
}

template<typename T, class Comparator>
int Heap<T, Comparator>::Size() const {
    return this->entities.Size();
}

template<typename T, class Comparator>
void Heap<T, Comparator>::Insert(T value) {
    this->entities.PushBack(value);
    SiftUp(this->entities.Size() - 1);
}

template<typename T, class Comparator>
T Heap<T, Comparator>::ExtractMin() {
    assert(!this->entities.IsEmpty());
    T res = this->entities.Front();
    this->entities.Front() = this->entities.Back();
    this->entities.PopBack();
    if (!this->entities.IsEmpty()){
        SiftDown(0);
    }
    return res;
}

int FindMinTime(const int *entities, int n){
    Heap<int, Comparator<int >> heap(entities, n);
    int min = 0;
    while(heap.Size() > 1){
        int a = heap.ExtractMin();
        int b = heap.ExtractMin();
        heap.Insert(a + b);
        min += a + b;
    }
    return min;
}