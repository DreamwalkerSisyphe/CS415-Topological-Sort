//
// Created by Nina Potts on 10/11/19.
//

#ifndef PROJ2_GRAPH_HPP
#define PROJ2_GRAPH_HPP

#include <vector>
#include <string>
#include <fstream>

class Graph {
public:
    explicit Graph(std::string);
    
    typedef struct Neighbor
    {
        int index = 0; //Index of the related node
        Neighbor *next = nullptr;
    };
    
    typedef struct Node
    {
        int start = 0;
        int end = 0;
        int weight = 0;
        Neighbor *next = nullptr;
        bool isStartNode = true;
    };

    Node * getNode();
    void formAdjacencyList();
    vector < Node * > topSort();
    int &clientCount();
    int &optimalRevenue();
    ~Graph();

private:
    std::vector < Node * > *nodeVector;
    std::vector < Node * > *startNodes;
    std::vector < Node * > *endNodes;
    std::string inputFileName;
    std::ifstream inputStream;
    bool _eof;
    int client_count, optimal_revenue;
    std::vector<int> contributingClients;
    std::vector<Node *> allNodes;
    void visit(int, vector<bool> &, vector<Graph::Node *> &);
};


#endif //PROJ2_GRAPH_HPP
