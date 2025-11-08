#include "Graph.h"
#include "DataLoader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Calculates the weight of an edge for two vertices
float Graph::weightCalculator(Node* v1, Node* v2){

        float weight = 0;


        if (v1 -> name != "Unknown" && v2 -> name != "Unknown"){
            if (v1 -> name == v2 -> name){
                weight +=1;
            }
        }

        if (v1->metacritic != 0 && v2->metacritic != 0){
            if (abs(v1->metacritic - v2->metacritic) <= 10){
                weight += 1;
            }
        }


        if (v1->released != "Unknown" && v2->released != "Unknown"){
            if (v1->released == v2->released){
                weight += 1;
            }
        }


        if (v1->website != "Unknown" && v2->website != "Unknown"){
            if (v1->website == v2->website){
                weight += 1;
            }
        }

        if (v1->rating != 0 && v2->rating != 0){
            if (abs(v1->rating - v2->rating) <= 10){
                weight += 1;
            }
        }


        if (v1->esrb_rating != "Unknown" && v2->esrb_rating != "Unknown"){
            if (v1->esrb_rating == v2->esrb_rating){
                weight += 1;
            }
        }


        if (!v1->platforms.empty() && !v2->platforms.empty()){
            int commonPlatforms = 0;
            for (const auto& platform1 : v1->platforms) {
                for (const auto& platform2 : v2->platforms) {
                    if (platform1 == platform2) {
                        commonPlatforms++;
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
                        commonDevelopers++;
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
            weight += commonGenres;
        }


        if (!v1->publishers.empty() || !v2->publishers.empty()){
            int commonPublishers = 0;
            for (const auto& pub1 : v1->publishers) {
                for (const auto& pub2 : v2->publishers) {
                    if (pub1 == pub2) {
                        commonPublishers++;
                        break;
                    }
                }
            }
            weight += commonPublishers;
        }

        return weight;

}

// Insert all vertexes into the matrix
// Takes in the data_map as an argument
void Graph::insertVertexes(map<string, Node*> &vertexMap) {

    // Loop to add weight to each of the vertices
    for (auto v1 = vertexMap.begin(); v1 != vertexMap.end(); v1++){

        for (auto v2 = vertexMap.begin(); v2 != vertexMap.end(); v2++){

            if (v1 == v2){

                graphMatrix[v1->first][v2->first] = 0;
            }

            // Call function to calculate the weight
            graphMatrix[v1->first][v2->first] = weightCalculator(v1->second, v2->second);
        }


    }
}
