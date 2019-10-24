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
    
    struct Neighbor
    {
        int index = 0; //Index of the related node
        Neighbor *next = nullptr;
    };
    
    struct Node
    {
        int start = 0;
        int end = 0;
        int weight = 0;
        Neighbor *next = nullptr;
        bool isStartNode = true;
        int initIndex = NULL;
    };

    Node * getNode();
    void formAdjacencyList();
    std::vector < Node * > topSort();
    std::vector < Node * > optimalPath(std::vector< Node * >);
    std::vector < Node * > pathFinder(Node *);
    int getProfit(std::vector< Node *>);
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
    void visit(int, std::vector<bool> &, std::vector<Graph::Node *> &);
};


#endif //PROJ2_GRAPH_HPP
