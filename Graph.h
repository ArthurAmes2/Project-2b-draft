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

    float weightCalculator(Node* v1, Node* v2);

    void insertEdges(Node* node, map<string, Node*> &vertexMap);

    vector<pair<string, float>> similaritySearch (string name, map<string, Node*> &vertexMap);

    Node* gameSearch (string name, map<string, Node*> &vertexMap);
};
