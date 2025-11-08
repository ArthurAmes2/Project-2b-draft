#pragma once
#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <vector>

using namespace std;

// Prevents errors by saying node exists but will be defined elsewhere
struct Node;

class Graph {
public:
    map <string, map<string, float>> graphMatrix;

    float weightCalculator(Node* v1, Node* v2);

    void insertVertex(map<string, Node*> &vertexMap);

};

