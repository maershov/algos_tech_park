//
// Created by aam on 2019-05-17.
//

#include "CArcGraph.h"
#include "assert.h"
#include "iostream"


CArcGraph::CArcGraph(int n):vertex_n(n), pairs(n){


}
CArcGraph::CArcGraph(const IGraph* my_graph):vertex_n(my_graph->VerticesCount()) {

    assert(my_graph != NULL);

    pairs.reserve(vertex_n);
    for(int i = 0; i < vertex_n; ++i){
        vector<int> buffer;

        buffer = my_graph->GetNextVertices(i);

        for (int j : buffer){

            AddEdge(i, j);
        }
    }
//    for (pair<int, int>& i : pairs){
//        cout << i.first<< 'h' << i.second;
//    }

}


// Добавление ребра от from к to.
void CArcGraph::AddEdge(int from, int to){
    assert(from >= 0);
    assert(to >= 0);

    for (int i = 0; i < vertex_n; ++i){
        if ((pairs[i].first == from) && (pairs[i].second == to)){
           // cout << "heyyo";
            return;
        }
    }
   // cout << from << to;

    pairs.push_back({from, to});

    return;
}

int CArcGraph::VerticesCount() const{
    return vertex_n;

}

vector<int> CArcGraph::GetNextVertices(int vertex) const{
    assert(vertex >= 0);

    vector<int> buffer;

    for (int i = 0; i < vertex_n; ++i){
        if (pairs[i].first == vertex){
            buffer.push_back(pairs[i].second);
        }

    }
    return buffer;

}

vector<int> CArcGraph::GetPrevVertices(int vertex) const{
    assert(vertex >= 0);

    vector<int> buffer;

    for (int i = 0; i < vertex_n; ++i){
        if (pairs[i].second == vertex){
            buffer.push_back(pairs[i].first);
        }

    }
    return buffer;

}