#pragma once

#ifndef TP3_1_IGRAPH_H
#define TP3_1_IGRAPH_H

using namespace std;


#include "vector"


class IGraph {
public:

    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual vector<int> GetNextVertices(int vertex) const = 0;
    virtual vector<int> GetPrevVertices(int vertex) const = 0;
};


#endif //TP3_1_IGRAPH_H
