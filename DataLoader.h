#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include "Graph.h"
using namespace std;

/*
DataLoader struct is used to parse csv data file
The class uses its constructor to pass relevant params to each data structure's insertion functions
The class will only need to have one object created in main, and no other calls made
*/

struct Node {
  string name;
  int metacritic;
  string released;
  string updated;
  string website;
  float rating;
  vector<string> platforms;
  vector<string> developers;
  vector<string> genres;
  vector<string> publishers;
  string esrb_rating;

  double similarity_score; //Used only in the B+ implementation

  //Constructor for node class
  Node(string name,
    int metacritic,
    string released,
    string updated,
    string website,
    float rating,
    vector<string> platforms,
    vector<string> developers,
    vector<string> genres,
    vector<string> publishers,
    string esrb_rating);
};

struct DataLoader {
  map<string, Node*> data_map;

  vector<string> listSplitter(string list);
  DataLoader();
  ~DataLoader();
};
