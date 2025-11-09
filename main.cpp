#include "DataLoader.h"
#include "Graph.h"
#include <iomanip>
using namespace std;
#include <SFML/Graphics.hpp>

int main() {
    DataLoader dataLoader;
    map<string, Node*> data_map = dataLoader.data_map;
    Graph gameGraph;

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