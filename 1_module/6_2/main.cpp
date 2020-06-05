/*
 * Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.

Требования: к дополнительной памяти: O(n). Среднее время работы: O(n). Должна быть отдельно выделенная функция partition. Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
 6_2. Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
 */
#include <iostream>
#include <cassert>

using namespace std;

template <class T>
bool isLess(T &, T &);
template <class T>
int *GetMedian(T *first, T *second, T *third, bool(*isLess) (const T&, const T&));
template <class T>
int Partition(T *arr, int left, int right, bool(*isLess) (const T&, const T&));
template <class T>
int k_stat(T *array, int left, int right, bool(*isLess)(const T &, const T &));


int main() {
    int length, k;
    cin >> length >> k;
    assert(!cin.fail());
    assert(length > 0 && k < length);
    int *array = new int[length];
    for (int i = 0; i < length; ++i) {
        cin >> array[i];
        assert(!cin.fail());
    }
    int result = k_stat(array, length, k, isLess);
    cout << result;

    delete[]array;
    return 0;
}

template <class T>
bool isLess(T &first, T &second) {
    return first < second;
}

template <class T>
int GetMedian(const T *arr, int left, int right, bool(*isLess) (const T&, const T&)) {
    assert(arr != nullptr);
    int medium = (left + right) / 2;
    right--;
    if (isLess(arr[right], arr[left]))
        return isLess(arr[medium], arr[right]) ? right : medium;
    return isLess(arr[medium], arr[left]) ? left : medium;
}

template <class T>
int Partition(T *arr, int left, int right, bool(*isLess) (const T&, const T&)) {
    assert(arr != nullptr);
    int pivot_pos = GetMedian(arr, left, right, isLess);
    if (right - left < 2){
        return pivot_pos;
    }

    swap(arr[pivot_pos], arr[right - 1]);
    pivot_pos = right - 1;
    int i = (int) right - 2, j = (int) right - 2;
    while (j >= 0) {
        if (isLess(arr[pivot_pos], arr[j])){
            swap(arr[i--], arr[j--]);
        } else {
            j--;
        }
    }
    swap(arr[i + 1], arr[pivot_pos]);

    return i + 1;
}

template <class T>
int k_stat(T *arr, int n, int k,  bool(*isLess)(const T &, const T &)) {
    int left = 0, right = n;
    int pivot_pos = Partition(arr, left, right, isLess);
    while (pivot_pos != k) {
        if (pivot_pos < k) {
            left = pivot_pos + 1;
        }
        else {
            right = pivot_pos;
        }
        pivot_pos = Partition(arr, left, right, isLess);
    }
    return arr[pivot_pos];
}