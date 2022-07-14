#include <iostream>
#include <set>
#include <sstream>


using namespace std;
class Node {

 private:

  set<int> adjacentNodeIDs;
	bool visited = false;

 public:

  void addEdge(int adjacentNodeID) {
    adjacentNodeIDs.insert(adjacentNodeID);
  }
	void visit(){
		visited = true;
	}
	bool isVisited() {
		return visited;
	}
	void unVisit(){
		visited = false;
	}

	set<int> adjacentNodes() {
		return adjacentNodeIDs;
	}

	string toString() {
		stringstream out;
		bool first = true;
		for (auto& nodeID : adjacentNodeIDs) {
			if (!first) {
        out << ",";
				}
    	first = false;
			out << "R" << nodeID;
			}
		return out.str();
	}

};