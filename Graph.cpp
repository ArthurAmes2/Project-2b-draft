#include "Graph.h"
#include "DataLoader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//Helper for weightCalculator
float similarity(float a, float b, float maxDiff) {
    float diff = abs(a - b);
    float sim = 1.0f - (diff / maxDiff);
    if (sim < 0) sim = 0;
    return sim*2.35;
}


// Calculates the weight of an edge for two vertices
float Graph::weightCalculator(Node* v1, Node* v2){
    float weight = 0;


    if (v1 -> name != "Unknown" && v2 -> name != "Unknown"){
        if (v1 -> name == v2 -> name){
            weight +=1;
        }
    }

    if (v1->metacritic != 0 && v2->metacritic != 0){
        weight += similarity(v1->metacritic, v2->metacritic, 100.0f);
    }


    if (v1->released != "Unknown" && v2->released != "Unknown"){
        if (v1->released == v2->released){
            weight += 0.5f;
        }
    }

    if (v1->rating != 0 && v2->rating != 0){
            weight += similarity(v1->rating, v2->rating, 10.0f);
    }


    if (v1->esrb_rating != "Unknown" && v2->esrb_rating != "Unknown"){
        if (v1->esrb_rating == v2->esrb_rating){
            weight += 0.75;
        }
    }


    if (!v1->platforms.empty() && !v2->platforms.empty()){
        int commonPlatforms = 0;
        for (const auto& platform1 : v1->platforms) {
            for (const auto& platform2 : v2->platforms) {
                if (platform1 == platform2) {
                    commonPlatforms += 0.25f;
                    break;
                }
            }
        }
        weight += commonPlatforms;
    }

    if (!v1->developers.empty() && !v2->developers.empty()){
        int commonDevelopers = 0;
        for (const auto& dev1 : v1->developers) {
            for (const auto& dev2 : v2->developers) {
                if (dev1 == dev2) {
                    commonDevelopers += 0.9f;
                    break;
                }
            }
        }
        weight += commonDevelopers;
    }


    if (!v1->genres.empty() && !v2->genres.empty()){
        int commonGenres = 0;
        for (const auto& genre1 : v1->genres) {
            for (const auto& genre2 : v2->genres) {
                if (genre1 == genre2) {
                    commonGenres++;
                    break;
                }
            }
        }
        weight += commonGenres*3.5f;
    }


    if (!v1->publishers.empty() || !v2->publishers.empty()){
        int commonPublishers = 0;
        for (const auto& pub1 : v1->publishers) {
            for (const auto& pub2 : v2->publishers) {
                if (pub1 == pub2) {
                    commonPublishers += 0.7f;
                    break;
                }
            }
        }
        weight += commonPublishers;
    }

    return weight;
}

// Insert edges for comparison of a game
void Graph::insertEdges(Node* node, map<string, Node*> &vertexMap) {
    // Loop to add weight to each of the vertices
    for (auto v1 = vertexMap.begin(); v1 != vertexMap.end(); v1++) {
        // Call function to calculate the weight
        graphMatrix[node->name][v1->second->name] = weightCalculator(node, v1->second);
    }
    cout << "Graph creation complete" << endl;
}

//Builds graph out with edges between search query and all other games
vector<pair<string, float>> Graph::similaritySearch(string name, map<string, Node*> &vertexMap) {
    vector<pair<string, float>> result;
    if (vertexMap.find(name) == vertexMap.end()) {
        cerr << "Searched name does not exist." << endl;
        return result;
    }
    insertEdges(vertexMap[name], vertexMap);
    for (auto it = graphMatrix[name].begin(); it != graphMatrix[name].end(); it++) {
        if (it->first == name) {
            continue;
        }
        result.push_back(make_pair(it->first, it->second));
    }
    //Sort result by weight
    sort(result.begin(), result.end(), [](const pair<string, float>& a, const pair<string, float>& b) {
    return a.second > b.second;
});

    return result;
}

Node * Graph::gameSearch(string name, map<string, Node*> &vertexMap) {
    if (vertexMap.find(name) == vertexMap.end()) {
        return nullptr;
    }
    return vertexMap[name];
}
