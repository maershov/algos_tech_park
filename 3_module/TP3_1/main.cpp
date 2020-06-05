#include <iostream>

#include "CMatrixGraph.h"
#include "CListGraph.h"
#include "CSetGraph.h"
#include "CArcGraph.h"

using namespace std;

void show(IGraph* graph){
    for (int i = 0; i < graph->VerticesCount(); ++i){
        vector<int> buffer = graph->GetNextVertices(i);
        cout<< i << ' ';
        for (int j : buffer){
            cout << j << ' ';
        }
        cout << endl;
    }
}

int main() {

    CListGraph graph(9);

    graph.AddEdge(0, 1);
    graph.AddEdge(1, 3);
    graph.AddEdge(2, 1);
    graph.AddEdge(2, 3);
    graph.AddEdge(2, 4);
    graph.AddEdge(3, 4);
    graph.AddEdge(4, 5);
    graph.AddEdge(5, 3);
    graph.AddEdge(5, 4);

    show(&graph);
    cout << endl;
    cout << "matr" << endl;
    CMatrixGraph matrgraph(&graph);
    show(&matrgraph);
    cout << "set" << endl;
    CSetGraph setgraph(&graph);
    show(&setgraph);
    cout << "list" << endl;
    CListGraph listgraph(&graph);
    show(&listgraph);
    cout << "arc" << endl;
    CArcGraph arcgraph(&graph);
    show(&arcgraph);




    //cout << "aa";

    return 0;
}