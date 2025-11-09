#include "DataLoader.h"
#include "Graph.h"
#include <iomanip>

#include "BPlusTree.h"
using namespace std;
#include <SFML/Graphics.hpp>

int main() {
    DataLoader dataLoader;
    map<string, Node*> data_map = dataLoader.data_map;
    Graph gameGraph;
    BPlusTree gameTree;

    vector<pair<string, float>> temp = gameTree.similaritySearch("Red Entity", data_map);
    for (auto pair : temp) {
        cout << pair.first << " " << pair.second << endl;
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Video Game Recommendation System");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear();
        window.display();
    }
    return 0;
 }