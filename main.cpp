#include "DataLoader.h"
#include "Graph.h"
#include <iomanip>
using namespace std;

int main() {
    DataLoader dataLoader;
    Graph gameGraph;
    gameGraph.insertVertexes(dataLoader.data_map);

    return 0;
 }