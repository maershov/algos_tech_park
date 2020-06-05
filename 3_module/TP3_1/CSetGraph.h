#pragma once

#ifndef TP3_1_CSETGRAPH_H
#define TP3_1_CSETGRAPH_H



#include "IGraph.h"
#include "set"

using namespace std;


class CSetGraph : public IGraph{
public:
    CSetGraph(int n);
    CSetGraph(const IGraph* my_graph);


    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override ;

    virtual int VerticesCount() const  override ;

    virtual vector<int> GetNextVertices(int vertex) const override ;
    virtual vector<int> GetPrevVertices(int vertex) const override ;

private:
    int vertex_n;
    vector<set<int> > sets;


};


#endif //TP3_1_CSETGRAPH_H
