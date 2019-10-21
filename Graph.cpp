//
// Created by Nina Potts on 10/11/19.
//

#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <utility>


using namespace std;

Graph::Graph(std::string name): inputFileName{std::move(name)}
{
    inputStream.open(inputFileName, std::ios::in);
    _eof = false;
    client_count = 0;
    optimal_revenue = 0;

}

Graph::Node * Graph::getNode() {
    char c;
    Node *node = new Node;

    if( ! inputStream.is_open()) {
        std::cout << "Graph::getNode() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
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
                    client_count += 1;
                    return node;
                }
                client_count += 1;
            }
         else{
            while( !isdigit(c) ) {
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

    //nodeVector->push_back(start);

    while(!_eof){
        //this is where I would put the nodes into a vector
        Node *node = getNode();
        nodeVector->push_back(node);
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
                if(nodeVector->at(i)->next != nullptr){
                    Neighbor *nextNeighbor; 
                    nextNeighbor = nodeVector->at(i)->next;
                    while (nextNeighbor != nullptr)
                        nextNeighbor = nextNeighbor->next;
                    nextNeighbor->next = nnode;
                }
             

            }
        }
    }

    int endIndex = nodeVectorSize - 1;

    for(int i = 0; i < nodeVector->size(); i ++){

        if(nodeVector->at(i)->isStartNode){
            //this is a starting node
            startNodes->push_back(nodeVector->at(i));
        }

        else if(nodeVector->at(i)->next == nullptr){
            //this is an ending node
            endNodes->push_back(nodeVector->at(i));
        }

    }

    for(int i = 0; i < nodeVectorSize; i ++){
        std::cout << nodeVector->at(i)->start  << " " << nodeVector->at(i)->end << " ";
        std::cout << nodeVector->at(i)->weight;
        if(nodeVector->at(i)->next != nullptr)
        {
            std::cout << " Next: " << nodeVector->at(nodeVector->at(i)->next->index)->start;
            std::cout<< " " << nodeVector->at(nodeVector->at(i)->next->index)->end << " "<< nodeVector->at(nodeVector->at(i)->next->index)->weight << "\n";
        }
        else{
            std::cout << "\n";
        }
    }



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

void Graph::visit(int nodePos, vector<bool> & marks, vector<Graph::Node *> & sortedNodes){
    if(marks[nodePos] == true)
        return;
    if(nodeVector->at(nodePos)->next != nullptr){
        Neighbor *nextNeighbor; 
        nextNeighbor = nodeVector->at(nodePos)->next;
        while (nextNeighbor != nullptr){
            visit(nextNeighbor->index, marks, sortedNodes);
            nextNeighbor = nextNeighbor->next;
        }
    }
    marks[nodePos] = true;
    sortedNodes.insert(sortedNodes.begin(), nodeVector->at(nodePos));
}

int &Graph::clientCount() {
    return client_count;
}

int &Graph::optimalRevenue() {
    return optimal_revenue;
}
