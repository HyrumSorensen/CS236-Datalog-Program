#include <iostream>
#include <sstream>
#include <map>
#include <stack>


using namespace std;

class Graph {

 private:

  map<int,Node> nodes;
	stack<Node> sortingStack;
	stack<Node> sortedStack;
	

 public:

  Graph(int size) {
    for (int nodeID = 0; nodeID < size; nodeID++)
      nodes[nodeID] = Node();
  }

  void addEdge(int fromNodeID, int toNodeID) {
    nodes[fromNodeID].addEdge(toNodeID);
  }
	void DFSForest(){
		for (unsigned int i = 0; i < nodes.size(); i++){
			if (!nodes[i].isVisited()){
			nodes[i].visit();
			DFSForest(nodes[i]);
			sortedStack.push(nodes[i]);
			}
		}	
		for (unsigned int i = 0; i < nodes.size(); i++){
			nodes[i].unvisit();
			}
	}
	
	void DFSForest(Node n){
		for (auto& adjN: n.adjacentNodes()) {
			if (!nodes[adjN].isVisited()) {
				nodes[adjN].visit();
				DFSForest(nodes[adjN]);
				sortedStack.push(nodes[adjN]);
			}
		}
	}
	string toString() {
			stringstream out;
		  for (auto& pair: nodes) {
      int nodeID = pair.first;
      Node node = pair.second;
			out << "R" << nodeID << ":" << node.toString() << endl;
    }
		return out.str();
	}

};