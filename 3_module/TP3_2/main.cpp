#include <iostream>
#include "vector"
#include "list"

#include "assert.h"
#include "queue"
using std::vector;
using std::list;
using std::cin;
using std::cout;
using std::endl;
using std::queue;

class CListGraph{
public:

    CListGraph(int n): vertex_n(n), lists(n){

    }



// Добавление ребра от from к to.
    void AddEdge(int from, int to){
        assert(from >= 0);
        assert(to >= 0);

        for (int i : lists[from]){
            if (i == to){
                return;
            }
        }

        lists[from].push_back(to);
        lists[to].push_back(from);
    }

    int VerticesCount() const{
        return this->vertex_n;

    }

    vector<int> GetNextVertices(int vertex) const{
        assert(vertex >= 0);

        vector<int> buffer;

        for (int i : lists[vertex]){
            buffer.push_back(i);
        }

        return buffer;

    }
    vector<int> GetPrevVertices(int vertex) const{
        assert(vertex >= 0);

        vector<int> buffer;

        for (int j = 0; j < vertex_n; ++j){
            for (int i : lists[j]){
                if (i == vertex){
                    buffer.push_back(j);
                    break;
                }
            }
        }
        return buffer;

    }

    void bfs(int v_from, int v_to, int edge){
        int min_path = edge;

        vector<int> counter (vertex_n, 0);
        vector<int> pathes (vertex_n);

        int path = 0;
        queue<int> q;
        q.push (v_from);
        vector<bool> used (vertex_n);
        vector<int> p (vertex_n);
        pathes[v_from] = 0;
        used[v_from] = true;
        counter[v_from] = 1;
        p[v_from] = -1;
        while (!q.empty())
        {
            int v = q.front();
            for (int i : lists[v]){
                if (!used[i]){

                    used[i] = true;
                    q.push (i);

                    pathes[i] = pathes[v] + 1;
                    p[i] = v;
                    counter[i] = counter[v];
                }
                else{
                    if ((pathes[v] + 1) == pathes[i]){
                        counter[i] += counter[v];


                    }
                    if ((pathes[v] + 1) < pathes[i]){
                        counter[i] = 1;

                    }
                }


            }
            q.pop();
        }

        cout << counter[v_to];
        cout << endl;

    }

private:
    int vertex_n;
    vector<list<int> > lists;

};

int main() {
    int vertex = 0;
    int edge = 0;

    cin >> vertex;
    //vertex = 4;
    assert ((vertex >= 0) && (vertex <= 50000));

    cin >> edge;
    //edge = 5;
    assert((edge >= 0)&&(edge <= 200000));

    //CMatrixGraph graph(vertex);
    CListGraph graph(vertex);

    for (int i = 0; i < edge; ++i){
        int vertex1 = 0;
        int vertex2 = 0;

        cin >> vertex1;
        assert ((vertex1 >= 0) && (vertex1 < vertex));
        cin >> vertex2;
        assert ((vertex2 >= 0) && (vertex2 < vertex));

        graph.AddEdge(vertex1, vertex2);
//        graph.AddEdge(0, 1);
//        graph.AddEdge(0, 2);
//        graph.AddEdge(1, 2);
//        graph.AddEdge(1, 3);
//        graph.AddEdge(2, 3);

    }

    int v_from = 0;
    int v_to = 0;
    cin >> v_from;
    assert ((v_from >= 0) && (v_from < vertex));
    cin >> v_to;
    //cout << v_to << "  " << vertex;

    assert ((v_to >= 0) && (v_to < vertex));

    //show(&graph);

    graph.bfs(v_from, v_to, edge);

    return 0;
}