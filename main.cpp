#include <iostream>
#include <fstream>
#include "Graph.hpp"



int main() {
    std::cout << "Enter the file to read data: ";
    std::string input;
    getline(std::cin, input);

    Graph graph(input);
    graph.formAdjacencyList();
    std::vector < Graph::Node *> topologicalNodes = graph.topSort();

    std::vector <Graph::Node *> pathNodes = graph.optimalPath(topologicalNodes);
    int profit = graph.getProfit(pathNodes);

    std::ofstream outfile;
    outfile.open("out"+input);
    outfile << "There are " << graph.clientCount()/3 << " clients in this file\n\n";
    outfile << "Optimal revenue earned is " << profit << "\n";
    outfile << "Clients contributing to this optimal revenue: ";
    std::cout<< "There are " << graph.clientCount()/3 << " clients in this file\n\n";
    std::cout << "Optimal revenue earned is " << profit << "\n";
    std::cout << "Clients contributing to this optimal revenue: ";
    int pathSize = pathNodes.size();
    for (int i = 0; i < pathNodes.size()-1; i++){
        outfile << pathNodes[i]->initIndex + 1 << ", ";
        std::cout<< pathNodes[i]->initIndex + 1 << ", ";
        
    }
    outfile << pathNodes[pathSize-1]->initIndex +1 << "\n";
    std::cout << pathNodes[pathSize-1]->initIndex +1<< "\n";
    outfile.close();

    return 0;
}