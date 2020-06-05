/*
 Требование для всех вариантов Задачи 5
Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием.
Решение должно поддерживать передачу функции сравнения снаружи.
Общее время работы алгоритма O(n log n).
5_3. Закраска прямой 1.
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri). Найти длину окрашенной части числовой прямой.
 */

#include <iostream>
#include <cassert>

using namespace std;

struct Point{
    int x;
    bool operator<(const Point &) const;
    int position;
};

template <class T>
bool isLess(T &, T &);
void Read(Point*, int);
template<typename T>
void MergeSort(T *a, int length, bool(*isLess) (const T&, const T&));
template<typename T>
void MergeSort(T *a, int low, int high, bool(*isLess) (const T&, const T&));
template<typename T>
void merge(T *a, int left_low, int left_high, int right_low, int right_high, bool(*isLess) (const T&, const T&));
int PaintedLine(Point*, int);

int main() {
    int n;
    cin >> n;
    assert(!cin.fail() && n > 0);
    int capacity = n * 2;
    Point *points = new Point[capacity];
    Read(points, capacity);
    int length = PaintedLine(points, capacity);
    cout << length << endl;

    delete[] points;
    return 0;
}

void Read(Point *points, int n){
    assert(points != nullptr);
    for (int i = 0; i < n; i += 2){
        int left, right;
        cin >> left >> right;
        assert(!cin.fail());
        points[i] = Point{left, 1};
        points[i + 1] = Point{right, -1};
    }
}

bool Point::operator<(const Point &other) const {
    return isLess(this->x, other.x);
}

template<typename T>
void MergeSort(T *a, int length, bool(*isLess) (const T&, const T&)) {
    MergeSort(a, 0, length - 1, isLess);
}

template<typename T>
void MergeSort(T *a, int low, int high, bool(*isLess) (const T&, const T&)) {
    if (low >= high)
        return;
    else {
        int mid = (low + high)/2;
        MergeSort(a, low, mid, isLess);
        MergeSort(a, mid + 1, high, isLess);
        merge(a, low, mid, mid+1,high, isLess);
    }
}

template<typename T>
void merge(T *a, int left_low, int left_high, int right_low, int right_high, bool(*isLess) (const T&, const T&))
{
    int length = right_high-left_low+1;
    Point temp[length];
    int left = left_low;
    int right = right_low;
    for (int i = 0; i < length; ++i) {
        if (left > left_high)
            temp[i] = a[right++];
        else if (right > right_high)
            temp[i] = a[left++];
        else if (isLess(a[left], a[right]))
            temp[i] = a[left++];
        else
            temp[i] = a[right++];
    }
    for (int i=0; i< length; ++i)
        a[left_low++] = temp[i];
}

int PaintedLine(Point *points, int n){
    assert(points != nullptr);
    MergeSort(points, n, isLess);
    int length = 0, included = 0;
    for (int i = 0; i < n - 1; i++){
        included += points[i].position;
        if (included > 0){
            length += points[i + 1].x - points[i].x;
        }
    }
    return length;
}

template <class T>
bool isLess(T &first, T &second) {
    return first < second;
}

