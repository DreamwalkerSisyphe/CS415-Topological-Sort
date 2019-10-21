#include <iostream>
#include <fstream>
#include "Graph.hpp"



int main(int argc, char *argv[]) {
//    std::cin >> "Enter the file to read data: ";

    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);    // open for reading
    if( ! inputStream.is_open()) {
        std::cout << "Unable to open " << argv[1] << ". Terminating...";
        exit(2);
    }
    inputStream.open(argv[2], std::ios::in);
    if( ! inputStream.is_open()) {
        std::cout << "Unable to open " << argv[2] << ". Terminating...";
        exit(3);
    }

    Graph graph(argv[1]);
    graph.formAdjacencyList();

//    std::cout << "There are " << graph.clientCount() << " clients in this file\n\n";
//    std::cout << "Optimal revenue earned is " << graph.optimalRevenue() << "\n";
//    std::cout << "Clients contributing to this optimal revenue: ";



    return 0;
}