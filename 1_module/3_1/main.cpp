/*
Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

3_1. Реализовать очередь с динамическим зацикленным буфером.
Требования: Очередь должна быть реализована в виде класса.
 */

#include <iostream>
#include <stdexcept>
#include <cassert>
using namespace std;

const unsigned int
    PopFront = 2,
    PushBack = 3;
static const int
    InitialCapacity = 10;

struct Command{
    unsigned int command;
    int value;
};

class Queue{
public:
    void Enqueue(int value);
    int Dequeue();
    bool isEmpty() const;

    ~Queue();

private:
    int head = 0, tail = 0, size = 0, capacity = 0;
    int *entities = nullptr;
};

void GetCommands(Command*, int);
int RunCommands(Command*, int);

int main() {
    int n;
    cin >> n;
    assert(!cin.fail());
    assert(n > 0);

    Command *commands = new Command[n];
    GetCommands(commands, n);

    int ok = RunCommands(commands, n);
    if (!ok){
        cout << "NO";
        delete[] commands;
        return 0;
    }
    cout << "YES";

    delete[] commands;
    return 0;
}

void GetCommands(Command *c, int n){
    assert(c != nullptr);
    for(int i = 0; i < n; i++){
        cin >> c[i].command >> c[i].value;
        assert(!cin.fail() && (c[i].command == PushBack || c[i].command == PopFront));
    }
}

bool Queue::isEmpty() const {
    return size == 0;
}

int Queue::Dequeue() {
    if (isEmpty()){
        throw logic_error("empty");
    }
    int res = entities[head];
    head = (head + 1) % capacity;
    size--;
    return res;
}

void Queue::Enqueue(int value) {
    if (size + 1 >= capacity){
        int new_capacity = capacity == 0 ? InitialCapacity : capacity * 2;
        int *new_entities = new int[new_capacity];
        if (head > tail){
            for(int i = 0; i < tail; i++){
                new_entities[i] = entities[i];
            }
            for(int i = capacity - 1, j = new_capacity - 1; i >= head; i--, j--){
                new_entities[j] = entities[i];
            }
            head = head +new_capacity - capacity;
        } else {
            for (int i = 0; i < tail; i++){
                new_entities[i] = entities[i];
            }
        }
        capacity = new_capacity;
        delete[] entities;
        entities = new_entities;
    }
    entities[tail] = value;
    size++;
    tail = (tail + 1) % capacity;
}

Queue::~Queue() {
    delete[] entities;
}

int RunCommands(Command * commands, int n){
    assert(commands != nullptr);
    Queue q;
    int res_pop;
    for (int i = 0; i < n; i++){
        if (commands[i].command == PopFront){
            if (q.isEmpty()){
                res_pop = -1;
            } else {
                res_pop = q.Dequeue();
            }
            if (res_pop != commands[i].value){
                return 0;
            }
        } else if (commands[i].command == PushBack){
            q.Enqueue(commands[i].value);
        }
    }
    return 1;
}