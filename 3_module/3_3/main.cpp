/*
Требуется отыскать самый выгодный маршрут между городами.
Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
Формат входных данных.
Первая строка содержит число N – количество городов.
Вторая строка содержит число M - количество дорог.
Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
Последняя строка содержит маршрут (откуда и куда нужно доехать).
Формат выходных данных.
Вывести длину самого выгодного маршрута.

 */

#include <iostream>
#include <vector>
#include <cassert>
#include <list>
#include <queue>
#include <limits>

using namespace std;

typedef pair<size_t, size_t> Edge;

class Graph{
public:
    explicit Graph(size_t vertices_number);
    bool AddEdge(size_t from, size_t to, size_t trip_time);
    vector<Edge> GetVertexEdges(size_t v) const;
    size_t CountVertices() const;
    ~Graph();
private:
    vector<Edge> *graph;
    size_t vertices;
};

Graph::Graph(size_t vertices_number) {
    vertices = vertices_number;
    graph = new vector<Edge>[vertices];
}

size_t GetFastesWayTime(Graph &graph, size_t from, size_t to);

bool Graph::AddEdge(size_t from, size_t to, size_t trip_time) {
    assert(from < vertices && to < vertices);
    if (from != to) {
        graph[to].push_back(Edge{from, trip_time});
    }
    graph[from].push_back(Edge{to, trip_time});
}

vector<Edge> Graph::GetVertexEdges(size_t v) const {
    assert(v < vertices);
    return graph[v];
}

size_t Graph::CountVertices() const {
    return vertices;
}

Graph::~Graph() {
    delete[] graph;
}

int main() {
    size_t cities, roades;
    cin >> cities >> roades;
    assert(cities > 0 && roades > 0);
    Graph graph(cities);
    for (size_t i = 0; i < roades; i++){
        size_t from, to, trip_time;
        cin >> from >> to >> trip_time;
        graph.AddEdge(from, to, trip_time);
    }

    size_t find_from, find_to;
    cin >> find_from >> find_to;
    size_t fastest_time = GetFastesWayTime(graph, find_from, find_to);
    cout << fastest_time;

    return 0;
}

size_t GetFastesWayTime(Graph &graph, size_t from, size_t to){
    assert(from < graph.CountVertices() && to < graph.CountVertices());
    size_t *ways = new size_t[graph.CountVertices()];
    size_t i = 0;
    while(i < graph.CountVertices()) {
        ways[i] = numeric_limits<size_t>::max();
        i++;
    }

    priority_queue<Edge, vector<Edge>, greater<Edge> > q;
    ways[from] = 0;
    q.push({0, from});
    while(!q.empty()) {
        size_t cur_way = q.top().first;
        size_t cur_v = q.top().second;
        q.pop();
        if (cur_way > ways[cur_v]) {
            continue;
        }
        for (Edge &edges : graph.GetVertexEdges(cur_v)) {
            if (ways[edges.first] > ways[cur_v] + edges.second) {
                ways[edges.first] = ways[cur_v] + edges.second;
                q.push({ways[edges.first], edges.first});
            }
        }
    }

    delete[] ways;
    return ways[to];
}

/*
6
9
0 3 1
0 4 2
1 2 7
1 3 2
1 4 3
1 5 3
2 5 3
3 4 4
3 5 6
0 2
 */