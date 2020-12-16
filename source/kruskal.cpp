#include "partition.h"
#include "graphwithedges.h"
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <chrono>
#include <ctime>
using namespace std;


//Edges is sorted in non decreasing order
void kruskal(const unordered_map<int, unordered_map<int, int>> &g, const priority_queue<Edge, vector<Edge>, greater<Edge>> &edges, list<Edge> &l){
    Partition part = Partition(g.size()); //O(n)

    //Copy of original list, it may be inmutable
    priority_queue<Edge, vector<Edge>, greater<Edge>> pend = priority_queue<Edge, vector<Edge>, greater<Edge>>(edges); //O(n)
    int i = 0;
    Edge edge;
    EqClass c1 = EqClass(), c2 = EqClass();
    while (i < g.size() - 1 && !pend.empty()){  //ends when all vertex are considereed or when there's no edges left to consider
        edge = pend.top(); //O(1)
        c1 = part.find(edge.ori); //O(1)
        c2 = part.find(edge.dest);//O(1)
        if (!c1.equalParent(c2)) {//O(1)
            //we can use join because find give the roots
            part.join(*c1._parent, *c2._parent); //O(1) //c1 and c2 are temporary, but changes would need to
            l.push_back(edge);  //O(1)                  //take effect in the partition variable, so we do in the part's EqClasses 
            i++;//O(1)
        }               
        pend.pop();//O(1)
    }
}

int main(int argc, char* argv[]){
    auto start = std::chrono::system_clock::now();
    float p = atof(argv[2]); int maxValue = atoi(argv[3]); int vertexs = atoi(argv[4]);
    GraphWithEdges ge;
    if(argc > 1 && *argv[1] == 'r'){
        if(*argv[1] == 'r'){
            cout << "Probability of two edges to be conected: " << p << endl << "Max value for an edge: " << maxValue << endl << "Number of vertexs: "<< vertexs << endl << *argv << endl;
            ge = GraphWithEdges(p, maxValue, vertexs);
        }
        else{
            cout << "Usage: 'r p ' to generate a random graph (x = number of vertexs)" << endl;
            return 0;
        }
    }else{
        ge = GraphWithEdges(false, 8);
        ge.addEdge(1, 2, 9);
        ge.addEdge(1, 7, 14);
        ge.addEdge(1, 6, 14);
        ge.addEdge(2, 3, 24);
        ge.addEdge(3, 6, 18);
        ge.addEdge(3, 5, 2);
        ge.addEdge(3, 4, 9);
        ge.addEdge(4, 5, 11);
        ge.addEdge(5, 6, 30);
        ge.addEdge(5, 7, 20);
        ge.addEdge(7, 6, 5);
    }
    
    list<Edge> l = list<Edge>();
    auto iniKrus = std::chrono::system_clock::now();
    kruskal(ge._graph, ge._edges, l);
    auto finKrus = std::chrono::system_clock::now();
    int costeTotal = 0;
    while (!l.empty()) {
        costeTotal += l.front().val;
        cout << "Arista (" << l.front().dest << ", " << l.front().ori 
            << ") Coste = " << l.front().val << " Coste acumulado: " << costeTotal << endl;
        
        l.pop_front();
    }
    cout << "coste total: " << costeTotal << endl;
    chrono::duration<double> elapsed_secondsKrus = finKrus - iniKrus;
    cout << "Tiempo del algoritmo: " << elapsed_secondsKrus.count() << endl;
    auto end = std::chrono::system_clock::now(); 
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "Tiempo total: " << elapsed_seconds.count() << endl;

    return 0;
}