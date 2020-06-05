//
// Created by aam on 2019-05-17.
//

#ifndef TP3_1_CARCGRAPH_H
#define TP3_1_CARCGRAPH_H



#include "IGraph.h"

using namespace std;


class CArcGraph : public IGraph{
public:
    CArcGraph(int n);
    CArcGraph(const IGraph* my_graph);


    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override ;

    virtual int VerticesCount() const  override ;

    virtual vector<int> GetNextVertices(int vertex) const override ;
    virtual vector<int> GetPrevVertices(int vertex) const override ;

private:
    int vertex_n;
    vector<pair<int, int> > pairs;


};


#endif //TP3_1_CARCGRAPH_H
