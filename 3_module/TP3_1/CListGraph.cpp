

#include "CListGraph.h"
#include "assert.h"


CListGraph::CListGraph(int n): vertex_n(n), lists(n){

}

CListGraph::CListGraph(const IGraph* my_graph): vertex_n(my_graph->VerticesCount()), lists(my_graph->VerticesCount()){
    assert(my_graph != NULL);

    for (int i = 0; i < vertex_n; ++i){
        vector<int> next = my_graph->GetNextVertices(i);

        for (int j : next){
            this->AddEdge(i, j);
        }
    }


}


// Добавление ребра от from к to.
void CListGraph::AddEdge(int from, int to){
    assert(from >= 0);
    assert(to >= 0);

    for (int i : lists[from]){
        if (i == to){
            return;
        }
    }

    lists[from].push_back(to);
}

int CListGraph::VerticesCount() const{
    return this->vertex_n;

}

vector<int> CListGraph::GetNextVertices(int vertex) const{
    assert(vertex >= 0);

    vector<int> buffer;

    for (int i : lists[vertex]){
        buffer.push_back(i);
    }

    return buffer;

}
vector<int> CListGraph::GetPrevVertices(int vertex) const{
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
