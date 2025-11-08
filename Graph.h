#pragma once
#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include "DataLoader.h"

using namespace std;

class Graph {
public:
    map <string, map<string, float>> graphMatrix;

    float weightCalculator(Node::Node* v1, Node::Node* v2);

    void insertVertexes(map<string, Node*> &vertexMap);
};
