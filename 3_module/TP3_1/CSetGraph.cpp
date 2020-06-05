//
// Created by aam on 2019-05-17.
//

#include "CSetGraph.h"
#include "assert.h"


CSetGraph::CSetGraph(int n): vertex_n(n), sets(n){

}
CSetGraph::CSetGraph(const IGraph* my_graph): vertex_n(my_graph->VerticesCount()), sets(my_graph->VerticesCount()){
    assert(my_graph != NULL);

    for (int i = 0; i < vertex_n; ++i){
        vector<int> buffer = my_graph->GetNextVertices(i);

        for (int j : buffer){
            AddEdge(i, j);
        }
    }
}


// Добавление ребра от from к to.
void CSetGraph::AddEdge(int from, int to){
    assert(from >= 0);
    assert(to >= 0);

    sets[from].insert(to);

}

int CSetGraph::VerticesCount() const{
    return vertex_n;
}

vector<int> CSetGraph::GetNextVertices(int vertex) const{
    assert(vertex >= 0);

    vector<int> buffer;

    for (int i : sets[vertex]){
        buffer.push_back(i);
    }

    return buffer;

}

vector<int> CSetGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0);

    vector<int> buffer;

    for (int i = 0; i < vertex_n; ++i) {
        for (int j : sets[i]) {
            if (j == vertex){
                buffer.push_back(i);
                break;
            }
        }
    }

    return buffer;

}