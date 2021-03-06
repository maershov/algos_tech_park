#pragma once

#ifndef TP3_1_CMATRIXGRAPH_H
#define TP3_1_CMATRIXGRAPH_H

#include "IGraph.h"

using namespace std;




class CMatrixGraph : public IGraph{
public:
    CMatrixGraph(int n);
    CMatrixGraph(const IGraph* my_graph);


    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override ;

    virtual int VerticesCount() const  override ;

    virtual vector<int> GetNextVertices(int vertex) const override ;
    virtual vector<int> GetPrevVertices(int vertex) const override ;

private:
    int vertex_n;
    vector<vector<bool> > matrix;


};



#endif //TP3_1_CMATRIXGRAPH_H
