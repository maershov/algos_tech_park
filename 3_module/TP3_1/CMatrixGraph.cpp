

#include "CMatrixGraph.h"
#include "assert.h"
#include "iostream"

CMatrixGraph::CMatrixGraph(int n): vertex_n(n), matrix(n){

    for (vector<bool>& i : matrix){
        i.assign(vertex_n, false);
    }

}

CMatrixGraph::CMatrixGraph(const IGraph* my_graph) : vertex_n(my_graph->VerticesCount()), matrix(my_graph->VerticesCount()){
    assert(my_graph != NULL);

    for (vector<bool>& i : matrix){
        i.assign(vertex_n, false);
    }

    for (int i = 0; i < vertex_n; i++){
        vector<int> buffer;

        buffer = my_graph->GetNextVertices(i);

        for (int j: buffer){
            AddEdge(i, j);
        }
    }

}


// Добавление ребра от from к to.
void CMatrixGraph::AddEdge(int from, int to){
    assert(from >= 0);
    assert(to >= 0);

    matrix[from][to] = true;

    return;

}

int CMatrixGraph::VerticesCount() const{
    return vertex_n;

}

vector<int> CMatrixGraph::GetNextVertices(int vertex) const{
    assert(vertex >= 0);

    vector<int> next;

    for (int i = 0; i < vertex_n; ++i){
        if (matrix[vertex][i] == true){
            next.push_back(i);
        }
    }
    return next;

}
vector<int> CMatrixGraph::GetPrevVertices(int vertex) const{
    assert(vertex >= 0);

    vector<int> next;

    for (int i = 0; i < vertex_n; ++i){
        if (matrix[i][vertex] == true){
            next.push_back(i);
        }
    }
    return next;

}