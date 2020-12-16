#ifndef GRAPHWITHEDGES_H
#define GRAPHWITHEDGES_H
#include <queue>
#include <ctime>
#include <unordered_map>
#include "eqclass.h"

using namespace std;

struct Edge{
    int ori;
    int dest;
    int val;
};

bool operator < (const Edge& n1, const Edge& n2) {
    return (n1.val < n2.val);
}

bool operator <=(const Edge& n1, const Edge& n2) {
    return (n1.val <= n2.val);
}

bool operator >(const Edge& n1, const Edge& n2) {
    return (n1.val > n2.val);
}

bool operator >=(const Edge& n1, const Edge& n2) {
    return (n1.val >= n2.val);
}

bool operator ==(const Edge& n1, const Edge& n2) {
    return (n1.val == n2.val);
}
class GraphWithEdges
{
public:

    //Constructors

    //Generate a non directed graph
    GraphWithEdges() {
        this->_directed = false; //Default
        this->_graph = unordered_map<int, unordered_map<int, int>>();
        this->_edges = priority_queue<Edge, vector<Edge>, greater<Edge>>();
    }

    /*
    Generates a random Graph
    p is the probability of two nodes being conected. 
    1 = fully conected. 0 = isolated nodes
    maxValue is the max value of a edge
    */
    GraphWithEdges(float p, int maxValue, int size) {
        float probGen;
        srand(time(NULL));
        this->_graph.emplace(0, unordered_map<int, int>());
        this->_directed = false;
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if(i == 0)
			        this->_graph.emplace(j, unordered_map<int, int>());
                probGen = (rand() % 10) / 10.00;
                if (probGen <= p) {
                    int value = (rand() % maxValue) +1;
                    this->addEdge(i, j, value);
                }
            }
        }
    }
    GraphWithEdges(float p, int maxValue, int size, bool directed) {
        int j;
        float probGen;
        srand(time(NULL));
        this->_graph.emplace(0, unordered_map<int, int>());
        for (int i = 0; i < size; i++) {
            if(this->_directed)
                j = 0;
            else
                j = i;
            while (j < size) {
                this->_graph.emplace(j, unordered_map<int, int>());
                probGen = (rand() % 10)/10.00;
                if (probGen <= p) {
                    int value = rand() % maxValue;
                    this->addEdge(i, j, value);
                }
                j++;
            }
        }
    }

    //If d is true, generate a directed graph, else generate a non directed graph
    GraphWithEdges(bool d) {
        this->_directed = d;
        this->_graph = unordered_map<int, unordered_map<int, int>>();
        this->_edges = priority_queue<Edge, vector<Edge>, greater<Edge>>();
    }

    //Generates a undirected graph with size being the number of vertex (without edges)
    GraphWithEdges(int size) {
        this->_directed = false;
        this->_graph = unordered_map<int, unordered_map<int, int>>();
        this->_edges = priority_queue<Edge, vector<Edge>, greater<Edge>>();
        for (int i = 0; i < size; i++) {
            this->_graph.emplace(i, unordered_map<int, int>());
        }
    }
    //Generates a directed(d == true) or undirected graph with size being the number of vertex (without edges)
    GraphWithEdges(bool d, int size) {
        this->_directed = d;
        this->_graph = unordered_map<int, unordered_map<int, int>>();
        this->_edges = priority_queue<Edge, vector<Edge>, greater<Edge>>();
        for (int i = 0; i < size; i++) {
            this->_graph.emplace(i, unordered_map<int, int>());
        }
    }

    //Destructor
    ~GraphWithEdges() {

    }

    //Mutators

    /*
    Mutates a graph that already exist
    p is the probability of two nodes being conected. 
    1 = fully conected. 0 = isolated nodes
    maxValue is the max value of a edge
    */
    void CreateRandomGraph(float p, int maxValue, int size){ //A vertex can have an edge with himself
        float probGen;
        srand(time(NULL));
        float f = time(NULL);
        cout << f << endl;
        int j;
        this->_graph.emplace(0, unordered_map<int, int>());
        for (int i = 0; i < size; i++) {
            if(this->_directed)
                j = 0;
            else
                j = i;
            while (j < size) {
                this->_graph.emplace(j, unordered_map<int, int>());
                probGen = (rand() % 10)/10.00;
                if (probGen <= p) {
                    int value = rand() % maxValue;
                    this->addEdge(i, j, value);
                }
                j++;
            }
        }
    }

    //Adds a edge between two vertex
    void addEdge(int ori, int dest, int val) {
        Edge e1;
        e1.dest = dest;
        e1.ori = ori;
        e1.val = val;
        _edges.push(e1);
        _graph.at(ori).insert({dest, val});
        if (!this->_directed) {
            Edge e2;
            e2.ori = dest;
            e2.dest = ori;
            e2.val = val;
            _edges.push(e2);
            _graph.at(dest).insert({ori, val});
        }
    }

    bool _directed;

    unordered_map<int, unordered_map<int, int>> _graph;  //(origin (destiny, cost))

    //We keep the edges sorted so we have not to do before an algorimth
    priority_queue<Edge, vector<Edge>, greater<Edge>> _edges; //For kruskal algorithm 
};

#endif // GRAPHWITHEDGES_H
