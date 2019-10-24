//
// Created by Nina Potts on 10/11/19.
//

#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>


using namespace std;

Graph::Graph(std::string name): inputFileName{std::move(name)}
{
    inputStream.open(inputFileName);
    _eof = false;
    client_count = 0;
    optimal_revenue = 0;
}

Graph::Node * Graph::getNode() {
    char c;
    Node *node = new Node;
    if( ! inputStream.is_open()) {
        std::cout << "Graph::getNode() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating." << endl;
        exit(2);
    }

    for(int i = 0; i < 3; i ++){
        inputStream.get(c);
        if(isdigit(c)){

                inputStream.putback(c);
                int num;
                inputStream >> num;
                if(i == 0)
                    node->start = num;
                else if(i == 1)
                    node->end = num;
                else
                    node->weight = num;


                if( inputStream.eof() ){
                    //if there is no more input to read from the file
                    _eof = true;
                    //cout << "Reached eof" << endl;
                    client_count += 1;
                    return node;
                }
                client_count += 1;
            }
         else{
            
            while( !isdigit(c)) {
                //to pass up all of the whitespace
                
                inputStream.get(c);
            }
            inputStream.putback(c);
            i= i-1;
        }


    }


    return node;

}

Graph::~Graph() {

}

void Graph::formAdjacencyList() {

    if(nodeVector == nullptr)
        nodeVector = new std::vector<Node *>;
    if(startNodes == nullptr)
        startNodes = new std::vector<Node *>;
    if(endNodes == nullptr)
        endNodes = new std::vector <Node *>;
    //nodeVector->push_back(start);
    int i = 0;
    while(!_eof){
        //this is where I would put the nodes into a vector
        Node *node = getNode();
        node->initIndex = i;
        nodeVector->push_back(node);
        i++;
    }

    //nodeVector->push_back(end);

    //making the adjacency list

    int nodeVectorSize= nodeVector->size() ;


    for(int i = 0; i < nodeVectorSize; i ++){
        //now that I have all of the nodes read from the input file and put into a vector I
        //can start to connect the nodes

        for(int j = 0; j < nodeVectorSize; j++){
            if(nodeVector->at(i)->end <= nodeVector->at(j)->start){
                nodeVector->at(j)->isStartNode = false;
                Neighbor *nnode = new Neighbor;
                nnode->index = j;
                nnode->next = nodeVector->at(i)->next;
                nodeVector->at(i)->next = nnode;

            }
        }
    }

    int endIndex = nodeVectorSize - 1;
  
    /*for(int i = 0; i <  nodeVectorSize ; i ++){

        if(nodeVector->at(i)->isStartNode){
            //this is a starting node
            cout << "we're here" << endl;
            startNodes->push_back(nodeVector->at(i));
            cout << "we're here too" << endl;
        }

        else if(nodeVector->at(i)->next == nullptr){
            //this is an ending node
            endNodes->push_back(nodeVector->at(i));
        }
    }*/

//    for(int i = 0; i < nodeVectorSize; i ++){
//        std::cout << nodeVector->at(i)->start  << " " << nodeVector->at(i)->end << " ";
//        std::cout << nodeVector->at(i)->weight;
//        if(nodeVector->at(i)->next != nullptr)
//        {
//            std::cout << " Next: " << nodeVector->at(nodeVector->at(i)->next->index)->start;
//            std::cout<< " " << nodeVector->at(nodeVector->at(i)->next->index)->end << " "<< nodeVector->at(nodeVector->at(i)->next->index)->weight << "\n";
//        }
//        else{
//            std::cout << "\n";
//        }
//    }


}

vector <Graph::Node *> Graph::topSort(){
    vector<Graph::Node *> sortedNodes;
    vector<bool> marks;
    marks.assign(Graph::nodeVector->size(), false);
    //Keep visiting till all nodes have been marked
    while (std::find(marks.begin(), marks.end(), false) != marks.end())
    {
        for (int i = 0; i < Graph::nodeVector->size(); i++){
            if(marks[i] == false)
                visit(i, marks, sortedNodes);
        }
    }
    return sortedNodes;
}

void Graph::visit(int nodePos, std::vector<bool> & marks, std::vector<Graph::Node *> & sortedNodes){
    if(marks[nodePos])
        return; //Node is already visited so exit
    if(nodeVector->at(nodePos)->next != nullptr){
        Neighbor *nextNeighbor; 
        nextNeighbor = nodeVector->at(nodePos)->next;
        while (nextNeighbor != nullptr){
            visit(nextNeighbor->index, marks, sortedNodes);
            nextNeighbor = nextNeighbor->next;
        }
    }
    marks[nodePos] = true; //Mark node as visited
    sortedNodes.insert(sortedNodes.begin(), nodeVector->at(nodePos)); //Add node to the sorted list
}


vector<Graph::Node *> Graph::optimalPath(vector<Graph::Node *> nodes){
    vector<Graph::Node*> opt;
    for(int i = 0; i < nodes.size(); i++){
        if(find(opt.begin(), opt.end(), nodes[i]) != opt.end())
            continue;
        vector<Graph::Node *> path = pathFinder(nodes[i]);
        if(opt.empty() || (getProfit(path) > getProfit(opt)))
            opt = path;
    }
    return opt;
}

vector<Graph::Node *> Graph::pathFinder(Graph::Node * n){
    vector<Graph::Node *> optPath;
    if(n->next == nullptr) {
        optPath.insert(optPath.begin(), n);
        return optPath;
    }
    Neighbor * nextN = n->next;
    vector<Graph::Node *> newPath;
    while(nextN != nullptr) {
        newPath = pathFinder(Graph::nodeVector->at(nextN->index));
        if (optPath.empty() || (getProfit(newPath) > getProfit(optPath)))
            optPath = newPath;
        nextN = nextN->next;

    }
    optPath.insert(optPath.begin(), n);
    return optPath;
}

int Graph::getProfit(vector<Graph::Node *> nodes){
    int profit = 0;
    for(int i = 0; i < nodes.size(); i++)
        profit += nodes[i]->weight;
    return profit;

}


int &Graph::clientCount() {
    return client_count;
}

int &Graph::optimalRevenue() {
    return optimal_revenue;
}
