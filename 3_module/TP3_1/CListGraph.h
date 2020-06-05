#pragma once

#ifndef TP3_1_CLISTGRAPH_H
#define TP3_1_CLISTGRAPH_H

#include "IGraph.h"

using namespace std;

#include "list"


class CListGraph : public IGraph{
public:
    CListGraph(int n);
    CListGraph(const IGraph* my_graph);


    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override ;

    virtual int VerticesCount() const  override ;

    virtual vector<int> GetNextVertices(int vertex) const override ;
    virtual vector<int> GetPrevVertices(int vertex) const override ;

private:
    int vertex_n;
    vector<list<int> > lists;


};


#endif //TP3_1_CLISTGRAPH_H
