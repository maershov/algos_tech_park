/*
2_1. Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. n, m ≤ 10000.
Требования:  Время работы поиска k для каждого элемента B[i]: O(log(k)). Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска размером порядка k, а потом уже в нем делать бинарный поиск.
 */

#include <cassert>
#include <iostream>

using namespace std;

void ReadArr(int*, int);
void SearchResult(int*, int*, int*, int, int);
void GetInterval(const int*, int, int, int*, int*);
int GetPosition(const int*, int, int, int, int);
void Print(int*, int);

int main() {
    int n, m;
    cin >> n >> m;
    assert(!cin.fail());
    assert(n > 0 && m > 0);
    int *a, *b, *res;
    a = new int[n];
    b = new int[m];
    res = new int[m];

    ReadArr(a, n);
    ReadArr(b, m);
    SearchResult(a, b, res, n, m);
    Print(res, m);

    delete[] a;
    delete[] b;
    delete[] res;
    return 0;
}


void ReadArr(int *mas, int size) {
    assert(mas != nullptr);
    for (int i = 0; i < size; i++) {
        cin >> mas[i];
        assert(!std::cin.fail());
    }
}

void SearchResult(int *a, int *b, int *res, int n, int m){
    assert(a != nullptr && b != nullptr && res != nullptr);
    int first, last;
    for (int i = 0; i < m; i++){
        GetInterval(a, n, b[i], &first, &last);
        res[i] = GetPosition(a, n, b[i], first, last);
    }
}

void GetInterval(const int* a, int n, int value, int *first, int *last){
    assert(a != nullptr);
    int first_inside, last_inside;
    first_inside = 0;
    last_inside = 1;

    while(last_inside < n && a[last_inside] < value){
        int mid = (last_inside - first_inside) * 2;
        first_inside = last_inside;
        last_inside = first_inside + mid;
    }
    *first = first_inside;
    *last = last_inside < n ? last_inside : n - 1;
}

int GetPosition(const int *a, int n, int value, int first, int last){
    assert(a != nullptr);
    while (first < last){
        int mid = (last + first) / 2;
        if (a[mid] < value){
            first = mid + 1;
        } else {
            last = mid;
        }
    }
    return a[first] >= value ? first : n;
}

void Print(int* mas, int size){
    assert(mas != nullptr);
    for(int i = 0; i < size; i++){
        cout << mas[i] << ' ';
    }
    cout << '\n';
}