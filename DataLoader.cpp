#include "DataLoader.h"
#include <string>

Node::Node(string name,
    int metacritic,
    string released,
    string updated,
    string website,
    float rating,
    vector<string> platforms,
    vector<string> developers,
    vector<string> genres,
    vector<string> publishers,
    string esrb_rating) {
    this->name = name;
    this->metacritic = metacritic;
    this->released = released;
    this->updated = updated;
    this->website = website;
    this->rating = rating;
    this->platforms = platforms;
    this->developers = developers;
    this->genres = genres;
    this->publishers = publishers;
    this->esrb_rating = esrb_rating;
}


vector<string> DataLoader::listSplitter(string list) {
    vector<string> result;
    while (list.find("||") != string::npos) {
        result.push_back(list.substr(0, list.find("||")));
        list = list.substr(list.find("||")+2);
    }
    return result;
}

DataLoader::DataLoader() {
    ifstream data("../video_games.csv");
    if (!data.is_open()) {
        cerr << "Error opening csv " << endl;
    }

    string line;
    //Iterate through every row in the csv, except first row (headers)
    getline(data, line);
    while (getline(data, line)) {
        istringstream iss(line);
        string cell;
        vector<string> cells;
        //Iterate through each column and pushback into cells vector
        while (getline(iss, cell, ',')) {
            cells.push_back(cell);
        }
        if (!line.empty()) {
            cells.push_back("");
        }
        //Data cleaning
        //Convert numerics and store
        int temp_metacritic = 0;
        float temp_rating = 0.0;
        if (cells[1] != "") { //metacritic
            temp_metacritic = stoi(cells[1]);
        } else {
            temp_metacritic = 0;
        }

        //Replace empty/unrated data with Unknown
        for (int i = 0; i < cells.size(); i++) {
            if (cells[i] == "" || cells[i] == "0") {
                cells[i] = "Unknown";
            }
        }

        string temp_name = cells[0];
        string temp_released = cells[2];
        string temp_updated = cells[3];
        string temp_website = cells[4];
        vector<string> temp_platforms = listSplitter(cells[6]);
        vector<string> temp_developers = listSplitter(cells[7]);
        vector<string> temp_genres = listSplitter(cells[8]);
        vector<string> temp_publishers = listSplitter(cells[9]);
        string temp_esrb_rating = cells[10];

        //After data loaded, create and store game (node) objects
        Node* new_node = new Node(temp_name,
            temp_metacritic,
            temp_released,
            temp_updated,
            temp_website,
            temp_rating,
            temp_platforms,
            temp_developers,
            temp_genres,
            temp_publishers,
            temp_esrb_rating);
        data_map.insert(pair<string, Node*>(temp_name, new_node)); //Store game objects
    }


}

DataLoader::~DataLoader() {
    for (auto it = data_map.begin(); it != data_map.end(); it++) {
        delete it->second;
    }
}