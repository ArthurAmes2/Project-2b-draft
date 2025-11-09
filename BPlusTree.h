#pragma once
#include <vector>
#include "DataLoader.h"
using namespace std;

struct TreeNode {
  bool isLeaf = false;
  vector<Node*> keys;
  vector<TreeNode*> children;
  TreeNode* next = nullptr;

  TreeNode(bool isLeaf);
};

//B+ tree implementation, using static value of 50 for degree
struct BPlusTree {
  TreeNode* root = nullptr;

  float similarity(float a, float b, float maxDiff); //Helper for weightCalculator
  float weightCalculator(Node* v1, Node* v2); //Helper for similaritySearch

  vector<pair<string, float>> similaritySearch (string name, map<string, Node*> &vertexMap);

  Node* gameSearch (string name, map<string, Node*> &vertexMap);

  void splitChild (TreeNode* parent, int index, TreeNode* child);

  void insertNonFull (TreeNode* parent, Node* key);

  void insert (Node* key);

  //Recursive helper function to clear memory usage of TreeNodes
  void destructorHelper (TreeNode* node);

  ~BPlusTree();

};