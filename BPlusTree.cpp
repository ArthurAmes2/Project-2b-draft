#include "BPlusTree.h"

TreeNode::TreeNode(bool isLeaf) {
  this->isLeaf = isLeaf;
}

float BPlusTree::similarity(float a, float b, float maxDiff) {
  float diff = abs(a - b);
  float sim = 1.0f - (diff / maxDiff);
  if (sim < 0) sim = 0;
  return sim*2.35;
}

float BPlusTree::weightCalculator(Node *v1, Node *v2) {
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

vector<pair<string, float>> BPlusTree::similaritySearch(string name, map<string, Node *> &vertexMap) {
    vector<pair<string, float>> result;
    if (vertexMap.find(name) == vertexMap.end()) {
        return result;
    }

    //Set similarity score for every item
    for (auto item : vertexMap) {
        Node* temp = item.second;
    temp->similarity_score = weightCalculator(vertexMap[name], temp);
    }

    //Create B+ tree
    for (auto item : vertexMap) {
        insert(item.second);
    }

    TreeNode* node = root;
    while (!node->isLeaf) {
        node = node->children[0];
    }

    while (node && result.size() < 20) {
        for (auto item : node->keys) {
            if (item->name == name) {continue;}
            result.push_back(make_pair<string, float>(std::move(item->name), item->similarity_score));
            if (result.size() == 20) {break;}
        }
        node = node->next;
    }
    return result;
}

Node * BPlusTree::gameSearch(string name, map<string, Node *> &vertexMap) {
    if (vertexMap.find(name) == vertexMap.end()) {
        return nullptr;
    }
    return vertexMap[name];
}

void BPlusTree::splitChild(TreeNode *parent, int index, TreeNode *child) {
  TreeNode* newNode = new TreeNode(child->isLeaf);
  parent->children.insert(parent->children.begin() + index + 1, newNode);
  parent->keys.insert(parent->keys.begin() + index, child->keys[49]);

  newNode->keys.assign(child->keys.begin() + 50,child->keys.end());
  child->keys.resize(49);

  if (!child->isLeaf) {
    newNode->children.assign(child->children.begin() + 50, child->children.end());
    child->children.resize(50);
  }

  if (child->isLeaf) {
    newNode->next = child->next;
    child->next = newNode;
  }
}

void BPlusTree::insertNonFull(TreeNode *node, Node *key) {
  int insertIndex = 0;
  if (node->isLeaf) { //Inserting into leaf
    for (auto item : node->keys) {
      if (item->similarity_score > key->similarity_score) {
        insertIndex++;
      }
    }
    node->keys.insert(node->keys.begin() + insertIndex, key);
  } else { //Non-leaf
    insertIndex = node->keys.size() - 1;
      while (insertIndex >= 0 && key->similarity_score > node->keys[insertIndex]->similarity_score) {
          insertIndex--;
      }
    insertIndex++;
    if (node->children[insertIndex]->keys.size() == 99) {
      splitChild(node, insertIndex, node->children[insertIndex]);
      if (key->similarity_score > node->keys[insertIndex]->similarity_score) {
        insertIndex++;
      }
    }
    insertNonFull(node->children[insertIndex], key);
  }
}


void BPlusTree::insert (Node* key) {
  if (root == nullptr) { //Empty tree
    root = new TreeNode(true);
    root->keys.push_back(key);
  } else {
    if (root->keys.size() == 99) { //If TreeNode is full [2(50)-1 keys]
      TreeNode* newRoot = new TreeNode(false);
      newRoot->children.push_back(root);
      splitChild(newRoot, 0, root);
      root = newRoot;
    }
    insertNonFull(root, key);
  }
}

void BPlusTree::destructorHelper(TreeNode *node) {
    if (!node) {
        return;
    } if (!node->isLeaf) {
        for (TreeNode* child : node->children) {
            destructorHelper(child);
        }
    }
    delete node;
}

BPlusTree::~BPlusTree() {
    destructorHelper(root);
}
