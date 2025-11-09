#include "DataLoader.h"
#include "Graph.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace std;

Node* performGameSearch(const string &query, Graph &graph) {
    cout << "Searching for: " << query << endl;
    Node* result = graph.gameSearch(query);   // call your real search function
    if (!result) {
        cout << "No match found for: " << query << endl;
    }
    return result;
}

int main() {
    DataLoader dataLoader;
    Graph gameGraph;
    gameGraph.insertVertexes(dataLoader.data_map);
    Node* found = nullptr;

    //referenced from SFML Documentation for V2.5.1
    sf::RenderWindow window(sf::VideoMode(800, 600), "Video Game Recommendation System");
    //Using fonts from https://www.1001fonts.com/video-game-fonts.html
    //Using Astroz Regular from User:https://www.1001fonts.com/users/Gravitype/ for Title
    sf::Font font;
    if (!font.loadFromFile("../fonts/Astroz_Trial.ttf"))
    {
        cout << "Failed to load font" << endl;
    }
    sf::Font font_2;
    if (!font_2.loadFromFile("../fonts/Vipnagorgialla Rg.otf")){
        cout << "Failed to load font" << endl;
    }
    //loading text
    sf::Text text;
    text.setFont(font);
    text.setString("VRS");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, 0);
    text.setPosition(window.getSize().x / 2.0f, 0);
    //Search
    sf::RectangleShape search_bar(sf::Vector2f(300.f, 50.f));
    search_bar.setFillColor(sf::Color::White);
    search_bar.setOutlineThickness(2.f);
    search_bar.setOutlineColor(sf::Color::Black);
    search_bar.setPosition(80.f, 80.f);
    //Search button
    sf::RectangleShape search_button(sf::Vector2f(100.f, 48.f));
    search_button.setFillColor(sf::Color(200,200,200));
    search_button.setOutlineThickness(2.f);
    search_button.setOutlineColor(sf::Color::Black);
    search_button.setPosition(search_bar.getPosition().x + search_bar.getSize().x + 10.f, search_bar.getPosition().y);
    sf::Text button_label("Search", font, 20);
    button_label.setFillColor(sf::Color::Black);
    button_label.setPosition(search_button.getPosition().x + 12.f, search_button.getPosition().y + 8.f);
    //Search text
    string input_string;
    sf::Text input_text("", font_2, 20);
    input_text.setFillColor(sf::Color::Black);
    input_text.setPosition(search_bar.getPosition().x + 8.f, search_bar.getPosition().y + 8.f);
    //The actual button
    sf::RectangleShape press(sf::Vector2f(2.f, 32.f));
    press.setFillColor(sf::Color::Black);
    sf::Clock pressClock;
    // 0 = none, 1 = search_bar
    int focused = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mp(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                if (search_bar.getGlobalBounds().contains(mp)) {
                    focused = 1;
                } else {
                    focused = 0;
                }
                if (search_button.getGlobalBounds().contains(mp)) {
                    found = performGameSearch(input_string, gameGraph);
                }
            }

            if (event.type == sf::Event::TextEntered) {
                unsigned int unicode = event.text.unicode;
                if (focused == 1) {
                    if (unicode == 8) { // backspace
                        if (!input_string.empty()) input_string.pop_back();
                    } else if (unicode >= 32) { // printable
                        input_string += static_cast<char>(unicode);
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    if (focused == 1) {
                        found = performGameSearch(input_string, gameGraph);
                    }
                }
            }
        }

        input_text.setString(input_string);

        float pressX;
        if (focused == 1) {
            pressX = input_text.getPosition().x + input_text.getLocalBounds().width + 2.f;
            press.setPosition(pressX, input_text.getPosition().y + 2.f);
        }

        window.clear(sf::Color(30,30,30));
        window.draw(text);
        window.draw(search_bar);
        window.draw(search_button);
        window.draw(button_label);
        window.draw(input_text);
        if (focused != 0) {
            float t = pressClock.getElapsedTime().asSeconds();
            if (fmod(t, 1.0f) < 0.5f) window.draw(press);
        } else {
            pressClock.restart();
        }
        window.display();
    }
    return 0;
}
